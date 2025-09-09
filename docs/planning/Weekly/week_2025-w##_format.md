# Week YYYY-W## Format(Example)

## Theme / Focus

- 이번주 집중 주제

## Big Rocks (Now)

- [P1][S] 오프라인 보상 30초 계산 적용 (DoD: A1~A6 통과)
- [P1][M] UI 토스트 풀 정책 A 일괄 적용, 재-Add 금지 가드

## Commit (이번 주 반드시 끝낼 목록)

- [ ] Economy::RequestLoad 오프라인 계산 + 수령 후 즉시 저장
- [ ] Idle/Floating 위젯 OnFinished 반납 루틴
- [ ] CreateWidget 타입 가드 삽입(모든 생성 지점)

## Stretch (여유 있으면)

- [ ] UISettings 폴백 로딩 경로
- [ ] changelog 템플릿 자동화

## Risks & Mitigations

- Live Coding 후 유령 BPGC -> 콜드빌드 루틴 수행
- 위젯 풀 포화 -> 풀 크기 상한 + 스로틀

## Demo / DoD (주간 체크)

- 10분 플레이 무경고(Perf Smoke 통과)
- A1~A6, B1~B3, C1~C2 테스트 체크리스트 통과
- changelog/문서 갱신

## Carry-over (지난 주 이월)

- 항목 1, 2 ...

## Legend

```
# Priority Tags
[P0]: 지금 당장 막힌 치명적 이슈 (ex. Assertion 크래시)
[P1]: 이번 사이클에 반드시 끝낼 항목
[P2]: 하면 좋음
[P3]: 나중에

# Size Tags
[S]: 반나절~1일
[M]: 1~2일
[L]: 3~5일
```
