#ifndef CLASS_H
#define CLASS_H
#include <memory>
#include <string>
#include <vector>

#include "ClassType.h"
#include "Field.h"
#include "Function.h"


class Class {
public:
    Class() = default;

    [[nodiscard]] std::vector<std::shared_ptr<Field>> getPrivateFields() const;

    [[nodiscard]] std::vector<std::shared_ptr<Field>> getPublicFields() const;

    [[nodiscard]] std::vector<Function> getPrivateFunctions() const;

    [[nodiscard]] std::vector<Function> getPublicFunctions() const;

    explicit Class(std::string name);

    void setName(std::string name);

    void setSuperclassName(const std::string& superclass_name);

    void addField(const std::shared_ptr<Field>& field);

    void addFunction(const Function& function);

    [[nodiscard]] std::string getName() const;

    [[nodiscard]] std::string get_superclass_name() const;

    void setClassType(ClassType class_type);

    [[nodiscard]] std::string generateMermaid() const;

private:
    std::string name;
    std::string superclass_name;
    ClassType class_type;

    std::vector<std::shared_ptr<Field>> private_fields;
    std::vector<std::shared_ptr<Field>> public_fields;
    std::vector<std::shared_ptr<Field>> protected_fields;
    std::vector<Function> private_functions;
    std::vector<Function> public_functions;
    std::vector<Function> protected_functions;
};


#endif //CLASS_H
