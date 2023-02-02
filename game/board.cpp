#include "board.hpp"
// #include <iostream>

board::board() {
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            m_grid.at(i).at(j) = player::none;
        }
    }
    m_current_player = player::one;
    update();
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
        array<int, 2> coord;
        coord.at(0) = column;
        coord.at(1) = get_upper(column);

        at(coord) = m_current_player;
        switch_player();
        m_last_position_played.fill(coord);
    }
}

void board::move_cursor(int d) {
  if (!d) {
    cursor--;
  } else if (d == 1) {
    cursor++;
  }
  if (cursor < 0) {cursor = 0;}
  else if (cursor > 6) {cursor = 6;}
}

void board::validate() {
  play(cursor);
  cursor = 3;
}

/*
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
*/

player& board::at(array<int, 2> coord) {
    return m_grid.at(coord.at(1)).at(coord.at(0));
}

const player& board::at(const array<int, 2> &coord) const {
    return m_grid.at(coord.at(1)).at(coord.at(0));
}

player board::get_winner_from_arr(const array<array<int, 2>, 4> &coords) const {
    player current_player;
    player next_player;
    for (int i = 0; i < 3; i++) {
        current_player = at(coords.at(i));
        next_player = at(coords.at(i+1));
        if (current_player == player::none || current_player != next_player) {
            return player::none;
        }
    }
    return current_player;
}

player board::get_winner() const {
    int x = m_last_position_played.at(0);
    int y = m_last_position_played.at(1);

    int starting_index1;
    int starting_index2;
    int ending_index1;
    int ending_index2;
    array<int, 2> diagonal_start;

    array<array<int, 2>, 4> segment;
    player winner;

    // horizontal slash
    starting_index1 = x - 3;
    starting_index1 = starting_index1 >= 0 ? starting_index1 : 0;
    ending_index1 = x;
    ending_index1 = ending_index1 <= width - 4 ? ending_index1 : width - 4;
    for (int i = starting_index1; i <= ending_index1; i++) {
        for (int j = 0; j < 4; j++) {
            segment.at(j).at(0) = i + j;
            segment.at(j).at(1) = y;
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
            segment.at(j).at(0) = x;
            segment.at(j).at(1) = i + j;
        }
        winner = get_winner_from_arr(segment);
        if (winner != player::none) {return winner;}
    }

    // diagonal (top left to bottom right) slash
    int min = x - starting_index1 <=  y - starting_index2 ? x - starting_index1 : y - starting_index2;
    diagonal_start.at(0) = x - min;
    diagonal_start.at(1) = y - min;
    min = ending_index1 - diagonal_start.at(0) <=  ending_index2 - diagonal_start.at(1) ? ending_index1 - diagonal_start.at(0) : ending_index2 - diagonal_start.at(1);

    for (int i = 0; i <= min; i++) {
        for (int j = 0; j < 4; j++) {
            segment.at(j).at(0) = diagonal_start.at(0) + i + j;
            segment.at(j).at(1) = diagonal_start.at(1) + i + j;
        }
        winner = get_winner_from_arr(segment);
        if (winner != player::none) {return winner;}
    }

    // diagonal (top right to bottom left) slash
    min = 3 + ending_index1 - x <=  y - starting_index2 ? 3 + ending_index1 - x : y - starting_index2;
    diagonal_start.at(0) = x + min;
    diagonal_start.at(1) = y - min;

    min = diagonal_start.at(0) - starting_index1 <=  ending_index2 - diagonal_start.at(1) ? diagonal_start.at(0) - starting_index1 : ending_index2 - diagonal_start.at(1);

    for (int i = 0; i <= min; i++) {
        for (int j = 0; j < 4; j++) {
            segment.at(j).at(0) = diagonal_start.at(0) - i - j;
            segment.at(j).at(1) = diagonal_start.at(1) + i + j;
        }
        winner = get_winner_from_arr(segment);
        if (winner != player::none) {return winner;}
    }

    return player::none;
}

void board::update() {
  array<int, 2> coord;
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            coord.at(0) = j;
            coord.at(1) = i;
            if (at(coord) == player::one) {
                m_strip.setPixelColor(j + 7 * i, 255, 0, 0);
            } else if (at(coord) == player::two) {
                m_strip.setPixelColor(j + 7 * i, 255, 255, 0);
            } else {
                m_strip.setPixelColor(j + 7 * i, 0, 0, 0);
            }
        }
    }
    m_strip.show();

}
