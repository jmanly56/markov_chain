#ifndef TOKENIZER_H
#define TOKENIZER_H

#include <regex>
#include <set>
#include <string>
#include <vector>

class Tokenizer {
public:
  int create_vocab(std::vector<std::string> data);

private:
  struct Token {
    std::string string;
    int count = 0;
    bool operator<(Token &rhs) { return this->count < rhs.count; }
  };
  std::set<Token> _tokens;
  std::string standardize(std::string &str);
  std::vector<std::string> split(const std::string &str, char delim);
};

#endif // TOKENIZER_H
