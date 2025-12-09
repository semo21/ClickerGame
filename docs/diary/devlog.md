# Dev Log

## 06.11.25.

- Fixed an issue where Actors' meshes disappeared after restarting the editor -- the problem was resolved by building the solution in Visual Studio with the Development Editor configuration.
- Additionally, reviewed the C++ source code and fixed some syntax errors.

## 06.12.25.

- Fixed an issue where _UpgradeCost_ text was not displayed.
- Updated the currency display format.

## 06.13.25.

- Implemented Floating Text to appear on click.

## 06.15.25.

- Studied the detailed architecture of the Unreal Engine C++ build system.
  - Covered concepts like DLLs, UHT, UBT, etc.

## 06.16.25.

- Added animation to FloatingText for better visual feedback.

## 06.17.25.

- Started refactoring the source code, focusing on AMyPlayerController.
  - Began separating responsibilities from AMyPlayerController as it had become too monolithic.
- Investigated and resolved a branch synchronization issue between local and remote Git repositories, caused by misunderstanding how rebase merges affect commit histories

## 06.18.25.

- Resolved GitHub merge conflict.
- Created new UI manager script as part of the refactoring effort.

## 06.20.25.

- Began refactoring the HUD-related logic within the AMyPlayerController class, continuing the effort to modularize its responsibilities.
- Added new branch named "refactor/ui-manager"

## 06.23.25.

- Continued modularizing HUD responsibilites within AMyPlayerController.

## 06.24.25.

- Ongoing modularization work. Minor internal structuring adjustments.

## 06.25.25.

- Created Niagara FX for click events.
  - Currently configuring asset settings -- some issues are being worked through.

## 06.26.25.

- Implemented Niagara FX for click events.
  - Started refactoring the HUD logic inside the PlayerController script.

## 06.27.25.

- Still refactoring the PlayerController script.

## 06.30.25.

- Continued refactoring MyPlayerController script.
  - Resolved an error caused by duplicate variable declarations.
  - Further cleanup and modularization planned.

## 07.01.25.

- Nearly finished refactoring the MyPlayerController script.

## 07.02.25.

- Completed refactoring of the MyPlayerController script.
- Removed the refactor branch.
  - Created a new feature branch -- feature/currency-persistence.
- Added Save and Load system.

## 07.03.25.

- Refactored Initialize function in UIManager to improve clarity and reduce redundancy.

## 07.04.25.

- Added autosave system when exiting the game.
  - Added SaveManagerSubsystem to handle Load/Save operations.

## 07.07.25.

- Added autosave system triggered every 60 seconds.
- Added Save/Load buttons.
  - Added messages for Save/Load actions.

## 07.08.25.

- Added offline reward.

## 07.09.25.

- Working on additional offline reward system.

## 07.10.25.

- Working on offline reward message.

## 07.11.25.

- Fixed syntax error in the IdleRewardTextWidget script.

## 07.14.25.

- Working on Adding Idle Reward(Currency Per Second, Offline Reward) Text Widget.
  - Encountered some errors in the Widget BP. Currently working on fixing them.

## 07.15.25.

- Added Idle Reward Text Widget with animation.
- Resolved BP errors.

## 07.16.25.

- Clean up WBP structures.

## 07.17.25.

- Added some animations to Idle reward text.
- ~~Added Offline Reward Text~~
- Encountered some errors in ClickerComponent and ClickerUIManager. Planning to fix them tomorrow

## 07.18.25.

- Attempted to resolve syntax errors in scripts.

## 07.21.25.

- Continued working on resolvving editor-related issues.

## 07.22.25.

- Resovled errors in ClickerComponent and ClickerUIManager.
- Added Offline Reward Text
  - Make the animation for Offline Reward Text more detailed.

## 07.23.25.

- Started to make object pooling for idle reward text.

## 07.24.25.

- Added new branch for adding ObjectPooling.
- Deleted old branch --currency-persistence.
- Working on implementing object pooling for idle rewards.

## 07.25.25.

- Implemented visual effect using object pooling for IdleRewardTextWidget.
- However, a somewhat unfamiliar warning sign appears during runtime. Planning to investigate and resolve it.

## 07.27.25.

- Core game system is now complete.
- Started searching for suitable graphic assets.

## 07.28.25.

- Idle Widget Pooling completed.
- Started implementing sound system.
- Created feature/SoundSystem branch.

## 07.29.25.

- Searched Audio source.
  - Added audio package to the project.
- Implemented the core audio system.

## 07.30.25.

- Began refactoring UIManager, AudioConfigDataAsset and MyPLayerController scripts.
  - Realized that some script is handling too many responsibilites.
  - Realized the need for a global coordinator to manage communication between systems like UIManager, audio sources, and AudioConfigDataAsset.

## 07.31.25.

- Investigated architecture strategies for connecting UIManager with AudioConfigDataAsset.
  - Focused on designing a global coordinator -- or initializer, manager etc -- for better decoupling and system communication.

## 08.01.25.

- Added GameManager script to the game.
  - Added a plan to refactor existing scripts around the GameManager as the central coordinator.

## 08.04.25.

- Searched suitable asset in my Fab library.

## 08.05.25.

- Redesigned the flow of the scripts.

## 08.06.25.

- Started refactoring existing scripts around the GameManager as the central manager.

## 08.07.25.

- Refactoring is on progress.

## 08.11.25.

- Continued working on refactoring GameManager script.

## 08.12.25.

- Gained a deeper understanding of UE5 class inheritance.
- Decided to adjust the refactoring structure accordingly.
  - Sketched out the new structure.

## 08.13.25.

- Deleted GameManager script.
- Created ClickerUISubsystem, ClickerEconomySubsystem scripts.
- Started to refactor UIManager and ClickerComponent, PlayerController scripts.
- Completed refactoring UISubsystem and EconomySubsystem.
  - Added FEconomySnapshot structure script for handling economic data.

## 08.14.25.

- Still in progress of refactoring.
  - Completed refactoring ClickerComponent and PlayerController scripts.
  - Working on refactoring Save system structure.

## 08.15.25.

- Still in progress of refactoring.
  - Few corrections in UISubsystem and EconomySubsystem.
  - Completed refactoring SaveSubsystem.

## 08.17.25.

- Still in progress of refactoring.
  - Few typos and grammar errors are corrected.

## 08.18.25.

- Corrected some typos and details in whole project.
- Fixing Initializing error.

## 08.19.25.

- Created DataAsset scipt to handling assets.
- Try to Resolve Editor crash when the game is started.

## 08.20.25.

- Trying to resolve Editor crash and initialization errors.
  - Found the sources and fixed them.
  - New error appeared, but the game can start.
  - Added a UISettings DataAsset for editor-side asset handling.

## 08.21.25.

- Found a serious fault in soource code causing malfunction.
  - Planned the fix.
    - Introduced during refactor -- missed some core code in a fuew classes.

## 08.22.25.

- Adding core UI and input code.

## 08.23.25.

- Serious assertion crash occured.
  - Still investigating the cause.

## 08.25.25.

- Resolved the assertion crash.
- Fixed missing idle-reward text.
- Noticed an issue with save/load.

## 08.26.25.

- Assertion crash occured but was resolved immediately.
- Still investigating the save error.

## 08.27.25.

- Still tracking down the save error.

## 08.28.25.

- Completed structural refactor.
- Still working on save errors.
  - Resolved "save time null" error.
- Noticed UI updates not working.

## 08.29.25.

- Resolving delegate-related error.
- Studying UBT/UHT and the UE5 reflection system.

## 08.30.25.

- Re-checking errors.

## 09.02.25.

- Deciding to write more detailed logs:
  - What I did, what I’ll do next, and what I learned (instead of just “refactor done”, “save error”, etc.).
- IsA Assertion crash occured; needed to understand UBT/UHT caching.
  - Suspected a stale ("ghost") cache in UE.
  - Deleted saved, binaries, intermidiate folders, regenerated VS files, and rebuilt the project in the editor.
  - **[Solved]**
- Verified the project runs well after the refactor.
  - Save/Load, UI system, and economy systems are working.
- Need to clean up an output-log warning:
  - **_LogScript: Warning: Script Msg: The widget 'WBP_IdleRewardText_C_0' was already added to the screen._**
  - UISubsystem의 ShowIdleReward에서 IsAnimationPlaying() 함수가 문제일 것이라고 추측중.

## 09.03.25.

- IdleRewardText의 에러의 원인을 찾은 것 같음.
  - IdleRewarTextWidget의 IsAnimationPlaying()함수는 정상작동.
  - 뷰포트에 Add한 후에 제거하지 않은 채로 다시 Add를 하려해서 나는 경고였다고 생각중.

## 09.04.25.

- 앞으로의 Devlog format
  - what: 결과
  - why: 원인/의도
  - how: 취한 조치
  - proof: 로그/스크린샷/커밋 링크 등

## 09.05.25.

- what
  - ChangeLog 내용 작성
- why
  - 변경점 정리 목적
  - 기존 Devlog가 ChangeLog의 내용까지 포함하고 있었음
- how
  - Devlog 내용을 바탕으로 ChangeLog 일별 변경점 작성
- proof
  - docs/logs/ChangeLog.md 확인
  - 또는 깃헙 커밋 링크 확인.

## 09.10.25.

- what
  - Daily, Weekly 계획 수립 및 문서 작성
- why
  - 문서 포맷 적응 목적
  - 계획 수립 목적
- how
  - 사전에 정립한 Weekly, Daily 포맷을 바탕으로 작성
- proof
  - [Commit Link](https://github.com/semo21/ClickerGame/commit/f897e3b4004211b12f5d6ea83e6c0c195278f87a)

## 09.12.25.
- what 
  1. 문서 작성
- why
  - 1-1) 기존의 Developement Log에 모든 내용을 기록하는 구조는 문서로서 합리적인 구조가 아니라고 판단.
  - 1-2) 프로젝트의 전체 구조를 파악할 수 있는 문서를 마련하는 것이 이후에 더 좋을 것이라고 판단.
- how 
  - 1-1) api_reference 템플릿 조사 및 작성
  - 1-2) architecture_overview 문서 작성
- proof
  - [Commit Link](https://github.com/semo21/ClickerGame/commit/eda80711010bdf9afb19b5dee0fe84abd0fd2c3f)

## 09.13.25.
- what
  1. 문서 작성
- why
  - 1-1) 기존의 Developement Log에 모든 내용을 기록하는 구조는 문서로서 합리적인 구조가 아니라고 판단.
  - 1-2) 프로젝트의 전체 구조를 파악할 수 있는 문서를 마련하는 것이 이후에 더 좋을 것이라고 판단.
- how
  - 1-1) architecture_overview 작성
- proof
  - [Commit Link](https://github.com/semo21/ClickerGame/commit/43d7682a09e372591e0d337d83d43b2472eb0429)

## 09.15.25.
- what
  1. 문서 작성
- why
  - 1-1) 기존의 Developement Log에 모든 내용을 기록하는 구조는 문서로서 합리적인 구조가 아니라고 판단.
  - 1-2) 프로젝트의 전체 구조를 파악할 수 있는 문서를 마련하는 것이 이후에 더 좋을 것이라고 판단.
- how
  - 1-1) system_ui 작성
  - architecture_overview 작성
  - api_reference 작성
  - weekly plan 수립 및 작성
  - 부족한 문서 추가 조사
- proof
  - [Commit Link](https://github.com/semo21/ClickerGame/commit/67aada3547b237a2985231d3f0aa490749afc39c)

## 09.17.25.
- what
  1. 문서 작성
  2. CreateWidget 타입 가드 추가
- why
  - 1-1) 기존의 Developement Log에 모든 내용을 기록하는 구조는 문서로서 합리적인 구조가 아니라고 판단.
  - 1-2) 프로젝트의 전체 구조를 파악할 수 있는 문서를 마련하는 것이 이후에 더 좋을 것이라고 판단.
  - 2-1) Assertion 크래시 및 다른 에러 예방 목적
- how
  - 1-1) README 업데이트
  - 1-2) test_cases 작성
  - 1-3) system_ui 작성
  - 2-1) 모든 CreateWidget 실행 코드 앞에 ensure 및 조건문 가드 추가
- proof
  - [Commit Link](https://github.com/semo21/ClickerGame/commit/3de0661d58abcbf0bf11eb1e501263c114acc746)

## 09.18.25.
- what
  1. Economy 오프라인 보상수령 직후 Save 구조 설계, 분석
- why
  - 1 -> 원치않는 시점에 종료되어 보상을 중복수령하게 될 수 있는 구조 방지
- how
  - 1-1) Save/Load플로우 파악
  - 1-2)Offline 보상 수령 및 저장 구조 파악
  - 1-3) UI업데이트 구조 파악
- proof
  - [Commit Link](https://github.com/semo21/ClickerGame/commit/426ebe00af6e111ad3bbe0faaab78faf8b81749d)

## 09.19.25.
- what
  1. Economy 오프라인 보상수령 직후 Save구현
  2. 시작 직후 UISubsystem::ShowOfflineReward 실행되지 않는 현상 수정
- why
  - 1 -> 원치 않는 시점에서 종료 시 보상 중복수령 가능성 제거
  - 2 -> 설계대로 작동하지 않는 UI기능 수정
- how
  - 1-1) 예상치 못한 종료 상황 때 보상 중복 수령 가능한 상황 예방
  - 2-1) UISubsystem::ShowHUD()의 InitilaizeDependency 해제
  - 2-2) MyPlayerController::BeginPlay()의 UISubsystem, EconomySubsystem Init 순서 변경 
- proof
  - [Commit Link](https://github.com/semo21/ClickerGame/commit/8d86033f54f816ca412df34c07c7eea87f3b5c1a)

## 09.22.25.
- what
  1. 소스코드 파일 분류
- why
  - 스크립트 별 목적, 공개범위에 따라 정리해두는 것이 이후 추가 작업할 때 합리적일 것이라고 판단함.
- how
  - 헤더: 다른 클래스에서 사용되는 헤더들은 Public, 그렇지 않은 헤더들은 Private.
  - C++: 대부분 Private으로 지정
  - 추가 분류 기준
  - Gameplay, System, Data 3개의 대분류 후 Save, Data와 같은 세부 목적별로 추가 분류
  - 분류 후 Full rebuild를 통해 에디터 재시작
- proof
  - [Commit Link](https://github.com/semo21/ClickerGame/commit/46ea1babe6b2b12025c1735fa3c7edc42a38d8f2)


## 09.23.25.
- what
  - 헤더 선언부 전면 수정
- why
  - 소스코드 파일 경로 변경으로 인한 수정 필요
- how
  - 스크립트의 모든 헤더 경로 직접 수정
- proof
  - [Commit Link](https://github.com/semo21/ClickerGame/commit/792980a4eec0694fa37eb7fb3c34af48450b17dd)

## 09.24.25.
- what
  1. 밀린 Devlog 작성
  2. ensure 에러메시지 해결
- why
  - 1-1) 문서화 이후 Devlog 역할을 인지하지 못함.
  - 1-2) Devlog 역할과 내용 조사 후 역할 인지.
  - 2-1) 델리게이트로 인한 에러가 발생했기 때문에 해결하려 함.
- how
  - 1-1) Devlog 역할과 작성 내용 조사
  - 1-2) 그동안의 Daily Plan을 기반으로 밀린 Devlog 작성
  - 2-1) 델리게이트 중복 구독으로 인한 ensure 에러메시지 출력을 인지
  - 2-2) 델리게이트 중복 구독되는 원인 추적
  - 2-3) 중복 선언으로 인한 중복 구독으로 발생하는 에러임을 인지하고 수정하여 해결
- proof
  - Commit Link
<<<<<<< HEAD:docs/diary/Devlog.md

## 09.25.25.
- what
  1. FloatingText 풀 한도 초과시 설정해둔 경고 메시지 발생 확인 
  2. EconomySnapshot 구조체 독립
  3. README 링크 일부 수정
  4. Delegate 선언 관련 솔루션 오류 해결
  5. 프로젝트 내 함수 및 멤버 포인터 플로우 파악
- why
  - 1-1) 풀을 초과할 정도의 토스트를 생성할 때 대비책이 필요하다고 생각.
  - 2-1) 유지보수 측면과 가독성 측면에서 EconomySubsystem.h에 기생하는 구조면 합리적이지 못하다고 판단.
  - 3-1) README에 작성한 하위파일 링크가 파일명 대소문자 구분으로 정상 작동하지 않음. 포트폴리오로 올린 목적에 반하는 상황이기에 수정 결심.
  - 4-1) EconomySnapshot 파일 추가 도중 솔루션 빌드에 오류발생
  - 4-2) 솔루션 빌드 실패 원인은 델리게이트 인자 이름 중복
  - 5-1) 프로젝트 전반을 파악하며 포인터 플로우 이해의 부족을 체감하여 더 파악하기로 결정.
- how
  - 1-1) 문제점 인지한 상태로 마감.
  - 2-1) EconomySnapshot.h를 Public/Data/Economy/ 경로에 생성, Full rebuild로 솔루션에 캐싱 후 내용 작성
  - 2-2) 에디터 실행 후 데이터 정상작동 확인.
  - 3-1) Github에서 파일명 직접 수정하여 커밋
  - 4-1) 빌드 실패 로그로 델리게이트 관련 오류 내용 파악
  - 4-2) 델리게이트 매개변수 이름 중복부분 확인
  - 4-3) 수정 후 재 빌드 성공
  - 5-1) GPT와 포인터 관련 블로그 게시글을 활용하여 포인터 플로우 이해, 파악
- proof
  - [Commit Link](https://github.com/semo21/ClickerGame/commit/b94b593a086c90c77c4ebb6094d328747b47c2a4)
  - 1. Image ![Image](./assets/FloatingText_warning.png)

## 09.26.25.
- what
  1. UISubsystem의 EconomySubsystemRef 캐싱 멤버 타입 수정중
- why
  - 1-1) GISubsystem은 raw pointer를 사용해도 좋다는 사실을 인지.
  - 1-2) raw pointer 또는 TObjectPtr<T>를 사용하는 것이 가독성 면에서 유리하다고 판단.
- how
  - 1-1) Header에서 TWeakObjectPtr<T>에서 TObjectPtr로 수정
  - 1-2) 기존 WeakPtr을 사용할 때 필요하던 참조 체크 삭제.
  - 1-3) 하지만 Assertion Crash 발생.
- proof
  - [Commit Link](https://github.com/semo21/ClickerGame/commit/fa060ef0c3f1caeb6a37b5ff2ec19a0e941f4e48)

## 09.27.25.
- what
  1. Assertion Crash 해결
- why
  - 1-1) UISubsystem::EconomySubsystemRef의 참조방식을 수정하던 중 WBP 에디터 참조에서 유령 캐시 이슈로 Assertion이 난 것으로 추정
- how
  - 1-1) Saved, Binaries, Intermediate 폴더 삭제 후 Generate VS files 를 실행하는 Full rebuild로 해결
- proof
  - [Commit Link](https://github.com/semo21/ClickerGame/commit/d344ddf8722d59efc42e2f1ef5b94e0d5f129fa5)

## 10.02.25.
- what
  1. UISubsystem::EconomySubsystemRef 포인터 참조구조 변경.
- why
  - 1-1) GameInstnace Subsystem을 약참조할 필요가 없다고 판단.
  - 1-2) 약참조로 발생하는 필요없는 Get() 검증 코드 삭제
- how
  - 1-1) EconomySubsystemRef를 WeakPtr->ObjectPtr 타입으로 변경.
  - 1-2) 변경된 포인터 수준에 따라 기존 코드 일부 수정.
- proof
  - [Commit Link](https://github.com/semo21/ClickerGame/commit/a4848df3f3c56d05b98c0b1656dcfa7693237706)

## 10.03.25.
- what
  1. devlog, planning 문서 작성
- why
  - 1-1) 손목 부상, 컨디션 난조로 문서작성이 지연됐음
- how
  - 1-1) github과 기존 planning 문서 대조하며 작성
- proof
  - Commit Link

## 10.04.25.
- what
  1. 1Tick, Offline 재화지급 루틴 델리게이트로 일부 수정
- why
  - 1-1) 클래스별 책임분산을 명확히하기 위함
- how
  - 1-1) 재화를 지급하는 내용의 코드를 델리게이트 형식으로 변경중
- proof
  - [Commit Link](https://github.com/semo21/ClickerGame/commit/21bdf0093ac3e73ae3fc5cd2cc7f020f1c91c549)
  
## 10.13.25.
- what
  1. 1Tick, Offline 재화지급 부분 델리게이트 플로우로 변경
- why
  - 1-1) 클래스 별 책임 분산을 명확히하기 위함.
- how
  - 1-1) 델리게이트/콜백 플로우로 치환
- proof
  - [Commit Link](https://github.com/semo21/ClickerGame/commit/9b61625190184a8c079b71df65c9b8cf1855c1a7)

## 10.14.25.
- what
  1. 재화지급 플로우 델리게이트로 수정 마무리 중
- why
  - 1-1) 변경한 델리게이트 플로우에 최적화하기 위해서.
- how
  - 1-1) 필요없는 코드를 삭제
  - 1-2) 필요한 코드/함수를 생성
  - 1-3) 아직 미완
- proof
  - [Commit Link](https://github.com/semo21/ClickerGame/commit/3c8101c3047ac362193ffed6877883e555fda487)

## 10.20.25.
- what
  1. 오브젝트 풀링 생성 방식 변경
  2. 델리게이트 플로우 수정 진행중
  3. 코드 흐름 파악
- why
  - 1-1) 위젯별 풀링 생성/제거 방식이 통일되지 않은 상태였음
  - 2-1) 구조는 완성됐지만 아직 마무리 과정.
  - 3-1) 연휴와 개인 일정으로 놓친 작업 흐름 복구
- how
  - 1-1) UISubsystem의 오브젝트 풀링 함수 내용들 전면 수정 및 일부 삭제
  - 2-1) 델리게이트 콜백 메서드 추가
  - 3-1) 현재 집중중인 UISubsystem을 중심으로 코드 흐름 파악 후 오늘의 작업 진행
- proof
  - [Commit Link](https://github.com/semo21/ClickerGame/commit/a92477488140052df6cd81ce9570a4fe509d7f1f)

## 10.21.25.
- what
  1. 오브젝트 풀링 생성 방식 리팩터 완료
  2. IdleReward 텍스트 표기 오류 수정
  3. 게임 플로우 정상 작동 확인
- why
  - 1-1) Idle/Floating Text의 오브젝트 풀링 방식이 통일되지 않았음
  - 1-2) 둘의 방식을 통일하는 것이 유지보수와 가독성 측면에서 유리하다고 판단함
  - 2-1) IdleReward(PassiveIncome)가 "Offline Reward: $$"형식으로 의도되지 않은 형태로 출력되는 것을 확인
  - 3-1) 사소한 리팩터 후 게임 실행에 영향이 있는지 검사해야했음.
- how
  - 1-1) IdleWidget Pooling처럼 ShowHUD()함수에서 미리 10개씩 풀링하는 방식으로 진행
  - 1-2) 다만 FloatingText는 모자랄 수 있으므로 모자라다면 추가 생성하여 AddToViewport하고 풀에 Add하는 방식으로 추가 구조를 마련했음
  - 2-1) ShowReward()의 매개변수인 bIsOffline의 값이 의도와 다르게 설정된 것에서 발생했다고 추정
  - 2-2) bool값 분기를 찾아 수정 후 해결 확인.
  - 3-1) 라이브 코딩 후 게임실행하여 확인했음.
- proof
  - [Commit Link](https://github.com/semo21/ClickerGame/commit/4dfdac0f3e15940e0952e1e1b76733dba2efe003)

## 10.23.25.
- what
  1. ShowOffline 미표기 문제 해결
  2. UISubsystem::ShowFloatingText 리팩터 후 발생한 CreateLambda관련 에러 관련 해결
- why
  - 1-1) 실행 직후 Load하는데, Load시점에서 OfflineReward 보상이 더해지지만, UI로는 표시가 안되는 문제
  - 1-2) UISubsystem과 EconomySubsystem의 초기화 순서, 시점 문제였음
  - 2-1) 지난번 ObjectPooling 방식 통일 이후 해당 플로우에서 사용하는 CreateLambda함수 관련 에러 발생
  - 2-2) 클래스와 클래스 객체를 동시에 제공하여 안정성을 높이려다 발생한 에러라고 추정
- how
  - 1-1) MyPlayerController의 초기화 시점에서 각 객체를 먼저 생성.
  - 1-2) 두 객체가 모두 생성되었으면 Eco, UI 순으로 초기화 함수 실행.
  - 1-3) 이게 안정적인 방법이 맞는지는 내일 다시 검증 예정
  - 2-1) 기존엔 CreateLambda(ClassInstance) 형식으로 사용되던 함수를 리팩터함
  - 2-2) 리팩터 후 구조는 CreateLambda(Class, ClassInstance)타입의 매개변수로 실행
  - 2-3) 하지만 CreateLambda의 매개변수는 이런 타입을 사용할 수 없기에 CreateWeakLambda로 수정하여 해결
- proof
  - [Commit Link](https://github.com/semo21/ClickerGame/commit/6f6658c42666e7650ec211367d314e000cdc0d75)

## 10.24.25.
- what
  1. UI, Economy 서브시스템 초기화 코드 안정성 검토 완료
  2. 재화지급 플로우, 풀링 정책, 델리게이트 구현 구조 검토 완료
- why
  - 1-1) 작성한 코드가 잘못된 방향이 있거나, 추후에 수정해야만 하는 일회성 코드일 수 있으므로 안정성을 검토
  - 2-1) 이번 리팩터링 과정에서 구현한 결과물들이 합리적인 구조로 구현이 되었는지 안정성과 합리성을 확인하기 위해서 검토
- how
  - 1-1) GPT를 통한 초기화 부분 구현 사례, 합리성 검증 판단과 판단 근거, 출처를 추가 확인하여 검토
  - 2-1) 프로젝트 리팩터링 코드를 직접 순회하며 의심 파트를 검토
- proof
  - [Commit Link](https://github.com/semo21/ClickerGame/commit/6f6658c42666e7650ec211367d314e000cdc0d75)

## 10.28.25.
- what
  1. ShowOfflineText 미표기 현상 인지
  2. FloatingText 미표기 현상 인지 
- why
  - 1-1) 초기화 시점 문제로 추측중
  - 2-1) 클릭해도 FloatingText가 표기되지 않는 현상 발견
- how
  - 1-1) 내일 실행시점 재확인 예정
  - 1-2) 시점으로 해결 안된다면 추가 코드로 구현 예정
  - 2-1) Visualize 코드 누락으로 추측중
- proof
  - [Commit Link](https://github.com/semo21/ClickerGame/commit/349169fabf9457fe7305c68d57d745ccb5114d06)
  
## 10.29.25.
- what
  1. FloatingText 미표기 현상 해결 
  2. ShowOfflineText 미표기 현상 해결
- why
  - 1-1) 콜백 함수에 Collapsed된 Widget을 Visible로 바꾸는 코드 누락
  - 2-1) UI, Eco 초기화 시점으로 인한 문제
- how
  - 1-1) 받아온 Widget을 Visible로 설정하는 코드를 추가하여 해결
  - 2-1) 나중에 초기화되는 UI에서 OfflineReward를 Trigger하도록 변경
  - 2-2) 하지만 RequestLoad로 실행되는 위젯 재생이 아니므로 LoadButton을 클릭해도 ShowOfflineText는 실행되지 않게됨.
  - 2-3) 따라서 내일 이 부분 해결 예정
- proof
  - [Commit Link](https://github.com/semo21/ClickerGame/commit/71173cd699aa0460c5bd15eb813519d256f3fd5d)

## 10.30.25.
- what
  1. ShowOfflineReward 실행시/Load 버튼 클릭시 모두 출력되게 개선
  2. FloatingTextWidgetPool 활용방식 개선 진행 
- why
  - 1-1) 실행시 1회만 재생되거나, 실행시 재생안되고 Load 클릭시에만 재생되는 현상이었음
  - 2-1) FloatingText를 불러와 재생하는 과정에서 애니메이션 종료처리가 불분명하여 위젯이 풀에 존재함에도 부족하다고 판단하여 계속해서 새로운 위젯을 생성하는 현상이었음
- how
  - 1-1) 초기화 때 Trigger함수로 재생시키고, 이후 Load버튼 클릭시엔 기존과 같이 RequestLoad를 통해 재생하도록 개선
  - 2-1) FloatingTextWidget에 애니메이션 재생 함수, 사용가능여부 함수 작성중
- proof
  - [Commit Link](https://github.com/semo21/ClickerGame/commit/ff4b0df972371f07bc6248c8f64b3936712e45ad)

## 11.03.25.
- what
  1. FloatingTextWidgetPool 재사용 가능하도록 리팩터 진행중 
- why
  - 1-1) FloatingTextWidget이 현재 재사용이 불가능함.
  - 1-2) FloatingTextWidget의 애니메이션이 끝났다는 것을 제대로 받아오지 못하는 것으로 추측
- how
  - 1-1) FloatingTextWidget 자체에서 애니메이션이 끝나면 델리게이트 콜백으로 사용가능 상태 전환
  - 1-2) UIManager에서 해당 Widget의 사용가능 여부로 판단하여 재활용
  - 1-3) 현재 델리게이트 바인딩 구현부에서 문법 오류 해결중
- proof
  - [Commit Link](https://github.com/semo21/ClickerGame/commit/8fc1b1d6812e1c101c8bc3927cdcab4e66c21f49)

## 11.04.25.
- what
  1. FloatingTextWidget Pool 리팩터 완료
  2. OfflineReward 누적 8시간 제한 구현 
  3. 기존 브랜치 머지 후 새로운 작업 브랜치 생성
- why
  - 1-1) 사용 가능한 Pool의 위젯을 재활용하지 못하는 현상 해결
  - 2-1) 문서에 선언했던대로 구현
  - 3-1) 기존 브랜치에 지나치게 여러 작업을 했기에 앞으로 작업별로 브랜치를 생성해서 사용할 예정
- how
  - 1-1) ClickFloatingText 클래스에서 애니메이션을 재생
  - 1-2) 재생이 끝나면 사용 가능 상태를 표시하는 bool멤버를 전환하는 콜백 함수를 실행
  - 2-1) EconomySubsystem의 LastOfflineReward를 저장하는 부분에서 수식 수정
  - 3-1) feature/refactor 브랜치 머지 후 feature/refactor-toastwidget 브랜치 생성
- proof
  - [Commit Link](https://github.com/semo21/ClickerGame/commit/fe06b1736ce2fd4e47465cf0a72af88e3812b769)

## 11.05.25.
- what
  1. ToastWidgetBase 클래스 생성 후 공용 코드 작성 
- why
  - 1-1) 이후 비슷하지만 조금 달느 위젯을 만들거나, 현재 존재하는 위젯 관리의 유연성을 위해 상속구조로 개편하기로 결정
- how
  - 1-1) ToastWidgetBase라는 Toast Widget들의 부모클래스를 만들어 공용 코드를 작성했음.
  - 1-2) 이후 추가로 상속을 구현할 예정
- proof
  - [Commit Link](https://github.com/semo21/ClickerGame/commit/8da8857bd106d74b11fb4a08b7ed9d5685bd6278)

## 11.06.25.
- what
  1. Floating, Idle Widget, UIManager 코드 수정 
- why
  - 1-1) ToastWidgetBase 상속구조를 활용함에 따라 코드 정리 및 수정
- how
  - 1-1) Idle, Floating Widget 상속 부모 변경
  - 1-2) UIManger의 코드 수정중.
- proof
  - [Commit Link](https://github.com/semo21/ClickerGame/commit/3efd7ab1465bf93e4887c7d33f1b9bd6352b762c)

## 11.07.25.
- what
  1. UISubsystem 리팩터링 진행중 
- why
  - 1-1) ToastWidgetBase 기반 위젯 플로우 개편중
- how
  - 1-1) UISubsystem 리팩터 진행중
- proof
  - [Commit Link](https://github.com/semo21/ClickerGame/commit/5b806294e995585b09c7aa9e751670711a0fb5d6)

## 11.10.25.
- what
  1. ToastWidgetBase 기반 상속구조 코드 리팩터 완료 
- why
  - 1-1) 추후 범용성 및 유지보수에 적합
- how
  - 1-1) 코드구현은 완료했음
  - 1-2) 하지만 에디터에서 WBP 설정 관련 오류 발생
- proof
  - [Commit Link](https://github.com/semo21/ClickerGame/commit/9df1063c6860bc7414e333c26163a10d839b73af)

## 11.11.25.
- what
  1. WBP 에러 해결 
  2. Assertion Crash 해결
  3. ToastWidget과 UI관련 버그 해결
- why
  - 1-1) C++클래스에서 설정한 변수, 에디터 WBP에서의 Animation, TextBlock의 이름이 서로 달라서 발생한 에러 
  - 2-1) ToastWidget 상속구조 리팩터 과정에서 발생한 유령캐시로 추정
  - 3-1) Toast Widget과 HUD의 Z Order, ToastWidget의 Hit 설정을 잘못함.
- how
  - 1-1) 대응되는 요소들의 이름을 일치시켜주며 해결했음
  - 2-1) Clean build를 통해 캐시 정리 후 해결
  - 3-1) ToastWidget의 상태를 Visible -> SelfHitTestInvisible로 변경 후 해결
- proof
  - [Commit Link](https://github.com/semo21/ClickerGame/commit/fe41bb76db829d72e534aad0cb60232ca34ceb3c)

## 11.12.25.
- what
  1. 문서 갱신 시작
     - system_ui.md 문서 진행
- why
  - 1-1) 현재 게임이 안정적으로 실행되는 것을 확인했으며 지난 PR에 비해 바뀐 구조가 많으므로 문서 갱신이 필요함
- how
  - 1-1) system_ui 문서 갱신 진행
- proof
  - [Commit Link](https://github.com/semo21/ClickerGame/commit/eed91c247c5f38ca1946f08ba826ca1eeea230e4)

## 11.13.25.
- what
  1. feature/refactor-toastwidget브랜치 정리 후 dev 브랜치 생성
- why
  - 1-1) 브랜치 구조를 개편하기 위해서
  - 1-2) 수행하는 작업별(문서 정리, 기능구현, 리팩터 등)로 분리하는 편이 앞으로 개발에 더욱 좋을 것이라 판단
  - 1-3) 협업 구조를 더욱 잘 이해하기 위해서
- how
  - 1-1) feature/refactor-toastwidget브랜치를 커밋
  - 1-2) 커밋된 내용을 main에서 머지시킴
  - 1-3) feature/refactor-toastwidget브랜치 삭제
  - 1-4) 갱신된 main의 내용을 바탕으로 dev브랜치 생성
  - 1-5) dev브랜치를 github레포에 연결
- proof
  - [Commit Link](https://github.com/semo21/ClickerGame/commit/2f9a9140e5998af101da097f4593d279d4b725f3)

## 11.14.25.
- what
  1. 일일계획 자동화 프로그램 생성
- why
  - 1-1) 장기적 작업 능률 향상 목표
- how
  - 1-1) .bat프로그램으로 vscode가 부팅 시 열리도록 구현
- proof
  - [Commit Link](https://github.com/semo21/ClickerGame/commit/cceb0339708c3f4d9d5f3010ee8b1a91c6de1510)

## 11.15.25.
- what
  1. 일지 기본양식 형태로 자동 생성 및 시작 프로그램 구현 
- why
  - 1-1) 장기적 작업 능률 향상 목표
- how
  - 1-1) powershell을 이용하여 Daily Log의 양식을 자동 입력 및 당일 일지 파일 생성하도록 구현
- proof
  - [Commit Link](https://github.com/semo21/ClickerGame/commit/e9087794bbf9862ae2eed2d94aec9681633eb0e0)

## 11.16.25.
- what
  1. 자동화 프로그램의 오류 수정 
- why
  - 1-1) 텍스트 깨짐, 날짜 미수정 현상
- how
  - 1-1) UTF-8형식으로 설정, 날짜 갱신 로직 수정
- proof
  - [Commit Link](https://github.com/semo21/ClickerGame/commit/0c3ed53feae17728c77fb5fb2dad5b19dcfb41a3)

## 11.20.25.
- what
  1. design\system\system_ui.md 문서 갱신
- why
  - 1-1) 완료된 리팩터 부분 문서에 갱신
- how
  - 1-1) system_ui문서 갱신
- proof
  - [Commit Link](https://github.com/semo21/ClickerGame/commit/3a6d25e46dcf94646da1f8c354ef9d0a82ddd7d0)

## 11.24.25.
- what
  1. WIP - architecture_overview 문서 수정
- why
  - 1-1) system_ui.md 의 일부 내용이 architecture_overview에 보다 적합하여 내용 이전 및 갱신
- how
  - 1-1) 주요 시퀀스 내용 갱신
- proof
  - [Commit Link](https://github.com/semo21/ClickerGame/commit/c016190c10b058da24caad859a4c7c271c6885e0)

## 11.25.25.
- what
  1. WIP - architecture_overview 문서 수정
  2. 일지 자동화 프로그램 내용 일부 수정
- why
  - 1-1) system_ui.md 의 일부 내용이 architecture_overview에 보다 적합하여 내용 이전 및 갱신
  - 2-1) 갱신될 때마다 개행문자가 추가되고 있는 현상을 발견
- how
  - 1-1) 주요 시퀀스 내용 갱신
  - 2-1) 전 날 문서 내용을 복사하는 과정에서 Trim함수를 사용하여 끝 부분의 필요없는 개행문자를 제거
- proof
  - [Commt Link](https://github.com/semo21/ClickerGame/commit/360961ca5dbac120c44f363c047758531bd35cd8)

## 11.26.25.
- what
  1. 문서 갱신 
     1. WIP - architecture_overview 갱신
     2. WIP - system_ui 갱신
- why
  - 1-1) 리팩터 완료 이후 문서 갱신
  - 1-2) 추후 유지/보수에 용이한 흐름 추적을 위하여 작성
- how
  - 1-1) architecture_overview의 Major Sequences 갱신 완료
  - 1-2) system_ui의 EventFlow 갱신 시작
- proof
  - [Commit Link](https://github.com/semo21/ClickerGame/commit/faad0f3365a4614eda567842097dd3a0f4c709bc)

## 11.27.25.
- what
  1. 일지 자동화 스크립트 오류 수정 
- why
  - 1-1) powershell 스크립트 문법 오류
- how
  - 1-1) 문법 오류부분을 수정하여 해결
- proof
  - [Commit Link](https://github.com/semo21/ClickerGame/commit/e42012bfe4635f3e6aab25f8575364d99d8ded84)

## 11.28.25.
- what
  1. system_ui.md의 Event Flow부분 갱신 
- why
  - 1-1) 기존의 내용이 design문서로선 필요 이상으로 상세하게 기술되었음.
- how
  - 1-1) 기존의 흐름은 기록하되, 흐름의 디테일(함수나 클래스 명, 매개변수 타입 등)을 생략하여 흐름위주로 작성
- proof
  - [Commit Link](https://github.com/semo21/ClickerGame/commit/a9556e868c620ac55de39c689fc2aeb7281ae13f)

## 11.29.25
- what
  1. system_ui.md의 2. UI Layouts와 3. Widget Pool Policy 부분 수정
- why
  - 1-1) 리팩터하며 흐름이 살짝 변경되었고, 기존 내용은 중복되는 부분이 있었음
- how
  - 1-1) 바뀐 흐름 갱신과 중복되는 내용들 간소화
- proof
  - [Commit Link](https://github.com/semo21/ClickerGame/commit/b13a28698eba28fc61f776cd8ebbd8e02102e82b)

## 11.30.25.
- what
  1. system_ui.md 갱신 완료 
- why
  - 1-1) 리팩터하며 변경된 흐름 반영
  - 1-2) 문서 내용 최적화
- how
  - 1-1) 전체 오탈자 검수
  - 1-2) 5. Data Asset 갱신
- proof
  - [Commit Link](https://github.com/semo21/ClickerGame/commit/457bc7b775c832768c759068f06b10576371e11f)

## 12.01.25.
- what
  1. architecture_overview 갱신중 
- why
  - 1-1) 리팩터하며 변경된 흐름 반영
  - 1-2) 문서 내용 최적화
- how
  - 1-1) 3~6 챕터 수정
- proof
  - [Commit Link](https://github.com/semo21/ClickerGame/commit/5a2d1bc881410509aac0dc98c6b371f8b7c91349)

## 12.02.25.
- what
  1. architecture_overview 업데이트
- why
  - 1-1) 리팩터하며 변경된 흐름 반영
- how
  - 1-1) 문서 구조 정리 및 표현 개선
- proof
  - [Commit Link](https://github.com/semo21/ClickerGame/commit/d9f75a12ce0858d0b12a7b56f2295fbeb8bdbee8)

## 12.08.25.
- what
  1. WIP - update api_reference  
  2. 지난 일지 내용 수정 및 보완
  3. 주간 일지 작성
- why
  - 1-1) 리팩터 후 전체 문서 갱신중
  - 2-1) 일지 내용이 부정확했던 점을 발견
- how
  - 1-1) 시작 ~ 챕터 2 업데이트
  - 1-2) 추후 1, 2챕터 내용 추가 보완 필요
- proof
  - [Commit Link](https://github.com/semo21/ClickerGame/commit/2af0ddc06180b0d1955bd031fa41f3ccbbb174a5)

## 12.09.25.
- what
  1. WIP - update api_reference 
- why
  - 1-1) 리팩터 후 전체 문서 갱신중
- how
  - 1-1) 개요 내용 일부 수정
- proof
  - Commit Link