#include "Function.h"

#include <utility>

Function::Function(bool visibility, std::string name, std::string return_type): visibility(visibility),
    name(std::move(name)), return_type(std::move(return_type)) {
}

std::string Function::toMermaidStr() const {
    return std::string((visibility) ? "-" : "+").append(" ").append(name).append(" ").append(return_type);
}
