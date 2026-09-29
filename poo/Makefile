CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -pedantic

all: irrigacao_poo testes_poo

irrigacao_poo: main.cpp modelo.cpp modelo.h
	$(CXX) $(CXXFLAGS) main.cpp modelo.cpp -o irrigacao_poo

testes_poo: testes.cpp modelo.cpp modelo.h
	$(CXX) $(CXXFLAGS) testes.cpp modelo.cpp -o testes_poo

test: testes_poo
	./testes_poo

clean:
	rm -f irrigacao_poo testes_poo

.PHONY: all test clean
