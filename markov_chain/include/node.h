#ifndef NODE_H
#define NODE_H

#include <vector>

typedef struct Node {
        int32_t id = 0;
        std::map<int32_t, int32_t> next_ids;
        std::vector<float> probs;
} node_t;

#endif // NODE_H
