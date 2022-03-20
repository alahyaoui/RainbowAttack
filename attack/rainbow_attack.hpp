#ifndef GENRAINBOWTABLEUTILS_HPP
#define GENRAINBOWTABLEUTILS_HPP

#include <cstring>
#include <fstream>
#include <string>

#include "../utils/reduction.hpp"
#include "../utils/sha256.h"

namespace rainbow {

int size;

std::string generate_tail(std::string hash, const int& pos, const int& nb_of_reductions) {
    std::string tail;

    for (size_t i = pos; i < nb_of_reductions; i++) {
        tail = reduce(hash, i, size);
        hash = sha256(tail);
    }

    tail = reduce(hash, nb_of_reductions, size);
    return tail;
}

std::string find_in_chain(const std::string& head, const std::string& hash_to_crack, const int& nb_of_reductions) {
    std::string pwd = head;
    std::string hash;

    for (size_t i = 1; i < nb_of_reductions + 1; i++) {
        hash = sha256(pwd);
        if (strcmp(hash_to_crack.c_str(), hash.c_str()) == 0) {
            return pwd;
        }
        pwd = reduce(hash, i, size);
    }

    return "";
}

std::string find_in_rainbow_table_file(const std::string& tail_generated, const std::string& hash_to_crack, const int& nb_of_reductions, const std::string& rainbow_table_path) {
    std::ifstream rainbow_table_file;
    rainbow_table_file.open(rainbow_table_path);

    if (rainbow_table_file.is_open()) {
        std::string head_tail;
        std::string head;
        std::string tail;

        rainbow_table_file.clear();
        rainbow_table_file.seekg(0);

        while (std::getline(rainbow_table_file, head_tail)) {
            int lineSeparator = head_tail.find(":");

            tail = head_tail.substr(lineSeparator + 1);
            if (strcmp(tail_generated.c_str(), tail.c_str()) == 0) {
                head = head_tail.substr(0, lineSeparator);

                std::string pwd_in_chain = find_in_chain(head, hash_to_crack, nb_of_reductions);
                if (pwd_in_chain != "")
                    return pwd_in_chain;
            }
        }

        rainbow_table_file.close();
    } else
        throw std::runtime_error("Input files could not be opened");
    return "";
}

bool attack(std::string hash_to_crack, const int& pwd_size, const int& nb_of_reductions, const std::string& rainbow_table_path) {
    std::string tail;
    std::string pwd;

    size = pwd_size;
    bool is_found = false;
    int i = nb_of_reductions;
    while (is_found == false && i > 0) {
        tail = generate_tail(hash_to_crack, i, nb_of_reductions);
        pwd = find_in_rainbow_table_file(tail, hash_to_crack, nb_of_reductions, rainbow_table_path);

        if (pwd != "") {
            if (strcmp(sha256(pwd).c_str(), hash_to_crack.c_str()) == 0) {
                is_found = true;
                std::cout << "pwd found " << pwd << ":" << hash_to_crack << std::endl;
                break;
            }
        }
        i--;
    }
    return is_found;
}

}  // namespace rainbow

#endif  // GENRAINBOWTABLEUTILS_HPP
