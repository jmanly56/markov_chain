#include "vectorizer.h"
#include "markov_chain.h"
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
        Markov_Chain m;

        m.create_chain(v, t.vocab_size());
        std::string s = Markov_Chain::to_string(m.traverse(), t.vocab());
        std::cout << s << "\n";


        return 0;
}
