#include <iostream>
#include <string>
#include <optional>
#include <sstream>
#include <fstream>
#include "JsonParser.hpp"

int main()
{
        std::optional<JSON> S1;
        //     S1 = ParseJSONString(R"({
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

//         S1 = ParseJSONString(R"({
//   "name": "Hesham Yasser",
//   "age": 24.5 ,
//   "student": false,
//   "skills": ["C++", "Linux"],
//   "address": {
//     "country": "Egypt",
//     "city": "Fayoum"
//   }
// })");
        std::ifstream File("Data.txt");
        S1 = ParseJSONFile(File);
        std::ofstream OutFile("Export.txt");
        GenerateJSONFile(S1.value(), OutFile);
        // std::cout << GenerateJSONString(S1.value()) << std::endl;

        // S1.value()["location"].print();
        S1.value()
            .print();

        // S1.value()["location"]["code"].print();
        return 0;
}
