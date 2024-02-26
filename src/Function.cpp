#include "Function.h"

#include <utility>

Function::Function(const Visibility visibility, std::string name, std::string args, std::string return_type,
                   const bool is_virtual): visibility(visibility),
                                           name(std::move(name)), args(std::move(args)), return_type(std::move(return_type)),
                                           is_virtual(is_virtual) {

    if (this->name.at(this->name.length()-1) == ';') {
        this->name = this->name.substr(0, this->name.length()-1);
    }
}

Visibility Function::getVisibility() const {
    return visibility;
}

std::string Function::getName() const {
    return name;
}

std::string Function::getArgs() const {
    return args;
}

std::string Function::getReturnType() const {
    return return_type;
}

std::string Function::toMermaidStr() const {
    std::string prefix;

    if (visibility == Visibility::Private)
        prefix = "-";
    else if (visibility == Visibility::Public)
        prefix = "+";
    else if (visibility == Visibility::Protected)
        prefix = "#";

    /*if (is_virtual) {
        prefix = "#";
    }*/

    return prefix.append(" ").append(name).append("(").append(args).append(")").append(" ").append(return_type);
}