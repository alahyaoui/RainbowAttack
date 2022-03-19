# RainbowAttack
C++ application that cracks password using a Rainbow Table

# Definition

## Rainbow Table
A rainbow table is a precomputed table for caching the output of cryptographic hash functions, usually for cracking password hashes. Tables are usually used in recovering a key derivation function (or credit card numbers, etc.) up to a certain length consisting of a limited set of characters. It is a practical example of a space–time tradeoff, using less computer processing time and more storage than a brute-force attack which calculates a hash on every attempt, but more processing time and less storage than a simple key derivation function with one entry per hash.

## Rainbow Table Attack
A rainbow table attack is a type of hacking wherein the perpetrator tries to use a rainbow hash table to crack the passwords stored in a database system. A rainbow table is a hash function used in cryptography for storing important data such as passwords in a database.

# Usage

## Compilation
make all

## Execution
### Generation of the Rainbow Table
./executable/rainbow_table_gen

### Checking of the Rainbow Table
./executable/rainbow_table_check

### Rainbow Table Attack
./executable/rainbow_table_attack

## Clean
clean executable and tmp files -> make clean

# Supported hashes
sha256
