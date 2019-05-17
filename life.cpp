/**
 * @file   life.cpp
 * @author Gleb Semenov <gleb.semenov@gmail.com>
 * @date   Thu May  9 20:21:01 2019
 * 
 * @brief  The game of life
 * 
 * 
 */

#include "life.hpp"

std::pair<int, int> ncursesInit() {
    std::pair<int, int> rowcol;
    initscr();
    noecho();
    clear();
    refresh();
    getmaxyx(stdscr, rowcol.first, rowcol.second);
    return rowcol;
}

int main(int ac, char **av) {
    RuleInterface<cell_unit_t> *rules = new ConwayRule<cell_unit_t>;
    
    auto [row, col] = ncursesInit();
    
    try {
        World<cell_unit_t> W(row, col, rules);
        W.fillRandom();
        while(1) {
            getch();
            W.nextGeneration();            
        }
    }
    catch(std::exception &e) {
        endwin();
        std::cerr << e.what() << std::endl;
        delete rules;
        return 1;
    }
    endwin();
    delete rules;
    return 0;
}



