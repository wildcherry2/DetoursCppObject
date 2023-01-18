#pragma once

template<class Ret, class ... Args>
class IHook {
    protected:
        using FuncSig = Ret(__fastcall*)(Args...);
    public:
        virtual bool Activate() { return false; }
        virtual bool Deactivate() { return false; }
        void* GetTarget() { return target; }
        FuncSig GetTargetTyped() { return reinterpret_cast<FuncSig>(target); }
        void SetTarget(void* new_target) { target = new_target; }
        FuncSig GetHook() { return hook; }
        void SetHook(FuncSig new_hook) { hook = new_hook; }
        IHook(void* target, FuncSig hook) : target(target), hook(hook) {}
        IHook() = default;
        virtual ~IHook() { Deactivate(); }
    protected:
        void* target = nullptr;
        FuncSig hook = nullptr;
        bool active = false;
};