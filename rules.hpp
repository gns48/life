/**
 * @file   rules.hpp
 * @author Gleb Semenov <gleb.semenov@gmail.com>
 * @date   Fri May 10 23:26:23 2019
 * 
 * @brief  Rules of life definition, requires c++17
 * 
 * 
 */

#include <vector>
#include <stdexcept>
#include <type_traits>

#ifndef __RULES_HPP__
#define __RULES_HPP__

/*! Generic rule interface, abstract class */
template <typename Cell> class RuleInterface {
public:
    //! dummy virtual desstructor
    virtual ~RuleInterface() {};
    /** 
     * draw a cell 
     * @param raw  raw
     * @param col  column
     * @param Cell cell item
     */
    virtual void draw(int raw, int col, Cell) = 0;
    /** 
     * kill cell item
     * @param Cell 
     * @return Cell item in the 'killed' state
     */
    virtual Cell kill(Cell) = 0;
    virtual Cell kill() = 0;
     /** 
     * born cell item
     * @param Cell 
     * @return Cell item in the 'live' state
     */
    virtual Cell born(Cell) = 0;
    /** 
     * Cell alive predicate
     * @param Cell 
     * @return true if the cell is alive
     */
    virtual bool is_alive(Cell) = 0;
    /** 
     * evaluate cell's neighborhood and return Cell in proper state
     * 
     * @param Cell - current Cell
     * @param neighboors - array with cell's neighbours
     * @param nsize - neighboors count
     * @return Cell alive or not 
     */
    virtual Cell next(Cell, const Cell* neighboors, int nsize) = 0;
};

inline const char* justBool("Just bool elementary type implemented");

/*! Classic Conway's rules with boolean type for cell unit */
template <typename Cell> class ConwayRule: public RuleInterface<Cell>
{
public:
    ConwayRule(): RuleInterface<Cell>() { };
    virtual ~ConwayRule() { };
    
    virtual void draw(int raw, int col, Cell c) {
        // C++17 feature, we do not need partial template specification,
        // SFINAE out-of-the-box
        if constexpr (std::is_same_v<Cell, bool>)
            mvaddch(raw, col, c ? '*' : '\x20');     
        else throw std::logic_error(justBool); 
    }
    
    virtual Cell kill(Cell c) {
        if constexpr (std::is_same_v<Cell, bool>)
            c = false;
        else throw std::logic_error(justBool);           
        return c;   
    }
    virtual Cell kill() {
        if constexpr (std::is_same_v<Cell, bool>)
           return false;
	else throw std::logic_error(justBool);
    }

    virtual Cell born(Cell c) {
        if constexpr (std::is_same_v<Cell, bool>)
           return true;
        else throw std::logic_error(justBool);           
    }
    
    virtual bool is_alive(Cell c) {
        if constexpr (std::is_same_v<Cell, bool>)
           return c;
        else throw std::logic_error(justBool);        
    }
    
    virtual Cell next(Cell c, const Cell* neibours, int size) {
        int count = 0;
        for(int i = 0; i < size; i++) 
            if(is_alive(neibours[i])) count++;
        if(is_alive(c)) {
            if(count < 2 || count > 3) c = kill(c);
        }
        else if(count == 3) c = born(c);
        return c;
    }    
};

#endif // #ifndef __RULES_HPP__

