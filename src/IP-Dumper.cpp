
#include "client.h"
#include <iostream>

int main() {
  std::string ip;

  std::cout << "Enter ip: ";
  std::cin >> ip;

  try {
    dumper::API_IP api;
    api.getApiInfo(ip);

    api.log();
  } catch (std::exception &exception) {
    std::cerr << exception.what() << std::endl;
  }

  system("pause");
  return 0;
}
