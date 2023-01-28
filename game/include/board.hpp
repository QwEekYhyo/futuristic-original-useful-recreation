#ifndef GAME_BOARD_HPP
#define GAME_BOARD_HPP

#include <array.hpp>
#include <iostream>

constexpr int POSITIVE_INFINITY = 1000000000;
constexpr int NEGATIVE_INFINITY = -POSITIVE_INFINITY;

using coords = array<int, 2>;

enum class player {
    one, 
    two, 
    none,
};

std::ostream& operator<<(std::ostream& os, const player& p);
player opponent_of(const player& p);

class board {
    public:
        board();
        static constexpr int width = 7;
        static constexpr int height = 6;
        static constexpr int ai_depth = 4;

        player& at(coords coordinates);
        const player& at(const coords& coordinates) const;
        void start_game();
        friend std::ostream& operator<<(std::ostream& os, const board& b);

    private:
        array<array<player, width>, height> m_grid;
        player m_current_player;
        coords m_last_position_played;

        void switch_player();
        bool is_column_full(int column) const;
        int get_upper(int column) const;
        bool is_full() const;
        void play(int column);
        player get_winner_from_arr(const array<coords, 4> &coordinates) const;
        player get_winner() const;
        player get_winning_move() const;

        template <int N>
        int count_in_arr(const array<coords, N> &coordinates, const player& target_player) const;

        int evaluate_arr(const array<coords, 4> &coordinates, const player& current_player) const;
        int evaluate_position(const player& current_player) const;
        int choose_column() const;
        friend pair<int> minimax(const board &b, int depth, int alpha, int beta, bool maximizing_player);
};


#endif
