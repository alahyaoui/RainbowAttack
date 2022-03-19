#include <iostream>
#include <chrono>

#include "rainbow_table.hpp"

using namespace std;
using namespace rainbow;

int main(int argc, char *argv[]){
    auto start = std::chrono::high_resolution_clock::now();
    if (argc != 5 && argc != 6){
        std::cerr << "Usage : \"rainbow_table-main_gen nb_of_chains nb_of_reduction pwd_size rainbow_table_path, where" << std::endl
                  << "- nb_of_chains is the number of heads and tails that you want to generate," << std::endl
                  << "- nb_of_reductions is the number of reduction function to apply," << std::endl
                  << "- pwd_size is the allowed size of the head," << std::endl
                  << "- rainbow_table_path is the name of the output file where the heads and tails"
                  << " will be stored or you can enters separately each file where " << std::endl
                  << "- heads is the name of the output file where the heads will be stored," << std::endl
                  << "- tails is the name of the output file where the tails will be stored" << std::endl;
        return 1;
    }

    int nb_of_chains = std::stoi(argv[1]);
    int nb_of_reductions = std::stoi(argv[2]);
    int pwd_size = std::stoi(argv[3]);

    cout << "You decided to generate " << nb_of_chains << " chains" << endl;
    cout << "with each "<< nb_of_reductions << " reduction functions applied" << endl;
    cout << "with each heads of size "<< pwd_size << endl;

    if (argc == 5){
        cout << "in the file " << argv[4] << endl;
        mass_generate(nb_of_chains, nb_of_reductions, pwd_size, argv[4]);
    }else if (argc == 6){
        cout << "in the heads file " << argv[4] << " and the tails file " << argv[5] << endl;
        mass_generate(nb_of_chains, nb_of_reductions, pwd_size, argv[4], argv[5]);
    }else{
        cout << "error" << endl;
    }

    auto finish = std::chrono::high_resolution_clock::now();
    std::cout << endl
              << std::chrono::duration_cast<std::chrono::nanoseconds>(finish - start).count() << "ns\n";
}
