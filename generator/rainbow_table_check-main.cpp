#include <iostream>
#include <chrono>
#include <iomanip>

#include "rainbow_table.hpp"

using namespace std;
using namespace rainbow;

int main(int argc, char *argv[]){
    auto start = std::chrono::high_resolution_clock::now();
    if (argc != 3 && argc != 4){
        std::cerr << "Wrong number of arguments: ";
        for(int i = 0; i < argc; i++){
            std::cerr << argv[i] << " ";
        }
        std::cerr << std::endl;
        std::cerr << "Usage : \"rainbow_table_check-main nb_of_reductions rainbow_table_path, where" << std::endl
                  << "- nb_of_reductions is the number of reduction function to apply," << std::endl
                  << "- rainbow_table_path is the name of the output file where the heads and tails"
                  << " will be stored or you can enters separately each file where " << std::endl
                  << "- heads is the name of the output file where the heads will be stored," << std::endl
                  << "- tails is the name of the output file where the tails will be stored" << std::endl;
        return -1;
    }

    int nb_of_reductions = std::stoi(argv[1]);

    int success = 0;
    if (argc == 3){
        cout << "check the file " << argv[2] << endl;
        success = mass_check(nb_of_reductions, argv[2]);
    }else if (argc == 4){
        cout << "in the heads file " << argv[2] << " and the tails file " << argv[3] << endl;
        success = mass_check(nb_of_reductions, argv[2], argv[3]);
    }else{
        cout << "erreur" << endl;
    }
    std::cout << std::setprecision(4) << success << "% success" << std::endl;

    auto finish = std::chrono::high_resolution_clock::now();
    std::cout << endl
              << std::chrono::duration_cast<std::chrono::nanoseconds>(finish - start).count() << "ns\n";
}
