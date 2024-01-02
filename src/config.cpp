#include "config.h"

using json = nlohmann::json;

void Config::Config::read_user_config() {
  // read from the users file, then update the default config.
  // 1. read the users config.

  std::ifstream input_file(this->m_filename);

  if (!input_file.is_open()) {
    Logger::GetInstance().error() << "Error Opening the file";
  }

  json data = json::parse(input_file);
  std::cout << data["project_name"];

  // on each run the config file will be read for changes.
  // when we support hot reloading on each time the file changes this file will be read..
  this->m_default_config.project_name = data["project_name"];
  this->m_default_config.authors = data["authors"];
  this->m_default_config.license_file = data["license"];
}

