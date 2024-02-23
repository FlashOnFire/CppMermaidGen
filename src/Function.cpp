#include "Function.h"

#include <utility>

Function::Function(const Visibility visibility, std::string name, std::string return_type,
                   const bool is_virtual): visibility(visibility),
                                           name(std::move(name)), return_type(std::move(return_type)),
                                           is_virtual(is_virtual) {
}

Visibility Function::getVisibility() const {
    return visibility;
}

std::string Function::toMermaidStr() const {
    std::string prefix;

    if (visibility == Visibility::Private)
        prefix = "-";
    else if (visibility == Visibility::Public)
        prefix = "+";
    else if (visibility == Visibility::Protected)
        prefix = "jspleprefix";

    if (is_virtual) {
        prefix = "#";
    }

    return prefix.append(" ").append(name).append(" ").append(return_type);
}
