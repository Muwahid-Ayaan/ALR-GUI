#ifndef ESP_COMMS_H
#define ESP_COMMS_H

#include <arpa/inet.h>
#include <fcntl.h>
#include <unistd.h>
#include <iostream>
#include <string>
#include <cstring>

namespace comms {

class ESPClient {
 public:
  ESPClient(const std::string& ip = "192.168.4.1", int port = 5005);
  ~ESPClient();

  bool connectESP();                     // Connect to ESP's TCP server
  bool sendMessage(const std::string& message);  // Send text message

 private:
  int sock_{-1};
  std::string ip_;
  int port_;
  sockaddr_in serverAddr_{};
};

}  // namespace comms

#endif
