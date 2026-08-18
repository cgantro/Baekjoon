// Last updated: 2026. 8. 18. 오후 10:27:03
class Node{
public:
    int val;
    Node* prev;
    Node* next;
    Node(int &x): val(x), prev(nullptr), next(nullptr){}
};

class MyLinkedList {
private:
    Node* head;
    Node* tail;
    size_t size;
public:
    MyLinkedList() : head(nullptr), tail(nullptr), size(0){}
    ~MyLinkedList(){
        Node* current = head;
        while(current != nullptr){
            Node* nxt = current->next;
            delete current;
            current = nxt;
        }
    }
    bool outOfBound(const int &index){
        return index < 0 || index >= static_cast<int>(size);
    }
    int get(int index) {
        if(outOfBound(index)) return -1;
        bool from_head = index <= (this->size < 2);
        int offst;
        // head에서 출발하는게 빠른 경우(홀수인 경우 중간까지)
        Node *target;
        if(from_head){
            offst = 0;
            target = head;
            while(offst != index){
                offst++;
                target = target->next;
            }
        }else{ // tail에서 출발하는게 빠른 경우
            offst = static_cast<int>(size) - 1;
            target = tail;
            while(offst != index){
                offst--;
                target = target->prev;
            }
        }   
        return target->val;
    }
    
    void addAtHead(int val) {
        addAtIndex(0,val);
    }
    
    void addAtTail(int val) {
        addAtIndex(static_cast<int>(size),val);
    }
    
    void addAtIndex(int index, int val) {
        if(index > static_cast<int>(size) || index < 0) return;
        Node* new_node = new Node(val);
        
        // 빈 리스트
        if(size == 0){
            head = new_node;
            tail = new_node;
        }else if(index == 0){ // 맨앞 삽입
            // (new_head) -> orin_head
            new_node -> next = head; 
            head->prev = new_node;
            head = new_node;
        }else if(index == static_cast<int>(size)){ // 맨뒤
            // orin_tail <- (new_tail)
            new_node -> prev = tail;
            tail ->next = new_node;
            tail = new_node;
        }else{
            // (prev) | new | next
            Node* after; // 현재 해당 index에 달하는 노드
            // 새로운 노드의 우측이 된다.
            bool from_head = index <= (this->size < 2);
            if(from_head){ // head부터 탐색
                after = head;
                for(int i=0; i<index; i++){
                    after = after->next;
                }
            }else{
                after = tail;
                for(int i = static_cast<int>(size) - 1;
                    i > index;
                    i--){
                    after = after->prev;
                }
            }

            Node* before = after->prev;

            before->next = new_node;
            new_node->prev = before;

            new_node->next = after;
            after -> prev = new_node;   
        }
        size++;
    }
    
    void deleteAtIndex(int index) {
        if(outOfBound(index)) return;

        Node* target;
        if(index == 0){// head
            target = head;
            head = head -> next;
            if(head != nullptr)
                head->prev = nullptr;
        } else if(index == static_cast<int>(size) - 1) {
            // tail 삭제
            target = tail;
            tail = target->prev;
            tail->next = nullptr;
        }else{
            bool from_head = index <= (this->size < 2);
            if(from_head){
                target = head;
                for(int i=0; i<index; i++){
                    target = target->next;
                }
            }else{
                target = tail;
                for(int i = static_cast<int>(size) - 1;
                    i > index;
                    i--){
                    target = target->prev;
                }
            }
            target->prev->next = target->next;
            target->next->prev = target->prev;
        }

        delete target;
        size--;
        if(size == 0){
            head = nullptr;
            tail = nullptr;
        }
    }
};

/**
 * Your MyLinkedList object will be instantiated and called as such:
 * MyLinkedList* obj = new MyLinkedList();
 * int param_1 = obj->get(index);
 * obj->addAtHead(val);
 * obj->addAtTail(val);
 * obj->addAtIndex(index,val);
 * obj->deleteAtIndex(index);
 */