#include <ctime>      // std::time_t
#include <vector>     // std::vector
#include <iostream>   // std::cout
#include <chrono>     // std::chrono
#include <iomanip>    // std::put_time
#include <functional> // std::cref

// -----------------------------------------------------------------------------
//   PATTERN
// -----------------------------------------------------------------------------

template<typename Snapshot>
class memento {
    Snapshot snapshot;
    std::time_t time;

public:
    memento(Snapshot snapshot, std::time_t time) :
        snapshot(std::move(snapshot)), time(time) {}

    Snapshot const& get_snapshot() const { return snapshot; }
    time_t get_time() const { return time; }
};

template<typename Caretakee>
class caretaker {
    Caretakee caretakee;
    std::vector<memento<Caretakee>> history;

public:
    caretaker(Caretakee&& caretakee) :
        caretakee(std::move(caretakee)) {};

    template<typename F>
    void do_sth(F f) {
        time_t time = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());

        std::cout << "[CARETAKER] > Creating snapshot at "
                  << std::put_time(std::localtime(&time), "%F %T")
                  << std::endl;

        history.push_back(memento<Caretakee>{caretakee, time});

        f(caretakee);
    }

    template<typename F>
    void do_sth_const(F f) {
        f(std::cref(caretakee));
    }

    void undo_sth() {
        if (!history.empty()) {
            memento<Caretakee> memento = history.back();

            time_t time = memento.get_time();
            std::cout << "[CARETAKER] > Removing snapshot from "
                      << std::put_time(std::localtime(&time), "%F %T")
                      << std::endl;

            caretakee = memento.get_snapshot();
            history.pop_back();
        }
    }
};

// -----------------------------------------------------------------------------
//   USAGE
// -----------------------------------------------------------------------------

struct point {
    int x, y;

    void move(int shiftx, int shifty) {
        x += shiftx;
        y += shifty;
    }
};

int main() {
    point p{0, 0};
    caretaker<point>  ctaker(std::move(p));

    ctaker.do_sth([](point& p) {
        p.move(10, 10);
        std::cout << "point{ " << p.x << ", " << p.y << " }" << std::endl;
    });

    ctaker.do_sth([](point& p) {
        p.move(-5, 40);
        std::cout << "point{ " << p.x << ", " << p.y << " }" << std::endl;
    });

    ctaker.undo_sth();
    ctaker.do_sth_const([](point const& p) {
        std::cout << "point{ " << p.x << ", " << p.y << " }" << std::endl;
    });
}
