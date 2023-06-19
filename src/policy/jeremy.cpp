#include <cstdlib>
#include <iostream>

#include "../state/state.hpp"
#include "./jeremy.hpp"

int minimax(State *state, int depth, bool myself);

/**
 * @brief Use Minimax to choose next move
 * 
 * @param state Now state
 * @param depth You may need this for other policy
 * @return Move 
 */
Move MinimaxJ::get_move(State *state, int depth){
    if(!state->legal_actions.size()) state->get_legal_actions();
    auto actions = state->legal_actions;
    int chosen=0;
    int minval = 100000000;
    int maxval = -100000000;
    bool flag = depth%2;
    for (unsigned long i = 0; i < actions.size(); i++){
        int tem = minimax(state->next_state(actions[i]),depth,flag);
        if (flag){
            if (maxval < tem){
                chosen = i;
                maxval = tem;
            }
        }
        else {
            if (minval>tem){
                chosen = i;
                minval=tem;
            } 
        }
    }
    return actions[chosen];
}

int minimax(State *state, int depth, bool myself){//myself if state is player take action
    if (!depth) return state->evaluate();
    if (!state->legal_actions.size()) state->get_legal_actions();
    auto actions = state->legal_actions;

    if (myself){
        int minval=100000000;    
        for (unsigned long i = 0; i < actions.size(); i++){
            int tem = minimax(state->next_state(actions[i]),depth-1,false);
            minval = std::min(minval,tem);
        }
        return minval;
    }
    else {
        int maxval=-100000000;
        for (unsigned long i = 0; i < actions.size(); i++){
            int tem = minimax(state->next_state(actions[i]),depth-1,true);
            maxval = std::max(maxval,tem);
        }
        return maxval;
    }
}