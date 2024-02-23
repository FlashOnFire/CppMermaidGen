#ifndef CLASSDIAGRAM_H
#define CLASSDIAGRAM_H
#include <vector>
#include <regex>

#include "Class.h"
#include "Link.h"

const std::regex enum_regex("(?:enum class) (.*) \\{");
const std::regex class_regex("(?:class) (.*) \\{");
const std::regex struct_regex("(?:struct) (.*) \\{");
const std::regex function_return_regex("(.*) (.*\\(.*\\).*)");
const std::string function_destructor_regex = "(.*)(~class\\(.*\\).*)";
const std::string function_constructor_regex = "(.*)(class\\(.*\\).*)";
const std::regex superclass_regex("(.*) : (?:public|protected|private) (.*)");

class ClassDiagram {
public:
    explicit ClassDiagram(const std::vector<std::string>& files);
    [[nodiscard]] std::string generateMermaid() const;
private:
    std::vector<std::shared_ptr<Class>> classes;
    std::vector<Link> links;
};



#endif //CLASSDIAGRAM_H
