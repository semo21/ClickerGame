# Economy System Spec (Design)

## 1. 의도
- 게임의 경제 시스템 흐름을 문서화.
- 수식 변경/추가 시 가이드라인을 제공하기 위함.

## 2. 경제 시스템 목적
- 짧은 세션에서도 성취감, 오프라인 보상으로 복귀 유도.

## 3. 핵심 루프

1. 클릭 -> Currency 획득
2. 업그레이드 구매 -> CPS 증가
3. 오프라인 보상 수령 -> 루프 재진입

## 4. 수식/규칙

- CPC = f(UpgradeLevel) = Base \* L
- CPS = f(UpgradeLevel) = Base \* L
- 오프라인 보상 = CPS \* 오프라인시간(초)
  - 오프라인 보상 누적 제한: 8시간
- 업그레이드 티어별 수치:
  - 업그레이드 비용:
    - Cost = BaseCost * Growth^Level(예시)
  - 추가 작성 예정

## 5. 핵심 구조(미구현)

- 업그레이드 10티어, 각 5레벨
- 업그레이드 비용 지수식 성장

## 6. UX 플로우
- 첫 진입 
  1. 튜토리얼 
  2. 첫 보상 토스트 
  3. 업그레이드 안내
- 게임 플레이 루프
  1. 클릭
  2. 업그레이드
  3. 세이브/로드
  4. 오프라인 보상 
  5. economy 갱신
  6. UI갱신

## 7. 데이터 모델
- EconomySnapshot
  - 구조체 데이터 모델
  - 위치: ClickerEconomySubsystem.h 상단에 선언
  - 멤버:
    1. UpgradeLevel: 업그레이드 진척도
    2. Currency: 현재 보유한 재화
    3. Currency Per Click: 클릭 당 재화 획득량
    4. Currency Per Second: 초당 재화 자동 획득량
    5. UpgradeCostBase: 업그레이드 비용 베이스
    6. UpgradeGrowth: 업그레이드 비용 계수
    7. LastSaveTime: 마지막 저장한 시각(int64 Unix) 
    

