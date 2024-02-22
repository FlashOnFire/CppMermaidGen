#include <fstream>
#include <iostream>

#include <filesystem>
namespace fs = std::filesystem;

#include "ClassDiagram.h"


int main() {
    std::string path = "/home/flashonfire/CLionProjects/Rashnawa/src/";

    std::vector<std::string> filenames;

    int i = 0;
    for (const auto& entry: fs::recursive_directory_iterator(path)) {
        //if (i > 2)
            //continue;
        if (entry.is_regular_file() && entry.path().has_extension() && entry.path().extension() == ".h") {
            std::cout << "Adding " << entry.path().filename() << "\n";
            filenames.push_back(entry.path());
            i++;
        }
    }

    //filenames.emplace_back("/home/flashonfire/CLionProjects/Rashnawa/src/Game.h");

    auto diagram = ClassDiagram(filenames);

    std::string mermaid = diagram.generateMermaid();

    std::ofstream out("../out/diag.mermaid");
    out << mermaid;

    return 0;
}
