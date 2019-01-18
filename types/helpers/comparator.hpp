#ifndef ENN_COMPARATOR_HPP
#define ENN_COMPARATOR_HPP

#define ENN_GEN_COMP_FOR(type)                                                 \
    friend bool operator>  (type const& t1, type const& t2) {                  \
        return t2 < t1;                                                        \
    }                                                                          \
                                                                               \
    friend bool operator<= (type const& t1, type const& t2) {                  \
        return !(t2 < t1);                                                     \
    }                                                                          \
                                                                               \
    friend bool operator>= (type const& t1, type const& t2) {                  \
        return !(t1 < t2);                                                     \
    }                                                                          \
                                                                               \
    friend bool operator== (type const& t1, type const& t2) {                  \
        return !(t1 < t2 || t2 < t1);                                          \
    }                                                                          \
                                                                               \
    friend bool operator!= (type const& t1, type const& t2) {                  \
        return !(t1 == t2);                                                    \
    }                                                                          \


#endif // ENN_COMPARATOR_HPP
