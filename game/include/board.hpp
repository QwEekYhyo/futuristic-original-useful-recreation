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

        void play(int column);
        friend std::ostream& operator<<(std::ostream& os, const board& b);

    private:
        std::array<std::array<player, width>, height> m_grid;
        player m_current_player;

        void switch_player();
        bool is_column_full(int column);
        int get_upper(int column);
};

#endif
