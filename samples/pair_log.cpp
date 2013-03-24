/*
 * Part of EasyLogging++ to demonstrate std::pair log and usage of std::vector alongwith
 *
 * Revision 1.0
 * @author mkhan3189
 */

#include "../easylogging++.h" // Include header
#include <utility> // for std::pair
#include <vector>

_INITIALIZE_EASYLOGGINGPP     // Initialize - Needed only once in your application

std::pair<unsigned int, std::string> newPlayer(unsigned int id_, const std::string& name_) {
    return std::pair<unsigned int, std::string>(id_, name_);
}

int main(int argc, char** argv) {

    std::pair<int, std::string> idNamePair(1, "Cashew");
    std::pair<int, std::string> idNamePair2(2, "Peanut");
    
    LINFO << idNamePair << " " << idNamePair2;

    BTRACE << "Now building vector of pairs";

    std::vector<std::pair<unsigned int, std::string> > players;
    players.push_back(newPlayer(1, "Akbar"));
    players.push_back(newPlayer(2, "Shumaiz"));
    players.push_back(newPlayer(3, "Mellisa"));
    players.push_back(newPlayer(4, "Stacy"));
    players.push_back(newPlayer(5, "Cancer"));

    BTRACE << "Now printing whole vector " << players;

    return 0;
}


