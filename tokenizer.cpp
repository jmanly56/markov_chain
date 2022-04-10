#include "tokenizer.h"
#include <algorithm>
#include <sstream>

const static std::regex chars_to_keep("[^ A-z0-9.?!,]");
const static std::regex chars_add_space("([.?!,])");

void Tokenizer::create_vocab(std::vector<std::string> data)
{
        // Allocate the tokens map. This is a pointer so that
        // it isn't sitting around on the stack when I don't need it
        // anymore. The rationale behind this approach is that I need a way to
        // ensure the uniqueness of tokens, and a fast way to insert/update them.
        // However, after the initial creation of the tokens, I need something that
        // I can sort easily, and encapsulates all the data needed. The overhead
        // of the map is no longer required.
        _tokens = new std::unordered_map<std::string, Token>();

        auto process_data = [&](std::string s) {
                s = _standardize(s);
                std::vector<std::string> v = _split(s, ' ');
                _process_tokens(v);
        };
        std::for_each(data.begin(), data.end(), process_data);

        auto result = _tokens->find("");
        _tokens->erase(""); // Remove empty string from the token list.

        create_token_vector();

        _tokens->clear();
        delete _tokens;
}

std::string Tokenizer::_standardize(std::string &str)
{
        str = std::regex_replace(str, chars_to_keep, "");
        str = std::regex_replace(str, chars_add_space, " \1 ");
        std::string::iterator end = std::remove(str.end(), str.end(), ' ');
        str.erase(end, str.end());

        return str;
}

void Tokenizer::create_token_vector()
{
        for (auto iter = _tokens->begin(); iter != _tokens->end(); iter++) {
                iter->second.word = iter->first;
                _vocab.push_back(std::move(iter->second));
        }
}

std::vector<std::string> Tokenizer::_split(const std::string &str, char delim)
{
        std::vector<std::string> split_str;
        std::stringstream ss(str);
        std::string substr;

        while (getline(ss, substr, delim)) {
                split_str.push_back(substr);
        }
        return split_str;
}

void Tokenizer::_process_tokens(const std::vector<std::string> &tokens)
{
        _process_tokens_df(tokens);
        _process_tokens_tf(tokens);
}

void Tokenizer::_process_tokens_df(const std::vector<std::string> &tokens)
{
        std::set<std::string> unique_tokens(tokens.begin(), tokens.end());
        auto increase_df = [&](std::string token) {
                Token *t = &(*_tokens)[token];
                t->df += 1;
        };
        std::for_each(unique_tokens.begin(), unique_tokens.end(), increase_df);
}

void Tokenizer::_process_tokens_tf(const std::vector<std::string> &tokens)
{
        auto increase_tf = [&](std::string token) {
                Token *t = &(*_tokens)[token];
                t->tf += 1;
        };
        std::for_each(tokens.begin(), tokens.end(), increase_tf);
}
