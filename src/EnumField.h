#ifndef ENUMFIELD_H
#define ENUMFIELD_H
#include "Field.h"


class EnumField : public Field {
public:
    explicit EnumField(const std::string& name): Field(false, "", name) {
    }

    [[nodiscard]] std::string generateMermaid() const override;
};



#endif //ENUMFIELD_H
