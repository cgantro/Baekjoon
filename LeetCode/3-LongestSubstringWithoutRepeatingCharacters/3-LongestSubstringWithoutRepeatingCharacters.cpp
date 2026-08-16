// Last updated: 2026. 8. 16. 오후 4:27:02
class Solution {
private:
    bool duplicated[128] = {false,};
    int mx_len = 0;
public:
    int lengthOfLongestSubstring(string s) {
        int s_len = s.length();
        if(s_len == 0) return 0;

        size_t left = 0;
        size_t right = 0;
        while(right < s_len){
            
            int l_ch = (int)s[left] ;
            int r_ch = (int)s[right];
        
            if(!duplicated[r_ch]){
                // 중복이 없는 경우
                duplicated[r_ch] = true;
                mx_len = max(mx_len,(int)(right-left+1));
                right++;
            }
            // 중복인 경우
            else{
                duplicated[l_ch] = false;
                left++;
            }
        }

        return mx_len;
    }
};