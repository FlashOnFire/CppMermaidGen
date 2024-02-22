#ifndef FIELD_H
#define FIELD_H
#include <string>


class Field {
    bool visibility;
    std::string type;
    std::string name;

public:
    Field(bool visibility, std::string  name, std::string  type);

    [[nodiscard]] bool getVisibility() const;

    [[nodiscard]] std::string getName() const;

    [[nodiscard]] std::string getType() const;

    [[nodiscard]] std::string generateMermaid() const;
};



#endif //FIELD_H
