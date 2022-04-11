#ifndef VECTORIZER_H
#define VECTORIZER_H

#include <cstdint>
#include <string>
#include <unordered_map>
#include <vector>

/// @brief Tokenizes lines of text and creates a vocabulary to be used to
/// vectorize it.
class Vectorizer
{
    public:
        /// @brief Reserves the index 0 of the vocab as "" for the padding token, if needed.
        /// Also reserves the index 1 for the unknown token, "[UNK]".
        Vectorizer();
        Vectorizer(const Vectorizer &) = delete;
        Vectorizer(Vectorizer &&) = delete;

        /// @brief Creates an internal vocabulary with term and document frequencies.
        /// Internally, the input text is standardized and split on whitespace.
        /// @param data: A vector of strings to create a vocabulary from.
        /// @param lower: Whether to change all characters to lowercase. Default false.
        /// @param max_tokens: The number of tokens to keep. Keeps the most frequent. Default -1
        /// means no limit. The actual size of the vocab will be max_tokens - 2 because of the
        /// reserved indices. Acceptable values of max_tokens: -1 or n > 2.
        void create_vocab(std::vector<std::string> data, bool lower = false, int max_tokens = -1);

    private:
        /// @brief Holds the token, and its term and document frequencies.
        struct Token {
                std::string word;
                // Term frequency of this token.
                int64_t tf = 0;
                // The number of documents this token appears in.
                int64_t df = 0;
        };

        // Only used in the `create_vocab` function. It is allocated and deallocated in that
        // function.
        std::unordered_map<std::string, Token> *_tokens;
        std::vector<Token> _vocab;

        /// @brief Remove certain characters from the string,
        /// and add space around punctuation.
        std::string _standardize(std::string &str);

        /// @brief Splits the string on the given delimiter using getline, and returns a vector of
        /// tokens.
        std::vector<std::string> _split(const std::string &str, char delim);

        /// @brief Compute the tf and df of the given vector of strings.
        void _process_tokens(const std::vector<std::string> &tokens);
        /// @brief Compute the document frequency. Uses a set internally to get unique tokens.
        void _process_tokens_df(const std::vector<std::string> &tokens);

        /// @brief Compute the term frequency of the tokens.
        void _process_tokens_tf(const std::vector<std::string> &tokens);

        /// @brief Use the `_tokens` map to create the `_vocab` vector.
        void _create_token_vector(int max_tokens);
};

#endif // VECTORIZER_H
