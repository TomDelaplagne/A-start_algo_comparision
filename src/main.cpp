#include <vector>
#include <list>
#include <set>
#include <map>
#include <string>
#include "state.h"
#include "affiche.h"

#include <iostream>

using namespace std;
 


int main() {
    // algorythm for solving the 8-puzzle problem 'taquin' with A* search

    // 1. create "randomly" the first state
    map<int, jeton> jetons;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            int coords = j + 3*i, value = coords + 1;
            if (value < 9) {
                jeton s(i, j, value);
                jetons.insert(pair<int, jeton>(coords, s));
            } else {
                jeton s(i, j, 0);
                jetons.insert(pair<int, jeton>(coords, s));
            }
        }
    }

    // for (int i = 0; i < 3; i++) {
    //     for (int j = 0; j < 3; j++) {
    //         int coords = j + 3*i, value = j*3 + i;
    //         jeton s(i, j, value);
    //         jetons.insert(pair<int, jeton>(coords, s));
    //     }
    // }

    state s_init(jetons);
    cout << "initial state:" << endl;
    cout << s_init;

    // 2. create the goal state
    map<int, jeton> jetons_goal;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            int coords = j + 3*i, value = coords;
            jeton s(i, j, value);
            jetons_goal.insert(pair<int, jeton>(coords, s));
        }
    }

    state s_goal(jetons_goal);
    cout << "goal state:" << endl;
    cout << s_goal;
    cout << s_goal.hash() << endl;

    // set<state> states;
    // state s_init_copy(s_init);
    // states.insert(s_goal);
    // while (states.size() <= 362880) {
    //     set<state>::iterator end = states.end();
    //     for (set<state>::iterator it = states.begin(); it != end; it++) {
    //         for (int i = -1; i <= 1; i++) {
    //             for (int j = -1; j <= 1; j++) {
    //                 try {
    //                     state next_state = it->get_next_state(i, j);
    //                     next_state.set_heuristic_value(it->get_heuristic_value()+1);
    //                     states.insert(next_state);
    //                     if (next_state == s_init_copy) {
    //                         cout << "goal state found" << endl;
    //                         s_init_copy = next_state;
    //                         goto end;
    //                     }
    //                 } catch (const char* msg) {
    //                     // cout << msg << endl;
    //                 }
    //             }
    //         }
    //     }
    //     cout << "number of states explored: " << states.size() << endl;
    // }
    // end:
    // cout << "number of states explored: " << states.size() << endl;

    // cout << "goal state:" << endl;
    // cout << s_init_copy;
    // affiche(states);
    // cout << "goal state parent:" << endl;
    // cout << states;
    
    // 3. create the list of states to expand
    set<int> expanded;

    // 4. create the list of states not expanded yet
    multiset<state> not_expanded_yet;

    // 5. expand the first state
    state current(s_init);
    state next_state;

    while (current != s_goal) {
        // expand current node
        for (int i = -1; i <= 1; i++) {
            for (int j = -1; j <= 1; j++) {
                // find the next state
                try {
                    next_state = current.get_next_state(i, j);

                    // see if the node has allready been expanded
                    if (expanded.find(next_state.hash()) == expanded.end()) {
                        next_state.set_f_value();
                        not_expanded_yet.insert(next_state);
                    }
                } catch (const char* msg) {
                    // cout << msg << endl;
                }
            }
        }
        // after expanding the node, add it to the list of expanded nodes
        expanded.insert(current.hash());

        // cout << "current f value: " << current.set_f_value() << endl;

        // find the next node to expand it's the one with the lowest f value
        current = *(not_expanded_yet.begin());
        not_expanded_yet.erase(not_expanded_yet.begin());

        if (!not_expanded_yet.size()) {
            throw "no solution found";
        }
    }
    current.get_historic().push_back(current.hash());

    // 6. print the result
    cout << "goal state found" << endl;
    cout << current;
    cout << "number of states explored: " << expanded.size() << endl;
    cout << "number of moves to reach the goal state: " << current.get_historic().size() - 1 << endl;
    cout << "historic of the goal state:" << endl;
    cout << current.get_historic();
    cout << current;
    return 0;
}
