#pragma once

#include <boost/beast.hpp>
#include <boost/asio/connect.hpp>
#include <boost/asio/ip/tcp.hpp>

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

#include <string>

#ifndef http
#define http boost::beast::http
#endif

struct API_IP;
const API_IP getApiInfo(const std::string&);
const std::string getResponse(const std::string& ip);

const static std::string MAIN_API = "ip-api.com";
const static std::string API_ARGUMENTS = "/json/";



struct API_IP
{
	std::string ip;
	std::string status;
	std::string country;
	std::string countryCode;
	std::string region;
	std::string regionName;
	std::string city;
	std::string zipcode;
	double      lat;
	double      lon;
	std::string timezone;
	std::string isp;
	std::string org;
	std::string as;

};


const API_IP getApiInfo(const std::string& ip)
{
	std::string json = getResponse(ip);

	std::stringstream jsonEncoded(json);
	boost::property_tree::ptree root;
	boost::property_tree::read_json(jsonEncoded, root);

	API_IP api;

	if (root.empty())
		return api;

	api.ip          = root.get<std::string>("query");
	api.status      = root.get<std::string>("status");
	api.country     = root.get<std::string>("country");
	api.countryCode = root.get<std::string>("countryCode");
	api.region      = root.get<std::string>("region");
	api.regionName  = root.get<std::string>("regionName");
	api.city        = root.get<std::string>("city");
	api.zipcode     = root.get<std::string>("zip");
	api.timezone    = root.get<std::string>("timezone");
	api.isp         = root.get<std::string>("isp");
	api.org         = root.get<std::string>("org");
	api.as          = root.get<std::string>("as");

	std::string lat = root.get<std::string>("lat");
	std::string lon = root.get<std::string>("lon");

	if (!lat.empty()) api.lat = stod(lat);
	if (!lon.empty()) api.lon = stod(lon);

	return api;
}



const std::string getResponse(const std::string& ip)
{
	boost::asio::io_context io;
	boost::asio::ip::tcp::resolver resolver(io);
	boost::asio::ip::tcp::socket socket(io);

	boost::asio::connect(socket, resolver.resolve(MAIN_API, "80"));


	http::request<http::string_body> req(http::verb::get, API_ARGUMENTS + ip, 11);

	req.set(http::field::host, MAIN_API);
	req.set(http::field::user_agent, BOOST_BEAST_VERSION_STRING);

	http::write(socket, req);

	std::string response;
	{
		boost::beast::flat_buffer buffer;
		http::response<http::dynamic_body> res;
		http::read(socket, buffer, res);
		response = boost::beast::buffers_to_string(res.body().data());
	}
	socket.shutdown(boost::asio::ip::tcp::socket::shutdown_both);
	return response;
}