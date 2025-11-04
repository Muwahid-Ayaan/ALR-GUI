#include "Esp_comms.h"

namespace comms {

ESPClient::ESPClient(const std::string& ip, int port) : ip_(ip), port_(port) {}

ESPClient::~ESPClient() {
  if (sock_ >= 0) close(sock_);
}

bool ESPClient::connectESP() {
  sock_ = socket(AF_INET, SOCK_STREAM, 0);
  if (sock_ < 0) {
    perror("Socket creation failed");
    return false;
  }

  serverAddr_.sin_family = AF_INET;
  serverAddr_.sin_port = htons(port_);

  if (inet_pton(AF_INET, ip_.c_str(), &serverAddr_.sin_addr) <= 0) {
    perror("Invalid address");
    close(sock_);
    sock_ = -1;
    return false;
  }

  std::cout << "Connecting to ESP at " << ip_ << ":" << port_ << "...\n";

  if (connect(sock_, (struct sockaddr*)&serverAddr_, sizeof(serverAddr_)) < 0) {
    perror("Connection failed");
    close(sock_);
    sock_ = -1;
    return false;
  }

  std::cout << "Connected to ESP!\n";
  return true;
}

bool ESPClient::sendMessage(const std::string& message) {
  if (sock_ < 0) return false;

  ssize_t sent = send(sock_, message.c_str(), message.size(), 0);
  if (sent < 0) {
    perror("Send failed");
    return false;
  }

  std::cout << "Sent message: \"" << message << "\" (" << sent << " bytes)\n";
  return true;
}

}  // namespace comms
