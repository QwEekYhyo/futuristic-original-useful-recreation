#ifndef GAME_BOARD_HPP
#define GAME_BOARD_HPP

#include <array>
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

        player& at(int *coordinates);
        const player& at(const int *coordinates) const;
        void start_game();
        friend std::ostream& operator<<(std::ostream& os, const board& b);

    private:
        std::array<std::array<player, width>, height> m_grid;
        player m_current_player;
        int m_last_position_played[2];

        void switch_player();
        bool is_column_full(int column) const;
        int get_upper(int column) const;
        bool is_full() const;
        void play(int column);
        player get_winner_from_arr(const std::array<int*, 4> &coordinates) const;
        player get_winner() const;
};

#endif
