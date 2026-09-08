// Last updated: 2026. 9. 8. 오후 5:14:14
// 요구사항 : LRU 캐시
// LRU란 : Least Recently Used의 약자로, 가장 최근에 사용되지 않은 것들을 Cache에서 교체하는 알고리즘이다.
#include <unordered_map>
#include <list>

class LRUCache {
private:
    int capacity;
    // front : 가장 최근에 사용
    // back  : 가장 오래 사용 x 
    // {key,val}
    list<pair<int,int>> entries;
    unordered_map<int, list<pair<int, int>>::iterator> cache;
public:
    LRUCache(int capacity): capacity(capacity){}

    // RAII와RuleOfZero
    // 이 클래스는 포인터를 관리하지 않기 때문에 소멸자 작성하지 않는 것이 좋다.
    int get(int key) {
        auto it = cache.find(key);

        if(it == cache.end()) return -1; // 캐시에 없는 경우

        // 가장 최근에 사용했으요
        entries.splice(entries.begin(),entries,it->second);
        return it->second->second;
    }
    
    void put(int key, int value) {
        auto it = cache.find(key);
        if(it != cache.end()){ // 이미 존재하는 키라면
            it->second->second = value;
            // 이동할 위치, 자료구조, 이동할 자료
            entries.splice(entries.begin(),entries,it->second);
            return;
        }

        if(cache.size() == capacity){ // 캐시가 꽉 찬 경우
            int rmv_key = entries.back().first;

            cache.erase(rmv_key);
            entries.pop_back();
        }

        // 새로운 값 주입
        entries.push_front({key,value});
        cache[key] = entries.begin();
    }
};

/**
 * Your LRUCache object will be instantiated and called as such:
 * LRUCache* obj = new LRUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */