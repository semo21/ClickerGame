# UI System Spec (Design)
## 1. 목적
- UI 시스템의 구조, 위젯 풀링 정책, 이벤트 흐름을 문서화
- 새로운 위젯 추가 시 일관성을 유지하기 위한 가이드라인 제공.

## 2. UI Layouts
### 1. HUD Layout
- 위젯 위치: Content/Widgets/WBP_ClickerUI
- 역할: Main HUD
- 주요 위젯: 
  - CurrencyText
  - ClickValueText
  - UpgradeCostText
  - PassiveInconeText
  - UpgradeSuccessText
  - UpgradeButton
  - SaveButton
  - LoadButton
- 배치:
  1. 재화관련 텍스트: 좌상단에 위치
  2. Save/Load 버튼: 좌하단에 위치
  3. 업그레이드 버튼: 우상단에 위치
  4. 업그레이드 성공 텍스트: 상단 중앙에 위치
- 사진:
![HUD 레이아웃](../assets/ui/HUD_Layout.png)

### 2. Floating Text 
- 위젯 위치: Content/Widgets/WBP_ClickFloatingText
- 역할: Object Click 시 출력되는 토스트 위젯
- 위젯 요소:
  - RewardText
- 배치:
  - 화면 정 중앙
- 색:
  - Yellow
- 애니메이션:
  1. ToastAnim

### 3. Idle Reward Text
- 위젯 위치: Content/Widgets/WBP_IdleRewardText
- 역할: Offline / 1 Tick Idle Reward 표시 토스트 위젯
- 위젯 요소:
  - RewardText
- Location:
  - 소스코드에서 랜덤 위치로 제어
- Color:
  - Green
- Animation:
  - ToastAnim

## 3. Widget Pool Policy
- HUD / Idle / FloatingText Widgets:
  - 초기 1회만 AddToViewport
  - 이후 Visible/Collapsed 토글로 사용
  - 애니메이션 종료 후 Collapsed
- 생성 지점 및 반납 루틴:
  - HUDWidget
    - 생성: UISubsystem.ShowHUD()
    - 반납: - 
  - IdleRewardText
    - 생성: UISubsystem::GetWidgetFromPool()
    - 반납: UToastWidgetBase::PlayToast()->UToastWidgetBase::OnToastFinished()->Collapsed
  - FloatingText
    - 생성: UISubsystem::GetWidgetFromPool()
    - 반납: UToastWidgetBase::PlayToast()->UToastWidgetBase::OnToastFinished()->Collapsed

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
