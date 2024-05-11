# CppMermaidGen

Small utility quickly made to generate Mermaid class diagram directly from cpp source files
To use it just edit the path and the blacklist in main.cpp and run !

The code is awful but i needed it fast to submit a beautiful graph for a school project.
It is quite buggy as it doesn't parse well operator functions nor global variables (anything declared outside a class).

There are plenty of better alternatives out there i didn't find at the time such as 
[clang-uml](https://github.com/bkryza/clang-uml) or [hpp2plantuml](https://github.com/thibaultmarin/hpp2plantuml)
