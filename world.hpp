/**
 * @file   world.hpp
 * @author Gleb Semenov <gleb.semenov@gmail.com>
 * @date   Thu May  9 21:57:18 2019
 * 
 * @brief  The World class declaration
 * 
 * 
 */

#include <random>

#ifndef __WORLD_HPP__
#define __WORLD_HPP__

/*! World of cells */
template <typename Cell> class World {
    int m_rows;                 /**< World's height */
    int m_cols;                 /**< World's width */

    typedef std::vector<std::vector<Cell>> board_t;
    
    board_t m_curr, *p_curr;    /**< Current generation */
    board_t m_next, *p_next;    /**< Next generation  */

    /*
      Cells' neighbourhood:
      nnn
      nCn
      nnn
    */
    static constexpr int m_neighboursCount = 8; /**< Cell's neighbourhood size */
    Cell m_neighbours[m_neighboursCount];       /**< Cell's neighbourhood */
    
    RuleInterface<Cell> *m_rules; /**< Ptr to rules */
    
    // our world is toroid

    inline int wrap_row(int row) {
        if(row < 0) return m_rows - 1;
        else if(row == m_rows) return 0;
        else return row;
    }
    
    inline int wrap_col(int col) {
        if(col < 0) return m_cols - 1;
        else if(col == m_cols) return 0;
        else return col;
    }
    
    void neighbourhood(int row, int col) {
        int i = 0;
        for(int r = row - 1;  r <= row + 1; r++)
            for(int c = col - 1;  c <= col + 1; c++) {
                if(r == row && c == col) continue;
                if(i >= m_neighboursCount)
                    throw std::logic_error("Incorrect neighbourhood size detected!");
                m_neighbours[i++] = (*p_curr)[wrap_row(r)][wrap_col(c)];
            }
    }
    
public:

    explicit World(int r, int c, RuleInterface<Cell> *rules):
        m_rows(r), m_cols(c), m_rules(rules)
    {
        Cell cl;
        cl = m_rules->kill(cl);
        for(int r = 0; r < m_rows; r++) {
            std::vector<Cell> vc, vn;
            for(int c = 0; c < m_cols; c++) {
                vc.push_back(cl);
                vn.push_back(cl);
            }
            m_curr.push_back(vc);
            m_next.push_back(vn);
        }
        p_curr = &m_curr;
        p_next = &m_next;
    }
    
    ~World() {
    };

    // just for future
    std::vector<Cell>& operator [] (int row) const {
        return (*p_curr)[row];
    }

    /** 
     * evaluate next generation and swap pointers. 
     * 
     */
    void nextGeneration() {
        for(int r = 0; r < m_rows; r++) {
            for(int c = 0; c < m_cols; c++) {
                neighbourhood(r, c);
                (*p_next)[r][c] = m_rules->next((*p_curr)[r][c], m_neighbours, m_neighboursCount);
                m_rules->draw(r, c, (*p_next)[r][c]);
            }
            refresh();
        }
        // swap Generations
        std::swap(p_curr, p_next);
    }

    /** 
     * Create random first generation
     * 
     */
    void fillRandom() {
        std::random_device rd;
        constexpr unsigned int false_limit =  std::numeric_limits<unsigned int>::max() / 3;
        for(int r = 0; r < m_rows; r++) {
            for(int c = 0; c < m_cols; c++) {
                (*p_curr)[r][c] = rd() < false_limit
                                         ? m_rules->kill((*p_curr)[r][c])
                                         : m_rules->born((*p_curr)[r][c]);
                 m_rules->draw(r, c, (*p_curr)[r][c]);
            }
        }
        refresh();
    }
};

#endif // #ifndef __WORLD_HPP__










