#ifndef ENN_ERR_H
#define ENN_ERR_H

#if __cplusplus
    #include <cstdio>
    #include <cstdlib>

    #define ENN_NAMESPACE_STD std::
    #define ENN_NAMESPACE_BEGIN(name) namespace name {
    #define ENN_NAMESPACE_END }
#else
    #include <stdio.h>
    #include <stdlib.h>

    #define ENN_NAMESPACE_STD
    #define ENN_NAMESPACE_BEGIN(name)
    #define ENN_NAMESPACE_END
#endif

ENN_NAMESPACE_BEGIN(enn)
ENN_NAMESPACE_BEGIN(err)

    inline void expect(bool expr, char const* msg = NULL) {
        if (expr)
            return;
        if (msg)
            ENN_NAMESPACE_STD fprintf(stderr, "[ERROR] > %s\n", msg);
        ENN_NAMESPACE_STD exit(EXIT_FAILURE);
    }

ENN_NAMESPACE_END // namespace err
ENN_NAMESPACE_END // namespace enn

#if 1
    #undef ENN_NAMESPACE_STD
    #undef ENN_NAMESPACE_BEGIN
    #undef ENN_NAMESPACE_END
#endif

#endif // ENN_ERR_H
