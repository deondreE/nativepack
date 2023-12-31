#include "logger.h"
#include <iostream>
#include <toml++/toml.hpp>

int main(int argc, char **argv) {
  toml::table tbl;

  try {
    tbl = toml::parse_file(argv[1]);
    Logger::GetInstance().error() << tbl;
    std::cout << "\n";
  } catch (const toml::parse_error &err) {
    Logger::GetInstance().error() << err;
    return 1;
  }

  return 0;
}
