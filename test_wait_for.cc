// 测试函数条件变量 wait_for，
// TestCpuOcupy: 检测wait_for cpu占用率

#include <chrono>
#include <condition_variable>
#include <iostream>
#include <mutex>
#include <thread>

void TestCpuOcupy() {
    std::mutex y;
    std::condition_variable x;
    std::unique_lock<std::mutex> lock{y};
    int i = 0;
    auto increment = [&] {
        ++i;
        return false;
    };
    using namespace std::chrono_literals;

    // lock 5s if increment returns false
    // let's see how often was increment called?
    x.wait_for(lock, 5s, increment);
    std::cout << i << std::endl;

    // compare this with a simple loop:
    // how often can my system call increment in 5s?
    auto const end = std::chrono::system_clock::now() + 5s;
    i = 0;
    while (std::chrono::system_clock::now() < end) {
        increment();
    }
    std::cout << i;
}
void Testnotyfiy() {
    std::mutex mtx;
    std::condition_variable cv_;
    bool ret_g = false;

    std::thread t([&] {
        while (true) {
            std::unique_lock<std::mutex> lck(mtx);
            cv_.wait_for(lck, std::chrono::seconds(5),
                         [&] { return ret_g == true; });
            if (ret_g == true) {
                std::cout << "******get main ret\n";
            } else {
                std::cout << "********time out";
            }
            ret_g = false;
        }
    });
    std::thread t2([] {
        static int count = 0;
        while (1) {
            std::this_thread::sleep_for(std::chrono::seconds(1));
            std::cout << "time :" << count++ << std::endl;
        }
    });

    while (true) {
        {
            std::unique_lock<std::mutex> lck(mtx);
            ret_g = true;
            std::cout << "------------main thread condition \n";
            cv_.notify_one();
        }
        std::this_thread::sleep_for(std::chrono::seconds(7));
    }
    t.join();
    t2.join();
}
int main() {
    std::this_thread::sleep_for(std::chrono::seconds(17));

    TestCpuOcupy();
    return 0;
}

/*
pidstat -t 1 -p 55445
Linux 4.15.0-72-generic (ubuntu)        2019年12月21日  _x86_64_        (8 CPU)

15时35分29秒   UID      TGID       TID    %usr %system  %guest    %CPU   CPU  Command
15时35分30秒  1000     55445         -    0.00    0.00    0.00    0.00     6  a.out
15时35分30秒  1000         -     55445    0.00    0.00    0.00    0.00     6  |__a.out

15时35分30秒   UID      TGID       TID    %usr %system  %guest    %CPU   CPU  Command
15时35分31秒  1000     55445         -    0.00    0.00    0.00    0.00     6  a.out
15时35分31秒  1000         -     55445    0.00    0.00    0.00    0.00     6  |__a.out

15时35分31秒   UID      TGID       TID    %usr %system  %guest    %CPU   CPU  Command
15时35分32秒  1000     55445         -    0.00    0.00    0.00    0.00     6  a.out
15时35分32秒  1000         -     55445    0.00    0.00    0.00    0.00     6  |__a.out

15时35分32秒   UID      TGID       TID    %usr %system  %guest    %CPU   CPU  Command
15时35分33秒  1000     55445         -    0.00    0.00    0.00    0.00     6  a.out
15时35分33秒  1000         -     55445    0.00    0.00    0.00    0.00     6  |__a.out

15时35分33秒   UID      TGID       TID    %usr %system  %guest    %CPU   CPU  Command
15时35分34秒  1000     55445         -    0.00    0.00    0.00    0.00     6  a.out
15时35分34秒  1000         -     55445    0.00    0.00    0.00    0.00     6  |__a.out

15时35分34秒   UID      TGID       TID    %usr %system  %guest    %CPU   CPU  Command
15时35分35秒  1000     55445         -    0.00    0.00    0.00    0.00     6  a.out
15时35分35秒  1000         -     55445    0.00    0.00    0.00    0.00     6  |__a.out

15时35分35秒   UID      TGID       TID    %usr %system  %guest    %CPU   CPU  Command
15时35分36秒  1000     55445         -   50.00    0.00    0.00   50.00     6  a.out
15时35分36秒  1000         -     55445   50.00    0.00    0.00   50.00     6  |__a.out

15时35分36秒   UID      TGID       TID    %usr %system  %guest    %CPU   CPU  Command
15时35分37秒  1000     55445         -  100.00    0.00    0.00  100.00     6  a.out
15时35分37秒  1000         -     55445  100.00    0.00    0.00  100.00     6  |__a.out

15时35分37秒   UID      TGID       TID    %usr %system  %guest    %CPU   CPU  Command
15时35分38秒  1000     55445         -   99.01    0.00    0.00   99.01     6  a.out
15时35分38秒  1000         -     55445   99.01    0.00    0.00   99.01     6  |__a.out

15时35分38秒   UID      TGID       TID    %usr %system  %guest    %CPU   CPU  Command
15时35分39秒  1000     55445         -  100.00    0.00    0.00  100.00     6  a.out
15时35分39秒  1000         -     55445  100.00    0.00    0.00  100.00     6  |__a.out

15时35分39秒   UID      TGID       TID    %usr %system  %guest    %CPU   CPU  Command
15时35分40秒  1000     55445         -  100.00    0.00    0.00  100.00     6  a.out
15时35分40秒  1000         -     55445  100.00    0.00    0.00  100.00     6  |__a.out

15时35分40秒   UID      TGID       TID    %usr %system  %guest    %CPU   CPU  Command
*/