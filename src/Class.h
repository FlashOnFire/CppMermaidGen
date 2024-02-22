#ifndef CLASS_H
#define CLASS_H
#include <string>
#include <vector>

#include "Field.h"
#include "Function.h"


class Class {
public:
    Class() = default;

    [[nodiscard]] std::vector<Field> getPrivateFields() const;

    [[nodiscard]] std::vector<Field> getPublicFields() const;

    [[nodiscard]] std::vector<Function> getPrivateFunctions() const;

    [[nodiscard]] std::vector<Function> getPublicFunctions() const;

    explicit Class(std::string name);

    void setName(std::string name);

    void setSuperclassName(const std::string& superclass_name);

    void addField(const Field& field);

    void addPrivateFunction(const std::string& name, const std::string& return_type);

    void addPublicFunction(const std::string& name, const std::string& return_type);

    [[nodiscard]] std::string getName() const;

    [[nodiscard]] std::string generateMermaid() const;


private:
    std::string name;
    std::string superclass_name;

public:
    [[nodiscard]] std::string get_superclass_name() const;

private:
    std::vector<Field> private_fields;
    std::vector<Field> public_fields;
    std::vector<Function> private_functions;
    std::vector<Function> public_functions;
};


#endif //CLASS_H
