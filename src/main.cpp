#include "vectorizer.h"
#include <fstream>
#include <iostream>

int main()
{
        std::vector<std::string> data;
        std::ifstream f("./data/messages_modified.txt");
        std::string line;

        while (std::getline(f, line)) {
                data.push_back(line);
        }

        Vectorizer t;
        t.create_vocab(data);
        ragged_matrix_t v = t.vectorize(data);
        return 0;
}
