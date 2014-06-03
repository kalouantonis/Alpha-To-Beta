#ifndef SCRIPT_EXPORTS_H
#define SCRIPT_EXPORTS_H

class ScriptExports
{
public:
    ScriptExports();
    ~ScriptExports();
    
    template<class CallerType, class RetType>
    static void registerExport(const char* luaFuncName, RetType (CallerType::*func)());

    template<class RetType>
    static void registerExport(const char* luaFuncName, RetType (*func)());
};

#endif // SCRIPT_EXPORTS_H
