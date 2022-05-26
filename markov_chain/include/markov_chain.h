#ifndef MARKOV_CHAIN_H
#define MARKOV_CHAIN_H

#include <cstdint>
#include <map>
#include <random>
#include <vector>

/// @brief A simple typedef used by the vectorizer. A vector of vectors of ints.
typedef std::vector<std::vector<int32_t>> ragged_matrix_t;

class Markov_Chain
{
    public:
        /**
         * @brief Construct a new Markov_Chain object.
         * Adds the pad, unknown, start, and end tokens to the chain.
         */
        Markov_Chain();
        /**
         * @brief Create the markov chain.
         *
         * @param data A vector of vectors containing integers that will be used as the node ids.
         * @param vocab_size The max number of nodes to create.
         * @return int Will always return 0.
         */
        int create_chain(const ragged_matrix_t &data, size_t vocab_size);

        /**
         * @brief Traverse the markov chain to create a series of output predictions.
         *
         * @param max_len The maximum number of jumps to do.
         * @return std::vector<int32_t> The id of each node that was landed on.
         */
        std::vector<int32_t> traverse(int max_len = 50) noexcept;

        /**
         * @brief When using the markov chain on text, this function will convert each id to the
         *  token it represents.
         * @param indices The indices returned from traverse.
         * @param vocab  The vocabulary index.
         * @return std::string A string converted from the chain outputs.
         */
        static std::string to_string(const std::vector<int32_t> &indices,
                                     const std::vector<std::string *> &vocab);

    private:
        typedef struct Node {
                int32_t id = 0;
                std::vector<int32_t> next_ids;
                std::vector<int32_t> probs;
                std::discrete_distribution<int32_t> d;
        } node_t;

        std::mt19937 _rand_gen;
        std::vector<node_t> _nodes;

        /// Adds a node to the chain, or if it already exists in prev_node_id, simply increase the
        /// count.
        int _process_id(const int32_t node_id, const int32_t prev_node_id);
        /// Call process_id on each index of line.
        void _process_line(const std::vector<int32_t> &line);
        /// Check if id is already in the next_ids list of the node.
        int _find_index(const std::vector<int32_t> &next_ids, int32_t id) const noexcept;
        /// Create the probability distributions for each node.
        void _finalize_nodes() noexcept;
};
#endif // MARKOV_CHAIN_H
