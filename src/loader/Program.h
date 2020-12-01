#ifndef DANZUN_PROGRAM_H_INCLUDED
#define DANZUN_PROGRAM_H_INCLUDED

#include <filesystem>

#include "Script.h"
#include "Data.h"
#include "ScriptVM.h"
#include "../core/Engine.h"

namespace dan {
    class Program {
        ScriptVM vm;
        Engine engine;
        Data data;
    public:
        Program(const std::filesystem::path &startFile);
        Data &getData();
        Engine &getEngine();
    };
}

#endif
