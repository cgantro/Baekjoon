# Last updated: 2026. 9. 8. 오후 5:13:56
class Solution:
    def mergeAlternately(self, word1: str, word2: str) -> str:
        answer = ""
        if len(word1) <= len(word2):
            i = 0
            for i in range(len(word1)):
                answer+=(word1[i] + word2[i])
            for j in range(i+1,len(word2)):
                answer+=(word2[j])
        else:
            i = 0
            for i in range(len(word2)):
                answer+=(word1[i] + word2[i])
            for j in range(i+1,len(word1)):
                answer+=(word1[j])
        return answer
        