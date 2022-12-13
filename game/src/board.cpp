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

bool board::is_column_full(int column) const {
    return m_grid.at(0).at(column) != player::none;
}

int board::get_upper(int column) const {
    // we assume that this is called on a non-full column
    for (int i = height - 1; i >= 0; i--) {
        if (m_grid.at(i).at(column) == player::none) {
            return i;
        }
    }
    return 69; // compiler is crying because it might return void but in
               // reality it cannot
}

bool board::is_full() const {
    for (int i = 0; i < width; i++) {
        if (!is_column_full(i)) {
            return false;
        }
    }
    return true;
}

void board::play(int column) {
    if (!is_column_full(column)) {
        int top = get_upper(column);
        m_grid.at(top).at(column) = m_current_player;
        switch_player();
        m_last_position_played = std::make_pair(column, top);
    }
}

player board::get_winner_from_arr(std::array<std::pair<int, int>, 4> coords) const {
    for (int i = 0; i < coords.length - 1; i++) {
        auto current_player = m_grid.at(coord[i].second).at(coord[i].first);
        auto next_player = m_grid.at(coord[i+1].second).at(coord[i+1].first);
        if (current_player == player::none || current_player != next_player) {
            return player::none;
        }
    }
    return current_player;
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
