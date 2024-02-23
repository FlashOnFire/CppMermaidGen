#include "Class.h"

#include <fstream>
#include <utility>

std::vector<std::shared_ptr<Field>> Class::getPrivateFields() const {
    return private_fields;
}

std::vector<std::shared_ptr<Field>> Class::getPublicFields() const {
    return public_fields;
}

std::vector<Function> Class::getPrivateFunctions() const {
    return private_functions;
}

std::vector<Function> Class::getPublicFunctions() const {
    return public_functions;
}

Class::Class(std::string name): class_type(ClassType::Class) {
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

void Class::setClassType(const ClassType class_type) {
    this->class_type = class_type;
}

void Class::setSuperclassName(const std::string& superclass_name) {
    this->superclass_name = superclass_name;
}

void Class::addField(const std::shared_ptr<Field>& field) {
    if (field->getVisibility()) {
        private_fields.push_back(field);
    } else {
        public_fields.push_back(field);
    }

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

    for (const auto& f: public_fields) {
        str.append("      " + f->generateMermaid() + "\n");
    }

    for (const auto& f: private_fields) {
        str.append("      " + f->generateMermaid() + "\n");
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
