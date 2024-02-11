#pragma once

#include <string>
#include <vector>

namespace nmea {

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
      : value(std::move(latitude)), hemisphere(hemisphere) {}

  // Latitude.
  //
  // Format: ddmm.mmmm
  //
  // Example: 3342.6618
  std::string value;

  // Northern or southern hemisphere.
  VerticalHemisphere hemisphere;
};

class Longitude {
 public:
  Longitude(std::string latitude, HorizontalHemisphere hemisphere)
      : value(std::move(latitude)), hemisphere(hemisphere) {}

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
  GGA(std::string time, Latitude latitude, Longitude longitude, PositionFixIndicator pfi,
      uint8_t satelliteCount, std::string hdop, std::string altitude);
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

  uint8_t satelliteCount;

  // Horizontal dilution of precision.
  std::string hdop;

  // Mean Surface Level Altitude.
  std::string altitude;

  static inline const std::string id = "GGA";
};
class GLL {
 public:
  GLL(std::string time, Latitude latitude, Longitude longitude)
      : time(std::move(time)), latitude(latitude), longitude(longitude) {}

  // UTC time.
  //
  // Format: hhmmss.sss
  //
  // Example: 002153.000
  std::string time;

  Latitude latitude;

  Longitude longitude;

  static inline const std::string id = "GLL";
};

class GSA {
 public:
  GSA(std::string mode, std::string modeFix, std::vector<uint8_t> satelliteIDs,
      std::string pdop, std::string hdop, std::string vdop)
      : mode(std::move(mode)), modeFix(std::move(modeFix)), satelliteIDs(std::move(satelliteIDs)),
        pdop(std::move(pdop)), hdop(std::move(hdop)), vdop(std::move(vdop)) {}

  // Mode
  std::string mode;

  // Mode Fix
  std::string modeFix;

  // List of satellite IDs used in fix
  std::vector<uint8_t> satelliteIDs;

  // Position dilution of precision
  std::string pdop;

  // Horizontal dilution of precision
  std::string hdop;

  // Vertical dilution of precision
  std::string vdop;

  static inline const std::string id = "GSA";
};

class Parser {
 public:
  Parser();
  ~Parser();

  auto parseGGA(const std::string &sentence) -> GGA *;
  auto parseGLL(const std::string &sentence) -> GLL *;
  auto parseGSA(const std::string &sentence) -> GSA *;
};

}  // namespace nmea
