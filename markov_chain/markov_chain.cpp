#include "include/markov_chain.h"
#include "../vectorizer/include/vectorizer.h"

#include <algorithm>

Markov_Chain::Markov_Chain(){
        _nodes.reserve(5);
        _nodes.push_back({PAD_INDEX}); // 0
        _nodes.push_back({UNK_INDEX}); // 1
        _nodes.push_back({START_INDEX}); // 2
        _nodes.push_back({END_INDEX}); //3
}

int Markov_Chain::create_chain(const ragged_matrix_t& data, size_t vocab_size)
{
        _nodes.resize(vocab_size);
        std::for_each(data.begin(), data.end(), _process_line);
}

void Markov_Chain::_process_line(const std::vector<int32_t> &line)
{
        _process_id(line[0], START_INDEX);
        for (auto it = line.begin() + 1; it != line.end() - 1;) {
                _process_id(*it, *(it - 1));
        }
        _process_id(END_INDEX, *(line.end()));
}

int Markov_Chain::_process_id(const int32_t node_id, const int32_t prev_node_id)
{
        /*_nodes[node_id].id = node_id;
        Node &n = _nodes[prev_node_id];
        n.next_ids[node_id] += 1;*/
}
