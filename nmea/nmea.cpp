#include "nmea/nmea.h"
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

// Implementation of the NMEA parser and data structures.
//
// See also:
//
// * https://www.sparkfun.com/datasheets/GPS/NMEA%20Reference%20Manual-Rev2.1-Dec07.pdf
namespace nmea {

// Anonymous namespace for private utility functions.
namespace {

// Splits "str" into a vector of strings using "sep" as a delimeter.
std::vector<std::string> split(const std::string &str, std::string sep) {
  std::vector<std::string> result;

  auto start = 0U;
  auto end = str.find(sep);
  while (end != std::string::npos) {
    result.push_back(str.substr(start, end - start));
    start = end + sep.length();
    end = str.find(sep, start);
  }

  result.push_back(str.substr(start, end));

  return result;
}

VerticalHemisphere parseVerticalHemisphere(std::string hemisphere) {
  if (hemisphere == "N") {
    return VerticalHemisphere::North;
  } else if (hemisphere == "S") {
    return VerticalHemisphere::South;
  } else {
    throw std::runtime_error("Invalid vertical hemisphere: " + hemisphere);
  }
}

HorizontalHemisphere parseHorizontalHemisphere(std::string hemisphere) {
  if (hemisphere == "E") {
    return HorizontalHemisphere::East;
  } else if (hemisphere == "W") {
    return HorizontalHemisphere::West;
  } else {
    throw std::runtime_error("Invalid horizontal hemisphere: " + hemisphere);
  }
}

PositionFixIndicator parsePositionFixIndicator(std::string indicator) {
  if (indicator == "0") {
    return PositionFixIndicator::ZERO;
  } else if (indicator == "1") {
    return PositionFixIndicator::ONE;
  } else if (indicator == "2") {
    return PositionFixIndicator::TWO;
  } else if (indicator == "3") {
    return PositionFixIndicator::THREE;
  } else if (indicator == "4") {
    return PositionFixIndicator::FOUR;
  } else if (indicator == "5") {
    return PositionFixIndicator::FIVE;
  } else if (indicator == "6") {
    return PositionFixIndicator::SIX;
  } else {
    throw std::runtime_error("Invalid position fix indicator: " + indicator);
  }
}
} // namespace

std::string nmea_stuff() { return "nmea_stuff"; }

GGA::GGA(std::string time, Latitude latitude, Longitude longitude,
         PositionFixIndicator pfi)
    : time(time), latitude(latitude), longitude(longitude), pfi(pfi) {
  std::cout << "GGA constructor" << std::endl;
}

GGA::~GGA() { std::cout << "GGA destructor" << std::endl; }

Parser::Parser() { std::cout << "Parser constructor" << std::endl; }

Parser::~Parser() { std::cout << "Parser destructor" << std::endl; }

GGA *Parser::parseGGA(const std::string &sentence) {
  std::vector<std::string> splits = split(sentence, ",");

  for (auto &s : splits) {
    std::cout << s << std::endl;
  }

  std::string time = splits[1];
  Latitude latitude(splits[2], parseVerticalHemisphere(splits[3]));
  Longitude longitude(splits[4], parseHorizontalHemisphere(splits[5]));
  PositionFixIndicator pfi = parsePositionFixIndicator(splits[6]);

  GGA *gga = new GGA(time, latitude, longitude, pfi);
  return gga;
}

} // namespace nmea
