#ifndef DANZUN_SCRIPTVM_H_INCLUDED
#define DANZUN_SCRIPTVM_H_INCLUDED

#include <ostream>
#include <filesystem>

struct lua_State;

namespace dan {
    class Script;
}

namespace dan {
    class ScriptVM {
    public:
        typedef std::function<void(ScriptVM&, const std::string&)> errorCallback_t;
    private:
        lua_State *L;
        errorCallback_t errCallback;
        std::filesystem::path workingDir;
        bool checkState(int code);
        void steal(ScriptVM &other);
        void free();
    public:
        // Throws std::runtime_error if lua VM init failed
        ScriptVM();
        ScriptVM(ScriptVM &&other);
        ~ScriptVM();
        ScriptVM &operator=(ScriptVM &&other);

        void setErrCallback(const errorCallback_t &callback);

        void setGlobal(const std::string &name, const std::string &val);
        void setGlobal(const std::string &name, float val);
        void setGlobal(const std::string &name, int val);

        std::string getGlobal(const std::string &name);

        void setWorkingDir(const std::filesystem::path &path);
        std::filesystem::path getWorkingDir() const;

        // Throws logic_error on error
        void exec(const std::string &code);
        void exec(const Script &script);

        ScriptVM &getVM(lua_State *L);
    };
}

#endif
