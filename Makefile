build:
	g++  -pedantic-errors -Wall -Weffc++ -Wextra -Wsign-conversion -std=c++17 db-utils.cpp main.cpp utils.cpp -lpqxx -o url-short.tsk

clean:
	rm url-short.tsk