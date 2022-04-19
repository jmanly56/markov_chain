#ifndef MARKOV_CHAIN_H
#define MARKOV_CHAIN_H

#include <cstdint>
#include <vector>
#include <map>
#include <random>
#include "node.h"

/// @brief A simple typedef used by the vectorizer. A vector of vectors of ints.
typedef std::vector<std::vector<int32_t>> ragged_matrix_t;

class Markov_Chain {
public:
        Markov_Chain();
        int create_chain(const ragged_matrix_t& data, size_t vocab_size);
private:
        typedef struct {
                int32_t id = 0;
                std::vector<int32_t> next_ids;
                std::vector<float> probs;
        } node_t;

        static std::default_random_engine _rand_gen;
        static std::uniform_real_distribution<float> uniform;
        std::vector<node_t> _nodes;
        int _process_id(const int32_t node_id, const int32_t prev_node_id);
        void _process_line(const std::vector<int32_t> &line) noexcept;
};
#endif // MARKOV_CHAIN_H
