# Public API (C++)

## UClickerEconomySubsystem

- void RequestLoad():
- void RequestSave():
- const FEconomySnapshot& GetSnapshot() const:
- FOnEconomyChanged OnEconomyChanged:

## UClickerUISubsystem

- void ShowIdleReward(double Amount):
- void ShowFloatingText(const FText& Text, FVector2D ScreenPos):

## USaveManagerSubsystem

- void SaveProgress(const FEconomySnapshot& Snapshot):
- bool LoadProgress(FEconomySnapshot& OutSnapshot):
