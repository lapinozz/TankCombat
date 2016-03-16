# Project Guidelines

## Data structure:

1. The project lives in the main directory.
2. In the main directory, there are separate folders for source (```src```), headers (```inc```), documentation (```doc```), media (```media```) and binaries (```bin```).
3. Binaries (and the whole ```bin``` directory) shouldn't be ever commited into repo.
4. Media (and the whole ```media``` directory) shouldn't be commited into repo until late development. They should be shared using other means (Google Drive, Dropbox, OneDrive, FTP, ...).
5. In the main directory, there is a single ```Makefile``` and a ```README.md``` description file.
6. In the source directory, there are all source files (```.cpp```).
7. In the header directory, there are all header files (```.hpp```).
8. Only important documents should be commited into documentation directory. Database schemes (```.sql``` or other raw importable formats) belong here. Any kind of UMLish charts as well. Other files like design document and this style guide belong there too.
9. No document should be uploaded without prior discussion.
10. No IDE project files, helper shell/batch scripts or similar files should be commited into repo.
11. All file names and extensions have to be in lower case, using underscores if needed. (```main.cpp```, ```game.hpp```, ```image.png```, ```track.flac```, ```thing_manager.cpp```)
12. Every class should have it's own source and header pair, unless it's a private utility class for some other class or templated class, which only has header file. File name should reflect the class contained accordingly. (```MyClass``` -> ```my_class.cpp```, ```my_class.hpp```)

## Git:

1. Git repo lives in the project main directory.
2. Each feature should be developed on a properly named branch and merged into master once finished.
3. No branch should be merged without code review and prior discussion.
4. Each commit should be cleanly compilable and runnable. (No important warnings, no errors, the binary is stable, doesn't behave weird and doesn't leak.)
5. Each commit message should be in form of a present simple tense sentence starting with capital letter and ending with full stop and should describe what the commit changes. (```Adds x.```, ```Fixes x.```, ```Modifies x.```, ```Optimizes x.```, ```Rewrites x.``` etc.)
6. Each commit should be gpg signed.
7. All commits should be pushed to GitHub, BitBucket, and private repo.
8. Version tags should be added upon reaching important stages, usually after finishing important Trello ```Week```.
9. SSH key pair should be used for all communication with git repos.

## Code style:

1. All files should be UTF-8 encoded.
2. All files should have UNIX line endings. (```LF```)
3. All files should end in a single empty line.
4. There should never be more than one continuous empty line.
5. Empty lines should only be used to make visual gap between meaningful blocks of code like distinct functions or logical parts of a function.
6. Empty lines should be indented to level of surrounding code.
7. There should never be a trailing whitespace.
8. All indentation should be done in tabs, one tab per level.
9. Block constitutes an indentation level, so does labels (```public:```, ```protected:```, ```private:```, ```case 'X':```).
10. Blocks should open on the same line as the keyword that runs them (```while (1) {```, ```for (; 1; ) {```, ```if (1) {```). (Egyptian brackets, K&R brackets)
11. Blocks should close on their own line (```}```) with the same indentation level as the line with their opening.
12. Else goes on a new line, while of ```do..while``` block goes on the same line with block close.
13. All file paths and include paths must use forward slashes (```/```).
14. System (```<iostream>```) and project (```"inc/this.hpp"```) headers must be properly decorated.
15. All headers must have proper header shields using usual filename to macro name conversion (```this.hpp``` -> ```THIS_HPP```).
16. All constants have to be in upper case and use underscore notation (```const double MY_PI = 3.141592;```).
17. All variables have to be in lower case and use underscore notation (```int some_value = 1;```).
18. All objects should be in UpperCamelCase (```class PlayerCharacter```, ```struct CharacterData```, ```union DataDump```).
19. Everything besides the main function should be inside a namespace. (```namespace game {```)
20. Namespaces should be in lower case and use underscore notation if needed.
21. No using namespaces. (```using namespace std;```)
22. All members should always be called using ```this``` pointer. (```this->value```, ```this->method()```)
23. All member data should always be private or protected. Getters and setters should be introduced where appropriate.
24. Header include order should be this file header (```src/this.cpp``` -> ```"inc/this.hpp"```), any STL headers (```<string>```), any other system headers (```<SFML/Graphics.hpp>```), any other project headers (```"inc/that.hpp"```).
25. Null pointer should be ```nullptr```, not ```NULL```.
26. All functions but constructors and destructors should return explicitly. (```void f() {return;}```)
27. Enums should be enum classes.
28. Lambdas should always have a parameter list and return type.
29. Whenever it makes no logical difference, use prefix increment/decrement over postfix one. (```++i;``` over ```i++;```)
30. Always use member initializers when possible. (```MyClass::MyClass(int a) : a(a) {}```)
31. Empty blocks should always be denoted by ```{}``` rather than a semicolon. (```for (j = 0; j < k; j += z) {}```)
32. Bool values shouldn't be checked by (in)equality operators. Just test them straight or negated. (```if (runs) {```, ```while (!ended) {```)
33. Try to make all names meaningful, yet not overly long.
34. Always open blocks on all logical constructs (```if```, ```else```, ```while```, ```for```, ```do```, ```switch```).
35. On constructors and setters, use the same parameter names as are the matching memeber variables. (```void set_value(int value) {this->value = value; return;}```)
36. In classes, ```public``` members and parents always come first, followed by ```protected``` ones and finally ```private``` ones. Inside the visibility groups, enums come first followed by typedefs, methods (first constructors, destructor and then anything else) and finally member variables.
37. Spaces should go as per these examples: (yes between logic constructs and braces, no between functions and braces, generally yes on outside of any braces or brackets but not inside, yes around math operators, yes after ```,``` and ```;```, no before them etc.)
```
int a = 5 + (10 - 2) / 4 * 2, x = 3;
int *b = nullptr;
int &c;
int f(int a) {
int* g(int *g) {
int& h(int &h) {
const int& const i(const int* const a) const {
while (x && y == 2 || z != 3) {
for (int i; i < 5; ++i) {
std::cout << "a" << 5 << std::endl;
std::cin >> q >> d;
MyClass::MyClass(int a, int b) : a(a), b(b) {}
z = a << 4 & mask | flags;
if (this) {
else if (that) {
else {
[=](int a) -> int {return a * modifier;}
[&, this]() -> int {return this->a * modifier;}
[=, &value]() -> bool {return &value == nullptr;}
MyType MyType::operator+(MyType &other) {
std::unordered_map<std::string, std::vector<sf::Texture>> textures;
```

## Comments:

1. Comments should be written on unclear places.
2. Always explain the idea behind the code, don't dub the code.
3. Be very picky about what to comment. Too much comments = diluted code.
4. Comments should be turned into doxygen style comments whereever appliable.
5. Public API of each class has to be doxygen documented once it is stable.
6. Link sources when some non-trivial idea comes from some source with explanation.

## Trello:

1. All tasks should be added to appropriate lists on trello board.
2. Tasks are split into ```Weeks``` where each ```Week``` represents an incremental update to the previous one.
3. ```Weeks``` are done once they're done. No hard dates are given on them and they can last for shorter or longer than an actual week.
4. Appropriate labels should be added to all tasks.
5. Only person working on the task should update progression labels.
6. Tasks should link any related issues in issue tracker and any other relevant information.
7. Task names should be reasonably short and as clear as possible.
8. Tasks should have short concise description if their names don't make them clear.
9. Should any task need longer description or discussion, issue in issue tracker should be open for it.
10. People shouldn't assign tasks to anyone including themselves without prior discussion.
11. Only person working on the task should move it.
12. Tasks in preparatory stages should be moved in ```Next``` region.
13. Tasks in ```Next``` region should be further analysed and crumbled into subtasks when necessary.
14. Tasks actively worked on should be moved into ```Working on``` region.
15. Tasks considered done should be moved into ```Done``` region.
16. Tasks can be moved back from ```Done``` to ```Working on``` from ```Working on``` to ```Next``` and even from ```Next``` to ```Week``` if needed.
17. Once all tasks in a week are done, reviewed and merged into ```master```, the current ```Week``` should be moved into the past and everything from ```Done``` moved back to it. New ```Week``` can be processed. Previous ```Weeks``` should be left on the board and not archieved without previous discussion.
18. Tasks can be moved between ```Weeks``` when needed after previous discussion.

## Issue tracker:

1. Issues should be open for bugs and features needing longer description or discussion. Short and clear issues are OK just in Trello.
2. Issue names should be reasonable short and as clear as possible, preferably matching a Trello task name they represent.
3. Appropriate labels should be added to all issues.
4. Issues should link any related tasks in Trello and any other relevant information.
5. Only person working on the issue should update progression labels.
6. People shouldn't assign issues to anyone including themselves without prior discussion unless the issue is clearly connected to task, they have assigned.

## Tests:

1. Tests could and should be written in one of three ways: auto tests, unit tests and I/O tests.
2. Auto tests are part of the class code and tests integrity of the class state.
3. Unit tests should be written in Catch.
4. I/O tests should be written as input/output pairs named ```inputXX.test``` and ```outputXX.test``` where ```XX``` is number from ```01``` continuously up.
5. Every commit should pass all tests.
