#include "Field.h"

Field::Field(const Visibility visibility, std::string type, std::string name)
    : visibility(visibility),
      type(std::move(type)),
      name(std::move(name)) {
}

Visibility Field::getVisibility() const {
    return visibility;
}

std::string Field::getType() const {
    return type;
}

std::string Field::getName() const {
    return name;
}

std::string Field::generateMermaid() const {
    std::string prefix;

    if (visibility == Visibility::Private)
        prefix = "-";
    else if (visibility == Visibility::Public)
        prefix = "+";
    else if (visibility == Visibility::Protected)
        prefix = "#";

    return prefix.append(" ").append(type).append(" ").append(name);
}
