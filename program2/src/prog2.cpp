#include "prog2.h"

Prog2::Prog2() {
    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket == -1) {
        std::cerr << "Error: Failed to create socket\n";
        return;
    }

    int opt = 1;
    if (setsockopt(server_socket, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) == -1) {
        std::cerr << "Error: Failed to set socket options\n";
        close(server_socket);
        return;
    }

    sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(8080);
    server_address.sin_addr.s_addr = INADDR_ANY;

    if (bind(server_socket, (struct sockaddr *)&server_address, sizeof(server_address)) == -1) {
        std::cerr << "Error: Failed to bind socket\n";
        close(server_socket);
        return;
    }

    if (listen(server_socket, 5) == -1) {
        std::cerr << "Error: Failed to listen\n";
        close(server_socket);
        return;
    }

    std::cout << "Server is listening on port 8080...\n";
}

void Prog2::handleClient(int client_socket) {
    char buffer[256];
    while (true) {
        std::memset(buffer, 0, sizeof(buffer));
        int bytes_received = recv(client_socket, buffer, sizeof(buffer) - 1, 0);
        if (bytes_received <= 0) {
            if (bytes_received == 0) {
                std::cerr << "Client disconnected\n";
            } else {
                std::cerr << "Error: Failed to receive data\n";
            }
            break;
        }
        std::string sum = buffer;
        processSum(sum);
    }
    close(client_socket);
}

void Prog2::processSum(const std::string &sum) {
    try {
        int number = std::stoi(sum);
        if (sum.size() > 2 && number % 32 == 0) {
            std::cout << "Received sum: " << sum << std::endl;
        } else {
            std::cout << "Error. The sum is too small or not a multiple of 32" << std::endl;
        }
    } catch (const std::invalid_argument &e) {
    } catch (const std::out_of_range &e) {
    }
}

void Prog2::startListening() {
    while (true) {
        int client_socket = accept(server_socket, NULL, NULL);
        if (client_socket == -1) {
            std::cerr << "Error: Failed to accept connection\n";
            close(server_socket);
            return;
        }

        std::thread(&Prog2::handleClient, this, client_socket).detach();
    }
}

Prog2::~Prog2() { close(server_socket); }
