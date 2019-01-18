#ifndef ENN_SYS_INFO_HPP
#define ENN_SYS_INFO_HPP

#ifdef _WIN32
    #define ENN_SYS_WINDOWS 1
    #ifdef _WIN64
        #define ENN_SYS_X64 1
    #else
        #define ENN_SYS_X32 1
    #endif
#elif __APPLE__
    #if TARGET_IPHONE_SIMULATOR
        #define ENN_SYS_IPHONESIMULATOR 1
    #elif TARGET_OS_IPHONE
        #define ENN_SYS_IPHONE 1
    #elif TARGET_OS_MAC
        #define ENN_SYS_MAC 1
    #else
        #error "Unknown platform: unknown apple operating system"
    #endif
#elif __linux__
    #define ENN_SYS_LINUX 1
    #define ENN_SYS_POSIX 1
#elif __unix__
    #define ENN_SYS_UNIX 1
    #define ENN_SYS_POSIX 1
#else
    #error "Unknown platform: unknown operating system"
#endif

#endif // ENN_SYS_INFO_HPP
