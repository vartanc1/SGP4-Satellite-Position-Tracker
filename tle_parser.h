#ifndef TLE_PARSER_H
#define TLE_PARSER_H

#include <vector>
#include <string>
#include "satellite.h"

std::vector<Satellite> parse_tle_string(const std::string& data);

#endif