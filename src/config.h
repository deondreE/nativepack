#include "core.h"
#include <toml++/toml.hpp>

class Config {
public:
  Config();
  ~Config();

  void get_global_config(std::string filename);

private:
  // This could be a string_view, havent yet decided.
  toml::table user_table;
};
