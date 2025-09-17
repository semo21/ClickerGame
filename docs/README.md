# Clicker Game

Unreal Engine 5 C++로 개발된 Idle/Clicker Game의 프로토타입.
핵심 시스템을 C++로 구현했으며, 기획/설계를 문서화했음.

## 프로젝트 목적
- 학습/포트폴리오 목적

## 주요 기능
- 클릭을 통한 재화 획득
- 업그레이드 시스템 (CPS, CPC 증가)
- 오프라인 보상 (최대 16시간)
- UI 풀링 (위젯 재사용)
- Save/Load 시스템

## 개발 환경
- Unreal Engine 5.4.4
- Visual Studio 2022 (Windows)
- C++

## 빌드/실행
1. '.uproject' 우클릭 -> Generate Visual Studio project files
2. 'ClickerGame.sln' 실행 -> Development Editor / Win 64 빌드
3. Unreal Editor 실행

## 문서
1. design
   - [Game Design](docs/design/game_design.md)
   - [Economy System](docs/design/system/system_economy.md)
   - [UI System](docs/design/system/system_ui.md)
2. tech
   - [API Reference](docs/tech/api_reference.md)
   - [Architecture Overview](docs/tech/architecture_overview.md)
3. logs
   - [Changelog](docs/logs/changelog.md)
4. diary
   - [Devlog](docs/diary/devlog.md)
5. testing
   - [Test Cases](docs/testing/test_cases.md)
6. release
   - 빌드/릴리즈 노트
