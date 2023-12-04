
#include <iostream>
#include "Client.h"

void log(const API_IP& api)
{
	std::cout << "[IP]\t" << api.ip << std::endl;
	std::cout << "[STATUS]\t" << api.status << std::endl;
	std::cout << "[COUNTRY]\t" << api.country << std::endl;
	std::cout << "[COUNTRY CODE]\t" << api.countryCode << std::endl;
	std::cout << "[REGION]\t" << api.region << std::endl;
	std::cout << "[REGION NAME]\t" << api.regionName << std::endl;
	std::cout << "[CITY]\t" << api.city << std::endl;
	std::cout << "[ZIP CODE]\t" << api.zipcode << std::endl;
	std::cout << "[LAT]\t" << api.lat << std::endl;
	std::cout << "[LON]\t" << api.lon << std::endl;
	std::cout << "[TIME ZONE]\t" << api.timezone << std::endl;
	std::cout << "[ISP]\t" << api.isp << std::endl;
	std::cout << "[ORG]\t" << api.org << std::endl;
	std::cout << "[AS]\t" << api.as << std::endl;
}


int main()
{
    std::string ip;

    std::cout << "Enter ip: ";
    std::cin >> ip;

    const API_IP api = getApiInfo(ip);

	log(api);

	system("pause");
    return 0;
}



