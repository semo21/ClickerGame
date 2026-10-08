# Roadmap — 2026 Q4

## Q4 Overall Goal
### Lobby-Clicker 구조를 완성하고, 두 번째 장르 룸을 에셋까지 입혀 완성한다

이번 분기의 핵심은 "구조 검증"에서 "콘텐츠 생산"으로 전환하는 것이다. 구조 리팩터는 10월 안에 종료하고, 남은 기간은 실제 장르 룸을 만들어내는 데 쓴다. 두 번째 룸이 플레이 가능한 상태로 나오는 것이 이번 분기의 성패 기준이다.

## October 2026 — Global-Level 구조 확립 마무리

### Goal
소스코드와 BP 양쪽을 점검하며 Global(전역)과 Level(룸별)의 책임 분리를 확립하고, Lobby-Clicker 구조를 완결 짓는다

### Tasks
- 레벨별 기초 구성요소(GameMode / PlayerController / Pawn / RootWidget) 점검 및 명시적 설정
- BP 측 점검: 그동안의 소스코드 리네임/구조 변경이 반영되지 않은 부분 정리
- 점검 과정에서 발견되는 구조적 결함 수정 (암묵적 의존, 누락된 설정 등)
- (여유 시) Clicker에서 Global 재화를 획득하는 방식 결정 및 연결

### Deliverables
- Global / Level 책임이 코드와 BP 양쪽에서 명시적으로 드러나는 상태
- Lobby <-> Clicker 전체 흐름이 암묵적 의존 없이 동작하는 빌드

### Revision (2026-10-07)
- 사유: 위 Tasks 중 구조 점검 3건이 W39~W40에 조기 완료되어, 11월 계획이던 두 번째 장르 룸(Defense) 구현을 9/28부터 앞당겨 시작함
- 추가 Tasks
  - Defense 타일 그리드, 타워 배치, 경로탐색
  - Defense 적 스폰 및 경로 이동, 타워 공격
  - Defense 웨이브 진행 및 승패 판정
- 이관: "Clicker에서 Global 재화를 획득하는 방식 결정 및 연결" → 11월
- 추가 Deliverable: Lobby에서 Defense로 진입해 웨이브 한 판을 승패까지 플레이할 수 있는 빌드

---
## November 2026 — 두 번째 장르 룸 구현

### Goal
Mode 시스템 뼈대를 세우고, 그 위에 두 번째 장르 룸을 플레이 가능한 수준까지 구현한다

### Tasks
- Mode 시스템 인터페이스/베이스 클래스 설계 및 구현
  - Clicker의 이동 모드 <-> 클릭 모드 전환도 이 시스템 위에서 처리
- 두 번째 장르 룸의 GameMode/PlayerController/Economy 서브클래스 구현
- Portal을 통한 Lobby <-> 두 번째 룸 이동 연결

### Deliverables
- 두 개 이상의 장르 룸을 오갈 수 있는 플레이 가능한 빌드

### Revision (2026-10-07)
- 사유: 두 번째 장르 룸(Defense) 구현이 10월로 앞당겨짐
- 10월로 이동: "두 번째 장르 룸의 GameMode/PlayerController 서브클래스 구현", "Portal을 통한 Lobby <-> 두 번째 룸 이동 연결" (9/28 착수)
- 10월에서 이관: "Clicker / Defense에서 Global 재화를 획득하는 방식 결정 및 연결"
- 추가 Task: Global 재화 사용처 최소 1개 연결
- 변경된 Goal: 룸의 결과를 Global 재화로 정산하는 최소 루프를 연결하고, Mode 시스템 뼈대를 세운다
- 변경된 Deliverable: Lobby <-> Clicker / Defense를 오가며 Global 재화를 벌고 쓰는 플레이 가능한 빌드

---
## December 2026 — 에셋 적용 및 폴리싱

### Goal
두 번째 룸에 에셋을 입히고, 전체 플레이 흐름을 다듬는다

### Tasks
- 두 번째 룸에 그래픽/사운드 에셋 적용
- Lobby-Clicker-두 번째 룸 전체 플레이 흐름 폴리싱
- 문서 갱신 및 플레이 영상 촬영

### Deliverables
- 에셋이 적용된, 처음부터 끝까지 플레이 가능한 빌드
