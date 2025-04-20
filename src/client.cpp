#include "client.h"

#include <boost/asio/connect.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/beast.hpp>

#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>

// std
#include <iostream>
#include <string>

#ifndef http
#define http boost::beast::http
#endif

#define MAIN_API "ip-api.com"
#define API_ARGUMENTS "/json/"

namespace dumper {
void API_IP::getApiInfo(const std::string &ip_dump) {
  getResponse(ip_dump);

  std::stringstream jsonEncoded(json);
  boost::property_tree::ptree root;
  boost::property_tree::read_json(jsonEncoded, root);

  if (root.empty())
    return;

  ip = root.get<std::string>("query");
  status = root.get<std::string>("status");
  country = root.get<std::string>("country");
  countryCode = root.get<std::string>("countryCode");
  region = root.get<std::string>("region");
  regionName = root.get<std::string>("regionName");
  city = root.get<std::string>("city");
  zipcode = root.get<std::string>("zip");
  timezone = root.get<std::string>("timezone");
  isp = root.get<std::string>("isp");
  org = root.get<std::string>("org");
  as = root.get<std::string>("as");

  std::string lat = root.get<std::string>("lat");
  std::string lon = root.get<std::string>("lon");

  if (!lat.empty())
    lat = stod(lat);
  if (!lon.empty())
    lon = stod(lon);
}
void API_IP::getResponse(const std::string &ip) {
  boost::asio::io_context io;
  boost::asio::ip::tcp::resolver resolver(io);
  boost::asio::ip::tcp::socket socket(io);

  boost::asio::connect(socket, resolver.resolve(MAIN_API, "80"));

  http::request<http::string_body> req(http::verb::get, API_ARGUMENTS + ip, 11);

  req.set(http::field::host, MAIN_API);
  req.set(http::field::user_agent, BOOST_BEAST_VERSION_STRING);

  http::write(socket, req);
  {
    boost::beast::flat_buffer buffer;
    http::response<http::dynamic_body> res;
    http::read(socket, buffer, res);
    json = boost::beast::buffers_to_string(res.body().data());
  }
  socket.shutdown(boost::asio::ip::tcp::socket::shutdown_both);
}

void API_IP::log() {
  std::cout << "[IP]          \t" << ip << std::endl;
  std::cout << "[STATUS]      \t" << status << std::endl;
  std::cout << "[COUNTRY]     \t" << country << std::endl;
  std::cout << "[COUNTRY CODE]\t" << countryCode << std::endl;
  std::cout << "[REGION]      \t" << region << std::endl;
  std::cout << "[REGION NAME] \t" << regionName << std::endl;
  std::cout << "[CITY]        \t" << city << std::endl;
  std::cout << "[ZIP CODE]    \t" << zipcode << std::endl;
  std::cout << "[LAT]         \t" << lat << std::endl;
  std::cout << "[LON]         \t" << lon << std::endl;
  std::cout << "[TIME ZONE]   \t" << timezone << std::endl;
  std::cout << "[ISP]         \t" << isp << std::endl;
  std::cout << "[ORG]         \t" << org << std::endl;
  std::cout << "[AS]          \t" << as << std::endl;
}
} // namespace dumper