#include <iostream>

struct checkbox;
struct button;
struct config;
struct mediator;

// -----------------------------------------------------------------------------
//   PATTERN
// -----------------------------------------------------------------------------

struct checkbox {
    mediator* manager;
    bool checked;

    void on_click();
};

struct button {
    mediator* manager;
    bool locked;

    void on_click();
};

struct config {
    bool feature1_enabled = false;
    bool feature2_enabled = false;

    friend bool operator==(config const& c1, config const& c2) {
        return c1.feature1_enabled == c2.feature1_enabled
            && c1.feature2_enabled == c2.feature2_enabled;
    }

    static config get_default_config () {
        return config{false, false};
    }
};

struct mediator {
    checkbox& f1;
    checkbox& f2;
    button& rset;
    button& save;
    config& conf;

    mediator(checkbox& f1, checkbox& f2, button& rset, button& save, config& conf) :
        f1(f1), f2(f2), rset(rset), save(save), conf(conf) {

        f1.manager = this;
        f2.manager = this;
        rset.manager = this;
        save.manager = this;
    }

    void notify(checkbox&);
    void notify(button&);
    void notify(config&);
};

// -----------------------------------------------------------------------------
//   PATTERN (implementation)
// -----------------------------------------------------------------------------

void checkbox::on_click() {
    checked = !checked;
    manager->notify(*this);
}

void button::on_click() {
    manager->notify(*this);
}

void mediator::notify(checkbox& cbox) {
    std::printf(" > click checkbox (%p) -> %i\n", &cbox, int(cbox.checked));

    config unsaved{f1.checked, f2.checked};

    if (unsaved == config::get_default_config()) {
        rset.locked = true;
        std::printf(" > unsaved configuration == default (reset button -> locked)\n");
    } else {
        rset.locked = false;
        std::printf(" > unsaved configuration != default (reset button -> unlocked)\n");
    }

    if (unsaved == conf) {
        save.locked = true;
        std::printf(" > unsaved configuration == saved (reset button -> locked)\n");
    } else {
        save.locked = false;
        std::printf(" > unsaved configuration != saved (reset button -> unlocked)\n");
    }
}

void mediator::notify(button& btn) {
    if (&btn == &rset) {
        std::printf(" > click reset button\n");
        if (btn.locked)
            return;

        conf = config::get_default_config();
        rset.locked = true;
        std::printf(" > reset configuration (reset button -> locked)\n");
    } else if (&btn == &save) {
        std::printf(" > click save button\n");
        if (btn.locked)
            return;

        conf = config{f1.checked, f2.checked};
        save.locked = true;
        std::printf(" > save configuration (save button -> locked)\n");
    }
}

// -----------------------------------------------------------------------------
//   USAGE
// -----------------------------------------------------------------------------

int main() {
    const config def_conf = config::get_default_config();

    checkbox f1_cbox{nullptr, def_conf.feature1_enabled};
    checkbox f2_cbox{nullptr, def_conf.feature2_enabled};

    button reset{nullptr, true};
    button save{nullptr, true};

    config new_conf = def_conf;

    mediator menu(f1_cbox, f2_cbox, reset, save, new_conf);

    f1_cbox.on_click();
    f1_cbox.on_click();
    f2_cbox.on_click();
    save.on_click();
    f2_cbox.on_click();
    f2_cbox.on_click();
    reset.on_click();
}
