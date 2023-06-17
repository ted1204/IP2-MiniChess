#include <cstdlib>
#include <iostream>

#include "../state/state.hpp"
#include "./minimax.hpp"
#include <map>


/**
 * @brief use minimax algorithm
 * 
 * @param state Now state
 * @param depth You may need this for other policy
 * @return Move 
 */


Move Minimax::get_move(State *state, int depth){

  if(!state->legal_actions.size())
    state->get_legal_actions();
  auto actions = state->legal_actions;
  std::map<int, Move> next_move;
  State *next;
  int maxVal = -2e9;
  for (auto &i : actions) {
    next = state->next_state(i);
    next_move.insert({-1 * DFS_value(next, depth - 1), i});
    maxVal = std::max(maxVal, -1 * DFS_value(next, depth-1));
  }
  return next_move[maxVal];
  /*
  return actions[(rand()+depth)%actions.size()];
  */
}

int Minimax::DFS_value(State *state, int depth)
{ 
  if(!state->legal_actions.size())
    state->get_legal_actions();

  auto actions = state->legal_actions;  
  if (depth == 0 || actions.empty()) {
    return state->evaluate();
  }
  int retVal;
  State *next;
    retVal = -2e9;
    for (auto &i : actions) {
        next = state->next_state(i);
        retVal = std::max(retVal, -1 * DFS_value(next, depth - 1));
    }
    return retVal;
}