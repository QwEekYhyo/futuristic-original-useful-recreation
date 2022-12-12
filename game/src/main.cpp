#include <board.hpp>
#include <string>
#include <sstream>

int main(void) {
    board b;
    std::stringstream ss;
    std::string line;
    int c;

    while (true) {
        std::cout << b << '\n';
        std::cout << "Column : ";
        std::getline(std::cin, line);
        ss << line;
        ss >> c;
        b.play(c);
        ss.clear();
        std::cout << '\n';
    }
    return 0;
}
