#include "config.h"

void Config::set_user_table() {
  try {
    // set the value of the user_table.
    user_table = toml::parse_file(m_filename);
    // Logger::GetInstance().info() << user_table;
  } catch (const toml::parse_error &err) {
    Logger::GetInstance().error() << err;
  }
}

Config::UserConfig Config::get_user_config() { return user_config; }

void Config::translate_user_config(toml::table user_table) {
  Config::UserConfig new_config;
  auto authors = user_table["authors"];
  auto project_name = user_table["project_name"].value<std::string>();

  user_config.project_name = project_name;
}
