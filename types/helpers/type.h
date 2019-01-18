#ifndef ENN_TYPE_H
#define ENN_TYPE_H

#if __cplusplus
    #include <cstdint>

    #define ENN_NAMESPACE_STD std::
    #define ENN_NAMESPACE_BEGIN(name) namespace name {
    #define ENN_NAMESPACE_END }
#else
    #include <stdint.h>

    #define ENN_NAMESPACE_STD
    #define ENN_NAMESPACE_BEGIN(name)
    #define ENN_NAMESPACE_END
#endif

ENN_NAMESPACE_BEGIN(enn)
ENN_NAMESPACE_BEGIN(type)

    typedef signed char ichar;
    typedef unsigned char uchar;
    typedef unsigned char byte;

    typedef ENN_NAMESPACE_STD int8_t i8;
    typedef ENN_NAMESPACE_STD int16_t i16;
    typedef ENN_NAMESPACE_STD int32_t i32;
    typedef ENN_NAMESPACE_STD int64_t i64;

    typedef ENN_NAMESPACE_STD uint8_t u8;
    typedef ENN_NAMESPACE_STD uint16_t u16;
    typedef ENN_NAMESPACE_STD uint32_t u32;
    typedef ENN_NAMESPACE_STD uint64_t u64;

    typedef ENN_NAMESPACE_STD size_t size;

    typedef float f32;
    typedef double f64;

ENN_NAMESPACE_END // namespace type
ENN_NAMESPACE_END // namespace enn

#if 1
    #undef ENN_NAMESPACE_STD
    #undef ENN_NAMESPACE_BEGIN
    #undef ENN_NAMESPACE_END
#endif

#endif // ENN_TYPE_H
