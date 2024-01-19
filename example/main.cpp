#include <iostream>
#include <string>
#include "nmea/nmea.h"

int main(int argc, char** argv) {
  std::string who = nmea::nmea_stuff();
  std::cout << who << std::endl;
  return 0;
}
