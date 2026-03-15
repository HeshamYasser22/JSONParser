#include "JsonParser.hpp"

constexpr int null = INT32_MAX;

JSON::JSON() {}
JSON::JSON(int Data)
{
    D = Data;
}
JSON::JSON(float Data)
{
    D = Data;
}
JSON::JSON(bool Data)
{
    D = Data;
}
JSON::JSON(std::string Data)
{
    D = Data;
}

JSON JSON::Array()
{
    JSON Add;
    Add = new std::vector<JSON>();
    return Add;
}

JSON JSON::Object()
{
    JSON Add;
    Add = new std::map<std::string, JSON>();
    return Add;
}

JSON &JSON::operator[](const std::string &Index)
{
    if (!std::holds_alternative<std::map<std::string, JSON> *>(D))
    {
        D = new std::map<std::string, JSON>();
    }
    return (*(std::get<std::map<std::string, JSON> *>(D)))[Index];
}

void JSON::push_back(const JSON &j)
{
    if (!std::holds_alternative<std::vector<JSON> *>(D))
    {
        D = new std::vector<JSON>();
    }
    std::get<std::vector<JSON> *>(D)->push_back(j);
}

void JSON::print()
{
    if (std::holds_alternative<int>(D))
    {
        if (std::get<int>(D) == null)
        {
            std::cout << "null";
        }
        else
        {
            std::cout << std::get<int>(D);
        }
    }
    else if (std::holds_alternative<float>(D))
    {
        std::cout << std::get<float>(D);
    }
    else if (std::holds_alternative<bool>(D))
    {
        std::cout << (std::get<bool>(D) ? "true" : "false");
    }
    else if (std::holds_alternative<std::string>(D))
    {
        std::cout << '"' << std::get<std::string>(D) << '"';
    }

    else if ((std::holds_alternative<std::map<std::string, JSON> *>(D)))
    {
        static int Depth = 0;
        int Counter = 0;
        int Size = (*std::get<std::map<std::string, JSON> *>(D)).size();
        if (Depth!=0)
        {
            std::cout << std::endl;
        }
        std::cout 
                  << std::string(Depth, '\t') << "{" << std::endl;
        Depth++;
        for (auto &i : *std::get<std::map<std::string, JSON> *>(D))
        {
            std::cout << std::string(Depth, '\t');
            std::cout << '"' << i.first << '"' << " : ";
            i.second.print();
            if (Counter != Size - 1)
            {
                std::cout << ",";
            }
            Counter++;
            std::cout << " " << std::endl;
        }
        Depth--;
        std::cout << std::string(Depth, '\t') << "}";
    }
    else if ((std::holds_alternative<std::vector<JSON> *>(D)))
    {
        std::cout << "[ ";
        for (auto &i : *std::get<std::vector<JSON> *>(D))
        {
            i.print();
            if (&i != &(*(std::get<std::vector<JSON> *>(D))).at((*(std::get<std::vector<JSON> *>(D))).size() - 1))
            {
                std::cout << ",";
            }
            std::cout << ' ';
        }
        std::cout << "]";
    }
}

std::optional<JSON> ParseJSONFile(const std::string &Str)
{
    JSON S1;
    std::stringstream ss(Str);
    char C;
    std::string Data;
    std::string Token;
    std::string Extra_S;
    std::optional<JSON> DataJSON;
    if (ss.peek() != '{')
    {
        std::cout << ss.peek();
        std::cout << "Error in Opening Brackets" << std::endl;
        return std::nullopt;
    }
    while (ss >> C)
    {
        if (C == '"')
        {

            std::getline(ss, Data, '"');
            IgnoreSpaces(ss);
            ss >> C;
            IgnoreSpaces(ss);
            if (ss.peek() == '"')
            {
                std::getline(ss, Token, ',');
                DataJSON = GetStringFromString(Token).value();
            }
            else if ((ss.peek() != '{') && (ss.peek() != '['))
            {
                std::getline(ss, Token, ',');
                DataJSON = GetNumFromString(Token);
            }
            else if (ss.peek() == '[')
            {
                std::getline(ss, Token, ',');
                std::getline(ss, Token, ']');
                Token += "]";
                while (CheckArrDepth(Token) > 0)
                {
                    std::getline(ss, Extra_S, ']');
                    Token += Extra_S + ']';
                }
                // cout << "Combo Token : " << Token << endl;
                DataJSON = GetArrFromString(Token);
            }
            else if (ss.peek() == '{')
            {
                std::getline(ss, Token, '}');
                Token += "}";

                while (CheckObjectDepth(Token) != 0)
                {
                    std::getline(ss, Extra_S, '}');
                    Token += Extra_S + '}';
                }
                DataJSON = ParseJSONFile(Token);
            }
            if (DataJSON != std::nullopt)
            {
                S1[Data] = DataJSON.value();
            }
        }
    }
    return S1;
}

void RemoveStartEndSpaces(std::string &s)
{
    while ((s.at(s.size() - 1) == ' ') || (s.at(s.size() - 1) == '\n') || (s.at(s.size() - 1) == '\t'))
    {
        s = s.substr(0, s.size() - 1);
    }
    while ((s.at(0) == ' ') || (s.at(0) == '\n') || (s.at(s.size() - 1) == '\t'))
    {
        s = s.substr(1, s.size() - 1);
    }
}

void RemoveStartEndSquareBrackets(std::string &s)
{
    while (s.at(s.size() - 1) == ']')
    {
        s = s.substr(0, s.size() - 1);
    }
    while (s.at(0) == '[')
    {
        s = s.substr(1, s.size() - 1);
    }
}

void RemoveStartEndCurlBrackets(std::string &s)
{
    while (s.at(s.size() - 1) == '}')
    {
        s = s.substr(0, s.size() - 1);
    }
    while (s.at(0) == '{')
    {
        s = s.substr(1, s.size() - 1);
    }
}

void RemoveStartEndQuote(std::string &s)
{
    while (s.at(s.size() - 1) == '"')
    {
        s = s.substr(0, s.size() - 1);
    }
    while (s.at(0) == '"')
    {
        s = s.substr(1, s.size() - 1);
    }
}

std::optional<JSON> GetNumFromString(std::string s)
{
    RemoveStartEndSquareBrackets(s);
    RemoveStartEndCurlBrackets(s);
    RemoveStartEndQuote(s);
    RemoveStartEndSpaces(s);
    if ((s == "true") || (s == "false"))
    {
        return (s == "true") ? true : false;
    }
    else if ((s == "null"))
    {
        return (null);
    }
    else
    {
        if ((s.find('.') == std::string::npos) && (s.find('e') == std::string::npos) && (s.find('E') == std::string::npos))
        {
            try
            {
                return (JSON(stoi(s)));
            }
            catch (std::exception &e)
            {
                std::cerr << "Counld Get Value from String (Int)" << std::endl;
            }
        }
        else
        {
            try
            {
                return (JSON(stof(s)));
            }
            catch (const std::exception &e)
            {
                std::cerr << "Counld Get Value from String (Float)" << std::endl;
            }
        }

        return std::nullopt;
    }
}


std::optional<JSON> GetArrFromString(std::string s)
{
    std::string Data;
    std::optional<JSON> Parsed_Data;
    JSON Values;
    RemoveStartEndSquareBrackets(s);
    RemoveStartEndSpaces(s);
    std::stringstream ss(s);
    if (ss.peek() != '{')
    {
        while (std::getline(ss, Data, ','))
        {
            // cout << "Data : " << Data << endl;
            RemoveStartEndSpaces(Data);
            if (Data[0] == '"')
            {
                Parsed_Data = GetStringFromString(Data);
            }
            else
            {
                Parsed_Data = GetNumFromString(Data);
            }
            if (Parsed_Data != std::nullopt)
            {
                Values.push_back(Parsed_Data.value());
            }
        }
    }
    else
    {
        // cout << "String Here : " << s << endl;
        while (std::getline(ss, Data, '}'))
        {
            RemoveStartEndComma(Data);
            RemoveStartEndSpaces(Data);
            // cout << "Data : " << Data << endl;
            Parsed_Data = ParseJSONFile(Data);
            if (Parsed_Data != std::nullopt)
            {
                Values.push_back(Parsed_Data.value());
            }
            // while (ss.peek() != '{')
            // {
            //     ss.ignore();
            // }
        }
    }
    return Values;
}

std::optional<JSON> GetStringFromString(std::string s)
{
    RemoveStartEndSquareBrackets(s);
    RemoveStartEndCurlBrackets(s);
    RemoveStartEndSpaces(s);
    RemoveStartEndQuote(s);
    return s;
}

int CheckArrDepth(std::string s)
{
    int Depth = 0;
    for (auto i : s)
    {
        if (i == '[')
        {
            Depth++;
        }
        else if (i == ']')
        {
            Depth--;
        }
    }
    return Depth;
}

void RemoveStartEndComma(std::string &s)
{
    while (s.at(s.size() - 1) == ',')
    {
        s = s.substr(0, s.size() - 1);
    }
    while (s.at(0) == ',')
    {
        s = s.substr(1, s.size() - 1);
    }
}

int CheckObjectDepth(std::string s)
{
    int Depth = 0;
    for (auto i : s)
    {
        if (i == '{')
        {
            Depth++;
        }
        else if (i == '}')
        {
            Depth--;
        }
    }
    return Depth;
}

void IgnoreSpaces(std::stringstream &ss)
{
    while ((ss.peek() == ' ') || (ss.peek() == 0) || (ss.peek() == 10))
    {
        ss.ignore();
    }
}