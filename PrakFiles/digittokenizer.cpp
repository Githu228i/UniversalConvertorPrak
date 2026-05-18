#include "digittokenizer.h"

DigitTokenizer::DigitTokenizer() : memory(""), memory_start(0) {}

std::string DigitTokenizer::CharToDigit(std::string input) {
    bool IsOpen = false;
    for(int i = 0; i < input.size(); ++i) {
        char part = input[i];
        if (part == '[') IsOpen = true;
        if (part == ']') IsOpen = false;
        if(memory == "" && part == '[') {
            memory_start = i;
            memory += part;
            continue;
        } else if(memory == "[" && ((part >= 'A' && part <= 'Z') || (part >= 'a' && part <= 'z'))) {
            memory += part;
            continue;
        } else if(memory.size() == 2 && part == ']') {
            memory += part;
            std::string temp;
            char c = std::toupper(memory[1]);
            int num = (c - 'A') + 10;
            temp = "[" + std::to_string(num) + "]";
            input.replace(memory_start, 3, temp);
            i += temp.size() - 3;
        } else if (memory == "" && part >= 'A' && part <= 'Z') {
            std::string temp;
            int num = (part - 'A') + 10;
            temp = "[" + std::to_string(num) + "]";
            input.replace(i, 1, temp);
            i += temp.size() - 1;
        } else if (memory == "" && part >= 'a' && part <= 'z') {
            std::string temp;
            int num = (part - 'a') + 10;
            temp = "[" + std::to_string(num) + "]";
            input.replace(i, 1, temp);
            i += temp.size() - 1;
        } else if (memory == "" && part >= '0' && part <= '9' && IsOpen == false) {
            std::string temp;
            temp += "[";
            temp += part;
            temp += "]";
            input.replace(i, 1, temp);
            i += temp.size() - 1;
        }
        memory = "";
    }
    return input;
}
