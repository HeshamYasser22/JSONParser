FILES=$(wildcard *.cpp)
CC=g++
OUT=Project.exe
CC_V=c++17
PARAM= -fdiagnostics-color=always -g


Build: 
	$(CC) $(PARAM) -std=$(CC_V) $(FILES) -o $(OUT)


run : Build
	./$(OUT)