#include <iostream>
#include <string>
#include <optional>
#include <sstream>
#include <fstream>
#include "JsonParser.hpp"

int main()
{
        std::optional<JSON> S1;
        //     S1 = ParseJSONFile(R"({
        //                             "location": {
        //                                 "country": "India",
        //                                 "state": "Uttar Pradesh",
        //                                 "city": "Greater Noida"
        //                             },
        //                             "organizations": [
        //                                 {
        //                                     "name": "GeeksforGeeks",
        //                                     "type": "Educational",
        //                                     "departments": ["Computer Science", "Mathematics", "Physics"]
        //                                 },
        //                                 {
        //                                     "name": "TechCorp",
        //                                     "type": "Technology",
        //                                     "departments": ["Software Development", "Hardware Design"]
        //                                 }
        //                             ],
        //                             "projects": {
        //                                 "ongoing": ["ProjectA", "ProjectB"],
        //                                 "completed": ["ProjectX", "ProjectY"]
        //                             }
        //                         }
        // )");

        S1 = ParseJSONFile(R"({
  "name": "Hesham Yasser",
  "age": 24.5 ,
  "student": false,
  "skills": ["C++", "Linux"],
  "address": {
    "country": "Egypt",
    "city": "Fayoum"
  }
})");

        // S1.value()["location"].print();
        S1.value()
            .print();

        // S1.value()["location"]["code"].print();
        return 0;
}
