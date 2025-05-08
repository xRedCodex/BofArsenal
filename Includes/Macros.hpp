#define DFR(module, function) DECLSPEC_IMPORT decltype(function) module##$##function;

// Macro to place a variable or function in a specific binary section
#define SEC_ATTR(X) [[gnu::section(X)]]

// Macro to cast a value to a generic pointer
template<typename T>
constexpr auto PTR(T v) -> PVOID {
    return reinterpret_cast<PVOID>(v);
}

// Macro to cast a value to an unsigned pointer-sized integer
template<typename T>
constexpr auto U_PTR(T v) -> ULONG_PTR {
    return reinterpret_cast<ULONG_PTR>(v);
}

// Macro to cast a value to pointer to bytes
template<typename T>
constexpr auto B_PTR(T v) -> PBYTE {
    return reinterpret_cast<PBYTE>(v);
}

// Macro to check if a pointer or value is NULL
template<typename T>
constexpr auto IS_NULL(T* v) -> BOOL {
    return v == nullptr;
}
