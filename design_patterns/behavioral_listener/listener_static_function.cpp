#include <cstdio>
#include <vector>
#include <functional>

// -----------------------------------------------------------------------------
//   PATTERN
// -----------------------------------------------------------------------------

struct event_logger {
    void operator()(char const* event_name) {
        std::printf("[LOG] > logging event (%s)\n", event_name);
    }
};

struct event_handler {
    void operator()(char const* event_name) {
        std::printf("[HANDLER] > handling event (%s)\n", event_name);
    }
};

struct event_source {
    // it supports callable's inner state
    using callback_type = std::function<void(char const*)>;

    static std::size_t next_idx;
    std::vector<std::pair<std::size_t, callback_type&>> listeners;

    // can cause memory leaks known as "lapsed listener problem"
    // since the listener can be deallocated without calling unsubscribe
    //
    // can be cured with std::weak_ptr in
    // event_source constructed from std::shared_ptr
    std::size_t subscribe(callback_type& listener_callback) {
        listeners.push_back({next_idx, listener_callback});
        return ++next_idx;
    }

    void unsubscribe(std::size_t listener_idx) {
        for (auto i = listeners.begin(); i != listeners.end(); ++i) {
            if (i->first == listener_idx)
                listeners.erase(i);
        }
    }

    void notify_listeners(char const* event_name) {
        for (std::pair<std::size_t, callback_type&> listener : listeners)
            std::get<1>(listener)(event_name);
    }
};

std::size_t event_source::next_idx = 0;

// -----------------------------------------------------------------------------
//   USAGE
// -----------------------------------------------------------------------------

int main() {
    std::function<void(char const*)> handler{event_handler{}};
    std::function<void(char const*)> logger{event_logger{}};

    event_source source;
    std::size_t handle_idx = source.subscribe(handler);
    std::size_t logger_idx = source.subscribe(logger);

    source.notify_listeners("event #1");

    source.unsubscribe(logger_idx);
    source.notify_listeners("event #2");
}
