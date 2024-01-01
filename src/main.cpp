#include <iostream>
#include <string>
#include <toml++/toml.hpp>

#include "cli.h"
#include "config.h"
#include "logger.h"

int main(int argc, char* argv[]) {
  bool running = false;
  Config* config = new Config("./src/configuration.toml");
  // Make sure the user provides arguments...
  if (argc == 1) {
    Logger::GetInstance().error() << "Run --help for more information";
  } else {
    running = true;
  }

  if (running) {
    auto* cli = new NativepackCore::Cli();
    cli->match_string(std::string(argv[1]));
  }

  return 0;
}
