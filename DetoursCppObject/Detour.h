#pragma once
#ifndef WIN32_LEAN_AND_MEAN
    #define WIN32_LEAN_AND_MEAN
#endif

#include <Windows.h>
#include <string>
#include <vector>
#include "./Detours/include/detours.h"
#include "IHook.h"

template<class Ret, class ... Args>
class Detour : public IHook<Ret, Args...>{
    #ifndef Base
        #define Base IHook<Ret, Args...>
    #endif

    public:
        using FuncSig = Ret(__fastcall*)(Args...);
        Detour(void* a_target, FuncSig a_hook) {
            Base::hook = a_hook;
            Base::target = a_target;
        }

        Detour(const std::string& function_name, FuncSig a_hook) {
            Base::hook = a_hook;
            Base::target = DetourFindFunction(__argv[0], function_name.c_str());
        }

        bool Activate() override {
            if(!Base::hook || !Base::target || Base::active) return false;
            
            DetourTransactionBegin();
            DetourUpdateThread(GetCurrentThread());
            DetourAttach(&static_cast<PVOID&>(Base::target), Base::hook);
            Base::active = DetourTransactionCommit() == NO_ERROR;
            return Base::active;
        }

        bool Deactivate() override {
            if(!Base::hook || !Base::target || !Base::active) return false;
            
            DetourTransactionBegin();
            DetourUpdateThread(GetCurrentThread());
            DetourDetach(&static_cast<PVOID&>(Base::target), Base::hook);
            Base::active = !(DetourTransactionCommit() == NO_ERROR);
            return Base::active;
        }

    #ifdef Base
        #undef Base
    #endif
};