#include <iostream>
#include "../include/JsonParser.hpp"
#include <fstream>
#include <vector>
#include <string>
#include <optional>

std::vector<std::string> ParseQuery(char Query[]);

void GetDataFromJSON(std::vector<std::string> Query, JSON &Obj);

JSON & GetJSON(std::string s, JSON &Obj);

int main(int argc, char *argv[])
{
    if (argc > 3)
    {
        std::cerr << "Error in Parameters" << std::endl;
        return 1;
    }
    std::ifstream InFile(argv[1]);
    if (!InFile.is_open())
    {
        std::cerr << "File is Not Valid" << std::endl;
        return 2;
    }
    std::optional<JSON> S1;
    S1 = ParseJSONFile(InFile);
    std::vector<std::string> Query = ParseQuery(argv[2]);
    GetDataFromJSON(Query, S1.value());
    return 0;
}

std::vector<std::string> ParseQuery(char Query[])
{
    std::vector<std::string> Entries;
    std::stringstream ss(Query);
    std::string Data;
    while (std::getline(ss, Data, '.'))
    {
        if (Data == "")
        {
            continue;
        }
        Entries.push_back(Data);
    }
    return Entries;
}

void GetDataFromJSON(std::vector<std::string> Query, JSON &Obj)
{
    JSON& Data = Obj;
    for (auto i : Query)
    {
        Data = GetJSON(i, Data);
    }
    Data.print();
}

JSON & GetJSON(std::string s, JSON &Obj)
{
    return Obj[s];
}