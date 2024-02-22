#include "Field.h"

Field::Field(const bool visibility, std::string type, std::string name)
    : visibility(visibility),
      type(std::move(type)),
      name(std::move(name)) {
}

bool Field::getVisibility() const {
    return visibility;
}

std::string Field::getType() const {
    return type;
}

std::string Field::getName() const {
    return name;
}

std::string Field::generateMermaid() const {
    return std::string((visibility) ? "-" : "+").append(" ").append(type).append(" ").append(name);
}
