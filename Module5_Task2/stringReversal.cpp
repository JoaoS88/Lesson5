#include <iostream>
#include <string>
#include <sstream>
#include <vector>
//Task2:

// function to get the string from the user
inline std::string getStringFromUser()
{
    std::string str;
    std::cout << "Enter a string: ";
    // get line in console and store in std::string "str" then return it
    std::getline(std::cin, str);
    return str;
}

// function to reverse the words in the string but keep each word the same
std::string reverseWords(const std::string& str)
{
    std::istringstream stream(str); // create a string stream to break the string into words
    std::vector<std::string> words;
    std::string word;

    // split the string into words
    while (stream >> word)
    {
        words.push_back(word);
    }

    // reverse the order of the words
    std::string reversed;
    for (int i = words.size() - 1; i >= 0; --i)
    {
        reversed += words[i]; // add each word to the reversed string
        if (i != 0)  // add space between words except for the last one
        {
            reversed += " ";
        }
    }

    return reversed;
}

int main()
{

    // Test everything works:
    std::cout << reverseWords(getStringFromUser()) << std::endl;

    return 0;
}