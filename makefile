MAIN=Main.cpp
LIB=JsonParser.cpp
CC=g++
OUT=Project.exe
CC_V=c++17
PARAM= -fdiagnostics-color=always -g
TOOL=JQ.cpp
OUTTOOL=JQ.exe
DATAFILE=./Export.txt


Build: 
	$(CC) $(PARAM) -std=$(CC_V) $(MAIN) $(LIB) -o $(OUT)


run : Build
	./$(OUT)

runonly:
	./$(OUT)

runscript: 
	$(CC) $(PARAM) -std=$(CC_V) $(TOOL) $(LIB) -o $(OUTTOOL)
	./$(OUTTOOL) $(DATAFILE) .name