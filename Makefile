all: rainbow_table_gen rainbow_table_check rainbow_table_attack

executable/rainbow_table_gen: rainbow_table_gen-main.cpp
	gcc $^ -o $@  

executable/rainbow_table_check: rainbow_table_check-main.cpp
	gcc $^ -o $@  

executable/rainbow_table_attack: rainbow_table_attack-main.cpp
	gcc $^ -o $@  

clean: 
	rm -f  executable/rainbow_table_gen executable/rainbow_table_check executable/rainbow_table_attack *.o ~*