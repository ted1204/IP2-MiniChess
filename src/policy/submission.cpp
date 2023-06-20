#include <cstdlib>
#include <iostream>

#include "../state/state.hpp"
#include "./submission.hpp"
#include <map>


/**
 * @brief use minimax algorithm
 * 
 * @param state Now state
 * @param depth You may need this for other policy
 * @return Move 
 */


Move Submission::get_move(State *state, int depth){

  if(!state->legal_actions.size())
    state->get_legal_actions();
  auto actions = state->legal_actions;
  std::map<int, Move> next_move;
  State *next;
  int maxVal = -2e9;
  int curVal;
  for (auto &i : actions) {
    next = state->next_state(i);
    curVal = -1 * DFS_value(next, depth - 1, -2e9, 2e9, false);
    next_move.insert({curVal, i});
    maxVal = std::max(maxVal, curVal);
  }
  return next_move[maxVal];
  /*
  return actions[(rand()+depth)%actions.size()];
  */
}

int Submission::DFS_value(State *state, int depth, int alpha, int beta, bool maximize)
{ 
  if(!state->legal_actions.size())
    state->get_legal_actions();

  auto actions = state->legal_actions;  
  if (depth <= 0 || actions.empty()) {
    return state->evaluate();
  }
  State *next;
  int curVal;
  if (maximize) {
    int retVal = -2e9;
      for (auto &i : actions) {
        next = state->next_state(i);
       curVal = -1 * DFS_value(next, depth - 1, alpha, beta, false);
       retVal = std::max(retVal, curVal);
        alpha = std::max(alpha, retVal);
        if (alpha >= beta) break;
      }
      return retVal;
  } else {
    int retVal = -2e9;
    for (auto &i : actions) {
      next = state->next_state(i);
      curVal = -1 * DFS_value(next, depth - 1, alpha, beta, true);
      retVal = std::max(retVal, curVal);
      beta = std::min(beta, -retVal);
      if (beta <= alpha) break;
    }
    return retVal;
  }
}