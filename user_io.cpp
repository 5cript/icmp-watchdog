#include "user_io.hpp"

#include <iostream>

//#####################################################################################################################
boost::optional <std::size_t> selectInterface(std::vector <std::string> interfaces)
{
    int i = 0;
	for (auto const& adr: interfaces)
    {
        ++i;
        std::cout << i << ") " << adr << "?\n";
    }
    std::cout << "Please enter number to choose interface: ";

    std::size_t netInterface = 0;
    while (std::cin >> netInterface, (!std::cin || netInterface > interfaces.size()))
    {
        std::cout << "enter a correct number or 0 to abort: \n";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits <std::streamsize>::max(), '\n');
    }

    if (netInterface == 0)
        return boost::none;

    return netInterface - 1;
}
//---------------------------------------------------------------------------------------------------------------------
//#####################################################################################################################
