#include <board.hpp>
#include <iostream>
#include <string>

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
    return at({column, 0}) != player::none;
}

int board::get_upper(int column) const {
    // we assume that this is called on a non-full column
    for (int i = height - 1; i >= 0; i--) {
        if (at({column, i}) == player::none) {
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
        at({column, top}) = m_current_player;
        switch_player();
        m_last_position_played = std::make_pair(column, top);
    }
}

void board::start_game() {
    int c;
    bool working = true;
    player winner;

    std::cout << *this << '\n';
    while (working) {
        std::cout << "Column : ";
        std::cin >> c;
        play(c);
        std::cout << '\n' << *this << '\n';
        
        winner = get_winner();
        if (winner != player::none) {
            std::string s_winner = winner == player::one ? "Player 1" : "Player 2";
            std::cout << s_winner << " won !!" << std::endl;
            working = false;
        } else if (is_full()) {
            std::cout << "Game over ! This is a tie" << std::endl;
            working = false;
        }
    }
}

player& board::at(std::pair<int, int> coord) {
    return m_grid.at(coord.second).at(coord.first);
}

const player& board::at(const std::pair<int, int> &coord) const {
    return m_grid.at(coord.second).at(coord.first);
}

player board::get_winner_from_arr(const std::array<std::pair<int, int>, 4> &coords) const {
    player current_player;
    player next_player;
    for (int i = 0; i < coords.size() - 1; i++) {
        current_player = at(coords[i]);
        next_player = at(coords[i+1]);
        if (current_player == player::none || current_player != next_player) {
            return player::none;
        }
    }
    return current_player;
}

player board::get_winner() const {
    int x = m_last_position_played.first;
    int y = m_last_position_played.second;

    int starting_index;
    int ending_index;

    std::array<std::pair<int, int>, 4> segment;
    player winner;

    // horizontal slash
    starting_index = x - 3;
    starting_index = starting_index >= 0 ? starting_index : 0;
    ending_index = x;
    ending_index = ending_index <= width - 4 ? ending_index : width - 4;
    for (int i = starting_index; i <= ending_index; i++) {
        for (int j = 0; j < 4; j++) {
            segment[j] = std::make_pair(i + j, y);
        }
        winner = get_winner_from_arr(segment);
        if (winner != player::none) {return winner;}
    }
    return player::none;
}

std::ostream& operator<<(std::ostream& os, const board& b) {
    for (int i = 0; i < b.height; i++) {
        for (int j = 0; j < b.width; j++) {
            if (b.at({j, i}) == player::one) {
                os << 'Y';
            } else if (b.at({j, i}) == player::two) {
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
