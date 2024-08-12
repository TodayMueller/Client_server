#include "prog1.h"

bool Prog1::isValid(const std::string &str) {
    return str.size() <= 64 && std::all_of(str.begin(), str.end(), [](char ch) { return ch >= '0' && ch <= '9'; });
}

void Prog1::switchThread(std::string inp_str, ThreadsData &threadsData) {
    std::unique_lock<std::mutex> lock(threadsData.mtx);
    threadsData.buffer = inp_str;
    threadsData.dataReady = true;
    threadsData.cv.notify_one();
}

void Prog1::createSocket(int client_socket) {
    if (client_socket == -1) {
        std::cerr << "Error: Failed to create socket\n";
    }
    sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(8080);
    inet_pton(AF_INET, "127.0.0.1", &server_address.sin_addr);
    if (connect(client_socket, (struct sockaddr *)&server_address, sizeof(server_address)) == -1) {
        std::cerr << "Error: Failed to connect to server\n";
        close(client_socket);
    }
};

void Prog1::sendMessage(int data, int client_socket) {
    std::string strsum = std::to_string(sum);
    if (send(client_socket, strsum.data(), strsum.size(), 0) == -1) {
        std::cerr << "Error: Failed to send message\n";
    }
};

void Prog1::thread1(ThreadsData &threadsData) {
    while (true) {
        std::string inp_str;
        std::getline(std::cin, inp_str);
        if (inp_str == "exit") {
            switchThread(inp_str, threadsData);
            break;
        }
        if (!isValid(inp_str)) {
            std::cout << "Error! Invalid input. Try again.\n";
            continue;
        }

        std::sort(inp_str.begin(), inp_str.end(), std::greater<char>());
        for (int i = 0; i < inp_str.size(); i++) {
            if ((inp_str[i] - '0') % 2 == 0) {
                inp_str = inp_str.substr(0, i) + "KB" + inp_str.substr(i + 1, inp_str.size());
                i++;
            }
        }

        switchThread(inp_str, threadsData);
    }
}

void Prog1::thread2(ThreadsData &threadsData) {
    while (true) {
        std::unique_lock<std::mutex> lock(threadsData.mtx);
        threadsData.cv.wait(lock, [&threadsData] { return threadsData.dataReady; });
        std::string data = threadsData.buffer;
        threadsData.dataReady = false;
        lock.unlock();

        int client_socket = socket(AF_INET, SOCK_STREAM, 0);
        createSocket(client_socket);

        if (data == "exit") {
            close(client_socket);
            break;
        }

        sum = 0;
        for (char ch : data) {
            if (isdigit(ch)) {
                sum += ch - '0';
            }
        }

        sendMessage(sum, client_socket);

        std::cout << "Received data: " << data << std::endl;
        std::cout << "Sum of numeric values: " << sum << std::endl;
        std::cout << "Enter a string of digits (up to 64 characters) or enter "
                     "\"exit\" to end the program: "
                  << std::flush;
    }
}