#include <board.hpp>
#include <iostream>

std::ostream& operator<<(std::ostream& os, const player& p) {
    if (p == player::one) {
        os << 'Y';
    } else if (p == player::two) {
        os << 'R';
    } else {
        os << '0';
    }
    return os;
}

board::board() {
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            m_grid.at(i).at(j) = player::none;
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
        coords coord;
        coord.at(0) = column;
        coord.at(1) = get_upper(column);

        at(coord) = m_current_player;
        switch_player();
        m_last_position_played.fill(coord);
    }
}

void board::start_game() {
    int c;
    bool working = true;
    player winner;

    std::cout << *this << '\n';
    while (working) {
        if (m_current_player == player::two) {
            int choice = choose_column();
            play(choice);
            std::cout << '\n' << *this << '\n';
            continue;
        }
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
    coords diagonal_start;

    array<coords, 4> segment;
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

template <int N>
int board::count_in_arr(const array<coords, N> &coordinates, const player& target_player) const {
    int ctr = 0;
    for (int i = 0; i < N; i++) {
        const coords& c = coordinates.at(i);
        if (at(c) == target_player)
            ctr++;
    }
    return ctr;
}

int board::evaluate_arr(const array<coords, 4> &coordinates,
                        const player &current_player) const {
    int score = 0;
    player opponent = player::one;

    if (current_player == player::one)
        opponent = player::two;

    int player_count = count_in_arr(coordinates, current_player);
    int opponent_count = count_in_arr(coordinates, opponent);
    int empty_count = count_in_arr(coordinates, player::none);

    if (player_count == 4) {
        score += 1000;
    } else if (player_count == 3 && empty_count == 1) {
        score += 5;
    } else if (player_count == 2 && empty_count == 2) {
        score += 2;
    }

    if (opponent_count == 3 && empty_count == 1)
        score -= 4;

    return score;
}

int board::evaluate_position(const player &current_player) const {
    int score = 0;

    array<coords, board::height> center_segment;
    for (int i = 0; i < board::height; i++) {
        coords c;
        c.at(0) = i;
        c.at(1) = 3;
        center_segment.at(i) = c;
    }

    int center_count = count_in_arr(center_segment, current_player);
    score += center_count * 6;

    // TODO: other thing


    std::cout << "score: " << score << "\n";

    return score;
}

int board::choose_column() const {
    int max_score = 0;
    int max_column = 0; // player zero by default, might be random

    for (int i = 0; i < board::width; i++) {
        if (!is_column_full(i)) {
            int column_score = negamax(*this, 2, player::two);
            if (column_score > max_score) {
              max_score = column_score;
              max_column = i;
            }
        }
    }

    return max_column;
}

int negamax(const board &b, int depth, const player& current_player) {
    if (depth == 0 /* || node is a terminal node */)
        return b.evaluate_position(current_player);

    int value = -1000000000; // -infinity

    for (int i = 0; i < board::width; i++) {
        if (!b.is_column_full(i)) {
            board copied_board = b;
            copied_board.play(i);
            player opponent_player =
                current_player == player::one ? player::two : player::one;
            value = std::max(
                value, -negamax(copied_board, depth - 1, opponent_player));
        }
    }

    return 0;
}

std::ostream& operator<<(std::ostream& os, const board& b) {
    coords coord;
    for (int i = 0; i < board::height; i++) {
        for (int j = 0; j < board::width; j++) {
            coord.at(0) = j;
            coord.at(1) = i;
            os << b.at(coord);
            os << ' ';
        }
        os << '\n';
    }
    return os;
}
