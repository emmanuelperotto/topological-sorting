all: compile

run: compile exec clear

compile:
	g++ -std=c++11 -g main.cpp graph.cpp utils.cpp -o exe

exec:
	./exe

clear:
	rm exe