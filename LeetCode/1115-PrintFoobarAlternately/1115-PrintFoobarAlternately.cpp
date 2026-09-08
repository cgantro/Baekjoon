// Last updated: 2026. 9. 8. 오후 5:13:58
// 이전에는 lock 획득하고 풀고 그랬다.
// 

class FooBar {
private:
    int n;
    atomic<bool> runFoo = true;
public:
    FooBar(int n) {
        this->n = n;
    }

    void foo(function<void()> printFoo) {
        
        for (int i = 0; i < n; i++) {
            
        	// printFoo() outputs "foo". Do not change or remove this line.
            while(!runFoo);
        	printFoo();
            runFoo = false;
        }
    }

    void bar(function<void()> printBar) {
        
        for (int i = 0; i < n; i++) {
            
        	// printBar() outputs "bar". Do not change or remove this line.
            while(runFoo);
        	printBar();
            runFoo = true;
        }
    }
};