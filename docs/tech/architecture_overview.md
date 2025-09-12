# Architecture Overview

## 1. 목적과 스코프
- 목적: Clicker의 런타임 구조, 흐름, 데이터/이벤트 경계 표시
- 스코프: 싱글 플레이, GameInstance Subsystem 기반, 세이브/로드/오프라인 보상/위젯 풀링
- 비스코프: 멀티플레이, 인 앱 결제시스템

## 2. 런타임 구조
- GameInstance
  - UClickerEconomySubsystem: 경제 상태/틱/오프라인 보상/세이브 트리거
  - UClickerUISubsystem: HUD/텍스트 갱신/토스트/FX/사운드
  - USaveManagerSUbsystem: SaveGame 슬롯 IO
-  PlayerController: 입력 진입점(클릭/업그레이드/세이브/로드 등 버튼 핸들러)
-  Widgets: HUD, Idle/FloatingText
  
## 3. 주요 시퀀스
### 3-1. 게임 시작(부팅)
- PlayerController.BeginPlay 
- -> Economy.StartWorld(UWorld*) 
- -> RequeestLoad() 
- -> SaveSubsystem.LoadProgress() 
- -> (Now - LastSaveTime) 오프라인 보상 계산 후 지급 
- -> ApplySnapshot 후 RequestSave() 
- -> 1초 Tick/AutoSave 타이머 시작 
- -> UI.ShowHUD() 
- -> Economy.OnEconomyChanged 구독, 초기 1회만 GetSnapshot()으로 UI 수치 갱신

### 3-2. 클릭
- PlayerController.OnClicked
- -> Economy.OnCLicked(Currency += CPC, Broadcast)
- -> UI.ShowClickEffect / ShowFloatingText

### 3-3. 업그레이드
- PlayerController.OnUpgradeClicked
- -> Economy.TryUpgrade (성공 시 Broadcast)
- -> UI.ShowUpgradeSuccessText

### 3-4 저장/로드
- PlayerController.OnSaveClicked
- -> Econonmy.RequestSave
- -> SaveSubsystem.SaveProgress(EconomySnapshot with LastSaveTime=UtcNow)
- -> PlayerController.OnLoadClicked
- -> Economy.RequestLoad (이후 3-1 시퀀스와 동일)

