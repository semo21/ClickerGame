# 게임 기획 문서

Scope: 싱글 플레이 오프라인 보상형 클릭커(Windows/UE5.4). HUD, 업그레이드, 세이브, 오프라인 보상 포함. 멀티,네트워크,IAP 제외.

## 1. Goals

- 핵심: 
```
클릭 -> 재화 -> 업그레이드 -> 오프라인 보상
```
이어지는 "짧은 세션 성취감" 제공
- 포트폴리오: 타인이 리소스만 교체해도 동작하는 모듈형 코드 구조(디자이너 친화)
- 학습: UE5 개발/릴리즈 파이프라인(스팀 빌드/배포) 이해

## 2. Out of Scope

- 멀티 플레이
- 서버 동기화
- 결제(IAP)
- 라이브 서비스

## 3. Target/Platforms

- Windows(PC), Android
- Unreal Engine 5 개발
- 싱글 플레이

## 4. 플레이어 약속

- 5분만 해도 업그레이드 한 단계, 복귀하면 오프라인 보상으로 바로 성장

## 5. 핵심 루프 / 세션 루프

1. 클릭하여 Currency 획득
2. 업그레이드 구매로 CPC/CPS 상승
3. 오프라인 보상 수령 -> 다시 업그레이드

## 6. 시스템(Design spec)

- 경제(Economy)
  - CPC(L) = CPC₀ + 1.0 \* L
  - CPS(L) = CPS₀ + 0.5 \* L
  - 업그레이드 비용: GetUpgradeCost(L) (지수 곡선 예정)
- 오프라인 보상
  - 의도: 1/2효율로 지급(최소 5분, 최대 16시간)
- UI
  - HUD(재화,CPC,CPS), 토스트(Idle/Floating)
  - 위젯 풀 정책 A: 최초 1회 Add -> Visible/Collapsed 토글(재-Add 금지)

## 7. UX 플로우(첫 진입)

튜토리얼 클릭 -> 업그레이드 안내 -> 첫 오프라인 보상 토스트 -> 루프 진입

## 8. 요구사항(Requirements)

- 필수
  - 클릭/업그레이드/오프라인 보상 루프 동작
  - 세이브/로드(슬롯 1개), 시간 교정 & 16h 상한
  - 위젯 풀 경고/Assertion 크래시가 나지 않는 상태
- 권장
  - 비용 곡선 파라미터화
  - 최소 10분 무경고 플레이
- 고려
  - 사운드/이펙트, 업그레이드 티어 세분화, 광고
- 예정 없음
  - 멀티/네트워크/인 앱 결제

## 9. 완료 기준(DoD)

- 테스트 케이스 통과
  - A. 세이브/로드 & 오프라인 보상
    1. 첫 실행(세이브 슬롯 없음)
       - Steps: 슬롯 삭제 -> 실행 -> 자동 저장 -> 즉시 재실행
    2. 짧은 오프라인(10초)
       - Steps: 실행 -> 저장 -> 10초 후 재실행
       - Expect: 보상 = CPS _ 10s _ 0.5, 적용 직후 즉시 저장되어 재실행하면 보상 0.
    3. 장시간 오프라인(4시간)
       - Expect: 보상 = CPS _ 4h _ 0.5, 적용 후 즉시 저장
    4. 상한 초과(24시간)
       - Expect: 보상은 16h로 고정된 값 지급, 적용 후 즉시 저장.
    5. 시간 이상치(미래 +5분 초과 / LastSaveTime <= 0)
       - Steps: SaveTime 조작 -> 실행
       - Expect: 보상 0, LastSaveTime = now로 교정.
    6. 중복 적용 방지
       - Steps: 보상 적용 직후 연속으로 RequestLoad() 3회
       - Expect: 첫 호출만 보상, 이후 0(Load 후 즉시 저장하기 때문)
  - B. UI/풀(Idle & Floating)
    1. 중복 Add 방지
       - Steps: 1초 내 3회 토스트 요청
       - Expcet: "already added" 로그 0회, 각 위젯은 최초 1회만 Add, 재사용 시 Visible/Collapsed 토글.
    2. 애니메이션 종료 반남
       - Steps: 토스트 재생 -> 종료
       - Expcet: bInUse=false, Collapsed, 다음 요청에 재사용.
    3. 동시 2개 재생
       - Steps: 속도 느리게 설정 -> 연속 2개 재생
       - Expect: 서로 다른 인스턴스 사용, Warning/Assertion 없도록.
  - C. 안정성/회귀
    1. CreateWidget 타입 가드
       - Steps: HUD/Idle/Floating 생성 경로에서 IsChildOf 가드 유지
       - Expect: 잘못된 클래스 지정 시 크래시 대신 ensure경고
    2. Performance Smoke
       - Steps: 10분 플레이(초당 5~10 클릭)
       - Expect: 프레임 저하/로그 경고 없음, 메모리 급증 없음
- 10분 플레이 경고 및 Assertion 크래시 없는 상태.
- changelog.md 반영, 설계 문서 최신화

## 출처

1. UE5 C++

   - GPT
   - 언리얼 개발자 포럼
   - 레딧
   - 기타 블로그

2. Graphics

   - Fab 

3. Team

   - 1인 개발
