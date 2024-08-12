#include "prog1.h"

int main() {
    ThreadsData threadsData;
    Prog1 inThread;
    Prog1 outThread;
    std::cout << "Enter a string of digits (up to 64 characters) or enter "
                 "\"exit\" to end the program: "
              << std::flush;

    std::thread t1(&Prog1::thread1, &inThread, std::ref(threadsData));
    std::thread t2(&Prog1::thread2, &outThread, std::ref(threadsData));

    t1.join();
    t2.join();

    return 0;
}