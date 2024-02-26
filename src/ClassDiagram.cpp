#include "ClassDiagram.h"

#include <fstream>
#include <iostream>

#include "EnumField.h"
#include "Utils.h"
#include "Visibility.h"

ClassDiagram::ClassDiagram(const std::vector<std::string>& files) {
    for (const auto& filename: files) {
        std::ifstream file(filename);

        std::string str;
        bool skip = false;
        auto cur_visibility = Visibility::Private;
        bool line_not_ended = false;
        bool in_enum = false;


        std::vector<std::shared_ptr<Class>> class_vector;

        std::shared_ptr<Class> c;

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

            size_t i;
            while (i = str.find("  "), i != std::string::npos) {
                str.replace(i, 2, " ");
            }

            if (auto i = str.find("//"); i != std::string::npos) {
                str = str.substr(0, i);
            }

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
            } else if (str.find('}') == 0) {
                continue;
            } else if (str.find("= delete") != std::string::npos) {
                continue;
            }

            if (str.at(str.length() - 1) == ';' && str.length() >= 2 && str.at(str.length() -2) != ')') {
                str = str.substr(0, str.length() - 1);
            } else if (str.at(str.length() - 1) != '{' && str.at(str.length() - 1) != ':' && !in_enum && str.at(str.length()-1) != ';') {
                line_not_ended = true;
                continue;
            }

            std::smatch m;

            bool class_or_struct = false;

            if (std::regex_match(str, m, enum_regex)) {
                c = std::make_shared<Class>();
                c->setClassType(ClassType::Enum);
                class_vector.push_back(c);
                c->setName(m[1]);

                cur_visibility = Visibility::Public;

                in_enum = true;
                continue;
            } else if (std::regex_match(str, m, class_regex)) {
                c = std::make_shared<Class>();
                c->setClassType(ClassType::Class);
                class_vector.push_back(c);
                class_or_struct = true;

                cur_visibility = Visibility::Private;

                in_enum = false;
            } else if (std::regex_match(str, m, struct_regex)) {
                class_or_struct = true;
                c = std::make_shared<Class>();
                c->setClassType(ClassType::Struct);
                class_vector.push_back(c);

                cur_visibility = Visibility::Public;

                in_enum = false;
            }

            if (class_or_struct) {
                std::string probably_name = m[1];
                c->setName(m[1]);

                if (std::regex_match(probably_name, m, superclass_regex)) {
                    c->setName(m[1]);
                    c->setSuperclassName(m[2]);
                }

                continue;
            } else if (str.find("public") != std::string::npos) {
                cur_visibility = Visibility::Public;
                continue;
            } else if (str.find("private") != std::string::npos) {
                cur_visibility = Visibility::Private;
                continue;
            } else if (str.find("protected") != std::string::npos) {
                cur_visibility = Visibility::Protected;
                continue;
            } else {
                replace_all(str, "<", "~");
                replace_all(str, ">", "~");

                bool isFunction = false;

                auto firstParanthesis = str.find('(');

                if (firstParanthesis != std::string::npos && str.substr(0, firstParanthesis).find("std::function") ==
                    std::string::npos && str.find(')') != std::string::npos) {
                    if (auto i = str.rfind(" const"); i != std::string::npos && i == str.length() - 6) {
                        str = str.substr(0, i);
                    }

                    replace_all(str, "[[nodiscard]]", "");

                    bool is_virtual = false;

                    if (str.find("virtual") != std::string::npos) {
                        is_virtual = true;
                        replace_all(str, "virtual", "");
                    } else if (str.find("override") != std::string::npos) {
                        is_virtual = true;
                        replace_all(str, "override", "");
                    }


                    if (auto j = str.find('='); j != std::string::npos && str.at(str.length()-1) != ')') {
                        str = str.substr(0, j);
                    }

                    trim(str);

                    if (std::regex_match(str, m, function_return_regex)) {
                        std::smatch match2;

                        if (auto wo_returntype = std::string(m[2]); std::regex_search(wo_returntype, match2, function_args_regex)) {
                            c->addFunction(Function(cur_visibility, match2[1], match2[2], m[1], is_virtual));
                        } else {
                            std::cout << "Wtf is happening" << std::endl;
                                std::cout << m[2] << std::endl;
                        }
                    } else {
                        auto destructor_regex = std::string(function_destructor_regex);

                        destructor_regex.replace(destructor_regex.find("class"), 5, c->getName());

                        if (auto regex = std::regex(destructor_regex); std::regex_match(str, m, regex)) {
                            std::smatch match2;

                            if (auto wo_returntype = std::string(m[2]); std::regex_search(wo_returntype, match2, function_args_regex)) {
                                c->addFunction(Function(cur_visibility, match2[1], match2[2], m[1], is_virtual));
                            } else {
                                std::cout << "Wtf is happening" << std::endl;
                            }
                        } else {
                            auto constructor_regex = std::string(function_constructor_regex);
                            constructor_regex.replace(constructor_regex.find("class"), 5, c->getName());
                            regex = std::regex(constructor_regex);

                            if (std::regex_match(str, m, regex)) {
                                std::smatch match2;

                                if (auto wo_returntype = std::string(m[2]); std::regex_search(wo_returntype, match2, function_args_regex)) {
                                    c->addFunction(Function(cur_visibility, match2[1], match2[2], m[1], is_virtual));
                                } else {
                                    std::cout << "Wtf is happening" << std::endl;
                                }
                            }
                        }
                    }
                } else {
                    if (str.at(str.length()-1) == ';') {
                        str = str.substr(0, str.length()-1);
                    }

                    trim(str);

                    if (str.empty())
                        return;


                    if (in_enum) {
                        if (auto i = str.find(" ="); i != std::string::npos) {
                            str = str.substr(0, i);
                        }

                        if (str.at(str.length() -1) == ',') {
                            str = str.substr(0, str.length()-1);
                        }

                        if (c != nullptr) {
                            c->addField(std::move(std::make_shared<EnumField>(str)));
                        }
                    } else if (auto i = str.find(' '); i != std::string::npos) {
                        if (auto i = str.find(" ="); i != std::string::npos) {
                            str = str.substr(0, i);
                        }

                        if (c != nullptr) {
                            c->addField(std::make_shared<Field>(cur_visibility, str.substr(0, i),
                                                                str.substr(i + 1, str.length())));
                        }
                    } else {
                        std::cout << "????? what even is this thing " << std::endl;
                        std::cout << str << std::endl;
                    }
                }
            }
            //std::cout << str << std::endl;;
        }


        for (const auto& item: class_vector) {
            classes.push_back(item);
        }
    }

    for (const auto& class1: classes) {
        for (const auto& class2: classes) {
            if (class1->getName() == class2->getName())
                continue;

            if (class1->get_superclass_name() == class2->getName()) {
                links.emplace_back(class1->getName(), class2->getName(), LinkType::Superclass);
                continue;
            }

            bool found = false;

            for (const auto& public_field: class1->getPublicFields()) {
                if (public_field->getType() == class2->getName() || public_field->getType().find(
                        "~" + class2->getName() + "~") != std::string::npos) {
                    links.emplace_back(class1->getName(), class2->getName(), LinkType::Classic);

                    found = true;

                    break;
                }
            }

            if (!found) {
                for (const auto& private_field: class1->getPrivateFields()) {
                    if (private_field->getType() == class2->getName() || private_field->getType().find(
                            "~" + class2->getName() + "~") != std::string::npos) {
                        links.emplace_back(class1->getName(), class2->getName(), LinkType::Classic);

                        found = true;

                        break;
                    }
                }
            }

            if (!found) {
                for (const auto& public_functions: class1->getPublicFunctions()) {
                    if (public_functions.getArgs().find(class2->getName()) != std::string::npos) {
                        links.emplace_back(class1->getName(), class2->getName(), LinkType::Indirect);

                        found = true;

                        break;
                    }
                }
            }

            if (!found) {
                for (const auto& private_functions: class1->getPublicFunctions()) {
                    if (private_functions.getArgs().find(class2->getName()) != std::string::npos) {
                        links.emplace_back(class1->getName(), class2->getName(), LinkType::Indirect);

                        found = true;

                        break;
                    }
                }
            }
        }
    }
}

std::string ClassDiagram::generateMermaid() const {
    std::string output;
    output.append("classDiagram\n");

    for (const auto& link: links) {
        output.append(link.generateMermaid());
    }

    for (const auto& class_: classes) {
        output.append(class_->generateMermaid());
        output.append("\n\n");
    }

    return output;
}
