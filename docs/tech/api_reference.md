# API 참고 문서

이 문서는 ClickerGame의 핵심 시스템, Public API, 이벤트, 데이터 모델을 정리한 HUB 문서이다. 상세한 런타임 플로우는 `tech/architecture_overview.md`, UI 관점 플로우는 `design/system/system_ui.md`를 참고한다.

필요 시 클래스별 상세 문서를 `/docs/tech/api/` 하위로 분리, 확장할 수 있다.

---

## 1. API 개요

| 클래스                       | 책임                                    | 핵심 API                                                                                              | 이벤트                                                   | 사용하는 데이터 모델               |
| ---------------------------- | --------------------------------------- | ----------------------------------------------------------------------------------------------------- | -------------------------------------------------------- | ---------------------------------- |
| **UClickerEconomySubsystem** | 경제 상태/업그레이드/오프라인 보상 관리 | StartWorld,RequestLoad, RequestSave, OnClicked, TryUpgrade, GetSnapshot, HasPendingOfflineReward      | OnEconomyChanged, OnPassiveIncome, OnOfflineReward       | FEconomySnapshot                   |
| **UClickerUISubsystem**      | HUD & 토스트 UI, FX                     | ShowHUD, ShowReward, ShowFloatingText, ShowClickEffect, ShowUpgradeSuccessText/HideUpgradeSuccessText | (구독)OnEconomyChanged, OnPassiveIncome, OnOfflineReward | FEconomySnapshot(Read-Only)        |
| **USaveManagerSubsystem**    | SaveGame IO (직렬화/역직렬화)           | SaveProgress, LoadProgress                                                                            | -                                                        | UClickerSaveGame, FEconomySnapshot |
| **AMyPlayerController**      | 입력/초기화 엔트리포인트                | BeginPlay, SetupInputComponent, OnClick, OnUpgradeClicked, OnSaveClicked, OnLoadClicked               | -                                                        | (간접적으로) FEconomySnapshot      |

---

## 2. 데이터 모델

### 2.1 FEconomySnapshot

게임 내 경제 상태를 나타내는 런타임 스냅샷 구조체.
EconomySubsystem이 유일한 쓰기 주체이며, UI/Save는 읽기 전용으로 사용한다.

| 멤버              | 타입        | 기본값    | 역할                       | 접근 권한                 |
| ----------------- | ----------- | --------- | -------------------------- | ------------------------- |
| Currency          | double      | 0         | 현재 보유 재화             | R/W: Economy / R: UI      |
| CurrencyPerClick  | double      | 1         | 클릭당 재화 획득량(CPC)    | R/W: Economy / R: UI      |
| CurrencyPerSecond | double      | Base\*L/2 | 초당 재화 자동 획득량(CPS) | R/W: Economy / R: UI      |
| UpgradeLevel      | int32       | 0         | 업그레이드 진척도          | R/W : Economy / R: UI     |
| UpgradeCostBase   | double      | 10        | 업그레이드 비용 기본값     | R: Economy, UI            |
| UpgradeGrowth     | double      | 1.5       | 업그레이드 비용 상승 계수  | R: Economy, UI            |
| LastSaveTime      | int64 (UTC) | 0         | 오프라인 보상 Δt 계산 기준 | R/W: Economy, SaveManager |


> **Note:** 'LastSaveTime'은 오프라인 보상 계산 직후 즉시 저장을 설계에 포함하여 동일한 보상이 중복 적용되지 않도록 설계한다.

---

### 2.2 UClickerSaveGame

디스크에 저장되는 SaveGame 오브젝트.
FEconomySnapshot의 내용을 직렬화한 형태로, SaveManagerSubsystem이 생성/저장/로드를 담당한다.
| 멤버              | 타입   | UPROPERTY(SaveGame) | 역할                  |
| ----------------- | ------ | ------------------- | --------------------- |
| Currency          | double | True                | 보유 재화             |
| CurrencyPerClick  | double | True                | 클릭당 재화 획득량    |
| CurrencyPerSecond | double | True                | 초당 재화 자동 획득량 |
| UpgradeLevel      | int32  | True                | 업그레이드 진척도     |
| LastSaveUnixTime  | int64  | True                | 저장 시점(UTC)        |

---

## 3. 클래스별 API 상세

### 3.1 UClickerEconomySubsystem

**책임:**

- 게임 경제 상태 관리 (Currency, CPC, CPS, UpgradeLevel)
- 클릭/업그레이드/틱/오프라인 보상 로직
- Save/Load 트리거 및 Snapshot 관리
- 경제 상태 변경 시 관련 이벤트 브로드캐스트

**라이프사이클:**

1. **Start:** 
   - `AMyPlayerController::BeginPlay()`에서 `StartWorld(UWorld*)` 호출
   - 내부에서 `RequestLoad()`를 호출해 이전 진행 상태를 로드
   - 로드된 Snapshot을 기반으로 오프라인 보상을 계산 후, 필요 시 1회 적용 (`TriggerOfflineReward()`)
   - 1초 틱 타이머 및 필요 시 오토 세이브 타이머 시작

2. **Run:** 
   - 매 1초마다 `OnTick1Second`를 통해:
     - `CurrencyPerSecond`만큼 Currency 증가
     - `OnPassiveIncome` 브로드캐스트
     - Snapshot 변경 후 `OnEconomyChanged` 브로드캐스트

3. **End:**
   - Subsystem `Deinitialize()` 단계에서 타이머 해제
   - 마지막 상태를 저장

**공개 API (Public Functions)**

| 함수                             | 설명                                                                                                        |
| -------------------------------- | ----------------------------------------------------------------------------------------------------------- |
| `void StartWorld(UWorld* World)` | 월드 시작 시 경제 시스템 초기화, 로드/오프라인 보상/틱 타이머 설정.                                         |
| `void RequestLoad()`             | SaveManagerSubsystem을 통해 진행 상태를 로드하고 Snapshot에 적용.                                           |
| `void RequestSave()`             | 현재 Snapshot을 SaveManagerSubsystem에 전달하여 저장.                                                       |
| `void OnClicked()`               | 클릭 입력 처리. CPC만큼 Currency를 증가시키고 `Broadcast` 호출.                                             |
| `void OnUpgradeClicked()`        | Upgrade 버튼 클릭 시 업그레이드 시도.                                                                       |
| `void OnSaveClicked()`           | Save 버튼 클릭 ㅅ시 RequestSave() 시도.                                                                     |
| `void OnLoadClicked()`           | Load 버튼 클릭 시 RequestLoad() 시도.                                                                       |
| `void TriggerOfflineeReward()`   | OfflineReward 지급과 브로드 캐스트를 통한 UI 표시. UISubsystem에서 초기 1회 외부 실행, 이 후 모두 내부 실행 |

<!-- ---

- **의존성:**
  - **필수:** SaveManager (세이브/로드)
  - **권장:** UISubsystem (보상 토스트 표시)
- **공개 API:**
  - void StartWorld(UWorld* World)
  - void RequestLoad()
  - void RequestSave()
  - void OnClicked()
  - bool TryUpgrade()
  - double GetUpgradeCost()
  - const FEconomySnapshot& GetSnapshot() const
- **이벤트:**
  - OnEconomyChanged(const FEconomySnapshot&)
- **사용하는 데이터 모델:**
  - FEconomySnapshot (Read & Write)
- **Notes:**
  - 로드 직후 즉시 저장 설계로 중복 보상 방지 -->

---

### 3.2 UClickerUISubsystem

**책임:**
- HUD 생성
- 토스트 위젯 생성
- 텍스트 갱신
- FX/사운드 재생

**위젯 풀링 방식:**
- 초기 1회 `AddToViewport()` 후 Visible/Collapsed 토글 사용

**라이프사이클:**

1. **Start**
   - `Initialize()`에서 EconomySubsystem의 `OnEconomyChanged`, `OnPassiveIncome`, `OnOfflineReward` 델리게이트 구독
   - `UISettings`의 바인딩 에셋들과 대응하는 멤버 연결
   - `AMyPlayerController::BeginPlay()`에서 `ShowHUD()` 호출
   - HUD 위젯 생성 및 텍스트/버튼 대응하는 UI 멤버 연결
   - `AMyPlayerController`에 Upgrade/Save/Load 버튼 델리게이트 구독 중개
   - OnEconomyChanged(FEconomySnapshot)으로 UI 내용 갱신
   - `EconomySubsystem::TriggerOfflineReward()` 호출하여 오프라인 리워드 출력

2. **Run**
   - 구독한 델리게이트들에 의한 콜백을 지속적으로 실행
     - UI갱신
     - 토스트 위젯 생성
     - 사운드/FX 재생

3. **End**
   - `Deinitialize()`에서 EconomySubsystem 델리게이트 구독 해지

4. Initialize() (의존성 구독 + UISettings 동기 로드) 
5. ShowHUD() (1회) 실행 직후 Economy
6. GetSnapshot으로 수치 초기화 
7. 이후 변화는 OnEconomyChanged 구독으로 갱신 
8. Deinitialize() (구독/타이머 정리)

- **소유 주체:**
  - Widgets = Viewport/WidgetTree 소유 (애니메이션 종료 시 Collapsed -> 재사용 시 Visible)
- **의존성:**
  - **필수:** Economy (이벤트 구독 필수)
  - **권장:** UISettings (DataAsset, 로드 실패 시 우회)
- **공개 API:**
  - void ShowHUD()
  - void ShowIdleReward(double)
  - void ShowFloatingText(FText, FVector2D)
- **사용하는 데이터 모델:**
  - FEconomySnapshot (Read-only; 텍스트 갱신 전용)
  
---

### USaveManagerSubsystem
 
- **책임:**
  - SaveGame 슬롯 IO, 스냅샷 직렬화/역직렬화
- **공개 API:**
  - void SaveProgress(const FEconomySnapshot&)
  - bool LoadProgress(FEconomySnapshot&)
- **사용하는 데이터 모델:**
  - UClickerSaveGame (저장)
  - FEconomySnapshot (실행)