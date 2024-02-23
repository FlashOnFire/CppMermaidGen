#ifndef FIELD_H
#define FIELD_H
#include <string>

#include "Visibility.h"


class Field {
protected:
    Visibility visibility;
    std::string type;
    std::string name;

public:
    virtual ~Field() = default;

    Field(Visibility visibility, std::string type, std::string name);

    [[nodiscard]] Visibility getVisibility() const;

    [[nodiscard]] std::string getName() const;

    [[nodiscard]] std::string getType() const;

    [[nodiscard]] virtual std::string generateMermaid() const;
};


#endif //FIELD_H
