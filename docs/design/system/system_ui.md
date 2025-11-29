# UI System Spec (Design)
## 1. 목적
- Clicker게임의 UI 시스템의 구조, 위젯 풀링 정책, 이벤트 흐름을 문서화한다.
- 새로운 위젯 추가 시 일관성을 유지하기 위한 가이드라인 제공한다.

---

## 2. UI Layouts

### 2-1. HUD Layout
- 위젯 위치: `Content/Widgets/WBP_ClickerUI`
- 역할: 메인 HUD
- 주요 위젯: 
  - `CurrencyText`
  - `ClickValueText`
  - `UpgradeCostText`
  - `PassiveInconeText`
  - `UpgradeSuccessText`
  - `UpgradeButton`
  - `SaveButton`
  - `LoadButton`
- 배치:
  1. 재화 관련 텍스트: 좌상단
  2. Save/Load 버튼: 좌하단
  3. Upgrade 버튼: 우상단
  4. Upgrade 성공 텍스트: 상단 중앙
- 사진:
![HUD 레이아웃](../assets/ui/HUD_Layout.png)

### 2-2. Floating Text 
- 위젯 위치: `Content/Widgets/WBP_ClickFloatingText`
- 역할: 오브젝트 클릭 시 출력되는 토스트 형태로 표시하는 위젯
- 구성 요소:
  - `RewardText`
- 배치:
  - 화면 정 중앙(월드 좌표 -> 스크린 좌표 변환 후 배치)
- 색:
  - Yellow
- 애니메이션:
  1. `ToastAnim` (위로 떠오르며 사라지는 연출)

### 2-3. Idle Reward Text
- 위젯 위치: `Content/Widgets/WBP_IdleRewardText`
- 역할: 오프라인 보상 / 1 Tick Idle Reward(패시브 수익) 을 토스트로 표시하는 위젯
- 구성 요소:
  - `RewardText`
- Location:
  - 소스코드에서 랜덤 스크린 좌표로 제어(구현 예정)
- Color:
  - Green
- Animation:
  - `ToastAnim`

---

## 3. Widget Pool Policy
### 3-1. 공통 정책
- HUD /  IdleRewardText / FloatingText 위젯은 다음 원칙을 따른다.
  - 초기 1회만 `AddToViewport`한다.
  - 이후에는 `Visible / Collapsed` 토글로 활성/비활성을 제어한다.
  - 애니메이션이 끝나면 `Collapsed`로 전환하여 화면에서 숨긴다.
- 풀링 목적:
  - 위젯 생성/파괴 비용을 줄이고, 재사용을 통해 퍼포먼스를 안정화한다.
  - 동일한 타입의 토스트를 반복적으로 사용할 수 있도록 한다.

### 3-2. 위젯별 생성 / 반납 규칙

- **HUDWidget**
  - 생성: `UISubsystem::ShowHUD()`
  - 반납: 없음 (게임 세션 동안 상시 유지)
- **IdleRewardWidget**
  - 생성: `UISubsystem::GetWidgetFromPool()` 호출 시 풀에서 꺼냄
  - 사용: 패시브 수익 / 오프라인 보상 수치를 토스트로 표시
  - 반납: 
    - `UToastWidgetBase::PlayToast()`
    - -> 애니메이션 종료 시 `UToastWidgetBase::OnToastFinished()`
    - -> Visibility를 `Collapsed`로 설정
- **FloatingText**
  - 생성: `UISubsystem::GetWidgetFromPool()` 호출 시 풀에서 꺼냄
  - 사용: 클릭 보상을 화면 중앙 부근에 토스트로 표시
  - 반납:
    - IdleRewardText와 동일한 플로우
    - (`PlayToast()` -> `OnToastFinished()` -> `Collapsed`) 

---

## 4. Event Flow

### 4-1. Economy Changed (HUD Update)
- EconomySubsystem이 'OnEconomyChanged' 델리게이트를 브로드캐스트
- UISubsystem이 이를 구독('OnEconomyChanged')하고, 콜백에서:
  - CurrencyText / ClickValueText / UpgradeCostText / PassiveIncomeText 등 HUD 텍스트를 갱신

### 4-2. Click (FX + Floating Text)
- PlayerController의 클릭 처리에서:
  - UISubsysteem::ShowClickEffect()를 호출하여 클릭 위치에 FX 재생
  - UISubsystem::ShowFloatingText()를 호출하여 클릭 보상 텍스트 토스트 재생
- Economy 수치는 EconomySubsystem 내부에서 갱신
- HUD 갱신은 4-1의 'EconomyChanged'를 통해 진행

### 4-3. Upgrade / Save / Load Buttons
- HUD 위젯 초기화에서:
  - Upgrade / Save / Load 버튼은 PlayerController의 각 핸들러에 바인딩
- UISubsystem의 책임:
  - 버튼의 배치 및 표시 상태 관리
  - 클릭 시 적절한 핸들러가 호출되도록 바인딩 유지
- 실제 Upgrade / Save / Load 로직은 EconomySubsystem / SaveSubsystem이 담당
- UI 갱신은 4-1의 'EconomyChanged'를 통해 진행

### 4-4. Passive Income (1 Tick Idle Reward)
- EconomySubsystem이 1초마다 'OnPassiveIncome' 델리게이트를 브로드캐스트
- UISubsystem은 이를 구독하고:
  - HUD상의 PassiveeIncome 텍스트를 갱신
  - 1 Tick Idle Reward 토스트(IdleRewardText)를 재생하여 패시브 수익 표시

### 4-5. Offline Reward
- 게임 시작 시 로드 이후, EconomySubsystem이 'OnOfflineReward'를 브로드캐스트
- UISubsystem은 이를 구독('OnOFflineReward')하고:
  - IdleRewardText 토스트를 재생하여 오프라인 누적 보상을 표시

## 5. Data Asset
- UISettings(Primary Data Asset)
  - 멤버:
    1. UI
       - HUD Widget Class: 메인 HUD 위젯(WBP_ClickerUI)
       - Floating Text Widget Class: Floating Text 위젯 클래스(WBP_ClickFloatingText)
       - Idle Reward Text Widget Class: Idle Reward 위젯 클래스(WBP_IdleRewardText)
    2. FX
       - Click Effect Asset: 클릭 FX(NS_ClickEffect)
    3. Sound 
       - Click Reward Sound: 클릭 보상 사운드
       - Offline Reward Sound: 오프라인 보상 사운드
