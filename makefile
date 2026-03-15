MAIN=./src/Main.cpp
LIB=./src/JsonParser.cpp
CC=g++
OUT=./build/Project.exe
CC_V=c++17
PARAM= -fdiagnostics-color=always -g
TOOL=./src/JQ.cpp
OUTTOOL=./build/JQ.exe
DATAFILE=./output/Export.txt



Build: 
	$(CC) $(PARAM) -std=$(CC_V) $(MAIN) $(LIB) -o $(OUT) 2> ./output/Log.txt


run : Build
	$(OUT)

runonly:
	$(OUT)

BuildScript:
	$(CC) $(PARAM) -std=$(CC_V) $(TOOL) $(LIB) -o $(OUTTOOL) 2> ./output/ToolLog.txt

runscript: BuildScript
	$(OUTTOOL) $(DATAFILE) $(ARG)

runonlyscript:
	$(OUTTOOL) $(DATAFILE) $(ARG)