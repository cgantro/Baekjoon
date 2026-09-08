// Last updated: 2026. 9. 8. 오후 5:13:59
#include <functional>
#include <mutex>
#include <condition_variable>

class Foo {
private:
    std::mutex m;
    std::condition_variable cv;

    short turn = 1; // 공유 변수
public:
    Foo() = default; // 컴파일러가 기본생성자를 만들도록 위임한다
    // 때에 따라선 생성자 자체를 만들지 않아 생성자 Call하는 오버헤드를 없앤다.

    void first(function<void()> printFirst) {
        
        printFirst();

        // printFirst() outputs "first". Do not change or remove this line.
        {
            // turn은 공유 변수 -> mutex를 통해 보호하면서 변경해야함.
            std::lock_guard<std::mutex> lock(m);
            turn = 2; 
        }

        // lock_guard 소멸 -> unlock 상태
        // turn = 2 -> second 스레드가 바로 깨어나나? 아님
        // 깨워줘야함
        cv.notify_all(); // 스레드 이름 같은 걸 알면 지정해도 됨
    }

    void second(function<void()> printSecond) {
        
        // printSecond() outputs "second". Do not change or remove this line.

        // cv::wait
        // mutex를 unlock하고 잠든다.
        // notify 받으면 깨어난다.
        // mutex를 lock
        // predicate(turn==2)확인
        // unlock/lock 제어 가능한 unique_lock 사용

        std::unique_lock<std::mutex> lock(m);
        // mutex 획득 후 잠금
        cv.wait(lock,[this](){
            return turn == 2; // turn == 2가 아니면 열고 잠듦
        });
        printSecond();
        // 여기부턴 turn == 2 상태| lock 가지고 있음
        turn = 3;
        lock.unlock(); // turn 바꿨으니 해제
        // third 스레드가 wait일 수 있으니 깨워준다.
        cv.notify_all();
    }

    void third(function<void()> printThird) {
        
        // printThird() outputs "third". Do not change or remove this line.
        std::unique_lock<std::mutex> lock(m); // 락 잠금
        // turn == 3이 아니면 잠근다
        cv.wait(lock,[this](){
            return turn == 3;
        });
        printThird();

        // lock.unlock();
    }
};