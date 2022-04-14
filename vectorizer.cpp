#include "vectorizer.h"
#include <algorithm>
#include <iostream>
#include <regex>
#include <set>
#include <cmath>
#include <sstream>

const static std::regex chars_to_keep("[^ A-z0-9.?!,]");
const static std::regex chars_add_space("([.?!,])");

Vectorizer::Vectorizer()
{
        _vocab.push_back({"", 0, 0});
        _vocab.push_back({"[UNK]", 0, 0});
}

void Vectorizer::create_vocab(std::vector<std::string> data, bool lower, int max_tokens)
{
        // Allocate the tokens map. This is a pointer so that
        // it isn't sitting around on the stack when I don't need it
        // anymore. The rationale behind this approach is that I need a way to
        // ensure the uniqueness of tokens, and a fast way to insert/update them.
        // However, after the initial creation of the tokens, I need something that
        // I can sort easily, and encapsulates all the data needed. The overhead
        // of the map is no longer required. I find this approach simpler than having to pass
        // a reference to each function that needs it.

        if (max_tokens != -1 && max_tokens < 3) {
                std::cerr << "Invalid parameter max_tokens. Acceptable values: -1 or a number > 2."
                          << " Did not create a vocabulary.\n";
                return;
        }
        _num_documents = data.size();
        _tokens = new std::unordered_map<std::string, Token>{};

        // I take this approach so as to avoid rechecking lower everytime
        // the lambda is run.
        if (lower) {
                auto process_data = [&](std::string &s) {
                        std::transform(s.begin(), s.end(), s.begin(),
                                       [](unsigned char c) { return std::tolower(c); });
                        s = _standardize(s);
                        std::vector<std::string> v = _split(s, ' ');
                        _process_tokens(v);
                };

                std::for_each(data.begin(), data.end(), process_data);
        } else {
                auto process_data = [&](std::string &s) {
                        s = _standardize(s);
                        std::vector<std::string> v = _split(s, ' ');
                        _process_tokens(v);
                };
                std::for_each(data.begin(), data.end(), process_data);
        }

        // Remove empty string from the token list.
        // It will however still appear in vocab.
        _tokens->erase("");

        _create_token_vector(max_tokens);

        _tokens->clear();
        delete _tokens;
}

ragged_matrix_t Vectorizer::vectorize(std::vector<std::string> &data, bool lower)
{
        ragged_matrix_t vectors;
        vectors.reserve(data.size());
        auto vectorize_line = [&](std::string &line) { vectors.push_back(_create_id_array(line, lower)); };

        std::for_each(data.begin(), data.end(), vectorize_line);
        return vectors;
}

const std::vector<std::string *> &Vectorizer::vocab() const
{
        return _reverse_lookup;
}

size_t Vectorizer::vocab_size() const
{
        return _reverse_lookup.size();
}

std::string Vectorizer::_standardize(std::string &str)
{
        str = std::regex_replace(str, chars_to_keep, "");

        // Add spaces around any character in the capture group, denoted by `\1`.
        str = std::regex_replace(str, chars_add_space, " $1 ");

        // Trim whitespace at the end.
        std::string::iterator end = std::remove(str.end(), str.end(), ' ');
        str.erase(end, str.end());

        return str;
}

void Vectorizer::_create_token_vector(int max_tokens)
{
        for (auto iter = _tokens->begin(); iter != _tokens->end(); ++iter) {
                iter->second.word = iter->first; // Assign the word to the token object.
                _vocab.push_back(std::move(iter->second));
        }
        // When passed to sort, will sort items based on descending order of `tf`.
        auto comp = [](const Token &a, const Token &b) { return b.tf < a.tf; };
        // Regardless of max_tokens, we need to sort based on term frequency.
        // The reason for the + 2 is to skip the padding and unknown tokens.
        // We want those to always be index 0 and 1, respectively.
        std::sort(_vocab.begin() + 2, _vocab.end(), comp);
        if (max_tokens != -1) {
                _vocab.resize(max_tokens);
                _vocab.shrink_to_fit();
        }

        // Create a vector of words, where the index is their integer representation.
        std::for_each(_vocab.begin(), _vocab.end(),
                      [&](Token &t) { _reverse_lookup.push_back(&(t.word)); });
}

std::vector<int32_t> Vectorizer::_create_id_array(std::string &line, bool lower) noexcept
{
        static std::vector<std::string> split_line;
        std::vector<int32_t> v;
        // split_line.clear();
        if (lower) {
                std::transform(line.begin(), line.end(), line.begin(),
                               [](unsigned char c) { return std::tolower(c); });
        }
        line = _standardize(line);
        split_line = _split(line, ' ');
        v.reserve(split_line.size());

        auto find_indexes = [&](std::string &word) {
                auto it = std::find_if(_reverse_lookup.begin(), _reverse_lookup.end(),
                                       [&](std::string *a) { return *a == word; });
                if (it == _reverse_lookup.end()) {
                        v.push_back(UNK_INDEX);
                } else {
                        v.push_back(std::distance(_reverse_lookup.begin(), it));
                }
        };

        std::for_each(split_line.begin(), split_line.end(), find_indexes);
        return v;
}

std::vector<std::string> Vectorizer::_split(const std::string &str, char delim)
{
        std::vector<std::string> split_str;
        std::stringstream ss(str);
        std::string substr;

        while (getline(ss, substr, delim)) {
                split_str.push_back(substr);
        }
        auto it = std::remove_if(split_str.begin(), split_str.end(),
                                       [&](std::string s) { return s == ""; });
        split_str.erase(it, split_str.end());
        return split_str;
}

void Vectorizer::_process_tokens(const std::vector<std::string> &tokens)
{
        _process_tokens_df(tokens);
        _process_tokens_tf(tokens);
}

void Vectorizer::_process_tokens_df(const std::vector<std::string> &tokens)
{
        // Uses a set to get the unique tokens in the string.
        // Document frequency is only a count of the total number of documents,
        // or in the case of this class, the number of lines containing a specific token.
        std::set<std::string> unique_tokens(tokens.begin(), tokens.end());
        auto increase_df = [&](std::string token) {
                Token *t = &(*_tokens)[token];
                t->df += 1;
        };
        std::for_each(unique_tokens.begin(), unique_tokens.end(), increase_df);
}

void Vectorizer::_process_tokens_tf(const std::vector<std::string> &tokens)
{
        auto increase_tf = [&](std::string token) {
                Token *t = &(*_tokens)[token];
                t->tf += 1;
        };
        std::for_each(tokens.begin(), tokens.end(), increase_tf);
}
