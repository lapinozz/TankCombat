#!/usr/bin/make -f
bin: src/main.cpp
	mkdir -p bin
	g++-5 -std=c++14 -O2 -Wall -Wextra -Wpedantic -I. -UDEBUG -UTEST -o bin/tankcombat src/*.cpp -lsfml-graphics -lsfml-window -lsfml-system
dbg: src/main.cpp
	mkdir -p bin
	g++-5 -std=c++14 -ggdb3 -Wall -Wextra -Wpedantic -I. -DDEBUG -UTEST -o bin/tankcombat src/*.cpp -lsfml-graphics -lsfml-window -lsfml-system
prof: src/main.cpp
	mkdir -p bin
	g++-5 -std=c++14 -pg -O2 -Wall -Wextra -Wpedantic -I. -UDEBUG -UTEST -o bin/tankcombat src/*.cpp -lsfml-graphics -lsfml-window -lsfml-system
test: src/main.cpp
	mkdir -p bin
	g++-5 -std=c++14 -O2 -Wall -Wextra -Wpedantic -I. -DTEST -UDEBUG -o bin/tankcombat src/*.cpp -lsfml-graphics -lsfml-window -lsfml-system
clang: src/main.cpp
	mkdir -p bin
	clang++-3.7 -std=c++14 -O2 -Wall -Wextra -Wpedantic -I. -UDEBUG -UTEST -o bin/tankcombat src/*.cpp -lsfml-graphics -lsfml-window -lsfml-system
clangdbg: src/main.cpp
	mkdir -p bin
	clang++-3.7 -std=c++14 -ggdb3 -Wall -Wextra -Wpedantic -I. -DDEBUG -UTEST -o bin/tankcombat src/*.cpp -lsfml-graphics -lsfml-window -lsfml-system
clangprof: src/main.cpp
	mkdir -p bin
	clang++-3.7 -std=c++14 -pg -O2 -Wall -Wextra -Wpedantic -I. -UDEBUG -UTEST -o bin/tankcombat src/*.cpp -lsfml-graphics -lsfml-window -lsfml-system
clangtest: src/main.cpp
	mkdir -p bin
	clang++-3.7 -std=c++14 -O2 -Wall -Wextra -Wpedantic -I. -DTEST -UDEBUG -o bin/tankcombat src/*.cpp -lsfml-graphics -lsfml-window -lsfml-system
clean:
	rm -rf bin
.PHONY: bin dbg prof test clang clangdbg clangprof clangtest clean
