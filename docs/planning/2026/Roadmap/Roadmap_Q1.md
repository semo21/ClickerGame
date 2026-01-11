# Roadmap — 2026 Q1

## Q1 Overall Goal
### 아키텍처가 명확하고 실제로 플레이 가능한 게임 상태 완성

## January 2026 — Core Structure & Visual Prototype

### Goal
UI/시스템 구조를 고정하고, '게임'처럼 보이게 만들기

### Tasks
- UI Architecture 리팩터 완료
  - HUD / Transient(Floating, Toast) / Modal 레이어 분리
  - WBP 분리 및 책임 명확화
- 기존 로직 유지한 채 UI 구조 안정화
- UI 에셋 적용
  - 폰트, 버튼, 패널, 컬러 팔레트 동일
- 기본 UX 폴리싱
  - 버튼 Hover/Press
  - 클릭/보상 연출 타이밍 조정
- Android / Windows 빌드 테스트

### Deliverables
- 안정적으로 플레이 가능한 빌드
- UI 구조 문서(system_ui.md)
- 1분 이내 플레이 영상

---
## Febrary 2026 — System Depth & Practical Engineering

### Goal
단순 동작이 아닌, **확장 가능한 시스템 구조** 완성

### Tasks
- 데이터 드리븐 경제 시스템
  - Upgrade / Cost / CPC / CPS를 DataTable / Curve 기반으로 이전
- SaveGame 안정화
  - SaveVersion 도입
  - 필드 변경 대응 로직 추가
- UX 보강
  - 오프라인 보상 요약 연출 개선
  - 수치 가독성 개선 (축약 표기, 강조)
- 코드 정리
  - Subsystem 책임 재정리
  - 불필요한 의존성 제거

### Deliverables
- 데이터 기반 밸런스 구조
- Save/Load 안정성 문서
- v0.1 태그 (annotated)

---
## March 2026 — Game Loop Completion

### Goal
**완결된 게임 루프** 완성

### Tasks
- 메타 시스템 추가
  - 환생
  - Daily Reward
  - Quest / Milestone
- 플레이 흐름 정리
  - 10~30분 플레이 기준 목표
- UX 최종 폴리싱
  - 사운드 볼륨 밸런스
  - 연출 정리
- 프로젝트 문서화
  - 플레이 영상도 추가
- 최종 빌드
  - Windows 실행 파일
  - Android APK

### Deliverables
- 완결된 클리커 게임
- README 정리
- 60~90초 분량의 플레이 영상
- 릴리즈 빌드 패키지 (Win + Android)
- v0.2 태그
