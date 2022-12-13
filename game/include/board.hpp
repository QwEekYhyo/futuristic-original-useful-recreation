#ifndef GAME_BOARD_HPP
#define GAME_BOARD_HPP

#include <array>
#include <iostream>
#include <utility>

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
        player& at(std::pair<int, int> coordinates);
        const player& at(std::pair<int, int> coordinates) const;
        friend std::ostream& operator<<(std::ostream& os, const board& b);

    private:
        std::array<std::array<player, width>, height> m_grid;
        player m_current_player;
        std::pair<int, int> m_last_position_played;

        void switch_player();
        bool is_column_full(int column) const;
        int get_upper(int column) const;
        bool is_full() const;
        player get_winner_from_arr(const std::array<std::pair<int, int>, 4> &coordinates) const;
};

#endif
