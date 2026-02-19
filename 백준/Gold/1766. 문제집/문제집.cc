#include <bits/stdc++.h>

using namespace std;

int N,M;
// 사이클 검사 필요없다.
vector<vector<int>> adj;
vector<int> in_degree;
void init(){
    cin >> N >> M;
    adj.assign(N+1,{});
    in_degree.assign(N+1,0);

    for(int i=0; i<M; i++){
        int from, to;
        cin >> from >> to;

        adj[from].push_back(to);
        in_degree[to]++;
    }
} 

void solution(){
    priority_queue<int,vector<int>,greater<int>> pq;
    vector<int> ans;
    for(int i=1; i<=N; i++){
        if(in_degree[i] == 0) pq.push(i);
    }

    /**
     * 그냥 넣으면 망함
     */
    while(!pq.empty()){
        int node = pq.top(); pq.pop();
        ans.push_back(node);

        for(auto& nxt: adj[node]){
            in_degree[nxt]--;
            if(in_degree[nxt] == 0) pq.push(nxt);
        }
    }

    for(int &node : ans) cout << node << " ";
}
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    init();
    solution();
}