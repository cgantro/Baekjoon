#include <bits/stdc++.h>

using namespace std;
int N, K;
const int MAX_ = 300000;
struct Jewel{
    int weight;
    int value;

    bool operator>(const Jewel& other) const{
        if(value != other.value) return value < other.value;
        return weight > other.weight;
    }
};

priority_queue<Jewel,vector<Jewel>, greater<Jewel>> pq_jewel;
multiset<int> bag;

void init(){
    cin >> N >> K;
    for(int i=0; i<N; i++){
        int w,v;
        cin >> w >> v;
        Jewel jw = {w,v};
        pq_jewel.push(jw);
    }
    for(int i=0; i<K; i++){
        int capacity; cin >> capacity;
        bag.insert(capacity);
    }


    // for(int a : bag) cout << a << '\n';
}

long long solution(){
    long long ans = 0;

    int bag_idx = 0;
    while(!(pq_jewel.empty() || bag.empty())){
        Jewel target = pq_jewel.top(); pq_jewel.pop();
        auto it = bag.lower_bound(target.weight);
        if(*it < target.weight) continue;
        ans += target.value;
        bag.erase(it);
    }
    return ans;
}
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    init();
    cout << solution();
}