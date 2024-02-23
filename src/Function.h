#ifndef FUNCTION_H
#define FUNCTION_H
#include <string>

#include "Visibility.h"


class Function {
public:
    Function(Visibility visibility, std::string name, std::string  return_type, bool is_virtual);

    [[nodiscard]] Visibility getVisibility() const;

    [[nodiscard]] std::string toMermaidStr() const;
private:
    Visibility visibility;
    std::string name;
    std::string return_type;
    bool is_virtual;
};



#endif //FUNCTION_H
