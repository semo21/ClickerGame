# Roadmap — 2026 Q3

## Q3 Overall Goal
### Clicker 전용 구조를 Global(Lobby+Room) 구조로 전환하고 안정화

## August 2026 — Global 구조 리팩터 착수

### Goal
Clicker 전용 서브시스템들을 WorldSubsystem 구조로 전환하고, Lobby-Clicker 레벨 전환 구조를 확립한다

### Tasks
- UI 패널 분리 리팩터 브랜치(refactor/ui-split-panels) 머지
- refactor/clicker-to-globalsystem 브랜치 개설
- ClickerEconomySubsystem, ClickerUISubsystem을 WorldSubsystem 구조로 전환

### Deliverables
- Global 구조 리팩터 착수 및 방향 확립

---
## September 2026 — 구조 안정화 및 책임 분리

### Goal
WorldSubsystem 전환을 마무리하고, PlayerController/SaveManager/Economy의 책임을 명확히 분리한다

### Tasks
- UI-Economy 바인딩 크래시 해결
- ClickerUISubsystem WorldSubsystem 전환 완료
- PlayerController를 Base/장르별 서브클래스로 분리
- SaveManager를 룸별/Meta 2단 구조로 일반화 (FInstancedStruct 기반)
- GlobalEconomySubsystem/GlobalProgressSubsystem 분리, Portal 언락 체크 연결

### Deliverables
- Lobby <-> Clicker 레벨 전환 및 언락 구조가 실제로 동작하는 빌드
- Global(GameInstance) / Room(World) 책임이 분리된 서브시스템 구조
