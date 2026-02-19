# [Gold II] 보석 도둑 - 1202 

[문제 링크](https://www.acmicpc.net/problem/1202) 

### 성능 요약

메모리: 20236 KB, 시간: 208 ms

### 분류

자료 구조, 그리디 알고리즘, 정렬, 우선순위 큐

### 제출 일자

2026년 2월 19일 14:46:32

### 문제 설명

<p>세계적인 도둑 상덕이는 보석점을 털기로 결심했다.</p>

<p>상덕이가 털 보석점에는 보석이 총 N개 있다. 각 보석은 무게 M<sub>i</sub>와 가격 V<sub>i</sub>를 가지고 있다. 상덕이는 가방을 K개 가지고 있고, 각 가방에 담을 수 있는 최대 무게는 C<sub>i</sub>이다. 가방에는 최대 한 개의 보석만 넣을 수 있다.</p>

<p>상덕이가 훔칠 수 있는 보석의 최대 가격을 구하는 프로그램을 작성하시오.</p>

### 입력 

 <p>첫째 줄에 N과 K가 주어진다. (1 ≤ N, K ≤ 300,000)</p>

<p>다음 N개 줄에는 각 보석의 정보 M<sub>i</sub>와 V<sub>i</sub>가 주어진다. (0 ≤ M<sub>i</sub>, V<sub>i</sub> ≤ 1,000,000)</p>

<p>다음 K개 줄에는 가방에 담을 수 있는 최대 무게 C<sub>i</sub>가 주어진다. (1 ≤ C<sub>i</sub> ≤ 100,000,000)</p>

<p>모든 숫자는 양의 정수이다.</p>

### 출력 

 <p>첫째 줄에 상덕이가 훔칠 수 있는 보석 가격의 합의 최댓값을 출력한다.</p>

## AI 코드 리뷰

<template>

### 코드 리뷰
```cpp
#include <bits/stdc++.h>

using namespace std;
int N, K;
const int MAX_ = 300000;
struct Jewel {
    int weight;
    int value;

    bool operator>(const Jewel& other) const {
        if (value != other.value) return value < other.value;
        return weight > other.weight;
    }
};

priority_queue<Jewel, vector<Jewel>, greater<Jewel>> pq_jewel;
multiset<int> bag;

void init() {
    cin >> N >> K;
    for (int i = 0; i < N; i++) {
        int w, v;
        cin >> w >> v;
        Jewel jw = {w, v};
        pq_jewel.push(jw);
    }
    for (int i = 0; i < K; i++) {
        int capacity; cin >> capacity;
        bag.insert(capacity);
    }
}

long long solution() {
    long long ans = 0;

    int bag_idx = 0;
    while (!(pq_jewel.empty() || bag.empty())) {
        Jewel target = pq_jewel.top(); pq_jewel.pop();
        auto it = bag.lower_bound(target.weight);
        if (*it < target.weight) continue;
        ans += target.value;
        bag.erase(it);
    }
    return ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    init();
    cout << solution();
}
```
이 코드는 보석 도둑 문제를 해결하기 위해 작성되었습니다. 보석과 가방의 정보를 입력받아 각 가방에 담을 수 있는 최대 가치를 계산하는 프로그램입니다. `Jewel` 구조체는 보석의 무게와 가치를 저장하며, 우선순위 큐를 사용하여 가장 가치가 높은 보석을 먼저 선택합니다. `multiset`를 사용하여 가방의 최대 용량을 관리하며, 해당 가방에 담을 수 있는 가장 무게가 적은 보석을 찾아서 값을 추가합니다.

1. **코드 블록 1**: 구조체와 전역 변수 선언
   - `Jewel` 구조체는 보석의 무게와 가치를 나타내며, `operator>`를 오버로드하여 가치를 기준으로 정렬합니다. 
   - 우선순위 큐 `pq_jewel`은 보석을 가치가 높은 순서로 저장합니다.

2. **코드 블록 2**: `init()` 함수
   - 보석 수 `N`과 가방 수 `K`를 입력받고, 보석과 가방의 정보를 각각 우선순위 큐와 다중 집합에 저장합니다.

3. **코드 블록 3**: `solution()` 함수
   - 보석이 남아있고 가방이 남아있는 동안, 가장 가치가 높은 보석을 꺼내어 해당 보석을 담을 수 있는 가방을 찾습니다. 가방의 무게가 보석의 무게보다 크거나 같으면, 그 보석의 가치를 총합에 추가하고 해당 가방을 제거합니다.

### 시간/공간 복잡도 분석
- **시간 복잡도**:
  - 보석과 가방을 입력받는 과정: `O(N + K)`
  - 보석을 우선순위 큐에서 꺼내고 가방을 검사하는 과정: 최악의 경우 `O(N log N + K log K)` (우선순위 큐에서의 삽입 및 삭제)입니다.
  - 전체 시간 복잡도는 `O(N log N + K log K)`로 나타낼 수 있습니다.

- **공간 복잡도**:
  - `priority_queue`와 `multiset`의 공간 사용량은 각각 `O(N)`과 `O(K)`입니다.
  - 따라서 전체 공간 복잡도는 `O(N + K)`입니다.

### 코드 최적화 가능성 및 개선 제안
- **최적화 가능성**:
  - 현재 코드 구조는 잘 작성되어 있으며, 우선순위 큐와 다중 집합을 사용하여 문제를 효과적으로 해결하고 있습니다. 따라서 최적화는 필요하지 않습니다.
  
- **개선 제안**:
  - `operator>`의 경우, 복잡도를 줄이기 위해 `std::greater<Jewel>`를 직접 사용하면 가독성이 높아질 수 있습니다.
  - `init()` 함수에서 입력을 받을 때, 직접 `cin`을 사용하는 대신, `std::vector`를 사용하여 후에 정렬할 수도 있습니다. 이 경우 가방의 최대 무게를 직접 정렬하는 것이 성능에 영향을 줄 수 있습니다.
  - 코드의 가독성을 높이기 위해 주석을 추가하여 각 코드 블록의 목적을 설명하는 것이 좋습니다.

- **가독성 및 유지보수성**:
  - 전반적으로 코드가 명확하고 의도가 분명하므로 가독성이 좋습니다. 그러나 각 함수의 역할과 입력/출력에 대한 설명을 주석으로 추가하면 유지보수성이 더욱 향상될 것입니다.

</template>

