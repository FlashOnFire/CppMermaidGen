#include "Link.h"

Link::Link(std::string class1, std::string class2, const LinkType type): class1(std::move(class1)),
                                                                         class2(std::move(class2)), type(type) {
}

std::string Link::generateMermaid() const {
    std::string output;
    output.append(class1 + " ");

    switch (type) {
        case LinkType::Classic:
            output.append("-->");
            break;
        case LinkType::Indirect:
            output.append("..>");
            break;
        case LinkType::Superclass:
            output.append("--|>");
            break;
    }

    output.append(" " + class2);
    output.append("\n");

    return output;
}
