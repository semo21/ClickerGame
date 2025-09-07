```
ChangeLog.md

ChangeLog format

# Date

### feature

- 기능 구현

### fix

- 문제 해결

### refactor

- 내부 구조 개선

### perf

- 성능/메모리 개선

### docs

- 문서 변경

### chore

- 빌드, 도구, 세팅 등 기타 작업
```

# 06.12.25.

### fix(build, ui)

- 에디터 재시작 후 Actor 메시 사라짐 문제
- 업그레이드 비용 텍스트 표기
- 업그레이드 비용 텍스트 포맷 수정

# 06.16.25.

### feature(ui)

- 클릭 플로팅 텍스트 및 애니메이션 추가

# 06.26.25.

### feature(fx, ui)

- 클릭 Niagara FX 적용
- HUD 로직 리팩터 시작.

# 07.02.25.

### feature(save)

- Save/Load 시스템 추가

### refactor(architecture)

- MyPlayerController 리팩터 완료

### chore(git)

- feature/currency-persistence 브랜치 생성

# 07.04.25.

### feature(save)

- 종료시 자동 저장 구현
- SaveManagerSubsystem 도입

# 07.07.25.

### feature(save)

- 일정시간 경과시 자동저장 구현

# 07.11.25

### feature(economy)

- 오프라인 보상 추가

### fix(syntax)

- IdleRewardTextWidget 문법 오류 수정

# 07.15.25.

### feature(ui)

- IdleRewardTextWidget + 애니메이션 추가

### fix(ui)

- Widget관련 BP오류 해결

# 07.22.25.

### feature(ui)

- Offline Reward Text 추가
- 애니메이션 개선

# 07.24.25.

### refactor(ui)

- 오브젝트 풀링 구현 시작

### chore(git)

- 오브젝트 풀링 전용 브랜치 생성
- 완료된 currency-persistence 브랜치 정리

# 07.25.25.

### feature(ui)

- IdleRewardText 풀링 기반 비주얼 이펙트 구현

# 07.29.25.

### feature(ui)

- Idle 위젯 풀링 완료
- 사운드 시스템 핵심 구현
- 오디오 패키지 추가

# 08.12.25.

### refactor(system)

- UE5 상속/구조 이해 심화
  - 설계 조정 및 새 구조 스케치

# 08.15.25.

### refactor(system)

- GameManager 제거
- UISubsystem, EconomySubsystem 생성
- economySnapshot 구조체 생성
- ClickerComponent, PlayerController, SaveSubsystem 리팩터 완료.

# 08.20.25.

### fix(boot)

- 초기화/크래시 원인 해결 진행
  - UISattings DataAsset 생성 후 에셋 주입 정리

# 08.22.25.

### fix(ui, input)

- 심각한 오작동 원인 파악 및 수리 계획 수립
  - 핵심 코드 누락 확인
  - 코어 UI/Input 코드 보강

# 08.25.25.

### fix(boot, ui, save)

- Assertion 크래시 해결.
  - Save, Binaries, Intermediate폴더 삭제 후 generate VS files, 에디터 rebuild.
- Idle Reward 텍스트 누락 복구.
- Save/Load 이슈 식별

# 08.26.25.

### fix(boot, save)

- Assertion 재발
  - 지난번과 같은 방법으로 즉시 해결
  - \+ VS솔루션 빌드 진행
- Save 시스템 오류 추적

# 08.28.25.

### refactor(system)

- 구조 리팩터 완료

### fix(save, ui)

- Save time 초기화 에러 해결
- UI 업데이트 이슈 발견

# 09.02.25.

### fix(boot)

- Assertion 크래시 재발
  - 유령 BPGC 캐시로 추정
  - 이전과 같은 방법으로 해결

### chore(flow)

- 전체 게임 시스템 정상 동작 확인

# 09.03.25.

### fix(ui)

- IdleRewardText 경고 원인 규명
  - Viewport에 남아있는 인스턴스 Re-Add가 원인
  - 코드 수정 스케치

### docs

- 개발 로그, 기획 등 추가 문서 세분화 및 세부 작성 계획

  - docs
    - design
      - system
        - system_economy.md
        - system_UI.md
      - GameDesign.md(GDD)
    - diary
      - Devlog.md(ex. DevelopmentLog.md)
    - logs
      - ChangeLog.md
    - plannng
      - Daily
      - Weekly
      - BACKLOG.md
      - ROADMAP.md
    - release
    - tech
      - TechnicalDesign.md (TDD)
    - testing

- 이후 필요 시 추가/생성 예정

# 09.05.25.

### docs

- 기존 Devlog내용을 바탕으로 ChangeLog 내용 추가.
