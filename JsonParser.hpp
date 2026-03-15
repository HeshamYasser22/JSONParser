#pragma once
#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <variant>
#include <optional>
#include <sstream>
#include <fstream>

class JSON
{

    std::variant<int, float, bool, std::string, std::vector<JSON> *, std::map<std::string, JSON> *> D;

public:
    JSON();
    JSON(int Data);
    JSON(float Data);
    JSON(bool Data);
    JSON(std::string Data);
    static JSON Array();
    static JSON Object();
    JSON &operator[](const std::string &Index);
    void push_back(const JSON &j);
    void print();
};

std::optional<JSON> ParseJSONFile(const std::string& Str);
void RemoveStartEndSpaces(std::string &s);
void RemoveStartEndSquareBrackets(std::string &s);
void RemoveStartEndCurlBrackets(std::string &s);
void RemoveStartEndQuote(std::string &s);
void RemoveStartEndComma(std::string &s);
std::optional<JSON> GetNumFromString(std::string s);
std::optional<JSON> GetArrFromString(std::string s);
std::optional<JSON> GetStringFromString(std::string s);
int CheckArrDepth(std::string s);
int CheckObjectDepth(std::string s);
void IgnoreSpaces(std::stringstream &ss);