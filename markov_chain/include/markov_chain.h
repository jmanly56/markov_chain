#ifndef MARKOV_CHAIN_H
#define MARKOV_CHAIN_H

#include <cstdint>
#include <vector>
#include <random>

#define PAD_INDEX 0
#define UNK_INDEX 1

/// @brief A simple typedef used by the vectorizer. A vector of vectors of ints.
typedef std::vector<std::vector<int32_t>> ragged_matrix_t;

class Markov_Chain {
public:
        Markov_Chain();
        int create_chain(const ragged_matrix_t& data);
private:
        static std::default_random_engine _rand_gen;
        static std::uniform_real_distribution<float> uniform;
        struct Node {
                int32_t id = 0;
                std::vector<int32_t> next_ids;
                std::vector<float> next_id_probabilities;
        };
        std::vector<Node> _nodes;
        int _add_node(const int32_t node_id);
};
#endif // MARKOV_CHAIN_H
