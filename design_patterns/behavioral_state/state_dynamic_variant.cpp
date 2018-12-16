#include <iostream>
#include <variant>

// -----------------------------------------------------------------------------
//   PATTERN
// -----------------------------------------------------------------------------

template<typename... States>
struct state_machine {

    std::variant<States...> state_holder;

public:

    template<typename State>
    state_machine(State&& state) :
        state_holder(std::forward<State>(state)) {}

    template<typename State>
    void set_state(State&& state) {
        state_holder = std::forward<State>(state);
    }

    template<typename Event>
    void handle(Event&& event) {
        auto handler = [this, &event] (auto& state) { state.handle(this, event); };

        std::visit(handler, state_holder);
    }

};

// -----------------------------------------------------------------------------
//   PATTERN (specific implementation)
// -----------------------------------------------------------------------------

struct event_open{};
struct event_close{};

struct state_opened;
struct state_closed;

using door_type = state_machine<state_opened, state_closed>;

struct state_opened {
    void handle(door_type*, event_open&);
    void handle(door_type*, event_close&);
};

struct state_closed {
    void handle(door_type*, event_open&);
    void handle(door_type*, event_close&);
};

void state_opened::handle(door_type*, event_open&) {
    std::cout << " > Stop breakin' the door, you brute!" << std::endl;
}

void state_opened::handle(door_type* ctx, event_close&) {
    std::cout << " > Closing the door..." << std::endl;
    ctx->set_state(state_closed{});
}

void state_closed::handle(door_type* ctx, event_open&) {
    std::cout << " > Opening the door..." << std::endl;
    ctx->set_state(state_opened{});
}

void state_closed::handle(door_type*, event_close&) {
    std::cout << " > Checking the closed door. Do you have OCD too?" << std::endl;
}

// -----------------------------------------------------------------------------
//   USAGE
// -----------------------------------------------------------------------------

int main() {
    door_type door{state_closed{}};

    door.handle(event_open{});
    door.handle(event_open{});
    door.handle(event_close{});
    door.handle(event_close{});
}
