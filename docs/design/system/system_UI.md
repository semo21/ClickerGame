# UI System Spec (Design)
## 1. 목적
- UI 시스템의 구조, 위젯 풀링 정책, 이벤트 흐름을 문서화
- 새로운 위젯 추가 시 일관성을 유지하기 위한 가이드라인 제공.

## 2. HUD 레이아웃
- 위젯 위치: Content/Widgets/WBP_ClickerUI
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
  - 1. 재화관련 텍스트: 좌상단에 위치.
  - 2. Save/Load 버튼: 좌하단에 위치
  - 3. 업그레이드 버튼: 우상단에 위치
  - 4. 업그레이드 성공 텍스트: 상단 중앙에 위치
- 사진:
![HUD 레이아웃](../assets/ui/HUD_Layout.png)

## 3. Floating Text 
- 위젯 위치: Content/Widgets/WBP_ClickFloatingText
- 위젯 요소:
  - FloatingText
- 배치:
  - 화면 정 중앙
- 색:
  - Yellow
- 애니메이션:
  1. FloatUpFade

## 4. Idle Reward Text
- 위젯 위치: Content/Widgets/WBP_IdleRewardText
- 위젯 요소:
  - AmountText
- 배치:
  - 소스코드에서 랜덤 위치로 제어
- 색:
  - Green
- 애니메이션:
  - FadeInOut
## 5. 위젯 풀링 규칙
- HUD / Idle / FloatingText위젯:
  - 초기 1회만 AddToViewport
  - 이후 Visible/Collapsed 토글로 사용
  - 애니메이션 종료 후 Collapsed
- 생성 지점 및 반납 루틴:
  - HUDWidget
    - 생성: UISubsystem.ShowHUD()
    - 반납: - 
  - IdleRewardText
    - 생성: UISubsystem.ShowHUD()
    - 반납: IdleRewardTextWidget.PlayFade()->Collapsed
  - FloatingText
    - 생성: UISubsystem.GetFloatingTextWidgetFromPool()
    - 반납: UISubsystem.ShowFloatingText()->RemoveFromParent()  // **UFloatingTextWidget에서 실행되도록 리팩터링 예정**

## 6. 이벤트 흐름
- 재화 획득:
  1. Economy.OnEconomyChanged 
  - -> UISubsystem.AddEvent(OnEconomyChanged) 
  - -> Economy.Broadcast()
  - -> UISubsystem.UpdateScore()
- 클릭:
  1. PlayerController.BindKey(LeftClick, PlayerController.OnClick)
  - -> Economy.OnClicked()
  - -> Economy.Broadcast()
  - -> Economy.OnEconomyChanged
  2. UI.ShowClickEffect()
  3. UI.ShowFlotingText()
- 업그레이드:
  - UpgradeButton.AddEvent(PlayerController.OnUpgradeClicked)
  - PlayerController.OnUpgradeClicked()
  - -> Economy.TryUpgrade()
  - -> Economy.Broadcast()
- UISettings DataAsset 로딩 타이밍
  - UISubsystem.Initialize()
  - 해제 타이밍은 UISubsystem.Deinitialize()

## 7. Data Asset
- UISettings(Primary Data Asset)
  - 멤버:
    1. UI
       - HUD Widget Class: 메인 HUD 위젯
       - Floating Text Widget Class: Floating Text 위젯 클래스
       - Idle Reward Text Widget Class: Idle Reward 위젯 클래스
    2. FX
       - Click Effect Asset: 클릭 FX
    3. Sound 
       - Click Reward Sound: 클릭 보상 사운드
       - Offline Reward Sound: 오프라인 보상 사운드