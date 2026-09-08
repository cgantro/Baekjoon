// Last updated: 2026. 9. 8. 오후 5:14:12
#include <vector>
#include <unordered_map>
#include <random>
using namespace std;

class RandomizedSet {
public:
    RandomizedSet() : m_rng(random_device{}()) {}

    bool insert(int val) {
        if (m_indices.find(val) != m_indices.end()) {
            return false;
        }

        // 벡터 끝에 추가하고, 해당 값의 위치를 기록
        m_indices[val] = m_values.size();
        m_values.push_back(val);
        return true;
    }

    bool remove(int val) {
        auto it = m_indices.find(val);
        if (it == m_indices.end()) {
            return false;
        }

        size_t remove_idx = it->second;
        int last_val = m_values.back();

        // 삭제할 자리를 마지막 원소로 채우고, 이동한 위치를 기록
        m_values[remove_idx] = last_val;
        m_indices[last_val] = remove_idx;

        // 마지막 원소와 삭제 대상의 인덱스 기록 제거
        m_values.pop_back();
        m_indices.erase(it);
        return true;
    }

    int getRandom() {
        // 문제 조건: 호출 시 원소가 최소 하나 존재
        uniform_int_distribution<size_t> dist(0, m_values.size() - 1);
        return m_values[dist(m_rng)];
    }

private:
    vector<int> m_values;
    unordered_map<int, size_t> m_indices; // 값 → 벡터 인덱스
    mt19937 m_rng;                       // 난수 생성기
};