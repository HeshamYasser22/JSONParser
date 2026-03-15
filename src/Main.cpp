#include <iostream>
#include <string>
#include <optional>
#include <sstream>
#include <fstream>
#include "../include/JsonParser.hpp"

int main()
{
        std::optional<JSON> S1;
        std::ifstream File("./data/Data.txt");
        S1 = ParseJSONFile(File);
        std::ofstream OutFile("./output/Export.txt");
        GenerateJSONFile(S1.value(), OutFile);

        S1.value()
            .print();

        return 0;
}
