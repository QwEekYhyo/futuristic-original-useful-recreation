#include "board.hpp"
// #include <iostream>

player opponent_of(const player& p) {
  return p == player::two ? player::one : player::two;
}

board::board() {
  for (int i = 0; i < height; i++) {
    for (int j = 0; j < width; j++) {
      m_grid.at(i).at(j) = player::none;
    }
  }
  real_players = {player::one, player::none};
  m_current_player = player::one;
}

void board::switch_player() {
  m_current_player = opponent_of(m_current_player);
}

bool board::is_current_player_ai() {
  return !real_players.contains(m_current_player);
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
    coords coord = {column, get_upper(column)};

    at(coord) = m_current_player;
    switch_player();
    m_last_position_played.fill(coord);
    // update();
  }
}

void board::move_cursor(int d) {
  top_strip->setPixelColor(- cursor + 6, 0, 0, 0);
  if (!d) {
    cursor--;
  } else if (d == 1) {
    cursor++;
  }
  if (cursor < 0) {
    cursor = 0;
  }
  else if (cursor > 6) {
    cursor = 6;
  }
  top_strip->setPixelColor(- cursor + 6, 200, 40, 200);
  top_strip->show();
}

void board::validate() {
  top_strip->setPixelColor(- cursor + 6, 0, 0, 0);
  play(cursor);
  cursor = 3;
  top_strip->setPixelColor(- cursor + 6, 200, 40, 200);
  top_strip->show();
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
    next_player = at(coords.at(i + 1));
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
      segment.at(j) = {i + j, y};
    } bool is_current_player_ai();
    winner = get_winner_from_arr(segment);
    if (winner != player::none) {
      winning_seg.fill(segment);
      return winner;
    }
  }

  // vertical slash
  starting_index2 = y - 3;
  starting_index2 = starting_index2 >= 0 ? starting_index2 : 0;
  ending_index2 = y;
  ending_index2 = ending_index2 <= height - 4 ? ending_index2 : height - 4;
  for (int i = starting_index2; i <= ending_index2; i++) {
    for (int j = 0; j < 4; j++) {
      segment.at(j) = {x, i + j};
    }
    winner = get_winner_from_arr(segment);
    if (winner != player::none) {
      winning_seg.fill(segment);
      return winner;
    }
  }

  // diagonal (top left to bottom right) slash
  int min = x - starting_index1 <=  y - starting_index2 ? x - starting_index1 : y - starting_index2;
  diagonal_start = {x - min, y - min};
  min = ending_index1 - diagonal_start.at(0) <=  ending_index2 - diagonal_start.at(1) ? ending_index1 - diagonal_start.at(0) : ending_index2 - diagonal_start.at(1);

  for (int i = 0; i <= min; i++) {
    for (int j = 0; j < 4; j++) {
      segment.at(j) = {diagonal_start.at(0) + i + j, diagonal_start.at(1) + i + j};
    }
    winner = get_winner_from_arr(segment);
    if (winner != player::none) {
      winning_seg.fill(segment);
      return winner;
    }
  }

  // diagonal (top right to bottom left) slash
  min = 3 + ending_index1 - x <=  y - starting_index2 ? 3 + ending_index1 - x : y - starting_index2;
  diagonal_start = {x + min, y - min};

  min = diagonal_start.at(0) - starting_index1 <=  ending_index2 - diagonal_start.at(1) ? diagonal_start.at(0) - starting_index1 : ending_index2 - diagonal_start.at(1);

  for (int i = 0; i <= min; i++) {
    for (int j = 0; j < 4; j++) {
      segment.at(j) = {diagonal_start.at(0) - i - j, diagonal_start.at(1) + i + j};
    }
    winner = get_winner_from_arr(segment);
    if (winner != player::none) {
      winning_seg.fill(segment);
      return winner;
    }
  }

  return player::none;
}

template <int N>
int board::count_in_arr(const array<coords, N>& coordinates, const player& target_player) const {
  int ctr = 0;
  for (int i = 0; i < N; i++) {
    const coords& c = coordinates.at(i);
    if (at(c) == target_player) ctr++;
  }
  return ctr;
}

int board::evaluate_arr(const array<coords, 4>& coordinates, const player& current_player) const {
  int score = 0;
  player opponent = opponent_of(current_player);

  int player_count = count_in_arr(coordinates, current_player);
  int opponent_count = count_in_arr(coordinates, opponent);
  int empty_count = count_in_arr(coordinates, player::none);

  if (player_count == 4) {
    score += 100;
  } else if (player_count == 3 && empty_count == 1) {
    score += 5;
  } else if (player_count == 2 && empty_count == 2) {
    score += 2;
  }

  if (opponent_count == 3 && empty_count == 1) score -= 4;

  return score;
}

int board::evaluate_position(const player& current_player) const {
  int score = 0;

  array<coords, board::height> center_segment;
  for (int i = 0; i < board::height; i++) {
    coords c = {3, i};
    center_segment.at(i) = c;
  }

  int center_count = count_in_arr(center_segment, current_player);
  score += center_count * 6;

  // Evaluate rows
  for (int y = 0; y < board::height; y++) {
    for (int x = 0; x < board::width - 3; x++) {
      array<coords, 4> row;
      for (int i = 0; i < 4; i++) {
        row.at(i) = {i + y, x};
      }
      score += evaluate_arr(row, current_player);
    }
  }

  // Evaluate cols
  for (int x = 0; x < board::width; x++) {
    for (int y = 0; y < board::height - 3; y++) {
      array<coords, 4> col;
      for (int i = 0; i < 4; i++) {
        col.at(i) = {y, i + x};
      }
      score += evaluate_arr(col, current_player);
    }
  }

  // Slash
  for (int r = 3; r < board::height; r++) {
    for (int c = 0; c < board::width - 3; c++) {
      array<coords, 4> diag;
      for (int i = 0; i < 4; i++) {
        diag.at(i) = {c + i, r - i};
      }
      score += evaluate_arr(diag, current_player);
    }
  }

  // Backslash
  for (int r = 3; r < board::height; r++) {
    for (int c = 3; c < board::width; c++) {
      array<coords, 4> diag;
      for (int i = 0; i < 4; i++) {
        diag.at(i) = {c - i, r - i};
      }
      score += evaluate_arr(diag, current_player);
    }
  }

  return score;
}

int board::choose_column() {
  m_current_ai = m_current_player;
  pair<int> ai_result = minimax(*this, 4, NEGATIVE_INFINITY, POSITIVE_INFINITY, true);
  int column = ai_result.at(0);
  if (is_column_full(column)) {
    // throw std::runtime_error("AI died during computing (consider this a win, jammy bastard)");
  }
  return column;
}

int board::random_playable_column() const {
  int column;
#if defined(USE_RANDOM)
  do {
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist6(0, 6);
    column = static_cast<int>(dist6(rng));
  } while (is_column_full(column));
#else
  for (int i = 0; i < 6; i++) {
    if (!is_column_full(i)) {
      column = i;
      break;
    }
  }
#endif
  return column;
}

pair<int> minimax(const board& b, int depth, int alpha, int beta, bool maximizing_player) {
  player winner = b.get_winner();
  if (depth == 0 || winner != player::none) {
    if (winner == b.m_current_ai) {
      return { -1, POSITIVE_INFINITY};
    } else if (winner == opponent_of(b.m_current_ai)) {
      return { -1, NEGATIVE_INFINITY}; // -10000000
    } else {
      return { -1, b.evaluate_position(b.m_current_ai)};
    }
  }

  if (maximizing_player) {
    int score = NEGATIVE_INFINITY;
    int column = b.random_playable_column();

    for (int i = 0; i < board::width; i++) {
      if (!b.is_column_full(i)) {
        board copied_board = b;
        copied_board.play(i);
        pair<int> result = minimax(copied_board, depth - 1, alpha, beta, false);
        int new_score = result.at(1);
        if (new_score > score) {
          score = new_score;
          column = i;
        }
        alpha = max(score, alpha);
        if (alpha >= beta) break;
      }
    }

    return {column, score};
  } else {
    int score = POSITIVE_INFINITY;
    int column = b.random_playable_column();

    for (int i = 0; i < board::width; i++) {
      if (!b.is_column_full(i)) {
        board copied_board = b;
        copied_board.play(i);
        pair<int> result = minimax(copied_board, depth - 1, alpha, beta, true);
        int new_score = result.at(1);
        if (new_score < score) {
          score = new_score;
          column = i;
        }
        beta = min(score, beta);
        if (alpha >= beta) break;
      }
    }

    return {column, score};
  }
}

void board::update() {
  coords coord;
  for (int i = 0; i < height; i++) {
    for (int j = 0; j < width; j++) {
      coord.at(0) = j;
      coord.at(1) = i;
      if (at(coord) == player::one) {
        m_strip->setPixelColor(j + 7 * i, 255, 0, 0);
      } else if (at(coord) == player::two) {
        m_strip->setPixelColor(j + 7 * i, 255, 255, 0);
      } else {
        m_strip->setPixelColor(j + 7 * i, 0, 0, 0);
      }
    }
  }
  m_strip->show();

}

void board::win_anim() {
  player winner = at(winning_seg.at(0));
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      auto coord = winning_seg.at(j);
      at(coord) = player::none;
    }
    update();
    delay(500);
    for (int j = 0; j < 4; j++) {
      auto coord = winning_seg.at(j);
      at(coord) = winner;
    }
    update();
    delay(500);
  }
}
