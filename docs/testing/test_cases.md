# Test Cases
## A. 세이브/로드 & 오프라인 보상
1. [ ] 첫 실행(세이브 슬롯 없음)
    - Steps: 
      - 슬롯 삭제 
      - -> 실행 
      - -> 자동 저장 
      - -> 즉시 재실행
2. [ ] 짧은 오프라인(10초)
    - Steps: 
      - 실행 
      - -> 저장 
      - -> 10초 후 재실행
    - Expect: 
      - 보상 = CPS * 10s * 0.5
      - 적용 직후 즉시 저장되어 재실행하면 보상 0.
3. [ ] 장시간 오프라인(4시간)
    - Expect: 
      - 보상 = CPS * 4h * 0.5, 적용 후 즉시 저장
4. [ ] 상한 초과(24시간)
    - Expect: 
      - 보상은 16h로 고정된 값 지급, 적용 후 즉시 저장.
5. [ ] 시간 이상치(미래 +5분 초과 / LastSaveTime <= 0)
    - Steps: 
      - SaveTime 조작 
      - -> 실행
    - Expect: 
      - 보상 0, LastSaveTime = now로 교정.
6. [ ] 중복 적용 방지
    - Steps: 
      - 보상 적용 직후 연속으로 RequestLoad() 3회
    - Expect: 
      - 첫 호출만 보상, 이후 0(Load 후 즉시 저장하기 때문)
## B. UI/풀(Idle & Floating)
1. [ ] 중복 Add 방지
    - Steps: 
      - 1초 내 3회 토스트 요청
    - Expect: 
      - "Already added" 로그 0회
      - 각 위젯은 최초 1회만 Add, 재사용 시 Visible/Collapsed 토글.
2. [ ] 애니메이션 종료 반남
    - Steps: 
      - 토스트 재생 
      - -> 종료
    - Expect: 
      - bInUse=false, Collapsed, 다음 요청에 재사용.
3. [ ] 동시 2개 재생
    - Steps: 
      - 속도 느리게 설정 
      - -> 연속 2개 재생
    - Expect: 
      - 서로 다른 인스턴스 사용, Warning/Assertion 없도록.
## C. 안정성/회귀
1. [ ] CreateWidget 타입 가드
    - Steps: 
      - HUD/Idle/Floating 생성 경로에서 IsChildOf 가드 유지
    - Expect: 
      - 잘못된 클래스 지정 시 크래시 대신 ensure경고
2. [ ] 퍼포먼스 체크
    - Steps: 
      - 10분 플레이(초당 5~10 클릭)
    - Expect: 
      - 60프레임 유지
      - 로그 경고 없음, 메모리 급증 없음
3. [ ] 10분 플레이
   - Steps:
      - 10분 이상 플레이
   - Expect:
   - 경고 및 Assertion 크래시 없는 상태.

## 기타
- changelog.md 반영, 설계 문서 최신화