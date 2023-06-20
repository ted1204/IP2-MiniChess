#pragma once
#include "../state/state.hpp"
#include <vector>


/**
 * @brief Policy class for random policy, 
 * your policy class should have get_move method
 */

class Submission{
public:
  static Move get_move(State *state, int depth);
  static int DFS_value(State *state, int depth, int alpha, int beta, bool maximize);
};