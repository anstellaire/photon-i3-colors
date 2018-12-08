#include <string>
#include <memory>
#include <iostream>

// -----------------------------------------------------------------------------
//   PATTERN (dynamic polymorphism)
// -----------------------------------------------------------------------------

struct expr {
    virtual ~expr() {}
    virtual void print(std::ostream& out) = 0;
    virtual double eval() = 0;
};

struct number : expr {
    float val;

    number(float val) : val(val) {}

    void print(std::ostream& out) {
        out << val;
    }

    double eval() {
        return val;
    }
};

struct binary_expr : expr {
    std::unique_ptr<expr> lh;
    std::unique_ptr<expr> rh;
    char op;

    binary_expr(std::unique_ptr<expr> lh, std::unique_ptr<expr> rh, char op) :
        lh(std::move(lh)), rh(std::move(rh)), op(op) {}

    void print(std::ostream& out) {
        out << "(";
        lh->print(out);
        out << " " << op << " ";
        rh->print(out);
        out << ")";
    }

    double eval() {
        switch (op) {
            case '+': return lh->eval() + rh->eval();
            case '-': return lh->eval() - rh->eval();
            case '*': return lh->eval() * rh->eval();
            case '/': return lh->eval() / rh->eval();
            default: throw std::exception{};
        };
    }
};

// -----------------------------------------------------------------------------
//   USAGE
// -----------------------------------------------------------------------------

int main() {
    std::unique_ptr<expr> expr1{new binary_expr{
        std::unique_ptr<expr>{new number(5)},
        std::unique_ptr<expr>{new number(11)},
        '+'
    }};

    std::unique_ptr<expr> expr2{new binary_expr{
        std::unique_ptr<expr>{new number(7)},
        std::unique_ptr<expr>{new number(3)},
        '-'
    }};

    std::unique_ptr<expr> expr3{new binary_expr{
        std::unique_ptr<expr>{new number(2)},
        std::move(expr2),
        '*'
    }};

    std::unique_ptr<expr> exprX{new binary_expr{
        std::move(expr3),
        std::move(expr1),
        '/'
    }};

    exprX->print(std::cout << "Expression ");
    std::cout << " equals " << exprX->eval() << std::endl;
}
