# Architecture Overview (Tech)

## 모듈/의존성

- UClickerEconomySubsystem: 상태/세이브/오프라인 보상
- UClickerUISubsystem: HUD/토스트 풀, 표시층
- SaveManagerSubsystem: 슬롯 IO
- UISettings (Primary Data Asset)

## 수명 주기

- GameInstance Init -> Economy.Init -> UI.Init(의존성 보장) -> 1s 타이머 틱 -> 상태 갱신 -> OnEconomyChanged 브로드캐스트

## 이벤트 (API)

- Economy:
  - RequestLoad(), RequestSave()
  - OnEconomyChanged(const FEconomySnapshot&)
- UI:
  - ShowIdleReward(double amount)
  - ShowFloatingText(FText text, FVector2D position)

## 데이터 모델

- FEconomySnapshot { Currency, CPC, CPS, LastSaveTime(UTC)}
- UClickerSaveGame {UPROPERTY(SaveGame) Currency, CPC, CPS, UpgradeLevel, LastSaveTime}

## 정책

- 위젯 풀: **초기 1회만 AddToViewport 이후 Visible/Collapsed 토글**
- 로드 직후 보상 적용 시 즉시 저장 (재적용 방지)
