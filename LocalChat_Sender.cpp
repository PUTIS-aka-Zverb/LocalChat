#include <iostream>
#include <string>
#include <SFML/Network.hpp>
#include <regex>

bool chkIp(std::string Ip) {
    return std::regex_match(Ip, std::regex("(([0-9]|[1-9][0-9]|1[0-9][0-9]|2[0-4][0-9]|25[0-5])\\.){3}([0-9]|[1-9][0-9]|1[0-9][0-9]|2[0-4][0-9]|25[0-5])"));
}

void setDestIp(sf::IpAddress& addr, std::string& iP, size_t& PORT) {
        std::cout << "Enter receiver IPv4 address:\n";
        std::cin >> iP;

        if (iP == "-leave") return;
        if (!chkIp(iP)) {
            std::cout << "Incorrect IPv4 address.\n";
            return setDestIp(addr, iP, PORT);
        }
        addr = iP.c_str();

        std::cout << "Enter receiver PORT:\n";
        std::cin >> PORT;
        return;
}

int main() {
    size_t PORT;     
    sf::UdpSocket socket;
    std::string rIp; // receiver IP addr
    sf::IpAddress recipient; 
    setDestIp(recipient, rIp, PORT);

    std::string nickName;
    std::cout << "Enter Your Nickname: ";
    std::cin >> nickName;

    std::cout << "\n\nType \"-leave\" to exit the chat.\n";
    std::cout << "Type \"-change\" to change destination IP\n\n";

    std::cin.get();

    while (true) {
        std::string msg;
        std::cout << "Enter msg: ";
        std::getline(std::cin, msg);
        
        if (msg == "-leave") return 0;
        else if (msg == "-change") setDestIp(recipient, rIp, PORT);

        else if(!msg.empty()){

            sf::Packet packet;
            packet << nickName.c_str() << msg.c_str();

            if (socket.send(packet, recipient, PORT) != sf::Socket::Done) {
                std::cerr << "Can't send packets to the following ip: " + rIp + " using port: " + std::to_string(PORT) + "\n\n";
            }
            else std::cout << "Successfully sent.\n";

            packet.clear();
            msg.clear();
        }
    }
    return 0;
}
