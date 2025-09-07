# Public API (C++)

## UClickerEconomySubsystem

- void RequestLoad()
- void RequestSave()
- const FEconomySnapshot& GetSnapshot() cosnt
- FOnEconomyChanged OnEconomyChanged

## UClickerUISubsystem

- void ShowIdleReward(double Amount)
- void ShowFloatingText(const FText& Text, FVector2D ScreenPos)
