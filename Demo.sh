#!/bin/bash

C='\033[44m'
E='\033[32m\033[1m'
N='\033[0m'
clear

echo "-----------------------------------------"
echo "(\(*0*) Welcome to Rainbow Attack (*0*)/)"
echo "-----------------------------------------"

echo -e "\nExecution of the ${E}makefile${N}"
make all

echo -e "\n"

# Rainbow Table Geneneration
read -r -p "Do you want to generate a rainbow table (yes/no) : " response

if [ "$response" == "yes" ]; then

    read -r -p "Enter the number of chains (association of head and tails) that you want to generate :" nb_of_chains

    read -r -p "Enter the number of reduction function that you want to apply for each chain :" nb_of_reductions

    read -r -p "Enter the password size to crack :" pwd_size

    read -r -p "Enter the path where you want to store the rainbow table :" rainbow_table_path

    echo -e "\nExecution of the ${E}rainbow table generation${N}"
    ./executable/rainbow_table_gen $nb_of_chains $nb_of_reductions $pwd_size "$rainbow_table_path"
fi

echo -e "\n"

# Rainbow Table Checking
read -r -p "Do you want to check your rainbow table (yes/no) : " response

if [ "$response" == "yes" ]; then

    read -r -p "Enter the number of reduction function that you applied for each chain :" nb_of_reductions

    read -r -p "Enter the path where you stored your rainbow table :" rainbow_table_path

    echo -e "\nExecution of the ${E}rainbow table checking${N}"
    ./executable/rainbow_table_check $nb_of_reductions "$rainbow_table_path"
fi

echo -e "\n"

# Rainbow Table Attack
read -r -p "Do you want to launch a rainbow table attack (yes/no) : " response

if [ "$response" == "yes" ]; then

    read -r -p "Enter the number of reduction function that you applied for each chain :" nb_of_reductions

    read -r -p "Enter the password size to crack :" pwd_size

    read -r -p "Enter the path where you stored your rainbow table :" rainbow_table_path

    read -r -p "Enter the path where you stored the password hashes to crack :" hash_to_crack_path

    echo -e "\nExecution of the ${E}rainbow table attack${N}"
    ./executable/rainbow_table_attack $nb_of_reductions $pwd_size "$rainbow_table_path" "$hash_to_crack_path"
fi

echo -e "\n"

echo "-----------------------------------------"
echo "Thanks for using my application, Bye (*0*)/)"
echo "-----------------------------------------"
