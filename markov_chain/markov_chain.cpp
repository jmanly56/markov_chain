#include "include/markov_chain.h"
#include "../vectorizer/include/vectorizer.h"

#include <algorithm>
#include <chrono>
#include <cmath>
#include <sstream>

Markov_Chain::Markov_Chain()
{
        _nodes.reserve(5);
        _nodes.push_back({PAD_INDEX}); // 0
        _nodes.push_back({UNK_INDEX}); // 1
        _nodes.push_back({START_INDEX}); // 2
        _nodes.push_back({END_INDEX}); // 3
        // Initialize to current time.
        this->_rand_gen = std::mt19937(std::chrono::steady_clock::now().time_since_epoch().count());
}

int Markov_Chain::create_chain(const ragged_matrix_t &data, size_t vocab_size)
{
        _nodes.resize(vocab_size);
        for (auto &line : data) {
                if (line.size() > 0)
                        _process_line(line);
        }
        _finalize_nodes();
        return 0;
}

std::vector<int32_t> Markov_Chain::traverse(int max_len) noexcept
{
        std::vector<int32_t> indices;
        Node &n = _nodes[START_INDEX];
        for (int i = 0; i < max_len; i++) {
                n = _nodes[n.next_ids[n.d(_rand_gen)]]; // Select a node to traverse randomly from
                                                        // the distribution.
                if (n.id != END_INDEX) {
                        if (n.id != UNK_INDEX)
                                indices.push_back(n.id);
                } else { // We've reached the END token so exit the function.
                        return indices;
                }
        }
        return indices;
}

std::string Markov_Chain::to_string(const std::vector<int32_t> &indices,
                                    const std::vector<std::string *> &vocab)
{
        std::stringstream ss;
        std::for_each(indices.begin(), indices.end(),
                      [&](int32_t index) { ss << *(vocab[index]) << " "; });
        return ss.str();
}

void Markov_Chain::_process_line(const std::vector<int32_t> &line)
{
        _process_id(line[0], START_INDEX);
        if (line.size() > 2) {
                for (auto it = line.begin() + 1; it != line.end() - 1; ++it) {
                        _process_id(*it, *(it - 1));
                }
                _process_id(END_INDEX, *(line.end() - 1));
        } else {
                _process_id(END_INDEX, line[0]);
        }
}

int Markov_Chain::_find_index(const std::vector<int32_t> &next_ids, int32_t id) const noexcept
{
        for (int i = 0; i < next_ids.size(); i++) {
                if (next_ids[i] == id)
                        return i;
        }
        return -1;
}

void Markov_Chain::_finalize_nodes() noexcept
{
        // Takes the counts inside n.probs and uses them as the weights for the distribution.
        auto create_probabilities = [&](Node &n) {
                n.d = std::discrete_distribution<int32_t>(n.probs.begin(), n.probs.end());
        };
        // + 2 to skip the PAD and UNK tokens.
        std::for_each(_nodes.begin() + 2, _nodes.end(), create_probabilities);
}

int Markov_Chain::_process_id(const int32_t node_id, const int32_t prev_node_id)
{
        _nodes[node_id].id = node_id;
        node_t &prev = _nodes[prev_node_id];
        int index = _find_index(prev.next_ids, node_id);

        if (index != -1) {
                prev.probs[index] += 1;
        } else {
                prev.next_ids.push_back(node_id);
                prev.probs.push_back(1.0f);
        }
        return 0;
}
