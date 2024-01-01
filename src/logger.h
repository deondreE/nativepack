// Copyright -- deondreE / Nativepack Core Team.
#pragma once
#include "core.h"

enum class LogLevel { Trace, Info, Warning, Error };
struct LogInstance {
  std::string logger_name;
};

class Logger {
 public:
  ~Logger() { std::cout.flush(); }

  // Gets the singleton instance, for the loggers lifetime...
  static Logger &GetInstance() {
    static Logger instance;
    return instance;
  }

  class LoggerProxy {
   public:
    LoggerProxy(LogLevel level, const Ref<LogInstance> &coreLogger)
        : m_Level(level), m_CoreLogger(coreLogger) {}

    template <typename T>
    LoggerProxy &operator<<(const T &value) {
      std::string colorCode;
      switch (m_Level) {
        case LogLevel::Trace:
          colorCode = "\033[37m";  // White
          break;
        case LogLevel::Info:
          colorCode = "\033[32m";  // Green
          break;
        case LogLevel::Warning:
          colorCode = "\033[33m";  // Yellow
          break;
        case LogLevel::Error:
          colorCode = "\033[31m";  // Red
          break;
        default:
          colorCode = "\033[0m";  // Reset color
      }

      // Get the current time from the system clock...
      auto now = std::chrono::system_clock::to_time_t(
          std::chrono::system_clock::now());
      std::tm timeinfo = *std::localtime(&now);

      // Format the timestamp...
      std::stringstream timestampStream;
      timestampStream << LogLevelToString(m_Level) << "] ["
                      << std::put_time(&timeinfo, "%Y-%m-%d %H:%M:%S");
      std::string timestamp = timestampStream.str();

      // construct the output stream.
      std::ostringstream logMessage;
      logMessage << colorCode << "[" << timestamp << "] ["
                 << m_CoreLogger->logger_name << "]\n"
                 << value << '\n'
                 << "\033[0m";  // Reset color

      std::cout << logMessage.str();

      return *this;
    }

   private:
    LogLevel m_Level;
    Ref<LogInstance> m_CoreLogger;

    // Takes in possible log level...
    static std::string LogLevelToString(LogLevel level) {
      switch (level) {
        case LogLevel::Trace:
          return "TRACE";
        case LogLevel::Info:
          return "INFO";
        case LogLevel::Warning:
          return "WARNING";
        case LogLevel::Error:
          return "ERROR";
        default:
          return "";
      }
    }
  };

  LoggerProxy trace() { return LoggerProxy(LogLevel::Trace, m_CoreLogger); }
  LoggerProxy info() { return LoggerProxy(LogLevel::Info, m_CoreLogger); }
  LoggerProxy warning() { return LoggerProxy(LogLevel::Warning, m_CoreLogger); }
  LoggerProxy error() { return LoggerProxy(LogLevel::Error, m_CoreLogger); }

 private:
  Logger() {
    m_CoreLogger = std::make_shared<LogInstance>();
    m_CoreLogger->logger_name = "Core Logger";
  }

  Ref<LogInstance> m_CoreLogger;
};
