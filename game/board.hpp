#ifndef GAME_BOARD_HPP
#define GAME_BOARD_HPP

#include "array.hpp"
#include <Adafruit_NeoPixel.h>

#if defined(USE_RANDOM)
#include <random>
#endif

constexpr int POSITIVE_INFINITY = 32767;
constexpr int NEGATIVE_INFINITY = -POSITIVE_INFINITY;

using coords = array<int, 2>;

enum class player {
  one,
  two,
  none,
};

player opponent_of(const player& p);

class board {
  public:
    board();
    static constexpr int width = 7;
    static constexpr int height = 6;

    void move_cursor(int direction);
    void validate();

    friend void setup();
    friend void loop();

  private:
    Adafruit_NeoPixel* m_strip;
    Adafruit_NeoPixel* top_strip;
    array<array<player, board::width>, board::height> m_grid;
    pair<player> real_players;
    int cursor{3};
    player m_current_player;
    player m_current_ai;
    coords m_last_position_played;
    array<coords, 4> winning_seg;

    player& at(coords coordinates);
    const player& at(const coords& coordinates) const;
    void switch_player();
    bool is_column_full(int column) const;
    bool is_full() const;
    int get_upper(int column) const;
    void play(int column);
    void update();
    player get_winner_from_arr(const array<coords, 4> &coordinates) const;
    player get_winner() const;
    void win_anim();

    bool is_current_player_ai();
    int random_playable_column() const;

    template <int N>
    int count_in_arr(const array<coords, N>& coordinates, const player& target_player) const;

    int evaluate_arr(const array<coords, 4>& coordinates, const player& current_player) const;
    int evaluate_position(const player& current_player) const;
    friend pair<int> minimax(const board& b, int depth, int alpha, int beta, bool maximizing_player);
    int choose_column();
};

#endif
