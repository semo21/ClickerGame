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
  1. 재화관련 텍스트: 좌상단에 위치.
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
- Currency Acquisition:
  1. EconomySubsystem::OnEconomyChanged 
     - -> UISubsystem::AddUniqueDynamic(OnEconomyChanged) 
     - -> EconomySubsystem::Broadcast()
     - -> OnEconomyChanged::Broadcast()
     - -> UISubsystem::OnEconomyChanged()
     - -> UISubsystem::UpdateScore()
- Click:
  1. PlayerController::BindKey(LeftClick, PlayerController.OnClick)
     - -> EconomySubsystem::OnClicked()
     - -> EconomymSnapshot.Currency ++
     - -> EconomySubsystem::Broadcast()
  2. UISubsystem::ShowClickEffect()
  3. UISubsystem::ShowFlotingText()
- Upgrade:
  1. UISubsystem::UpgradeButton->AddDynamic(PlayerController.OnUpgradeClicked)
  2. PlayerController::OnUpgradeClicked()
     - -> EconomySubsystem::TryUpgrade()
     - -> EconomySubsystem::Broadcast()
- Save:
  1. UISubsystem::SaveButtton->AddDynamic(PlayerController::OnSaveClicked)
     - -> PlayerController::OnSaveClicked()
     - -> EconomySubsystem::RequestSave()
     - -> SaveManagerSubsystem::SaveProgress(FEconomySnapshot)
     - -> UGameplayStatics::SaveGameToSlot(SaveDataContainer, SlotName, Index)
- Load:
  1. UISubsystem::LoadButtton->AddDynamic(PlayerController::OnLoadClicked)
     - -> PlayerController::OnLoadClicked() 
     - -> EconomySubsystem::RequestLoad()
     - -> SaveManagerSubsystem::LoadProgress(FEconomySnapshot)
     - -> UGameplayStatics::LoadGameFromSlot(SlotName, Index)
     - -> Cast<SaveDataContainer>(LoadData) => FEconomySnapshot
     - -> EconomySubsystem::UpdateLastOfflineReward(FEconomySnapshot)
     - -> EconomySubsystem::TriggerOfflineReward()
     - -> EconomySubsystem::ApplySnapshot(FEconomySnapshot)
     - -> EconomySubsystem::RequestSave()
- 1 Tick Idle Reward:
  1. EconomySubsystem::StartWorld()
     - -> EconomySubsystem::StartTickTimer()
     - -> WorldTimerManager.SetTimer(1.0s, EconomySubsystem::OnTick1Second, Loop)
  2. EconomySubsystem::OnTick1Second()
     - -> EconomySubsystem.Currency += CurrencyPerSecond
     - -> EconomySubsystem::OnPassiveIncome.Broadcase(CurrencyPerSecond)
     - -> EconomySubsystem::Broadcase() 
  3. UISubsystem::Initialize()
     - -> EconomySubsystem::OnPassiveIncome.AddUniqueDynamic(UISubsystem::OnPassiveIncome)
     - EconomySubsystem::OnEconomyChanged.AddUniqueDynamic(UISubsystem::OnEconomyChanged)
  4. UISubsystem::OnPassiveIncome(double AmountPerSec)
     - -> UISubsystem::HandlePassiveIncome(AmountPerSec)
     - -> UISubsystem::ShowReward(AmountPerSec, false // bIsOffline)
  5. UISubsystem::OnEconomyChanged(const FEconomySnapshot&)
     - -> UISubsystem::UpdateScore()  
- Offline Reward
- UISettings DataAsset Connection/Disconnection
  - Connection:
    - UISubsystem::Initialize()
  - Disconnection:
    -  UISubsystem.Deinitialize()

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
