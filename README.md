# RainbowAttack
C++ application that cracks password using a Rainbow Table

# Definition

### Rainbow Table Attack
A rainbow table attack is a type of hacking wherein the perpetrator tries to use a rainbow hash table to crack the passwords stored in a database system. A rainbow table is a hash function used in cryptography for storing important data such as passwords in a database.

### Rainbow Table
A rainbow table is a precomputed table for caching the output of cryptographic hash functions, usually for cracking password hashes. Tables are usually used in recovering a key derivation function (or credit card numbers, etc.) up to a certain length consisting of a limited set of characters. It is a practical example of a space–time tradeoff, using less computer processing time and more storage than a brute-force attack which calculates a hash on every attempt, but more processing time and less storage than a simple key derivation function with one entry per hash.

# Usage

### Script
**./Demo**
You can execute the Demo file or you can do the following

### Compilation
**make all**

### Execution
#### Generation of the Rainbow Table
**./executable/rainbow_table_gen nb_of_chains nb_of_reduction pwd_size rainbow_table_path**

##### Where
> - **nb_of_chains** is the number of heads and tails that you want to generate
> - **nb_of_reductions** is the number of reduction function to apply
> - **pwd_size** is the allowed size of the head (head need to be the same size as the size of password that you want to crack)
> - **rainbow_table_path** is the name of the output file where the heads and the tails will be stored 
>or you can enters separately each file where
>heads is the name of the output file where the heads will be stored,
>tails is the name of the output file where the tails will be stored"

#### Checking of the Rainbow Table
**./executable/rainbow_table_check nb_of_reductions rainbow_table_path**

##### Where
> - **nb_of_reductions** is the number of reduction function to apply
> - **rainbow_table_path** is the name of the output file where the heads and the tails are stored 
>or you can enters separately each file where 
>heads is the name of the output file where the heads are stored,
>tails is the name of the output file where the tails are stored


#### Rainbow Table Attack
**./executable/rainbow_table_attack nb_of_reductions pwd_size rainbow_table_path hash_to_crack_path**

##### Where
> - **nb_of_reductions** the number of reduction function that have been executed to make a chain (head -> tail) of the Rainbow Table
> - **pwd_size** the size of the heads of the given Rainbow Table (You need to have 1 rainbow table by the size of the password that you want to crack)
> - **rainbow_table_path** the path of the file of the Rainbow Table
> - **hash_to_crack_path** is the path of the file of hashes to crack
            
## Cleaning
#### clean executable data and tmp files 
**make clean**

# Supported
### Password rule
alphanumerical password but no special character

###  Hashes
sha256

