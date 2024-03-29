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
    if (field->getVisibility() == Visibility::Private) {
        private_fields.push_back(field);
    } else if (field->getVisibility() == Visibility::Public) {
        public_fields.push_back(field);
    } else {
        protected_fields.push_back(field);
    }
}

void Class::addFunction(const Function& function) {
    if (function.getVisibility() == Visibility::Private) {
        private_functions.push_back(function);
    } else if (function.getVisibility() == Visibility::Public) {
        public_functions.push_back(function);
    } else {
        protected_functions.push_back(function);
    }
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

    for (const auto& f: protected_fields) {
        str.append("      " + f->generateMermaid() + "\n");
    }

    for (const auto& f: public_functions) {
        str.append("      " + f.toMermaidStr() + "\n");
    }

    for (const auto& f: private_functions) {
        str.append("      " + f.toMermaidStr() + "\n");
    }
    for (const auto& f: protected_functions) {
        str.append("      " + f.toMermaidStr() + "\n");
    }

    str.append("    }");

    return str;
}
