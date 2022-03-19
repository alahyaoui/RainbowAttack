#ifndef GENRAINBOWTABLEUTILS_HPP
#define GENRAINBOWTABLEUTILS_HPP

#include "../utils/sha256.h"
#include <string>
#include <fstream>
#include <cstring>

#include "../utils/random.hpp"
#include "../utils/reduction.hpp"

namespace rainbow {

std::string generate_head(int length){
    static const std::string char_policy = "azertyuiopqsdfghjklmwxcvbnAZERTYUIOPQSDFGHJKLMWXCVBN1234567890";
    static const int c_len = char_policy.length();

    char str[length + 1];
    for(int i = 0; i < length; i++)
        str[i] = char_policy[ rainbow::random(0, c_len - 1)];
    str[length] = '\0';

    return std::string(str);
}

std::string generate_tail(const std::string & head, int nb_of_reductions){ 
    std::string tail;
    std::string hash = sha256(head);

    int pwd_size = head.size();

    for(size_t i = 1; i < nb_of_reductions; i++){
        tail = reduce(hash, i, pwd_size);
        hash = sha256(tail);
    }

    tail = reduce(hash, nb_of_reductions, pwd_size);
    return std::string(tail);
}

void mass_generate(int nb_of_chains, int nb_of_reductions, int length, const std::string& of_head, const std::string& of_tail){
    std::ofstream head_file;
    head_file.open(of_head);

    std::ofstream tail_file;
    tail_file.open(of_tail);

    if(head_file.is_open() && tail_file.is_open()){
        for(int i = 0; i < nb_of_chains; i++)
        {
            std::string head = generate_head(length);
            head_file << head << std::endl;

            std::string tail = generate_tail(head, nb_of_reductions);
            tail_file << tail << std::endl;
        }

        head_file.close();
        tail_file.close();
    }
    else
        throw std::runtime_error("Output files could not be opened");
}

void mass_generate(int nb_of_chains, int nb_of_reductions, int length, const std::string& rainbow_table_path){
    int state = 0;

    std::ofstream rainbow_table_file;
    rainbow_table_file.open(rainbow_table_path);

    if(rainbow_table_file.is_open()){
        for(int i = 0; i < nb_of_chains; i++){

            std::string head = generate_head(length);
            
            std::string tail = generate_tail(head, nb_of_reductions);

            rainbow_table_file << head << ':' << tail << std::endl;

            if(nb_of_chains > 1 && i % (nb_of_chains/10) == 0){
                std::cout << "State : "<<  state++ << "0%" << std::endl;
            }
        }

        rainbow_table_file.close();
    }
    else
        throw std::runtime_error("Output files could not be opened");
}


inline bool check_pwd(const std::string& head, const std::string& tail, int nb_of_reductionss){
    return generate_tail(head, nb_of_reductionss) == tail;
}

double mass_check(int nb_of_reductionss, const std::string& if_heads_tails){
    std::ifstream heads_tails_file;
    heads_tails_file.open(if_heads_tails);

    if(heads_tails_file.is_open()){
        std::string head_tail;
        std::string head;
        std::string tail;

        int count = 0;
        int success = 0;
        while(std::getline(heads_tails_file, head_tail)){
            int pos = head_tail.find(":");

            head = head_tail.substr(0, pos);
            tail = head_tail.substr(pos + 1);

            count++;
            if(check_pwd(head, tail, nb_of_reductionss))
                success++;
        }

        heads_tails_file.close();

        return (static_cast<double>(success) / count) * 100;
    }
    else
        throw std::runtime_error("Input files could not be opened");
}

double mass_check(int nb_of_reductionss, const std::string& if_head, const std::string& if_tail){
    std::ifstream head_file;
    head_file.open(if_head);

    std::ifstream tail_file;
    tail_file.open(if_tail);

    if(head_file.is_open() && tail_file.is_open()){
        std::string head;
        std::string tail;

        int count = 0;
        int success = 0;
        while(std::getline(head_file, head) && std::getline(tail_file, tail)){

            count++;
            if(check_pwd(head, tail, nb_of_reductionss))
                success++;
        }

        head_file.close();
        tail_file.close();

        return (static_cast<double>(success) / count) * 100;
    }
    else
        throw std::runtime_error("Input files could not be opened");
}

}//rainbow namespace

#endif // GENRAINBOWTABLEUTILS_HPP