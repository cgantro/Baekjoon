// Last updated: 2026. 8. 16. 오후 2:12:11
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */

#include<math.h>
#include<iostream>
class Solution {
public:

    // 자료형의 문제
    // add에다 올림연산해야할 듯 ㅋㅋ;

    int add(const int& v1, const int& v2, int *comp){
        int add = v1 + v2 + *comp; *comp = false; // 올림 소모
        int ret = add % 10;
        if(add >= 10) *comp = true;
        return ret;
    }
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        // 현재 자릿수에 대해서 Add 연산 후 comp반환
        ListNode *ret = new ListNode(0);
        ListNode *tmp = ret;
        int v1,v2;
        int comp = false;
        while(!(l1 == nullptr && l2 == nullptr)){
            v1 = 0; v2 =0;
            if(l1 != nullptr){
                v1 = l1 -> val;
                l1 = l1 -> next;
            }

            if(l2 != nullptr){
                v2 = l2 -> val;
                l2 = l2 -> next;
            }
            int put = add(v1,v2,&comp);
            tmp -> next = new ListNode(put);
            tmp = tmp -> next;
        }

        if(comp) tmp -> next = new ListNode(1);
        return ret->next;
    }
};