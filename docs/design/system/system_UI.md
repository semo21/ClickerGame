# UI System Spec (Design)
## 1. 목적
- UI 시스템의 구조, 위젯 풀링 정책, 이벤트 흐름을 문서화
- 새로운 위젯 추가 시 일관성을 유지하기 위한 가이드라인 제공.

## 2. HUD 레이아웃
- 주요 위젯: CurrencyText, ClickValueText, UpgradeCostText, PassiveInconeText, UpgradeSuccessText, UpgradeButton, SaveButton, LoadButton
- 배치:
  - 1. 재화관련 텍스트: 좌상단에 위치.
  - 2. Save/Load 버튼: 좌하단에 위치
  - 3. 업그레이드 버튼: 우상단에 위치
  - 4. 업그레이드 성공 텍스트: 상단 중앙에 위치
  - 예시: 

## 3. 위젯 풀링 규칙
- HUD / Idle / FloatingText위젯:
  - 초기 1회만 AddToViewport
  - 이후 Visible/Collapsed 토글로 사용
  - 애니메이션 종료 후 Collapsed
- 생성 지점 및 반납 루틴:
  - HUDWidget
    - 생성:
    - 반납:
  - IdleRewardText
    - 생성:
    - 반납:
  - FloatingText
    - 생성:
    - 반납:
## 4. 이벤트 흐름
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
- UISettings DataAsset 로딩 타이밍 (Initialize 단계에서 동기 로드)