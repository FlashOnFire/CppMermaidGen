#ifndef FIELD_H
#define FIELD_H
#include <string>


class Field {
protected:
    bool visibility;
    std::string type;
    std::string name;

public:
    virtual ~Field() = default;

    Field(bool visibility, std::string type, std::string name);

    [[nodiscard]] bool getVisibility() const;

    [[nodiscard]] std::string getName() const;

    [[nodiscard]] std::string getType() const;

    [[nodiscard]] virtual std::string generateMermaid() const;
};


#endif //FIELD_H
