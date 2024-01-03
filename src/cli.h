#pragma once
#include "config.h"
#include "core.h"
#include "logger.h"

namespace NativepackCore {
  /// @brief Cli is what the core of the application is. Allowing users to
  /// communicate with the compiler is esential.
  class Cli {
  public:
    static Cli &GetInstance() {
      static Cli instance;
      return instance;
    }

    void findCommand(const std::string &current_command) {
      size_t start_pos = current_command.find("--");

      if (start_pos != std::string::npos) {
        std::string command_word = current_command.substr(start_pos + 2);
        this->execute(command_word);
      }
    }

    void execute(const std::string &command) {
      Cli cliInstance;
      std::unordered_set<std::string> validCommands = {"help", "run", "init"};
      std::map<std::string, std::function<void(Cli &)> > commandMap;
      commandMap["help"] = std::bind(&Cli::help_command, &cliInstance);
      commandMap["run"] = std::bind(&Cli::help_command, &cliInstance);
      commandMap["init"] = std::bind(&Cli::init_commnad, &cliInstance);

      auto execute_command = commandMap.find(command);
      if (validCommands.find(command) != validCommands.end()) {
        // printf("%s", command.c_str());
        if (execute_command != commandMap.end()) {
          execute_command->second(cliInstance);
        }
      }
    }

  private:
    std::string help_string = R"(
    Welcome to the help center for nativepack!!!!

   ->Current Commands:
        --help : Help Command.
        --run: Run the project.
        --init: Intializie a new project.
        --v: Version of the cli.
    )";
    std::string cli_version = "0.0.1";

    // TODO: remove this soon.
    std::vector<std::string> commands = {"help", "name ", "init", "run"};

    /// @brief Checks if the command is valid.
    /// @param current_command
    /// @return
    bool check_valid(const std::string &current_command) {
      for (const std::string &possible_command: commands) {
        if (current_command == possible_command) return true;
      }

      return false;
    }

    void help_command() {
      printf("Welcome to the Nativepack Cli!\n");
      printf("%s\n", help_string.c_str());
    }

    /// Initililize a new project from scratch.
    void init_commnad() {
      // TODO: find a better solution for more dynamic user interaction.
      system("./scripts/init_project.sh");
    }
    /// Run the project, directory.
    void run_command() {
      // TODO: make this workie.
    }
    /// Show the version of the Cli.
    void run_version() {
      printf("The Version you are currently on is...\n");
      // TODO: find the users version inside from the path this is installed to.
      printf("%s\n", cli_version.c_str());
    }
  };
} // namespace NativepackCore
