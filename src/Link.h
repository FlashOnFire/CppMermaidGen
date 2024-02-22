#ifndef LINK_H
#define LINK_H


#include <string>
#include "LinkType.h"

class Link {
    std::string class1, class2;
    LinkType type;
public:
    Link(std::string class1, std::string  class2, LinkType type);

    [[nodiscard]] std::string generateMermaid() const;
};



#endif //LINK_H
