#pragma once
#include "core.h"
#include "logger.h"

namespace NativepackCore {
enum class CommandType { HELP, INIT, CONFIG };
struct UserCommand {
  std::string command_string;
  NativepackCore::CommandType command_type;
};

/// @brief Cli is what the core of the application is. Allowing users to
/// communicate with the compiler is esential.
class Cli {
 public:
  static Cli& GetInstance() {
    static Cli instance;
    return instance;
  }

  /// @brief Help string is what prints if the user runs things the incorrect
  /// way.
  std::string get_help_string() { return help_string; };

  /// @brief  This is Running on the users command, then calling Execute.
  /// @param current_command
  /// @return
  void match_string(std::string current_command) {
    NativepackCore::UserCommand command;

    if (check_valid(current_command)) {
      if (current_command == commands[0]) {
        // help command...
        command.command_type = NativepackCore::CommandType::HELP;
        command.command_string = current_command;
        this->execute(command);
      }
      if (current_command == commands[1]) {
        // --name
        command.command_type = NativepackCore::CommandType::CONFIG;
        command.command_string = current_command;
        this->execute(command);
      }
      if (current_command == commands[2]) {
        // --init
        command.command_type = NativepackCore::CommandType::INIT;
        command.command_string = current_command;
        this->execute(command);
      }
    }
  }

 private:
  std::string help_string = R"(
    Welcome to the help center for nativepack!!!!

   ->Current Commands:
        --help : Help Command.
        --name : Name of the project.
        --v: Version of the cli.
    )";

  std::vector<std::string> commands = {"--help", "--name", "--init"};

  int execute(const NativepackCore::UserCommand& command) {
    switch (command.command_type) {
      case NativepackCore::CommandType::INIT:
        system("./scripts/init_project.sh");
        break;
      case NativepackCore::CommandType::HELP:
        printf("Command Ran: %s\n", command.command_string.c_str());
        Logger::GetInstance().info() << help_string;
        break;
      case NativepackCore::CommandType::CONFIG:
        break;

      default:
        break;
    }
    return 0;
  }

  /// @brief Check if the command is valid.
  /// @param current_command Command the user puts in.
  /// @return boolean.
  bool check_valid(const std::string& current_command) {
    // TODO: Change this to std::any_of();
    for (const std::string& default_command : commands) {
      if (current_command == default_command) return true;
    }

    return false;
  }

  void create_default_p_config(const std::string& project_name) {

  }
};
}  // namespace NativepackCore
