all: demo.cc
	clang++ -Wall -Wextra demo.cc dfa_comp.cc -o demo.bin
