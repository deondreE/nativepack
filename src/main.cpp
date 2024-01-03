#include <iostream>
#include <memory>
#include <string>

// #include "cli.h"
// #include "config.h"
#include "lexer/lexer.h"
#include "logger.h"

int main(int argc, char* argv[]) {
  // bool running = false;
  // // Make sure the user provides arguments...
  // if (argc == 1) {
  //   Logger::GetInstance().error() << "Run --help for more information";
  // } else {
  //   running = true;
  // }
  //
  // if (running) {
  //
  // }

  // auto* cli = new NativepackCore::Cli();
  // cli->findCommand(argv[1]);
  std::string html =
      "<html><head><title>Hello World</title></head><body><p>This is a sample "
      "HTML document</p></body><script>alert('Hello from "
      "JavaScript!');</script></html>";
  std::string jsCode = R"(
         // JavaScript code example

        // Variable declaration and assignment
        var x = 5;
        var y = 10;

        // Arithmetic operations
        var sum = x + y;
        var product = x * y;

        // Console output
        console.log("Sum:", sum);
        console.log("Product:", product);

        // Conditional statement
        if (sum > 10) {
            console.log("Sum is greater than 10");
        } else {
            console.log("Sum is not greater than 10");
        }

        // Function declaration
        function greet(name) {
            console.log("Hello, " + name + "!");
        }

        // Function call
        greet("John");

        // Array creation and iteration
        var numbers = [1, 2, 3, 4, 5];
        for (var i = 0; i < numbers.length; i++) {
            console.log("Element at index " + i + ": " + numbers[i]);
        }

        // Object creation and property access
        var person = {
            firstName: "Alice",
            lastName: "Smith",
            age: 25
        };

        console.log("Person: ", person.firstName, person.lastName, "(" + person.age + " years old)
    )";
  NativepackCore::Lexer lexer(html);
  NativepackCore::Lexer::JavaScriptLexer jsLexer(jsCode);

  NativepackCore::Lexer::TokenHTML token;
  NativepackCore::Lexer::JavaScriptLexer::Token jsToken;
  do {
    jsToken = jsLexer.getNextToken();
    std::cout << "Token type: " << jsLexer.tokenTypeName(jsToken.type)
              << ", Value: '" << jsToken.value << "'\n";
  } while (jsToken.type !=
           NativepackCore::Lexer::JavaScriptLexer::TokenType::EOFToken);
  return 0;
}
