# API 참고 문서

이 문서는 ClickerGame의 핵심 시스템, Public API, 이벤트, 데이터 모델을 정리한 HUB 문서.

상세 내용은 필요 시 별도 파일(/docs/tech/api/)로 확장 예정.

## API 목록

| 클래스                       | 책임                                             | 핵심 API                                                                                | 이벤트                             | 사용하는 데이터 모델        |
| ---------------------------- | ------------------------------------------------ | --------------------------------------------------------------------------------------- | ---------------------------------- | --------------------------- |
| **UClickerEconomySubsystem** | 재화/업그레이드/오프라인 보상, 1초 틱, Save/Load | StartWorld,RequestLoad, RequestSave, OnClicked, TryUpgrade, GetUpgradeCost, GetSnapshot | OnEconomyChanged(FEconomySnapshot) | FEconomySnapshot            |
| **UClickerUISubsystem**      | HUD/텍스트 갱신, 토스트/FX/사운드, 풀링 위젯     | ShowHUD, ShowIdleReward, ShowFloatingText                                               | (구독)OnEconomyChanged             | FEconomySnapshot(Read-Only) |
| **USaveManagerSubsystem**    | SaveGame 슬롯 IO (직렬화/역직렬화)               | SaveProgress, LoadProgress                                                              | -                                  | UClickerSaveGame            |
| **AMyPlayerController**      | 입력, 초기 시작(ShowHUD/StartWorld), 버튼 핸들러 | OnClick, OnUpgradeClicked, OnSaveClicked                                                | -                                  | -                           |


## 데이터 모델
### FEconomySnapshot
| 멤버              | 타입        | 기본값    | 역할                       | 접근 권한            |
| ----------------- | ----------- | --------- | -------------------------- | -------------------- |
| Currency          | double      | 0         | 현재 보유 재화             | R/W: Economy / R: UI |
| CurrencyPerClick  | double      | 1         | 클릭당 재화 획득량         | R/W: Economy / R: UI |
| CurrencyPerSecond | double      | Base\*L/2 | 초당 재화 자동 획득량      | R/W: Economy / R: UI |
| UpgradeLevel      | int         | 0         | 업그레이드 진척도          | R/W:Economy / R: UI  |
| LastSaveTime      | int64 (UTC) | 0         | 오프라인 보상 Δt 계산 기준 | R/W: Economy, Save   |

> **Note:** 'LastSaveTime'은 오프라인 보상 계산 직후 즉시 저장을 설계에 포함. (중복 방지 목적)

### UClickerSaveGame
| 멤버              | 타입   | UPROPERTY(SaveGame) | 역할                  |
| ----------------- | ------ | ------------------- | --------------------- |
| Currency          | double | True                | 보유 재화             |
| CurrencyPerClick  | double | True                | 클릭당 재화 획득량    |
| CurrencyPerSecond | double | True                | 초당 재화 자동 획득량 |
| UpgradeLevel      | int    | True                | 업그레이드 진척도     |
| LastSaveUnixTime  | int64  | True                | 저장 시점(UTC)        |

## API 요약
### UClickerEconomySubsystem
- **책임:**
  - 재화/업그레이드/오프라인 보상, 1초 틱 수행(자동 보상), Save/Load 트리거
- **라이프사이클:**
  - **Start:** 
    1. AMyPlayerController의 BeginPlay() 실행 
    2. StartWorld(World) 실행 
    3. RequestLoad() 실행 (오프라인 보상 적용) 
    4. 1s 틱/오토세이브 타이머 시작
  - **Run:** 
    1. 매 1s 'CPS' 지급 
    2. -> OnEconomyChanged 브로드캐스트
  - **End:**
    1.  Deinitialize에서 타이머 해제(필요 시 저장)
- **소유 주체:**
  - Instance = GameInstance (Subsystem)
  - Timer = World TimerManager (시작/해제는 여기서 수행)
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
  - 로드 직후 즉시 저장 설계로 중복 보상 방지

---

### UClickerUISubsystem
- **책임:**
  - HUD 생성/텍스트 갱신, Idle/Offline 토스트, FloatingText, FX/사운드
  - **위젯 풀링 방식:**
    - 초기 1회 Add 후 Visible/Collapsed 토글 사용
- **라이프사이클:**
  1. Initialize() (의존성 구독 + UISettings 동기 로드) 
  2. ShowHUD() (1회) 실행 직후 Economy
  3. GetSnapshot으로 수치 초기화 
  4. 이후 변화는 OnEconomyChanged 구독으로 갱신 
  5. Deinitialize() (구독/타이머 정리)
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