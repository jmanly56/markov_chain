#include "tokenizer.h"
#include <algorithm>
#include <sstream>

const static std::regex chars_to_keep("[^ A-z0-9.?!,]");
const static std::regex chars_add_space("([.?!,])");

int Tokenizer::create_vocab(std::vector<std::string> data)
{ 
        for (auto iter = data.begin(); iter != data.end();) {
                std::string s = *iter;


        }
        return 0;
}

std::string Tokenizer::standardize(std::string& str)
{
        str = std::regex_replace(str, chars_to_keep, "");
        str = std::regex_replace(str, chars_add_space, " \1 ");
        std::string::iterator end = std::remove(str.end(), str.end(), ' ');
        str.erase(end, str.end());
        
        return str;
}

std::vector<std::string> Tokenizer::split(const std::string& str, char delim)
{
        std::vector<std::string> split_str;
        std::stringstream ss(str);
        std::string substr;

        while (getline(ss, substr, delim)) {
                split_str.push_back(substr);
        }

        return split_str;
}
