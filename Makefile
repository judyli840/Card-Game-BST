all: game tests

game : cards.cpp main.cpp
	g++ cards.cpp main.cpp -o game

tests : cards.cpp tests.cpp
	g++ cards.cpp tests.cpp -o tests
