#include <iostream>
#include <string>
#include <SFML/Network.hpp>

int main() {
    sf::UdpSocket socket;
    size_t PORT = 0;
    std::cout << "Enter PORT (default -> \"8080\")\n";
    std::cin >> PORT;

    if (socket.bind(PORT) != sf::Socket::Done) {
        std::cerr << "Can't bind the socket to a port " + std::to_string(PORT);
    }

    std::cout << "Here you can check all incoming messages.\n\n";

    while (true) {
        std::string nickName;
        std::string msg;
        sf::IpAddress inc_Ip;
        sf::Packet pack;
        unsigned short port;
        if (socket.receive(pack, inc_Ip, port) != sf::Socket::Done) return 0;
        pack >> nickName;
        pack >> msg;
        std::cout << nickName << ": " << msg << "\n";
        pack.clear();
        nickName.clear();
        msg.clear();
    }

    return 0;
}
