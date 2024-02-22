#include "ClassDiagram.h"

#include <fstream>
#include <iostream>

#include "Utils.h"

ClassDiagram::ClassDiagram(std::vector<std::string> files) {
    for (const auto& filename: files) {
        std::ifstream file(filename);

        std::string str;
        bool skip = false;
        bool cur_visibility = true;
        bool line_not_ended = false;


        Class c;

        while (!file.eof()) {
            if (!line_not_ended)
                std::getline(file, str);
            else {
                std::string nextline;
                std::getline(file, nextline);
                str.append(nextline);
                line_not_ended = false;
            }

            if (str.find("namespace") != std::string::npos) {
                continue;
            }

            replace_all(str, "final", "");
            replace_all(str, "explicit", "");
            replace_all(str, "  ", " ");

            trim(str);

            if (str.empty())
                continue;

            if (skip) {
                if (auto i = str.find("*/"); i != std::string::npos) {
                    skip = false;

                    if (i + 1 < str.length() - 1)
                        str = str.substr(i + 1);
                    else
                        continue;
                }
            }

            if (auto i = str.find("/*"); i != std::string::npos) {
                skip = true;
                if (i == 0)
                    continue;
                else
                    str = str.substr(i - 1);
            }

            if (str.find('#') == 0) {
                continue;
            } else if (str.find("//") == 0) {
                continue;
            } else if (str.find('}') == 0) {
                continue;
            }

            if (str.at(str.length() - 1) == ';') {
                str = str.substr(0, str.length() - 1);
            } else if (str.at(str.length() - 1) != '{' && str.at(str.length() - 1) != ':') {
                line_not_ended = true;
                continue;
            }

            std::smatch m;
            if (std::regex_match(str, m, class_regex)) {
                std::string probably_name = m[1];
                c.setName(m[1]);

                if (std::regex_match(probably_name, m, superclass_regex)) {
                    c.setName(m[1]);
                    c.setSuperclassName(m[2]);
                }

                continue;
            } else if (str.find("public") != std::string::npos) {
                cur_visibility = false;
                continue;
            } else if (str.find("private") != std::string::npos) {
                cur_visibility = true;
                continue;
            } else {
                if (auto i = str.find(" ="); i != std::string::npos) {
                    str = str.substr(0, i);
                }

                replace_all(str, "<", "~");
                replace_all(str, ">", "~");

                if (str.find('(') != std::string::npos && str.find(')') != std::string::npos) {
                    auto i = str.rfind(" const");

                    if (i != std::string::npos && i == str.length() - 6) {
                        str = str.substr(0, i);
                    }

                    replace_all(str, "[[nodiscard]]", "");
                    trim(str);

                    if (std::regex_match(str, m, function_return_regex)) {
                        //str = std::string(m[2]).append(" ").append(m[1]);
                        if (cur_visibility)
                            c.addPrivateFunction(m[2], m[1]);
                        else
                            c.addPublicFunction(m[2], m[1]);
                    }
                } else {
                    if (auto i = str.find(' '); i != std::string::npos) {
                        c.addField(Field(cur_visibility, str.substr(0, i), str.substr(i, str.length())));
                    } else {
                        std::cout << "????? what even is this thing " << std::endl;
                        std::cout << str << std::endl;
                    }
                }
            }
            //std::cout << str << std::endl;;
        }


        classes.push_back(c);
    }

    for (const auto& class1: classes) {
        for (const auto& class2: classes) {
            if (class1.get_superclass_name() == class2.getName()) {
                links.emplace_back(class1.getName(), class2.getName(), LinkType::Classic);
                continue;
            }

            bool found = false;

            for (const auto& public_field: class1.getPublicFields()) {
                if (public_field.getType() == class2.getName() || public_field.getType().find("~" + class2.getName() + "~") != std::string::npos) {
                    links.emplace_back(class1.getName(), class2.getName(), LinkType::Classic);

                    found = true;

                    break;
                }
            }

            if (!found) {
                for (const auto& private_field: class1.getPrivateFields()) {
                    if (private_field.getType() == class2.getName() || private_field.getType().find("~" + class2.getName() + "~") != std::string::npos) {
                        links.emplace_back(class1.getName(), class2.getName(), LinkType::Classic);

                        found = true;

                        break;
                    }
                }
            }
            /*
            if (!found) {
                for (auto public_functions: class1.getPublicFunctions()) {
                    if (public_functions.getName() == class2.getName()) {
                        links.emplace_back(class1.getName(), class2.getName(), LinkType::Classic);

                        found = true;

                        break;
                    }
                }
            }

            if (!found) {
                for (auto private_functions: class1.getPublicFunctions()) {
                    if (private_functions.get() == class2.getName()) {
                        links.emplace_back(class1.getName(), class2.getName(), LinkType::Classic);

                        found = true;

                        break;
                    }
                }
            }*/
        }
    }
}

std::string ClassDiagram::generateMermaid() const {
    std::string output;
    output.append("classDiagram\n");

    for (const auto& link : links) {
        output.append(link.generateMermaid());
    }

    for (const auto& class_: classes) {
        output.append(class_.generateMermaid());
        output.append("\n\n");
    }

    return output;
}
