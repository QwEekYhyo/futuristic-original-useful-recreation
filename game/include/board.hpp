#ifndef GAME_BOARD_HPP
#define GAME_BOARD_HPP

#include <array.hpp>
#include <iostream>

enum class player {
    one, 
    two, 
    none,
};

class board {
    public:
        board();
        static constexpr int width = 7;
        static constexpr int height = 6;

        player& at(array<int, 2> coordinates);
        const player& at(const array<int, 2> &coordinates) const;
        void start_game();
        friend std::ostream& operator<<(std::ostream& os, const board& b);

    private:
        array<array<player, width>, height> m_grid;
        player m_current_player;
        array<int, 2> m_last_position_played;

        void switch_player();
        bool is_column_full(int column) const;
        int get_upper(int column) const;
        bool is_full() const;
        void play(int column);
        player get_winner_from_arr(const array<array<int, 2>, 4> &coordinates) const;
        player get_winner() const;
};

#endif
