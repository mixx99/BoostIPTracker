#pragma once

#include <string>
namespace dumper {
struct API_IP {
  std::string ip;
  std::string status;
  std::string country;
  std::string countryCode;
  std::string region;
  std::string regionName;
  std::string city;
  std::string zipcode;
  double lat;
  double lon;
  std::string timezone;
  std::string isp;
  std::string org;
  std::string as;

  std::string json;
  void getApiInfo(const std::string &ip);
  void log();

private:
  void getResponse(const std::string &ip);
};
} // namespace dumper