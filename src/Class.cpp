#include "Class.h"

#include <fstream>
#include <utility>

Class::Class(std::string name) {
    this->name = std::move(name);
}

std::string Class::getName() const {
    return name;
}

void Class::setName(std::string name) {
    this->name = std::move(name);
}

std::string Class::get_superclass_name() const {
    return superclass_name;
}

void Class::setSuperclassName(const std::string& superclass_name) {
    this->superclass_name = superclass_name;
}

void Class::addPrivateField(std::string str) {
    private_fields.push_back("- " + str);
}

void Class::addPublicField(std::string str) {
    public_fields.push_back("+ " + str);
}

void Class::addPrivateFunction(const std::string& name, const std::string& return_type) {
    private_functions.emplace_back(true, name, return_type);
}

void Class::addPublicFunction(const std::string& name, const std::string& return_type) {
    public_functions.emplace_back(false, name, return_type);
}

std::string Class::generateMermaid() const {
    std::string str;

    str.append("    class " + name + " {" + "\n");

    for (const auto& s: public_fields) {
        str.append("      " + s + "\n");
    }

    for (const auto& s: private_fields) {
        str.append("      " + s + "\n");
    }

    for (const auto& f: public_functions) {
        str.append("      " + f.toMermaidStr() + "\n");
    }

    for (const auto& f: private_functions) {
        str.append("      " + f.toMermaidStr() + "\n");
    }

    str.append("    }");

    return str;
}
