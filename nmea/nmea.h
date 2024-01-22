#pragma once

#include <string>

namespace nmea {
std::string nmea_stuff();

enum class VerticalHemisphere {
  North,
  South,
};

enum class HorizontalHemisphere {
  East,
  West,
};

enum class PositionFixIndicator {
  // Fix not available or invalid
  ZERO,
  // 1 GPS SPS Mode, fix valid
  ONE,
  // Differential GPS, SPS Mode, fix valid
  TWO,
  // Not supported
  THREE,
  // Not supported
  FOUR,
  // Not supported
  FIVE,
  // Dead Reckoning Mode, fix valid
  SIX,
};

class Latitude {
public:
  Latitude(std::string latitude, VerticalHemisphere hemisphere)
      : value(latitude), hemisphere(hemisphere) {}

  // Latitude.
  //
  // Format: ddmm.mmmm
  //
  // Example: 3342.6618
  std::string value;

  // Northern or southern hemisphere.
  //
  // Example: N
  VerticalHemisphere hemisphere;
};

class Longitude {
public:
  Longitude(std::string latitude, HorizontalHemisphere hemisphere)
      : value(latitude), hemisphere(hemisphere) {}

  // Longitude value
  //
  // Format: dddmm.mmmm
  //
  // Example: 11751.3858
  std::string value;

  // Eastern or western hemisphere.
  HorizontalHemisphere hemisphere;
};

// Time, position and fix type data.
//
// Example:
// $GPGGA,002153.000,3342.6618,N,11751.3858,W,1,10,1.2,27.0,M,-34.2,M,,0000*5E
class GGA {
public:
  GGA(std::string time, Latitude latitude, Longitude longitude,
      PositionFixIndicator pfi);
  ~GGA();

  // UTC time.
  //
  // Format: hhmmss.sss
  //
  // Example: 002153.000
  std::string time;

  Latitude latitude;

  Longitude longitude;

  PositionFixIndicator pfi;

  static inline const std::string id = "GGA";
};

class Parser {
public:
  Parser();
  ~Parser();

  GGA *parseGGA(const std::string &sentence);
};

} // namespace nmea
