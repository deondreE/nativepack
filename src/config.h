#include <toml++/toml.hpp>

#include "core.h"
#include "logger.h"

class Config {
 public:
  Config(std::string filename) {
    m_filename = filename;
    this->set_user_table();
    this->translate_user_config(user_table);
  };
  ~Config();

  struct UserConfig {
    std::optional<std::string> project_name;
    std::vector<std::string> authors;
  };

  /// @brief returns the current user config.
  UserConfig get_user_config();

 private:
  /// @brief sets the user table to the given value.
  void set_user_table();

  /// @brief translates the user config from a toml::table to a the UserConfig
  /// type.
  void translate_user_config(toml::table user_table);

  // This could be a string_view, havent yet decided.
  toml::table user_table;
  UserConfig user_config;

  std::string m_filename;
};
