/**
 * @file   life.hpp
 * @author Gleb Semenov <gleb.semenov@gmail.com>
 * @date   Sat May 11 00:18:41 2019
 * 
 * @brief  The game of life, top-level header file
 * 
 * 
 */


#ifndef __LIFE_HPP__
#define __LIFE_HPP__

// current elementary cell type
typedef bool cell_unit_t;

#include <ncurses.h>
#include <utility>
#include <iostream>
#include "rules.hpp"
#include "world.hpp"

#endif // #ifndef __LIFE_HPP__
