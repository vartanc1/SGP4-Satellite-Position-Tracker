#include "tle_parser.h"
#include <sstream>
#include <iostream>
std::vector<Satellite> parse_tle_string(const std::string& data) {

    std::vector<Satellite> satellites;
    std::stringstream ss(data);

    std::string name, line1, line2;

    while (std::getline(ss, name)) {

        if (!std::getline(ss, line1)) break;
        if (!std::getline(ss, line2)) break;

        Satellite sat;
        sat.name = name;
        sat.line1 = line1;
        sat.line2 = line2;
        //grab id values
        //1 25544U 98067A   24066.51041667  .00016717  00000+0  10270-3 0  9993


        //EX 1 25544U, we want the (25544) part

        std::string id_string = line1.substr(2,5);
        sat.sat_id = std::stoi(id_string);//convert string id to int val

        satellites.push_back(sat); //add new sat to vector
    }

    return satellites;
}