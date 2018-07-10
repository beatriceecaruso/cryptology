all: pad.out btrans.out

pad.out : pad.cpp crypto.cpp crypto.h
	g++ pad.cpp crypto.cpp -o pad.output -std=c++11

btrans.out : btrans.cpp crypto.cpp crypto.h
	g++ btrans.cpp crypto.cpp -o btrans.out -std=c++11
