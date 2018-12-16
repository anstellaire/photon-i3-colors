#include <iostream>
#include <memory>

typedef unsigned log_level;
#define LOG_LVL_DEBUG (1u << 0)
#define LOG_LVL_INFO (1u << 1)
#define LOG_LVL_WARNING (1u << 2)
#define LOG_LVL_ERROR (1u << 3)

// -----------------------------------------------------------------------------
//   PATTERN (dynamic polymorphism)
// -----------------------------------------------------------------------------

struct logger {
    virtual ~logger() {};
    virtual void handle(log_level lvl, char const* msg) = 0;
};

struct term_logger : logger {
    log_level trigger;
    std::unique_ptr<logger> next;

    term_logger(log_level trigger, std::unique_ptr<logger> next) :
        trigger(trigger), next(std::move(next)) {}

    void handle(log_level lvl, char const* msg) {
        if (lvl & trigger)
            std::cout << "[TERM LOG] > " << msg << std::endl;
        if (next)
            next->handle(lvl, msg);
    }
};

struct file_logger : logger {
    log_level trigger;
    std::unique_ptr<logger> next;

    file_logger(log_level trigger, std::unique_ptr<logger> next) :
        trigger(trigger), next(std::move(next)) {}

    void handle(log_level lvl, char const* msg) {
        if (lvl & trigger)
            std::cout << "[FILE LOG] > " << msg << std::endl;
        if (next)
            next->handle(lvl, msg);
    }
};

struct email_logger : logger {
    log_level trigger;
    std::unique_ptr<logger> next;

    email_logger(log_level trigger, std::unique_ptr<logger> next) :
        trigger(trigger), next(std::move(next)) {}

    void handle(log_level lvl, char const* msg) {
        if (lvl & trigger)
            std::cout << "[MAIL LOG] > " << msg << std::endl;
        if (next)
            next->handle(lvl, msg);
    }
};

// -----------------------------------------------------------------------------
//   USAGE
// -----------------------------------------------------------------------------

int main() {
    std::unique_ptr<logger> email_log{
        new email_logger{LOG_LVL_ERROR, nullptr}};
    std::unique_ptr<logger> file_log{
        new file_logger{LOG_LVL_ERROR | LOG_LVL_WARNING, std::move(email_log)}};
    std::unique_ptr<logger> term_log{
        new term_logger{LOG_LVL_INFO | LOG_LVL_DEBUG, std::move(file_log)}};

    std::unique_ptr<logger> log_chain{std::move(term_log)};

    log_chain->handle(LOG_LVL_DEBUG,
        "We debug with printf's =0");
    log_chain->handle(LOG_LVL_INFO | LOG_LVL_WARNING,
        "Hans is sleeping at work again!");
    log_chain->handle(LOG_LVL_ERROR,
        "By the way, your server is burning down here");
    log_chain->handle(LOG_LVL_INFO,
        "Und wenn die ganze Welt gegen dich ist wirst du gegen sie gehen");
}
