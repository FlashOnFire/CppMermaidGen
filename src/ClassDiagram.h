#ifndef CLASSDIAGRAM_H
#define CLASSDIAGRAM_H
#include <vector>
#include <regex>

#include "Class.h"

const std::regex class_regex("(?:class|struct) (.*) \\{");
const std::regex function_return_regex("(.*) (.*\\(\\).*)");
const std::regex superclass_regex("(.*) : (?:public|protected|private) (.*)");

class ClassDiagram {
public:
    explicit ClassDiagram(std::vector<std::string> files);
    [[nodiscard]] std::string generateMermaid() const;
private:
    std::vector<Class> classes;
};



#endif //CLASSDIAGRAM_H
