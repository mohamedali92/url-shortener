build:
	g++  -pedantic-errors -Wall -Weffc++ -Wextra -Wsign-conversion -std=c++17 db-utils.cpp test-crow.cpp utils.cpp /Users/moe/Projects/project-assets/cpp-driver/build/libcassandra.2.15.3.dylib  -o url-short.tsk

clean:
	rm simple