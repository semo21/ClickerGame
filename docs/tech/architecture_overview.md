# Architecture Overview

## 1. 목적과 스코프
- 목적: Clicker의 런타임 구조, 흐름, 데이터/이벤트 경계 표시
- 스코프: 싱글 플레이, GameInstance Subsystem 기반, 세이브/로드/오프라인 보상/위젯 풀링
- 비스코프: 멀티플레이, 인 앱 결제시스템

## 2. 런타임 구조
- GameInstance
  - UClickerEconomySubsystem: 경제 상태/틱/오프라인 보상/세이브 트리거
  - UClickerUISubsystem: HUD/텍스트 갱신/토스트/FX/사운드
  - USaveManagerSubsystem: SaveGame 슬롯 IO
-  PlayerController: 입력 진입점(클릭/업그레이드/세이브/로드 등 버튼 핸들러)
-  Widgets: HUD, Idle/FloatingText
  
## 3. Major Sequences
### 3-1. Game Start
```
PlayerController::BeginPlay()
1. EconomySubsystem::StartWorld(UWorld*) 
  -> EconomySubsystem::RequestLoad() 
  -> 이후 [3-1. Load]항목과 동일하게 진행

2. UISubsystem::ShowHUD(UWorld*)
  -> HUD 위젯 생성 및 AddToViewport()
  -> HUD 내부 위젯 바인딩 (CurrencyText, Buttons...)
  -> UpgradeSuccessText를 기본적으로 Collapsed 설정
  -> Upgrade/Save/Load버튼 PlayerController 핸들러에 바인딩

3. EconomySubsystem::RequestLoad()
  -> 로드 이후 EconomySubsystem::TriggerOfflineReward() 호출
  -> Offline Reward 시퀀스 실행 (3-7 참조)
```
### 3-2. Click
```
PlayerController::SetupInputComponent()
1. UInputComponent::BindKey(LeftClick, PlayerController.OnClick)
  -> EconomySubsystem::OnClicked()
  -> EconomySnapshot.Currency += CPC
  -> EconomySubsystem::Broadcast()

2. UISubsystem::ShowClickEffect(FHitResult.Location)
  -> 클릭 위치에 Niagara 이펙트 스폰

3. UISubsystem::ShowFlotingText(...)
  -> Widget = UISubsystem::GetWidgetFromPool(...)
  -> Widget->SetupToast(...)
  -> Widget->PlayToast()
```
### 3-3. Upgrade
```
UISubsystem::UpgradeButton->AddDynamic(PlayerController.OnUpgradeClicked)
1. PlayerController::OnUpgradeClicked()
  -> EconomySubsystem::TryUpgrade()
  -> 성공 시 Economy 상태 업데이트 (Currency, Level, CPC, CPS)

2. if(Success): UISubsystem::ShowUpgradeSuccessText()
  -> UpgradeSuccessText Visible
  -> 일정 시간 후 타이머로 Collapsed
```
### 3-4. Save / Load
```
// Save
UISubsystem::SaveButtton->AddDynamic(PlayerController::OnSaveClicked)
1. PlayerController::OnSaveClicked()
  -> EconomySubsystem::RequestSave()
  -> SaveSubsystem::SaveProgress(FEconomySnapshot)
  -> Snapshot을 SaveGame 객체에 직렬화 후 슬롯에 저장

// Load
UISubsystem::LoadButtton->AddDynamic(PlayerController::OnLoadClicked)
1. PlayerController::OnLoadClicked() 
  -> EconomySubsystem::RequestLoad()
  -> SaveSubsystem::LoadProgress(FEconomySnapshot)
  -> 슬롯에서 SaveGame 로드 후 Snapshot 복원
  -> EconomySubsystem::ApplySnapshot(Snapshot)
```
### 3-5. Economy Changed
```
1. UISubsystem::Initialize()
  -> EconomySystem::OnEconomyChanged를 구독
  -> 콜백에서 HUD(Currency, CPS, CPC 등)을 갱신

2. EconomySubsystem::Broadcast()
  -> 내부 Snapshot 변경 후 항상 호출
  -> 다음과 같은 시점에서 사용
    - ApplySnapshot()
    - ApplyOfflineReward()
    - OnClicked()
    - OnTick1Second()
    - TryUpgrade()
```
### 3-6. Passive Income(1 Tick Idle Reward)
```
EconomySubsystem::StartWorld()
1. EconomySubsystem::StartTickTimer()
  -> WorldTimerManager.SetTimer(1.0s, EconomySubsystem::OnTick1Second, Loop)
  -> EconomySubsystem::OnTick1Second()
  -> EconomySubsystem.Currency += CPS
  -> EconomySubsystem::OnPassiveIncome.Broadcast(CPS)
  -> EconomySubsystem::Broadcast() 

2. UISubsystem::Initialize()
  -> EconomySubsystem::OnEconomyChanged.AddUniqueDynamic(UISubsystem::OnEconomyChanged)
  -> EconomySubsystem::OnPassiveIncome.AddUniqueDynamic(UISubsystem::OnPassiveIncome)

3. UISubsystem::OnEconomyChanged(FEconomySnapshot&)
  -> UISubsystem::UpdateScore()  

4. UISubsystem::OnPassiveIncome(double AmountPerSec)
  -> UISubsystem::HandlePassiveIncome(AmountPerSec)
  -> UISubsystem::ShowReward(AmountPerSec, bIsOffline=false)
```
### 3-7. Offline Reward
```
EconomySubsystem::RequestLoad()
1. SaveSubsystem::LoadProgress(FEconomySnapshot)
2. EconomySubsystem::UpdateLastOfflineReward(FEconomySnapshot)
3. EconomySubsystem::TriggerOfflineReward()
  -> EconomySubsystem::OnfflineReward.Broadcast(LastOfflineReward)
  -> UISubsystem::OnOfflineReward(Amount)
  -> HandleOfflineReward(Amount)
  -> ShowReward(Amount, bIsOffline=true)
  -> IdleRewardText 토스트를 풀에서 가져와 Toast
4. EconomySubsystem::ApplySnapshot(FEconomySnapshot)
  -> EconomySubsystem::Broadcast()
5. RequestSave()
  -> Save 시퀀스 실행
```
### 3-8. Delegate subscription
```
// Click Input
PlayerController::SetupInputComponent()
1. InputComponent::BindKey(LeftClick, Pressed, PlayerController,PlayerController::OnClick)

// UI Buttons
UISubsystem::ShowHUD()
1. UpgradeButton.OnClicked  -> PlayerController::OnUpgradeClicked
2. SaveButton.OnClicked     -> PlayerController::OnSaveClicked
3. LoadButton.OnClicked     -> PlyaerController::OnLoadClicked

// Currency Delegates
UISubsystem::Initialize()
1. EconomySubsystem::OnEconomyChanged -> UISubsystem::OnEconomyChanged
2. EconomySubsystem::OnPassiveIncome  -> UISubysystem::OnPassiveIncome
3. EconomySubsystem::OnOfflineReward  -> UISubsystem::OnOfflineReward
```

## 4. 라이프사이클(모듈별)
- **Economy Subsystem:**
  1. Initialize(의존성 확보) 
  2. StartWorld에서 로드/타이머 시작 
  3. 1s 틱에서 CPS 지급/브로드캐스트 -> Deinitialize에서 타이머 해제
- **UI Subsystem:** 
  1. Initialize() (의존성 구독 + UISettings 동기 로드)
  2. ShowHUD() (1회 AddToViewport)
  3. 이벤트 기반 갱신 (첫 1회만 GetSnapshot 호출하여 갱신)
  4. Deinitialize에서 구독/타이머 정리
- **Save Subsystem:**
  1. 표준 Subsystem Init/Deinit, 슬롯 IO 제공

## 5. 데이터 흐름 & 소유권
- FEconomySnapshot
  - **원본:** EconomySnapshot (EconomySubsystem 멤버)
  - **읽기:** GetSnapshot()으로 const ref 제공 (복사 없음)
  - **저장용 복사본:** RequestSave() 내부에서 생성 -> LastSaveTime=UtcNow 세팅 후 SaveProgress() 호출
- UClickerSaveGame
  - SaveManager가 생성/직렬화/로드, 디스크 슬롯 소유

## 6. 책임(Responsibility) & 의존성
- **Economy Subsystem** 
  - **수행:** 상태/틱/보상/세이브 트리거
  - **수행하지 않음:** 생성/버튼 바인딩
- **UI Subsystem**
  - **수행:** HUD/텍스트/토스트/FX/사운드/풀
  - **수행하지 않음:** 세이브/IO/경제 계산
- **Save Subsystem**
  - **수행:** 직/역직렬화
  - **수행하지 않음:** 게임 상태 계산

## 7. 운영 규칙
- **Widget Pool:** HUD/토스트는 초기 1회 AddToViewport 후 Visible/Collapsed 토글 사용
- **오프라인 보상:** 로드 시 1회 보상 후 즉시 저장하여 재적용 방지
- **이벤트 기반 갱신:** UI는 폴링 금지, OnEconomyChanged 구독으로 갱신

## 8. 오류 처리 & 가드 (구현 예정)
- DataAsset 로드 실패 시:
  - 핵심 DA -> 우회x, 실패 시 즉시 종료
  - 보조 DA -> 기능 우회, 코드에 경로 작성
- 잘못된 위젯 클래스/Null World: return + ensure 로그
- 세이브/로드 실패: 사용자 알림(토스트)

## 9. 성능/스레딩
- 1s Tick에서만 CPS 지급(고정), 클릭/업그레이드는 이벤트성
- UI는 이벤트 구독 기반 (불필요한 매 프레임 조회(Polling) 금지)
- 저장은 배치 (자동저장 타이머) 또는 명령형(RequestSave())로 수행

## 10. 확장 포인트 (구현 예정)
- 업그레이트 티어/코스트 곡선 커스터마이즈(데이터 드리븐)
- 사운드/FX 교체: UISettings DataAsset으로 플러그형 (*구현 완료*)
- 경제 데이터 드리븐: EconomyBalanceSettings DataAsset으로 구현
- 세이브 버전업: SaveGame에 Version 필드 추가, 로드시 버전 스위치로 구버전 마이그레이션.

## 11. 테스트 후크 (DoD 연결)
- A: Save/Load & 오프라인 보상 -- A1~A6 체크리스트
- B: UI 풀/토스트 -- Add 1회, 재사용, 애니 종료 후 Collapsed
- C: 안정성 -- Null 가드, 중복 타이머 미발생
> 상세 케이스는 '/docs/testing/test_cases.md' 참조

## 12. 용어
- CPC: Currency Per Click
- CPS: Currency Per Second
- Snapshot: 런타임 상태 구조체(FEconomySnapshot)
- SaveGame: 디스크 직렬화 오브젝트