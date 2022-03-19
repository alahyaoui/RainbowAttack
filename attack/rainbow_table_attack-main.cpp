#include <iostream>
#include <chrono>
#include <fstream>
#include <vector>

#include "rainbow_attack.hpp"
using namespace std;

int nbThreads = 0;
std::vector<bool> is_pwd_found;

int main(int argc, char *argv[]){
    auto start = std::chrono::high_resolution_clock::now();
    if(argc != 5){
        std::cerr << "Wrong number of arguments: ";
        for(int i = 0; i < argc; i++){
            std:cerr << argv[i] << " ";
        }
        std::cerr << std::endl;
        std::cerr << "Usage : \"rainbow_table_attack-main nb_of_reductions pwd_size rainbow_table_path hash_to_crack_path, where" << std::endl    
            << "- nb_of_reductions the number of reduction function that have been executed to make the a chain of the RT," << std::endl    
            << "- pwd_size the size of the heads of the given RT," << std::endl 
            << "- rainbow_table_path the path of the file of the Rainbow Table," << std::endl
            << "- hash_to_crack_path is the path of the file of hashes to crack" << std::endl;
        return -1;
    }

    int nb_of_reductions = std::stoi(argv[1]);
    int pwd_size = std::stoi(argv[2]);
    string rainbow_table_path = argv[3];
    string hash_to_crack_path = argv[4];
    
    std::ifstream hash_file;
    hash_file.open(hash_to_crack_path);

    std::string hash;
    int count_line = 1;
    while(std::getline(hash_file, hash)){
        cout << "hash to crack n*" << count_line++ << " -> "<< hash << std::endl;
        is_pwd_found.push_back(rainbow::attack(hash, pwd_size, nb_of_reductions, rainbow_table_path));
    }

    int count = 0; 
    for(auto e : is_pwd_found){
        std::cout << "pwd n*" << count << " found : " << e << std::endl;
        count++;
    }

    hash_file.close();

    auto finish = std::chrono::high_resolution_clock::now();
    std::cout << endl<<std::chrono::duration_cast<std::chrono::nanoseconds>(finish-start).count() << "ns\n";
}
