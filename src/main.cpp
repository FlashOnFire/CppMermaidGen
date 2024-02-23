#include <fstream>
#include <iostream>

#include <filesystem>
namespace fs = std::filesystem;

#include "ClassDiagram.h"


int main() {
    std::string path = "/home/flashonfire/CLionProjects/Rashnawa/src/";
    std::vector<std::string> blacklist = {
        "TriggerBox.h", "Defines.h", "StringHasher.h", "Events.h"
    };


    std::vector<std::string> filenames;

    for (const auto& entry: fs::recursive_directory_iterator(path)) {
        if (entry.is_regular_file() && entry.path().has_extension() && entry.path().extension() == ".h") {
            if (std::find(blacklist.begin(), blacklist.end(), entry.path().filename()) == blacklist.end()) {
                std::cout << "Adding " << entry.path().filename() << "\n";

                filenames.push_back(entry.path());
            } else {
                std::cout << "Not adding blacklisted " << entry.path().filename() << std::endl;
            }
        }
    }

    auto diagram = ClassDiagram(filenames);

    std::string mermaid = diagram.generateMermaid();

    std::ofstream out("../out/diag.mermaid");
    out << mermaid;

    return 0;
}
