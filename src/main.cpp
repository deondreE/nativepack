#include "config.h"
#include "logger.h"
#include <iostream>
#include <toml++/toml.hpp>

int main(int argc, char **argv) {
  Config *config = new Config("./src/configuration.toml");

  auto user_config = config->get_user_config();

  Logger::GetInstance().info() << *user_config.project_name;

  return 0;
}
