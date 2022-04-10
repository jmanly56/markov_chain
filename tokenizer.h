#ifndef TOKENIZER_H
#define TOKENIZER_H

#include <cstdint>
#include <regex>
#include <set>
#include <string>
#include <unordered_map>
#include <vector>

class Tokenizer
{
    public:
        void create_vocab(std::vector<std::string> data);

    private:
        struct Token {
                std::string word;
                int64_t tf = 0; // Term frequency.
                int64_t df = 0; // Document frequency.
        };
        std::unordered_map<std::string, Token> *_tokens;
        std::vector<Token> _vocab;
        // std::vector<token_t>

        void create_token_vector();
        std::string _standardize(std::string &str);
        std::vector<std::string> _split(const std::string &str, char delim);
        void _process_tokens(const std::vector<std::string> &tokens);
        void _process_tokens_df(const std::vector<std::string> &tokens);
        void _process_tokens_tf(const std::vector<std::string> &tokens);
};

#endif // TOKENIZER_H
