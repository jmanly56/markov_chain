#ifndef MARKOV_CHAIN_H
#define MARKOV_CHAIN_H

#include <cstdint>
#include <vector>
#include <map>
#include <random>

/// @brief A simple typedef used by the vectorizer. A vector of vectors of ints.
typedef std::vector<std::vector<int32_t>> ragged_matrix_t;

class Markov_Chain {
public:
        Markov_Chain();
        int create_chain(const ragged_matrix_t& data, size_t vocab_size);
private:
        typedef struct Node{
                int32_t id = 0;
                std::vector<int32_t> next_ids;
                std::vector<int32_t> probs;
                std::discrete_distribution<int32_t> d;
        } node_t;

        static std::default_random_engine _rand_gen;
        std::vector<node_t> _nodes;

        int _process_id(const int32_t node_id, const int32_t prev_node_id);
        void _process_line(const std::vector<int32_t> &line);
        int _find_index(const std::vector<int32_t> &next_ids, int32_t id) const noexcept;
        void _finalize_nodes() noexcept;
};
#endif // MARKOV_CHAIN_H
