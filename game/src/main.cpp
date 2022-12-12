#include <board.hpp>

int main(void) {
    board b;
    int c;

    while (true) {
        std::cout << b << '\n';
        std::cout << "Column : ";
        std::cin >> c;
        b.play(c);
        std::cout << '\n';
    }
    return 0;
}
