# Architecture Overview

## 1. 목적과 스코프
- 목적: Clicker의 런타임 구조, 흐름, 데이터/이벤트 경계 표시
- 스코프: 싱글 플레이, GameInstance Subsystem 기반, 세이브/로드/오프라인 보상/위젯 풀링
- 비스코프: 멀티플레이, 인 앱 결제시스템

---

## 2. 런타임 구조
- GameInstance
  - EconomySubsystem: 경제 상태/틱/오프라인 보상/세이브 트리거
  - UISubsystem: HUD/텍스트 갱신/토스트/FX/사운드
  - SaveSubsystem: SaveGame 슬롯 IO
-  PlayerController: 입력 진입점(클릭/업그레이드/세이브/로드 등 버튼 핸들러)
-  Widgets: HUD, Idle/FloatingText
  
---

## 3. Major Sequences
### 3-1. Game Start
```
PlayerController::BeginPlay()
1. EconomySubsystem::StartWorld(UWorld*) 
  -> EconomySubsystem::RequestLoad() 
  -> 로드 후 오프라인 보상을 계산, 필요 시 TriggerOfflineReward()를 통해 1회 적용
  -> 1초 틱 타이머 시작

2. UISubsystem::ShowHUD(UWorld*)
  -> HUD 위젯 생성 후 AddToViewport()
  -> HUD 내부 위젯 바인딩 (CurrencyText, Buttons 등)
  -> UpgradeSuccessText를 기본적으로 Collapsed 설정
  -> Upgrade/Save/Load버튼 PlayerController 핸들러에 바인딩
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

3. UISubsystem::ShowFloatingText(...)
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
UISubsystem::LoadButton->AddDynamic(PlayerController::OnLoadClicked)
1. PlayerController::OnLoadClicked() 
  -> EconomySubsystem::RequestLoad()
  -> SaveSubsystem::LoadProgress(FEconomySnapshot)
  -> 슬롯에서 SaveGame 로드 후 Snapshot 복원
  -> EconomySubsystem::ApplySnapshot(Snapshot)
```
### 3-5. Economy Changed
```
1. UISubsystem::Initialize()
  -> EconomySubsystem::OnEconomyChanged를 구독
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
3. LoadButton.OnClicked     -> PlayerController::OnLoadClicked

// Currency Delegates
UISubsystem::Initialize()
1. EconomySubsystem::OnEconomyChanged -> UISubsystem::OnEconomyChanged
2. EconomySubsystem::OnPassiveIncome  -> UISubsystem::OnPassiveIncome
3. EconomySubsystem::OnOfflineReward  -> UISubsystem::OnOfflineReward
```

---

## 4. Lifecycle (In Short)
- **Economy Subsystem:**
  - GameInstance Subsystem으로, 게임 시작 시 `StartWorld()`에서 로드, 오프라인 보상, 틱 타이머를 설정
  - 1초 틱과 업그레이드, 클릭 등의 이벤트에서 Economy 상태를 변경한 후 항상 `OnEconomyChanged`를 브로드캐스트

- **UI Subsystem:** 
  - Initialize 시 Economy 이벤트를 구독 후 `ShowHUD()`에서 HUD를 1회 생성 후 AddToViewport()
  - 이후 Economy 이벤트 (`OnEconomyChanged`, `OnPassiveIncome`, `OnOfflineReward`)를 기반으로 HUD와 토스트를 갱신

- **Save Subsystem:**
  Economy의 요청에 따라 `SaveProgress` / `LoadProgress`를 수행하며 SaveGame 슬롯 IO를 담당

> 각 Subsystem의 상세 Lifecycle과 API는 `tech/api_reference.md` 참조

---

## 5. Data Flow & Ownership
- **EconomySnapshot**
  - 원본은 `EconomySubsystem`이 소유
  - UI/Save는 `GetSnapshot()` 또는 `LoadProgress()`를 통해 읽기 전용으로 사용
  - 저장 시에는 Snapshot을 복사해 SaveGame 데이터(`SaveGame`)로 직렬화

- **SaveGame**
  - 디스크에 저장되는 직렬화 객체로, SaveSubsystem 생성/저장/로드를 담당

---

## 6. Responsibility & Dependency
- **EconomySubsystem**
  - 경제 상태 계산, 1초 틱, 오프라인 보상, Save/Load 트리거 담당
  - UI 생성/위젯 바인딩, SaveGame IO는 담당 x

- **UISubsystem**
  - HUD / 텍스트 / 토스트 / FX / 사운드 / 위젯 풀링 담당
  - 경제 계산 및 SaveGame IO는 담당 x

- **SaveSubsystem**
  - SaveGame IO 담당
  - 게임 상태 계산 및 UI는 담당 x

> 각 모듈의 Public API와 의존성 목록은 `api_reference.md` 참조
---

## 7. 운영 규칙
- **Widget Pool:** HUD/토스트는 초기 1회 AddToViewport 후 Visible/Collapsed 토글 사용
- **오프라인 보상:** 로드 시 1회 보상 후 즉시 저장하여 재적용 방지
- **이벤트 기반 갱신:** UI는 폴링 금지, OnEconomyChanged 구독으로 갱신

---

## 8. 오류 처리 & 가드 (구현 예정)
- DataAsset 로드 실패 시:
  - 핵심 DA -> 우회x, 실패 시 즉시 종료
  - 보조 DA -> 기능 우회, 코드에 경로 작성
- 잘못된 위젯 클래스/Null World: return + ensure 로그
- 세이브/로드 실패: 사용자 알림(토스트)

---

## 9. 성능/스레딩
- 1s Tick에서만 CPS 지급(고정), 클릭/업그레이드는 이벤트성
- UI는 이벤트 구독 기반 (불필요한 매 프레임 조회(Polling) 금지)
- 저장은 배치 (자동저장 타이머) 또는 명령형(RequestSave())로 수행

---

## 10. 확장 포인트 (구현 예정)
- 업그레이트 티어/코스트 곡선 커스터마이즈(구현 예정)
- 사운드/FX 교체: UISettings DataAsset으로 플러그형 (*구현 완료*)
- 경제 데이터 드리븐: EconomyBalanceSettings DataAsset으로 구현하여 업그레이드/밸런스 파라미터를 이것을 기반으로 외부화(구현 예정)
- 세이브 버전업: SaveGame에 Version 필드 추가, 로드시 버전 스위치로 구버전 마이그레이션.(구현 예정)

---

## 11. 테스트 후크 (DoD 연결)
- A: Save/Load & 오프라인 보상 -- A1~A6 체크리스트
- B: UI 풀/토스트 -- Add 1회, 재사용, 애니 종료 후 Collapsed
- C: 안정성 -- Null 가드, 중복 타이머 미발생
> 상세 케이스는 '/docs/testing/test_cases.md' 참조

---

## 12. 용어
- CPC: Currency Per Click
- CPS: Currency Per Second
- Snapshot: 런타임 상태 구조체(FEconomySnapshot)
- SaveGame: 디스크 직렬화 오브젝트(UClickerSaveGame)
- 
---