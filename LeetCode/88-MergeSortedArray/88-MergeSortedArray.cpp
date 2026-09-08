// Last updated: 2026. 9. 8. 오후 5:14:22
#include <cstdint>
class Solution {
public:
    void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
        // 병합할 때, nums1에 넣어야 한다.
        short p1 = m-1, p2 = n-1;
        // nums2를 돌면서, 해당 값을 nums1의 적절한 위치에 넣어줘야한다
        uint8_t put_idx = n + m - 1; // nums1의 size는 n+m이 보장되어 있다.
    
        while(p2 >= 0){
            // nums1의 원소가 nums2보다 큰 경우
            if(p1 >= 0 && nums1[p1] > nums2[p2]){
                nums1[put_idx--]=nums1[p1--]; 
            }else{
                nums1[put_idx--]=nums2[p2--]; 
            }
        }
        
    }
};