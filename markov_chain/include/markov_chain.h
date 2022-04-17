#ifndef MARKOV_CHAIN_H
#define MARKOV_CHAIN_H

#include <cstdint>
#include <vector>
#include <random>

#define PAD_INDEX 0
#define UNK_INDEX 1

typedef std::vector<std::vector<int32_t>> ragged_matrix_t;

class Markov_Chain {
public:
        Markov_Chain();
        int create_chain(const ragged_matrix_t& data);
private:
        static std::default_random_engine _rand_gen;
        struct Node {
                ~Node() {
                        delete next_ids;
                        delete next_id_counts;
                        delete d;
                }
                int32_t id = 0;
                size_t size = 0;
                int32_t *next_ids = nullptr;
                int32_t *next_id_counts = nullptr;
                std::discrete_distribution<int32_t> *d = nullptr;
        };
        std::vector<Node> _nodes;
};
#endif // MARKOV_CHAIN_H
