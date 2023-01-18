# Detour and Generic Hook Class
MS Detours lacks OOP, so this wraps and manages a detour. You could also derive from the IHook class and define your own hooking mechanisms or use different libraries. MS Detours can be found at https://github.com/microsoft/Detours
## Usage:
Suppose you want to hook a function with the signature `int foo(Object* object, int count)` located at address `void* Target`. 

**IMPORTANT PREFACE**: When constructing a Detour (or any IHook) object with a lambda, you must leave the capture clause (the `[]` at the beginning of a lambda) empty. This prevents it from becoming a context-dependent `std::function`. I'll eventually get around to making a formal template constraint.
### Replacement
 To replace the original function, do something like this:
 
			 Detour<int, Object*, int> a_detour(Target, [](Object* object, int count){
							 ... code
							 return 20; //dummy value
			 });
   Because it returns to the original function's caller, the original function is effectively replaced.
 ### Detour/Hook
 To call the original function at any point, do:  
 
 `static_cast<int(__fastcall*)(Object*, int)>(a_detour.GetTarget())(object, count)` 
 
 within your hook function. Do it before your code, return it as a closure, throw it in the middle, whatever you want.
