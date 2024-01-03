#include <iostream>
#include <string>

#include "cli.h"
#include "config.h"
#include "logger.h"

int main(int argc, char* argv[]) {
  bool running = false;
  // Make sure the user provides arguments...
  if (argc == 1) {
    Logger::GetInstance().error() << "Run --help for more information";
  } else {
    running = true;
  }

  if (running) {
    auto* cli = new NativepackCore::Cli();
    cli->findCommand(argv[1]);
  }

  return 0;
}
