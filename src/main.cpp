#include "vectorizer.h"
#include "markov_chain.h"
#include <fstream>
#include <iostream>
#include <chrono>

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
        auto start = std::chrono::high_resolution_clock::now();
        m.create_chain(v, t.vocab_size());
        auto chain_done = std::chrono::high_resolution_clock::now();
        std::string s = Markov_Chain::to_string(m.traverse(), t.vocab());
        auto traverse_and_convert = std::chrono::high_resolution_clock::now();
        auto start_chain = std::chrono::duration<double, std::milli>(chain_done - start);
        auto chain_traverse = std::chrono::duration<double, std::milli>(traverse_and_convert - chain_done);
        auto total_time = std::chrono::duration<double, std::milli>(traverse_and_convert - start);

        std::cout << s << "\n";
        std::cout << "Total time to create and traverse chain once: " << total_time.count()
                  << "ms\nTime to create chain: " << start_chain.count()
                  << "ms\nTime to traverse the chain once and convert to a string: "
                  << chain_traverse.count() << "ms\n";


        return 0;
}
