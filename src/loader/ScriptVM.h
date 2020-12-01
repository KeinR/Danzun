#ifndef DANZUN_SCRIPTVM_H_INCLUDED
#define DANZUN_SCRIPTVM_H_INCLUDED

#include <string>
#include <ostream>
#include <filesystem>
#include <functional>

struct lua_State;
struct luaL_Reg;

namespace dan {
    class Script;
    class Program;
    class Lib;
}

namespace dan {
    class ScriptVM {
    public:
        typedef std::function<void(ScriptVM&, const std::string&)> errCallback_t;
    private:
        lua_State *L;
        Program *program;
        errCallback_t errCallback;
        bool checkState(int code);
        void steal(ScriptVM &other);
        void free();
    public:
        // Throws std::runtime_error if lua VM init failed
        ScriptVM();
        ScriptVM(ScriptVM &&other);
        ~ScriptVM();
        ScriptVM &operator=(ScriptVM &&other);

        lua_State *getHandle();

        void setProgram(Program &p);
        Program &getProgram();
        void setErrCallback(const errCallback_t &callback);

        void setGlobal(const std::string &name, const std::string &val);
        void setGlobal(const std::string &name, float val);
        void setGlobal(const std::string &name, int val);

        void openLib(const Lib &lib);
        void closeLib(const Lib &lib);

        // Throws std::logic_error on failure
        void call(const std::string &name);

        std::string getGlobal(const std::string &name);

        // Throws logic_error on error
        void exec(const std::string &code);
        void execFile(const std::string &code);
        void exec(const Script &script);

        static ScriptVM &getVM(lua_State *L);
    };
}

#endif
