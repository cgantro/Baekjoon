#include <bits/stdc++.h>
using namespace std;

#define MAX 10005
#define MAX_VAL 10000000
/**
 * 트리를 전위 순회한 결과가 주어질 때, 후위 순회한 결과를 구하는 프로그램을 작성하시오.
 */

// 최악의 경우 : 일자로 쭉 펴진다 -> 칸 부족
// 

int pre_order[MAX];

void post_order(int start, int end){
    if(start > end) return;
    int root = pre_order[start];

    int mid = start+1;

    // 서브트리 자르기
    while(mid <= end && pre_order[mid] < root){
        mid++;
    }

    post_order(start+1,mid-1);
    post_order(mid,end);
    cout << root << '\n';
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int i=0, n;
    memset(pre_order,0,MAX);

    while(cin >> n){
        pre_order[i++] = n;
    }

    post_order(0,i-1);
    return 0;
}
