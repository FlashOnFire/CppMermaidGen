#ifndef FUNCTION_H
#define FUNCTION_H
#include <string>


class Function {
private:
    bool visibility;
    std::string name;
    std::string return_type;

public:
    Function(bool visibility, std::string  name, std::string  return_type);

    [[nodiscard]] std::string toMermaidStr() const;
};



#endif //FUNCTION_H
