#include <iostream>
#include <chrono>

#include "rainbow_table.hpp"

using namespace std;
using namespace rainbow;

int main(int argc, char *argv[]){
    auto start = std::chrono::high_resolution_clock::now();
    if (argc != 5 && argc != 6){
        std::cerr << "Usage : \"gen-RainbowTable-main nb_of_chains nb_of_reduction size_str head_tails, where" << std::endl
                  << "- nb_of_chains is the number of heads and tails that you want to generate," << std::endl
                  << "- nb_of_reductions is the number of reduction function to apply," << std::endl
                  << "- size_str is the allowed size of the head," << std::endl
                  << "- heads_tails is the name of the output file where the heads and the tails"
                  << " will be stored or you can enters separately each file where " << std::endl
                  << "- heads is the name of the output file where the heads will be stored," << std::endl
                  << "- tails is the name of the output file where the tails will be stored" << std::endl;
        return 1;
    }

    int nb_of_chains = std::stoi(argv[1]);
    int nb_of_reductions = std::stoi(argv[2]);
    int size_str = std::stoi(argv[3]);

    cout << "You decided to generate " << nb_of_chains << " chains" << endl;
    cout << "with each "<< nb_of_reductions << " reduction functions applied" << endl;
    cout << "with each heads of size "<< size_str << endl;

    if (argc == 5){
        cout << "in the file " << argv[4] << endl;
        mass_generate(nb_of_chains, nb_of_reductions, size_str, argv[4]);
    }else if (argc == 6){
        cout << "in the heads file " << argv[4] << " and the tails file " << argv[5] << endl;
        mass_generate(nb_of_chains, nb_of_reductions, size_str, argv[4], argv[5]);
    }else{
        cout << "error" << endl;
    }

    auto finish = std::chrono::high_resolution_clock::now();
    std::cout << endl
              << std::chrono::duration_cast<std::chrono::nanoseconds>(finish - start).count() << "ns\n";
}
