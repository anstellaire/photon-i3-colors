#include <iostream>

typedef unsigned log_level;
#define LOG_LVL_DEBUG (1u << 0)
#define LOG_LVL_INFO (1u << 1)
#define LOG_LVL_WARNING (1u << 2)
#define LOG_LVL_ERROR (1u << 3)

// -----------------------------------------------------------------------------
//   PATTERN (static polymorphism + composition)
// -----------------------------------------------------------------------------

template<typename Impl>
struct logger {
    Impl impl;

    void handle(log_level lvl, char const* msg) {
        return impl.handle(lvl, msg);
    }
};

template<>
struct logger<void> {
    void handle(log_level, char const*) {}
};

template<typename Impl>
struct term_logger {
    log_level trigger;
    logger<Impl> next;

    void handle(log_level lvl, char const* msg) {
        if (lvl & trigger)
            std::cout << "[TERM LOG] > " << msg << std::endl;
        return next.handle(lvl, msg);
    }
};

template<typename Impl>
struct file_logger {
    log_level trigger;
    logger<Impl> next;

    void handle(log_level lvl, char const* msg) {
        if (lvl & trigger)
            std::cout << "[FILE LOG] > " << msg << std::endl;
        return next.handle(lvl, msg);
    }
};

template<typename Impl>
struct email_logger {
    log_level trigger;
    logger<Impl> next;

    void handle(log_level lvl, char const* msg) {
        if (lvl & trigger)
            std::cout << "[MAIL LOG] > " << msg << std::endl;
        return next.handle(lvl, msg);
    }
};

// -----------------------------------------------------------------------------
//   USAGE
// -----------------------------------------------------------------------------

int main() {
    email_logger<void> email_log{
        LOG_LVL_ERROR, logger<void>{}};
    file_logger<email_logger<void>> file_log{
        LOG_LVL_ERROR | LOG_LVL_WARNING, email_log};
    term_logger<file_logger<email_logger<void>>> term_log{
        LOG_LVL_INFO | LOG_LVL_DEBUG, file_log};

    logger<term_logger<file_logger<email_logger<void>>>> log_chain{term_log};

    log_chain.handle(LOG_LVL_DEBUG,
        "We debug with printf's =0");
    log_chain.handle(LOG_LVL_INFO | LOG_LVL_WARNING,
        "Hans is sleeping at work again!");
    log_chain.handle(LOG_LVL_ERROR,
        "By the way, your server is burning down here");
    log_chain.handle(LOG_LVL_INFO,
        "Und wenn die ganze Welt gegen dich ist wirst du gegen sie gehen");
}
