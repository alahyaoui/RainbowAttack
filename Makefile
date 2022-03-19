GENERATE_SRC = generator/rainbow_table_gen-main.cpp generator/rainbow_table.hpp
CHECK_SRC = generator/rainbow_table_check-main.cpp generator/rainbow_table.hpp
ATTACK_SRC = attack/rainbow_table_attack-main.cpp attack/rainbow_attack.hpp
UTIL_SRC = utils/sha256.cpp

all: executable/rainbow_table_gen executable/rainbow_table_check executable/rainbow_table_attack

executable/rainbow_table_gen: $(GENERATE_SRC) $(UTIL_SRC)
	g++ -std=c++17 $^ -o $@

executable/rainbow_table_check: $(CHECK_SRC) $(UTIL_SRC)
	g++ -std=c++17 $^ -o $@

executable/rainbow_table_attack: $(ATTACK_SRC) $(UTIL_SRC)
	g++ -std=c++17 $^ -o $@

clean: 
	rm -f  executable/* data/* *.o ~*