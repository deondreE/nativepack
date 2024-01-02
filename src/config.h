#pragma once
#include <toml++/toml.hpp>
#include <nlohmann/json.hpp>
#include <fstream>

#include "core.h"
#include "logger.h"

class Config {
 public:

  Config() {

    // default config initialization.
    m_default_config.authors = {" "};
    m_default_config.build_types = { NativepackBuildTypes::Android };
    m_default_config.license_file = "";
    m_default_config.project_name = "DefaultProject";
  };

  /// @brief NativepackBuildTypes are similar to platform content.
  enum class NativepackBuildTypes {
    Android,
    iOS
  };

  /// Config Global type, that all things will return.
  struct NativepackConfig {
    std::string project_name;
    /// these are supplies from the user.
    std::vector<NativepackBuildTypes> build_types;
    /// authors
    std::vector<std::string> authors;
    std::string license_file;
  };

  /// @brief returns the current user config.
  NativepackConfig get_user_config() { return m_default_config; };

  /// @brief read the users config from the files.
  void read_user_config();

 private:
  /// default config that gets reconstructed.
  NativepackConfig m_default_config;
  std::string m_filename = "input/nativepack.json";

  // This could be a string_view, havent yet decided.
  // TODO: Think about making this json, for the main config. Toml for the compiler config.
  toml::table user_table;
};
