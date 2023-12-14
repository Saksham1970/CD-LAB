#include <iostream>
#include <string>
#include <unordered_set>
using namespace std;
int main() {
    // Define a set of C++ keywords
    ///constant-time average complexity for searching, making it efficient for checking if a word is a keyword or not
   unordered_set<std::string> cppKeywords = {"auto", "bool", "break", "char", "double", "else", "false", "float", "for", "if","int", "long", "private", "protected", "public", "return",  "void", "while" };
       // Get user input
    string userInput;
    cout << "Enter a word: ";
    cin >> userInput;
    
    if (cppKeywords.count(userInput) > 0) {
        std::cout << "\"" << userInput << "\" is a C++ keyword." << std::endl;
    } else {
        std::cout << "\"" << userInput << "\" is not a C++ keyword." << std::endl;
    }
    
    return 0;
}

