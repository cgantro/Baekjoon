#include <bits/stdc++.h>

using namespace std;

int N,M;
vector<vector<int>> pds_pick;
vector<vector<int>> adj;
vector<int> in_degree;
vector<int> visited;

void init(){
    pds_pick.resize(M);
    adj.assign(N+1,{});
    in_degree.assign(N+1,0);
    visited.assign(N+1,0);
    for(int i=0; i<M; i++){
        int k; cin >> k;
        pds_pick[i].resize(k);
        for(int j=0; j<k; j++){
            cin >> pds_pick[i][j];
        }
    }

    for(auto &pd: pds_pick){
        for(int i=0; i<(int)pd.size()-1;i++){
            int from, to;
            from = pd[i];
            to = pd[i+1];

            adj[from].push_back(to);
            in_degree[to]++;
        }
    }
}

bool checkCycle(const int& node){
    visited[node] = 1;

    for(auto &nxt: adj[node]){
        if(visited[nxt] == 0) {
            if(checkCycle(nxt)) return true;
        }else if(visited[nxt] == 1){
            return true;
        }
    }
    visited[node] = 2;
    return false;
}

void Topology(){
    queue<int> q;
    vector<int> answer;
    for(int i=1; i<=N; i++){
        if(in_degree[i] == 0) q.push(i);
    }

    while(!q.empty()){
        int node = q.front(); q.pop();
        answer.push_back(node);

        for(auto nxt : adj[node]){
            in_degree[nxt]--;
            if(in_degree[nxt] == 0)q.push(nxt);
        }
    }

    for(int &node : answer) cout << node << '\n';
}
void solution(){
    for(int i=1; i<=N; i++){
        if(visited[i]) continue;
        if(checkCycle(i)){
            cout << 0 << '\n'; return ;
        }
    }

    Topology();
}
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    cin >> N >> M;
    init();
    solution();
}