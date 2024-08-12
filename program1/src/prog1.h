#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>

#include <algorithm>
#include <condition_variable>
#include <iostream>
#include <mutex>
#include <string>
#include <thread>

struct ThreadsData {
   public:
    bool dataReady = false;
    std::string buffer;
    std::condition_variable cv;
    std::mutex mtx;
};

class Prog1 {
   private:
    int sum;
    void createSocket(int client_socket);
    void sendMessage(int data, int client_socket);
    bool isValid(const std::string &str);
    void switchThread(std::string inp_str, ThreadsData &threadsData);

   public:
    void thread1(ThreadsData &threadsData);
    void thread2(ThreadsData &threadsData);
};