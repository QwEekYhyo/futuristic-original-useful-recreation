#include <board.hpp>

board::board() {
    for (auto& row : m_grid) {
        for (auto& cell : row) {
            cell = player::none;
        }
    }
    m_current_player = player::one;
}

void board::switch_player() {
    m_current_player = m_current_player == player::one ? player::two : player::one;
}

bool board::is_column_full(int column) {
    return m_grid.at(0).at(column) != player::none;
}

int board::get_upper(int column) {
    if (!is_column_full(column)) {
        for (int i = height - 1; i >= 0; i--) {
            if (m_grid.at(i).at(column) == player::none) {
                return i;
            }
        }
    }
    return 69; // compiler is crying because it might return void but in
               // reality it cannot
}

void board::play(int column) {
    if (!is_column_full(column)) {
        m_grid.at(get_upper(column)).at(column) = m_current_player;
        switch_player();
    }
}

std::ostream& operator<<(std::ostream& os, const board& b) {
    for (int i = 0; i < b.height; i++) {
        for (int j = 0; j < b.width; j++) {
            if (b.m_grid.at(i).at(j) == player::one) {
                os << 'Y';
            } else if (b.m_grid.at(i).at(j) == player::two) {
                os << 'R';
            } else {
                os << '0';
            }
            os << ' ';
        }
        os << '\n';
    }
    return os;
}
