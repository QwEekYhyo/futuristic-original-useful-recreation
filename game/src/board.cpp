#include <board.hpp>
#include <utils.hpp>
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
    int coord[] = {column, 0};
    return at(coord) != player::none;
}

int board::get_upper(int column) const {
    // we assume that this is called on a non-full column
    for (int i = height - 1; i >= 0; i--) {
    int coord[] = {column, i};
        if (at(coord) == player::none) {
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
        int coord[] = {column, top};
        at(coord) = m_current_player;
        switch_player();
        reassign(m_last_position_played, coord);
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

player& board::at(int *coord) {
    return m_grid.at(coord[1]).at(coord[0]);
}

const player& board::at(const int *coord) const {
    return m_grid.at(coord[1]).at(coord[0]);
}

player board::get_winner_from_arr(const std::array<int*, 4> &coords) const {
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
    int x = m_last_position_played[0];
    int y = m_last_position_played[1];

    int starting_index1;
    int starting_index2;
    int ending_index1;
    int ending_index2;

    std::array<int*, 4> segment;
    int zero[4] = {0};
    segment.fill(zero);
    player winner;

    // horizontal slash
    starting_index1 = x - 3;
    starting_index1 = starting_index1 >= 0 ? starting_index1 : 0;
    ending_index1 = x;
    ending_index1 = ending_index1 <= width - 4 ? ending_index1 : width - 4;
    for (int i = starting_index1; i <= ending_index1; i++) {
        for (int j = 0; j < 4; j++) {
            int temp[] = {i + j, y};
            std::cout << "got here" << '\n';
            reassign(segment[j], temp);
        }
        winner = get_winner_from_arr(segment);
        if (winner != player::none) {return winner;}
    }

    // vertical slash
    starting_index2 = y - 3;
    starting_index2 = starting_index2 >= 0 ? starting_index2 : 0;
    ending_index2 = y;
    ending_index2 = ending_index2 <= height - 4 ? ending_index2 : height - 4;
    for (int i = starting_index2; i <= ending_index2; i++) {
        for (int j = 0; j < 4; j++) {
            int temp[] = {x, i + j};
            reassign(segment[j], temp);
        }
        winner = get_winner_from_arr(segment);
        if (winner != player::none) {return winner;}
    }

    // diagonal (top left to bottom right) slash
    int min = x - starting_index1 <=  y - starting_index2 ? x - starting_index1 : y - starting_index2;
    int diagonal_startTL[] = {x - min, y - min};
    min = ending_index1 - diagonal_startTL[0] <=  ending_index2 - diagonal_startTL[1] ? ending_index1 - diagonal_startTL[0] : ending_index2 - diagonal_startTL[1];

    for (int i = 0; i <= min; i++) {
        for (int j = 0; j < 4; j++) {
            int temp[] = {diagonal_startTL[0] + i + j, diagonal_startTL[1] + i + j};
            reassign(segment[j], temp);
        }
        winner = get_winner_from_arr(segment);
        if (winner != player::none) {return winner;}
    }

    // diagonal (top right to bottom left) slash
    min = 3 + ending_index1 - x <=  y - starting_index2 ? 3 + ending_index1 - x : y - starting_index2;
    int diagonal_startTR[] = {x + min, y - min};

    min = diagonal_startTR[0] - starting_index1 <=  ending_index2 - diagonal_startTR[1] ? diagonal_startTR[0] - starting_index1 : ending_index2 - diagonal_startTR[1];

    for (int i = 0; i <= min; i++) {
        for (int j = 0; j < 4; j++) {
            int temp[] = {diagonal_startTR[0] - i - j, diagonal_startTR[1] + i + j};
            reassign(segment[j], temp);
        }
        winner = get_winner_from_arr(segment);
        if (winner != player::none) {return winner;}
    }

    return player::none;
}

std::ostream& operator<<(std::ostream& os, const board& b) {
    for (int i = 0; i < b.height; i++) {
        for (int j = 0; j < b.width; j++) {
            int coord[] = {j, i};
            if (b.at(coord) == player::one) {
                os << 'Y';
            } else if (b.at(coord) == player::two) {
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
