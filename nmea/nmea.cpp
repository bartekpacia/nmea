#include "nmea/nmea.h"

#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <utility>
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
auto split(const std::string &str, std::string sep) -> std::vector<std::string> {
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

auto parseVerticalHemisphere(std::string hemisphere) -> VerticalHemisphere {
  if (hemisphere == "N") {
    return VerticalHemisphere::North;
  } else if (hemisphere == "S") {
    return VerticalHemisphere::South;
  } else {
    throw std::runtime_error("Invalid vertical hemisphere: " + hemisphere);
  }
}

auto parseHorizontalHemisphere(std::string hemisphere) -> HorizontalHemisphere {
  if (hemisphere == "E") {
    return HorizontalHemisphere::East;
  } else if (hemisphere == "W") {
    return HorizontalHemisphere::West;
  } else {
    throw std::runtime_error("Invalid horizontal hemisphere: " + hemisphere);
  }
}

auto parsePositionFixIndicator(std::string indicator) -> PositionFixIndicator {
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
}  // namespace

GGA::GGA(std::string time, Latitude latitude, Longitude longitude, PositionFixIndicator pfi,
         uint8_t satelliteCount, std::string hdop, std::string altitude)
    : time(std::move(time)),
      latitude(std::move(latitude)),
      longitude(std::move(longitude)),
      pfi(pfi),
      satelliteCount(satelliteCount),
      hdop(std::move(hdop)),
      altitude(std::move(altitude)) {}

GGA::~GGA() = default;

Parser::Parser() = default;

Parser::~Parser() = default;

auto Parser::parseGGA(const std::string &sentence) -> GGA * {
  std::vector<std::string> splits = split(sentence, ",");

  std::string time = splits[1];
  Latitude latitude(splits[2], parseVerticalHemisphere(splits[3]));
  Longitude longitude(splits[4], parseHorizontalHemisphere(splits[5]));
  PositionFixIndicator pfi = parsePositionFixIndicator(splits[6]);
  uint8_t satelliteCount = std::stoi(splits[7]);
  std::string hdop = splits[8];
  std::string altitude = splits[9];

  GGA *gga = new GGA(time, latitude, longitude, pfi, satelliteCount, hdop, altitude);
  return gga;
}

}  // namespace nmea
