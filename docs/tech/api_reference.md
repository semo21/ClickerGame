# Public API (C++)

## UClickerEconomySubsystem

### 책임

1. 클릭/업그레이드/초당 수익
2. 세이브/로드
3. 오프라인 보상
4. 1초 틱 루프 관리

### 라이프사이클

1. GameInstance Subsystem.
2. Initialize/Deinitialize에서 타이머 및 저장 정리

-
- void RequestSave():
- const FEconomySnapshot& GetSnapshot() const:
- FOnEconomyChanged OnEconomyChanged:

## UClickerUISubsystem

- void ShowIdleReward(double Amount):
- void ShowFloatingText(const FText& Text, FVector2D ScreenPos):
- void ShowUpgradeSuccessText()
- ShowOfflineReward

## USaveManagerSubsystem

- void SaveProgress(const FEconomySnapshot& Snapshot):
- bool LoadProgress(FEconomySnapshot& OutSnapshot):
