#ifndef GENRAINBOWTABLEUTILS_HPP
#define GENRAINBOWTABLEUTILS_HPP

#include <string>
#include <fstream>
#include <cstring>

#include "utils/sha256.h"
#include "utils/reduction.h"

namespace rainbow {

std::string generate_tail(std::string hash, int pwdSize, int pos ,int nbOfReduction){ 
    std::string tail;

    for(size_t i = pos; i < nbOfReduction; i++){
        tail = reduce(hash, i, pwdSize);
        hash = sha256(tail);
    }

    tail = reduce(hash, nbOfReduction, pwdSize);
    return tail;
}

std::string find_in_chain(const std::string & head, const std::string & hashToCrack, const int & nbOfReduction){ 
    std::string pwd = head;
    std::string hash;

    int pwdSize = head.size();

    for(size_t i = 1; i < nbOfReduction + 1; i++){
        hash = sha256(pwd);
        if(strcmp(hashToCrack.c_str(), hash.c_str()) == 0){
            std::cout << "hash trouvé dans la chaine" << std::endl;
            return pwd;
        }
        pwd = reduce(hash, i, pwdSize); 
    }

    return "";
}

std::string find_in_tail_file(const std::string & pwd , const std::string & hash, const int & nbOfReduction ,const std::string & if_heads_tails){
    std::ifstream heads_tails_file;
    heads_tails_file.open(if_heads_tails);

    if(heads_tails_file.is_open()){
        std::string head_tail;
        std::string head;
        std::string tail;

        heads_tails_file.clear();
        heads_tails_file.seekg(0);

        while(std::getline(heads_tails_file, head_tail)){
            int lineSeparator = head_tail.find(":");

            tail = head_tail.substr(lineSeparator + 1);
            if(strcmp(pwd.c_str(), tail.c_str()) == 0){  
                head = head_tail.substr(0, lineSeparator);

                std::cout << head << " " << pwd << '=' << tail << " tail similaire trouvé !!! je sors de findInTailFile"<< std::endl;
                std::string pwdInChain = find_in_chain(head, hash, nbOfReduction);
                if(pwdInChain != "")
                    return pwdInChain;
            }
        }

        heads_tails_file.close();

    }
    else
        throw std::runtime_error("Input files could not be opened");
    return "";
}

bool attack(std::string hash, const int & pwd_size, const int & nb_of_reductions, const std::string & if_heads_tails){
    std::string tail;
    std::string pwd;

    bool is_found = false;
    
    //int count = 1;
    int i = nb_of_reductions;
    while(is_found == false && i > 0){
        tail = generate_tail(hash, pwd_size, i, nb_of_reductions);
        pwd = find_in_tail_file(tail, hash, nb_of_reductions, if_heads_tails);

       
       if(pwd != ""){
            if(strcmp(sha256(pwd).c_str(), hash.c_str()) == 0){
                is_found = true;
                std::cout << "mdp trouvé " << pwd << ":" << hash << std::endl;
                break;
            }
        }
        i--;        
    }
    return is_found;
}

}//rainbow namespace

#endif // GENRAINBOWTABLEUTILS_HPP

