CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -pedantic

all: irrigacao testes

irrigacao: main.cpp irrigacao.cpp irrigacao.h
	$(CXX) $(CXXFLAGS) main.cpp irrigacao.cpp -o irrigacao

testes: testes.cpp irrigacao.cpp irrigacao.h
	$(CXX) $(CXXFLAGS) testes.cpp irrigacao.cpp -o testes

test: testes
	./testes

clean:
	rm -f irrigacao testes

