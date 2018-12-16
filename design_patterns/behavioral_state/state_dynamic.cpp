#include <iostream>
#include <memory>

// -----------------------------------------------------------------------------
//   PATTERN
// -----------------------------------------------------------------------------

template<typename State>
struct state_machine {
    std::unique_ptr<State> st;

    state_machine(std::unique_ptr<State> new_st) {
        st = std::move(new_st);
        st->set_context(this);
    }

    void set_state(std::unique_ptr<State> new_st) {
        st = std::move(new_st);
        st->set_context(this);
    }

    template<typename Event>
    void handle(Event&& event) { st->handle(event); }
};

template<typename Derived>
class state {
    state_machine<Derived>* ctx_;
public:
    void set_context(state_machine<Derived>* ctx) { ctx_ = ctx; }
    auto get_context() -> state_machine<Derived>* { return ctx_; }

    virtual ~state<Derived>() {}
};

// -----------------------------------------------------------------------------
//   PATTERN (specific implementation)
// -----------------------------------------------------------------------------

struct event_open{};
struct event_close{};

struct door_state : public state<door_state> {
    virtual void handle(event_open&) = 0;
    virtual void handle(event_close&) = 0;
};

struct door_state_opened : door_state {
    void handle(event_open&);
    void handle(event_close&);
};

struct door_state_closed : door_state {
    void handle(event_open&);
    void handle(event_close&);
};

void door_state_opened::handle(event_open&) {
    std::cout << " > Stop breakin' the door, you brute!" << std::endl;
}

void door_state_opened::handle(event_close&) {
    std::cout << " > Closing the door..." << std::endl;
    get_context()->set_state(std::unique_ptr<door_state>{new door_state_closed{}});
}

void door_state_closed::handle(event_open&) {
    std::cout << " > Opening the door..." << std::endl;
    get_context()->set_state(std::unique_ptr<door_state>{new door_state_opened{}});
}

void door_state_closed::handle(event_close&) {
    std::cout << " > Checking the closed door. Do you have OCD too?" << std::endl;
}

using door_type = state_machine<door_state>;

// -----------------------------------------------------------------------------
//   USAGE
// -----------------------------------------------------------------------------

int main() {
    door_type door(std::unique_ptr<door_state>{new door_state_closed{}});

    door.handle(event_open{});
    door.handle(event_open{});
    door.handle(event_close{});
    door.handle(event_close{});
}
