#include <iostream>

#include "gtest/gtest.h"
#include "nmea/nmea.h"

TEST(SmokeTest, ParseGGA) {
  // $GPGGA,002153.000,3342.6618,N,11751.3858,W,1,10,1.2,27.0,M,-34.2,M,,0000*5E
  std::string sentence =
      "$GPGGA,002153.000,3342.6618,N,11751.3858,W,1,10,1.2,"
      "27.0,M,-34.2,M,,0000*5E";
  nmea::Parser parser;
  nmea::GGA *gga = parser.parseGGA(sentence);
  EXPECT_EQ(gga->time, "002153.000");
  EXPECT_EQ(gga->latitude.value, "3342.6618");
  EXPECT_EQ(gga->latitude.hemisphere, nmea::VerticalHemisphere::North);
  EXPECT_EQ(gga->longitude.value, "11751.3858");
  EXPECT_EQ(gga->longitude.hemisphere, nmea::HorizontalHemisphere::West);
  EXPECT_EQ(gga->pfi, nmea::PositionFixIndicator::ONE);
  EXPECT_EQ(gga->satelliteCount, 10);
}

// ```
// $GPGGA,184353.07,1929.045,S,02410.506,E,1,04,2.6,100.00,M,-33.9,M,,0000*6D
// ```

// - `$GPGGA`: Sentence identifier, indicating that this is a GGA sentence using
//   GPS data.
// - `184353.07`: UTC (Coordinated Universal Time) time in hours, minutes, and
//   seconds (18:43:53.07 UTC).
// - `1929.045`: Latitude 19 degrees 29.045 minutes.
// - `S`: South hemisphere.
// - `02410.506`: Longitude 024 degrees 10.506 minutes.
// - `E`: East hemisphere.
// - `1`: Fix quality: 1 for GPS fix.
// - `04`: Number of satellites being tracked.
// - `2.6`: Horizontal dilution of precision (HDOP).
// - `100.00,M`: Altitude above mean sea level is 100.00 meters.
// - `-33.9,M`: Height of geoid (mean sea level) above WGS84 ellipsoid is -33.9
//   meters.
// - (empty field): Age of differential GPS data (if used), not provided.
// - (empty field): Differential reference station ID (if used), not provided.
// - `0000`: Checksum.

// The checksum value at the end is used to verify the integrity of the sentence
// during transmission. The asterisk (`*`) indicates the start of the checksum,
// and `6D` is the hexadecimal value.

// This NMEA sentence provides information about the GPS position, time, fix
// quality, number of satellites, dilution of precision, altitude, and other
// related data.
