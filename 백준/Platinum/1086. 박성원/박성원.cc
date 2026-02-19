#include <bits/stdc++.h>

using namespace std;
const int max_n = 15;
const int max_len = 50;
unsigned long long denominator;
int N, K;

string nums[max_n];
unsigned long long nums_mod[max_n];
unsigned long long ten_mod[max_len+1]; // 1, 10, 100 ... % K 저장
unsigned long long dp[1<<15][101];

/**
 * @brief 300%8을 한다 가정했을때
 * 300 % 8 = (3 % 8) = 3 mod
 *          (3(mod) * 10 % 8) = 6(mod)
 *           (6*10 % 8) = 4
 * 
 * @param num 
 * @return long long 
 */
unsigned long long factorial(){
    unsigned long long res = 1;
    for(int i=2; i<=N; i++){
        res *= i;
    }
    return res;
}
int getMod(string &num){
    int res = 0;
    for(int i=0; i<num.length();i++){
        int digit = num[i] - '0';
        res = (res * 10 + digit) % K;
    }
    return res;
}
void solution(){
    for(int mask = 0; mask < (1<<N); mask++){
        for(int mod =0; mod < K; mod++){
            if(dp[mask][mod] == 0) continue;

            for(int i=0; i<N; i++){
                if(!(mask & (1 << i))){
                    int n_mask = mask | (1<<i);
                    int n_mod = (mod * ten_mod[nums[i].size()]%K + nums_mod[i]) % K; // (앞에 들어올 수의 나머지(10**nums[i]만큼 된거)  + 새로 들어온 숫자의 나머지) % K = 새로운 수의 나머지
                    dp[n_mask][n_mod] += dp[mask][mod];
                }
            }
        }
    }


    unsigned long long up = dp[(1 << N) -1 ][0];

    if (up == 0) denominator = 1;
    unsigned long long gcd_ = gcd(up, denominator);


    cout << up/gcd_ << '/' << denominator/gcd_ <<'\n';
}
void init(){
    cin >> N;
    denominator = factorial();
    for(int i=0; i<N; i++){
        cin >> nums[i];
    }
    cin >> K;
    dp[0][0] = 1;
    for(int i=0; i<N; i++){
        nums_mod[i] = getMod(nums[i]);
    }
    ten_mod[0] = 1%K;
    for(int i=1; i<=max_len; i++){
        ten_mod[i] = (ten_mod[i-1]*10)%K;
    }

    

}
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    init();
    solution();
}