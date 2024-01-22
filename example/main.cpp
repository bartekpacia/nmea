#include "nmea/nmea.h"
#include <iostream>
#include <string>

int main(int argc, char **argv) {
  std::string who = nmea::nmea_stuff();
  std::cout << who << std::endl;

  std::string s = "scott>=tiger>=dupsko XD";
  std::string delim = ">=";

  auto start = 0U;
  auto end = s.find(delim);
  while (end != std::string::npos) {
    std::cout << s.substr(start, end - start) << std::endl;
    start = end + delim.length();
    end = s.find(delim, start);
  }

  std::cout << s.substr(start, end);

  return 0;
}
