#ifndef SCRIPTMANAGER_H
#define SCRIPTMANAGER_H

extern "C" {
    #include "lua/lua.h"
    #include "lua/lualib.h"
    #include "lua/lauxlib.h"
}

#include "luabind/luabind.hpp"
#include "luabind/operator.hpp"
#include "luabind/adopt_policy.hpp"

class ScriptManager
{
public:
    ScriptManager();
    void Initialize();
    void Release();

    inline lua_State* GetState() const {return mainState;}

    static ScriptManager* Get() { return singleton;}

private:
    static ScriptManager* singleton;
    lua_State* mainState;
};

#endif // SCRIPTMANAGER_H
