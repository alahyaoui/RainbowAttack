#ifndef GENRAINBOWTABLEUTILS_HPP
#define GENRAINBOWTABLEUTILS_HPP

#include <cstring>
#include <fstream>
#include <string>

#include "../utils/random.hpp"
#include "../utils/reduction.hpp"
#include "../utils/sha256.h"

namespace rainbow {

/**
 * Generate a random string of a given length
 * 
 * @param length The length of the string to generate.
 * 
 * @return a string of length `length` containing random characters from the `char_policy` string.
 */
std::string generate_head(int length) {
    static const std::string char_policy = "azertyuiopqsdfghjklmwxcvbnAZERTYUIOPQSDFGHJKLMWXCVBN1234567890";
    static const int c_len = char_policy.length();

    char str[length + 1];
    for (int i = 0; i < length; i++)
        str[i] = char_policy[rainbow::random(0, c_len - 1)];
    str[length] = '\0';

    return std::string(str);
}

/**
 * Generate a tail from a hashed head by applying reduction functions.
 * 
 * @param head The password you want to hash.
 * @param nb_of_reductions The number of times the password is reduced.
 * 
 * @return The tail of the password.
 */
std::string generate_tail(const std::string& head, int nb_of_reductions) {
    std::string tail;
    std::string hash = sha256(head);

    int pwd_size = head.size();

    for (size_t i = 1; i < nb_of_reductions; i++) {
        tail = reduce(hash, i, pwd_size);
        hash = sha256(tail);
    }

    tail = reduce(hash, nb_of_reductions, pwd_size);
    return std::string(tail);
}

/**
 * Generate a number of chains of a given length, with a given number of reductions, and write them to
 * the output files
 * 
 * @param nb_of_chains The number of chains to generate.
 * @param nb_of_reductions The number of reductions to perform on the head.
 * @param length The length of the head and tail.
 * @param of_head the name of the file where the head of the chains will be written
 * @param of_tail the name of the file where the tail will be written
 */
void mass_generate(int nb_of_chains, int nb_of_reductions, int length, const std::string& of_head, const std::string& of_tail) {
    std::ofstream head_file;
    head_file.open(of_head);

    std::ofstream tail_file;
    tail_file.open(of_tail);

    if (head_file.is_open() && tail_file.is_open()) {
        for (int i = 0; i < nb_of_chains; i++) {
            std::string head = generate_head(length);
            head_file << head << std::endl;

            std::string tail = generate_tail(head, nb_of_reductions);
            tail_file << tail << std::endl;
        }

        head_file.close();
        tail_file.close();
    } else
        throw std::runtime_error("Output files could not be opened");
}

/**
 * Generate a rainbow table by generating a number of chains of a given length, 
 * with a given number of reductions, and write them to the output file
 * 
 * @param nb_of_chains The number of chains to generate.
 * @param nb_of_reductions The number of times the password is reduced.
 * @param length The length of the generated strings.
 * @param rainbow_table_path The path to the file where the rainbow table will be written.
 */
void mass_generate(int nb_of_chains, int nb_of_reductions, int length, const std::string& rainbow_table_path) {
    int state = 0;

    std::ofstream rainbow_table_file;
    rainbow_table_file.open(rainbow_table_path);

    if (rainbow_table_file.is_open()) {
        for (int i = 0; i < nb_of_chains; i++) {
            std::string head = generate_head(length);

            std::string tail = generate_tail(head, nb_of_reductions);

            rainbow_table_file << head << ':' << tail << std::endl;

            if (nb_of_chains > 1 && i % (nb_of_chains / 10) == 0) {
                std::cout << "State : " << state++ << "0%" << std::endl;
            }
        }

        rainbow_table_file.close();
    } else
        throw std::runtime_error("Output files could not be opened");
}

/**
 * Checks if a given head gives by applying the number of reduction foncions the same tail as the given tail
 * 
 * @param head the head of the chain.
 * @param tail the tail of the chain.
 * @param nb_of_reductions the number of reductions to perform on the head.
 * 
 * @return A boolean value.
 */
inline bool check_pwd(const std::string& head, const std::string& tail, int nb_of_reductions) {
    return generate_tail(head, nb_of_reductions) == tail;
}

/**
 * It reads the rainbow table file, checks each chain in the file, and returns the  percentage of valid chains
 * 
 * @param nb_of_reductions The number of reductions to perform.
 * @param rainbow_table_path The path to the rainbow table file.
 * 
 * @return The percentage of valid chains.
 */
double mass_check(int nb_of_reductions, const std::string& rainbow_table_path) {
    std::ifstream heads_tails_file;
    heads_tails_file.open(rainbow_table_path);

    if (heads_tails_file.is_open()) {
        std::string head_tail;
        std::string head;
        std::string tail;

        int count = 0;
        int success = 0;
        while (std::getline(heads_tails_file, head_tail)) {
            int pos = head_tail.find(":");

            head = head_tail.substr(0, pos);
            tail = head_tail.substr(pos + 1);

            count++;
            if (check_pwd(head, tail, nb_of_reductions))
                success++;
        }

        heads_tails_file.close();

        return (static_cast<double>(success) / count) * 100;
    } else
        throw std::runtime_error("Input files could not be opened");
}

/**
 * It reads the rainbow table file (head file & tail file), checks each chain, and returns the  percentage of valid chains
 * 
 * @param nb_of_reductions The number of reductions to perform.
 * @param if_head The name of the file containing the head of the passwords
 * @param if_tail The file containing the tail of the passwords.
 * 
 * @return The percentage of passwords that were cracked.
 */
double mass_check(int nb_of_reductions, const std::string& if_head, const std::string& if_tail) {
    std::ifstream head_file;
    head_file.open(if_head);

    std::ifstream tail_file;
    tail_file.open(if_tail);

    if (head_file.is_open() && tail_file.is_open()) {
        std::string head;
        std::string tail;

        int count = 0;
        int success = 0;
        while (std::getline(head_file, head) && std::getline(tail_file, tail)) {
            count++;
            if (check_pwd(head, tail, nb_of_reductions))
                success++;
        }

        head_file.close();
        tail_file.close();

        return (static_cast<double>(success) / count) * 100;
    } else
        throw std::runtime_error("Input files could not be opened");
}

}  // namespace rainbow

#endif  // GENRAINBOWTABLEUTILS_HPP