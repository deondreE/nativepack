#pragma once

#include <cctype>

#include "../core.h"

namespace NativepackCore {
class Lexer {
 public:
  enum class TokenTypeHTML {
    StartTag,
    EndTag,
    Attribute,
    Text,
    OpenBracket,
    CloseBracket,
    Equals,
    DoubleQuote,
    SingleQuote,
    ScriptStart,
    ScriptEnd,
    EOFToken,
  };

  struct TokenHTML {
    TokenTypeHTML type;
    std::string value;
  };

  class JavaScriptLexer {
   private:
    std::string input;
    size_t position;

   public:
    enum class TokenType {
      Keyword,
      Identifier,
      NumericLiteral,
      StringLiteral,
      Operator,
      Punctuation,
      Comment,
      Whitespace,
      EOFToken,
    };

    struct Token {
      TokenType type;
      std::string value;
    };

    JavaScriptLexer(const std::string& code) : input(code), position(0) {}

    Token getNextToken() {
      if (position >= input.size()) {
        return {TokenType::EOFToken, ""};
      }

      char currentChar = input[position++];

      if (std::isalpha(currentChar) || currentChar == '_') {
        return scanIdentifier(currentChar);
      } else if (std::isdigit(currentChar)) {
        return scanNumericLiteral(currentChar);
      } else if (currentChar == '"' || currentChar == '\'') {
        return scanStringLiteral(currentChar);
      } else if (isOperator(currentChar)) {
        return {TokenType::Operator, std::string(1, currentChar)};
      } else if (isPunctuation(currentChar)) {
        return {TokenType::Punctuation, std::string(1, currentChar)};
      } else if (currentChar == '/') {
        if (position < input.size() && input[position] == '/') {
          return scanSingleLineComment();
        } else if (position < input.size() && input[position] == '*') {
          return scanMultiLineComment();
        }
      } else if (std::isspace(currentChar)) {
        return {TokenType::Whitespace, std::string(1, currentChar)};
      }

      return {TokenType::EOFToken,
              ""};  // Placeholder for unrecognized characters
    }

    std::string tokenTypeName(TokenType type) {
      switch (type) {
        case TokenType::Keyword:
          return "Keyword";
        case TokenType::Identifier:
          return "Identifier";
        case TokenType::NumericLiteral:
          return "NumericLiteral";
        case TokenType::StringLiteral:
          return "StringLiteral";
        case TokenType::Operator:
          return "Operator";
        case TokenType::Punctuation:
          return "Punctuation";
        case TokenType::Comment:
          return "Comment";
        case TokenType::Whitespace:
          return "Whitespace";
        case TokenType::EOFToken:
          return "EOFToken";
        default:
          return "Unknown";
      }
    }

   private:
    Token scanIdentifier(char initialChar) {
      std::string identifier;
      identifier += initialChar;

      while (position < input.size() &&
             (std::isalnum(input[position]) || input[position] == '_')) {
        identifier += input[position++];
      }

      return {TokenType::Identifier, identifier};
    }

    Token scanNumericLiteral(char initialChar) {
      std::string literal;
      literal += initialChar;

      while (position < input.size() &&
             (std::isdigit(input[position]) || input[position] == '.')) {
        literal += input[position++];
      }

      return {TokenType::NumericLiteral, literal};
    }

    Token scanStringLiteral(char delimiter) {
      std::string literal;
      literal += delimiter;

      while (position < input.size() && input[position] != delimiter) {
        literal += input[position++];
      }

      if (position < input.size()) {
        literal += input[position++];  // Include the closing delimiter
      }

      return {TokenType::StringLiteral, literal};
    }

    Token scanSingleLineComment() {
      std::string comment;
      comment += "//";

      while (position < input.size() && input[position] != '\n') {
        comment += input[position++];
      }

      return {TokenType::Comment, comment};
    }

    Token scanMultiLineComment() {
      std::string comment;
      comment += "/*";

      while (position < input.size() - 1 &&
             !(input[position] == '*' && input[position + 1] == '/')) {
        comment += input[position++];
      }

      if (position < input.size() - 1) {
        comment += "*/";
        position += 2;  // Skip the closing */
      }

      return {TokenType::Comment, comment};
    }

    bool isOperator(char ch) {
      // TODO: Add more operators as needed
      return (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '=' ||
              ch == '<' || ch == '>');
    }

    bool isPunctuation(char ch) {
      // TODO: Add more punctuation symbols as needed
      return (ch == ';' || ch == ',' || ch == '(' || ch == ')' || ch == '{' ||
              ch == '}');
    }
  };

  Lexer(const std::string& html) : input(html), position(0) {}

  TokenHTML getNextToken() {
    if (position >= input.size()) {
      return {TokenTypeHTML::EOFToken, ""};
    }

    char currentChar = input[position++];

    switch (currentChar) {
      case '<':
        return {TokenTypeHTML::OpenBracket, "<"};
      case '>':
        return {TokenTypeHTML::CloseBracket, ">"};
      case '=':
        return {TokenTypeHTML::Equals, "="};
      case '"':
        return {TokenTypeHTML::DoubleQuote, "\""};
      case '\'':
        return {TokenTypeHTML::SingleQuote, "\'"};
      case '/':
        if (position < input.size() && input[position] == '/') {
          return scanScript();
        }
      default:
        if (isalpha(currentChar)) {
          return scanTag();
        } else if (isspace(currentChar)) {
          return getNextToken();  // Ignore whitespace.
        } else {
          return scanText(currentChar);
        }
    }

    return {TokenTypeHTML::Text, std::string(1, currentChar)};
  }

 private:
  std::string input;
  size_t position;

  TokenHTML scanTag() {
    std::string tagValue;
    tagValue += input[position - 1];

    while (position < input.size() &&
           (isalnum(input[position]) || input[position] == '-')) {
      tagValue += input[position++];
    }

    if (tagValue.front() == '<') {
      return {TokenTypeHTML::StartTag, tagValue};
    } else {
      return {TokenTypeHTML::EndTag, tagValue};
    }
  }

  TokenHTML scanText(char initialChar) {
    std::string textValue;
    textValue += initialChar;

    while (position < input.size() && input[position] != '<') {
      textValue += input[position++];
    }

    return {TokenTypeHTML::Text, textValue};
  }

  TokenHTML scanScript() {
    // scan javascript code until end of the line.
    std::string scriptValue;
    while (position < input.size() && input[position] != '\n') {
      scriptValue += input[position++];
    }

    return {TokenTypeHTML::ScriptStart, scriptValue};
  }
};
};  // namespace NativepackCore
