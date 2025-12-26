# API Reference

이 문서는 ClickerGame의 핵심 시스템, Public API, 이벤트, 데이터 모델을 정리한 HUB 문서이다. 상세한 런타임 플로우는 `tech/architecture_overview.md`, UI 관점 플로우는 `design/system/system_ui.md`를 참고한다.

필요 시 클래스별 상세 문서를 `/docs/tech/api/` 하위로 분리, 확장할 수 있다.

---

## 1. API Outlines

| 클래스                       | 책임                                    | 핵심 API                                                                | 이벤트                                                         | 사용하는 데이터 모델               |
| ---------------------------- | --------------------------------------- | ----------------------------------------------------------------------- | -------------------------------------------------------------- | ---------------------------------- |
| **UClickerEconomySubsystem** | 경제 상태/업그레이드/오프라인 보상 관리 | StartWorld,RequestLoad, RequestSave, OnClicked, TryUpgrade, GetSnapshot | OnEconomyChanged, OnPassiveIncome, OnOfflineReward             | FEconomySnapshot(R/W)              |
| **UClickerUISubsystem**      | HUD & 토스트 UI, FX 표시                | ShowHUD, ShowReward, ShowFloatingText,                                  | (구독)OnEconomyChanged(구독), OnPassiveIncome, OnOfflineReward | FEconomySnapshot(Read-Only)        |
| **USaveManagerSubsystem**    | SaveGame IO (직렬화/역직렬화)           | SaveProgress, LoadProgress                                              | -                                                              | UClickerSaveGame, FEconomySnapshot |
| **AMyPlayerController**      | 입력/초기화 진입점                      | BeginPlay, OnClick, OnUpgradeClicked, OnSaveClicked, OnLoadClicked      | -                                                              | (간접적으로) FEconomySnapshot      |

---

## 2. Core Data Models

### 2.1 FEconomySnapshot

게임 내 경제 상태를 나타내는 런타임 스냅샷 구조체.
**EconomySubsystem이 유일한 쓰기 주체**이며, UI/Save는 읽기 전용으로 사용한다.

| 멤버              | 타입        | 기본값    | 역할                       | 접근 권한                 |
| ----------------- | ----------- | --------- | -------------------------- | ------------------------- |
| Currency          | double      | 0         | 현재 보유 재화             | R/W: Economy / R: UI      |
| CurrencyPerClick  | double      | 1         | 클릭당 재화 획득량(CPC)    | R/W: Economy / R: UI      |
| CurrencyPerSecond | double      | Base\*L/2 | 초당 재화 자동 획득량(CPS) | R/W: Economy / R: UI      |
| UpgradeLevel      | int32       | 0         | 업그레이드 진척도          | R/W : Economy / R: UI     |
| UpgradeCostBase   | double      | 10        | 업그레이드 비용 기본값     | R: Economy, UI            |
| UpgradeGrowth     | double      | 1.5       | 업그레이드 비용 상승 계수  | R: Economy, UI            |
| LastSaveTime      | int64 (UTC) | 0         | 오프라인 보상 Δt 계산 기준 | R/W: Economy, SaveManager |


> **Note** 'LastSaveTime'은 오프라인 보상 계산 직후 즉시 저장을 설계에 포함하여 동일한 보상이 중복 적용되지 않도록 설계한다.

---

### 2.2 UClickerSaveGame

디스크에 저장되는 SaveGame 오브젝트.
FEconomySnapshot의 내용을 직렬화한 형태로, SaveManagerSubsystem이 생성/저장/로드를 담당한다.
| 멤버              | 타입   | UPROPERTY(SaveGame) | 설명                       |
| ----------------- | ------ | ------------------- | -------------------------- |
| Currency          | double | True                | 보유 재화                  |
| CurrencyPerClick  | double | True                | 클릭당 재화 획득량(CPC)    |
| CurrencyPerSecond | double | True                | 초당 재화 자동 획득량(CPS) |
| UpgradeLevel      | int32  | True                | 업그레이드 단계            |
| LastSaveUnixTime  | int64  | True                | 저장 시각(UTC)             |

---

## 3. Class API Details

### 3.1 UClickerEconomySubsystem

**책임**

- 게임 경제 상태(Snapshot) 관리
- 클릭/업그레이드/패시브 수익/오프라인 보상 로직
- Save/Load 트리거
- 경제 상태 변경 시 이벤트 브로드캐스트

**Lifecycle**

1. **Start** 
   - `AMyPlayerController::BeginPlay()` -> `StartWorld(UWorld*)`
   - 내부에서 `RequestLoad()`를 호출
   - Load 직후 오프라인 보상 계산 및 1회 적용 
   - 보상 적용 후 `RequestSave()` 즉시 호출   - 
   - 1초 틱 타이머 및 필요 시 오토 세이브 타이머 시작

2. **Run** 
   - 매 1초마다 `OnTick1Second`를 통해:
     - `CurrencyPerSecond`만큼 Currency 증가
     - `OnPassiveIncome` 브로드캐스트
   - Snapshot 변경 시 `OnEconomyChanged` 브로드캐스트

3. **End**
   - Subsystem `Deinitialize()` 단계에서 타이머 해제
   - 마지막 상태를 저장

**Public API**

| 함수                                          | 설명                              |
| --------------------------------------------- | --------------------------------- |
| `void StartWorld(UWorld* World)`              | 경제 시스템 초기화 및 런타임 시작 |
| `void RequestLoad()`                          | 저장된 진행 상태를 로드           |
| `void RequestSave()`                          | 현재 Snapshot 저장                |
| `void OnClicked()`                            | 클릭 처리 (CPC 적용)              |
| `void TryUpgrade()`                           | 업그레이드 시도                   |
| `const FEconomySnapshot& GetSnapshot() const` | 현재 Snapshot 조회                |

> **Note** UI 버튼 이벤트는 **Controller 책임**이며, Economy는 "행위 API"만 제공한다.

---

### 3.2 UClickerUISubsystem

**책임**
- HUD 생성 및 토스트 UI 생성/표시
- Economy 이벤트 구독 및 시각화
- FX/사운드 트리거

**Lifecycle**

1. **Initialize()**
   - EconomySubsystem 델리게이트 구독
2. **ShowHUD()**
   - HUD 생성 및 초기 수치 표시
3. **Runtime**  
   - Delegate 콜백을 통해 UI 갱신
4. **Deinitialize()**
   - 델리게이트 구독 해제   

**Public API**

| 함수                                      | 설명                             |
| ----------------------------------------- | -------------------------------- |
| `void ShowHUD()`                          | HUD 생성 및 표시                 |
| `void ShowReward(double, bool)`           | 패시브/오프라인 수익 토스트 표시 |
| `void ShowFloatingText(FText, FVector2D)` | 플로팅 텍스트 표시               |

> **Note** UI는 Snapshot을 직접 수정하지 않으며, 이벤트 결과만 표현한다.
  
---

### 3.3 USaveManagerSubsystem
 
**책임**
   - SaveGame 슬롯 IO
   - Snapshot <-> SaveGame 직렬화/역직렬화

**공개 API**
| 함수                                         | 설명          |
| -------------------------------------------- | ------------- |
| `void SaveProgress(const FEconomySnapshot&)` | Snapshot 저장 |
| `bool LoadProgress(FEconomySnapshot&)`       | Snapshot 로드 |

---

### 3.4 AMyPlayerController (Entry Points only)
**책임**
- 입력(클릭/버튼) 이벤트를 받아 적절한 시스템으로 전달
- BeginPlay에서 Subsystem 초기화 흐름 시작

**Public/Callable Entry Points**
| 함수                         | 설명                                         |
| ---------------------------- | -------------------------------------------- |
| `void BeginPlay()`           | Economy `StartWorld` 호출, UI `ShowHUD` 호출 |
| `void SetupInputComponent()` | 클릭 입력 바인딩                             |
| `void OnClick()`             | Economy `OnClicked` 호출 + UI 효과 요청      |
| `void OnUpgradeClicked()`    | Economy `TryUpgrade` 호출                    |
| `void OnSaveClicked()`       | Economy `RequestSave` 호출                   |
| `void OnLoadClicked()`       | Economy `RequestLoad` 호출                   |

---

## 4. Delegate References

### 4.1 FOnEconomyChanged

```c++
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(
   FOnEconomyChanged, 
   const FEconomySnapshot&, 
   Snapshot
);
```
- Broadcaster: `UClickerEconomySubsystem`
- Subscriber: `UClickerUISubsystem`
- 호출 시점:
  - Snapshot이 변경되는 모든 시점
    - 클릭
    - 업그레이드
    - 패시브 수익 지급
    - 오프라인 보상 적용
    - 수동/자동 세이브 직전 등

### 4.2 FOnPassiveIncome

```c++
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(
   FOnPassiveIncome, 
   double, 
   AmountPerSec
);
```
- Broadcaster: `UClickerEconomySubsystem`
- Subscriber: `UClickerUISubsystem`
- 용도
  - 초당 수익 UI/토스트 표시

### 4.3 FOnOfflineReward

```c++
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(
   FOnOfflineReward, 
   double, 
   Amount
);
```
- Broadcaster: `UClickerEconomySubsystem`
- Subscriber: `UClickerUISubsystem`
- 용도
  - 오프라인 누적 보상 연출


## 5. Lifecycle Summary
BeginPlay
  - Economy.StartWorld
    - Load
    - Save
    - Start Tick
Runtime
  - Tick / Click / Upgrade
    - Snapshot Change -> Events -> UI
End
  - Save