
all: executable/rainbow_table_gen executable/rainbow_table_check executable/rainbow_table_attack

executable/rainbow_table_gen: generator/rainbow_table_gen-main.cpp generator/rainbow_table.hpp utils/sha256.cpp
	g++ -std=c++17 $^ -o $@

executable/rainbow_table_check: generator/rainbow_table_check-main.cpp generator/rainbow_table.hpp utils/sha256.cpp
	g++ -std=c++17 $^ -o $@

executable/rainbow_table_attack: attack/rainbow_table_attack-main.cpp attack/rainbow_attack.hpp utils/sha256.cpp
	g++ -std=c++17 $^ -o $@

clean: 
	rm -f  executable/rainbow_table_gen executable/rainbow_table_check executable/rainbow_table_attack *.o ~*