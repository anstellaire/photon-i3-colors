#include <cstdio>
#include <memory>
#include <set>

// -----------------------------------------------------------------------------
//   PATTERN
// -----------------------------------------------------------------------------

struct event_listener {
    virtual ~event_listener() {}
    virtual void notify(char const*) = 0;
};

struct event_source {
    std::set<event_listener*> listeners;

    // can cause memory leaks known as "lapsed listener problem"
    // since the listener can be deallocated without calling unsubscribe
    //
    // can be cured with std::weak_ptr in
    // event_source constructed from std::shared_ptr
    void subscribe(event_listener& listener) {
        listeners.insert(&listener);
    }

    void unsubscribe(event_listener& listener) {
        auto found = listeners.find(&listener);
        if (found != listeners.end())
            listeners.erase(found);
    }

    void notify_listeners(char const* event_name) {
        for (event_listener* listener : listeners)
            listener->notify(event_name);
    }
};

struct event_logger : event_listener {
    void notify(char const* event_name) {
        std::printf("[LOG] > logging event (%s)\n", event_name);
    }
};

struct event_handler : event_listener {
    void notify(char const* event_name) {
        std::printf("[HANDLER] > handling event (%s)\n", event_name);
    }
};

// -----------------------------------------------------------------------------
//   USAGE
// -----------------------------------------------------------------------------

int main() {
    std::unique_ptr<event_listener> handler(new event_handler);
    std::unique_ptr<event_listener> logger(new event_logger);

    event_source source;
    source.subscribe(*handler);
    source.subscribe(*logger);

    source.notify_listeners("event #1");

    source.unsubscribe(*logger);
    source.notify_listeners("event #2");
}
