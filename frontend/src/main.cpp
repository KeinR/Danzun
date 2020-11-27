
// #include "../../src/core.h"
#include "../../src/loader/Program.h"
#include "../../src/loader/Script.h"

const char *code = R"(

print ("Hell0 from LUA!")

)";

int main() {
    dan::Script s(code, ".");
    dan::Program p(s);
}
