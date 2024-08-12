#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>

#include <cstring>
#include <iostream>
#include <stdexcept>
#include <thread>

class Prog2 {
   private:
    void processSum(const std::string &sum);
    int server_socket;

   public:
    void handleClient(int client_socket);
    void startListening();

    Prog2();
    ~Prog2();
};
