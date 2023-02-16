#include <vector>
#include <list>
#include <set>
#include <map>
#include <string>
#include "state.h"
#include "affiche.h"

#include <iostream>

using namespace std;
 

int manathan_distance(const map<int, state> states, state s) {
    int distance = 0;
    // for (map<int, state>::const_iterator it = states.begin(); it != states.end(); it++) {
    //     distance += it->second.manathan_distance(s);
    // }
    return distance;
}

int main() {
    // A* algorithm for 3x3 'taquin' game

    // 1. create "randomly" the first state
    map<int, jeton> jetons;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            int value = j*3 + i;
            int coords = j + i*3;
            jeton s(i, j, value);
            jetons.insert(pair<int, jeton>(coords, s));
        }
    }
    state s_init(jetons);
    cout << "initial state:" << endl;
    cout << s_init;
    cout << s_init.hash() << endl;

    // 2. create the goal state
    map<int, jeton> jetons_goal;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            int coords = j + 3*i, value = coords + 1;
            if (value < 9) {
                jeton s(i, j, value);
                jetons_goal.insert(pair<int, jeton>(coords, s));
            } else {
                jeton s(i, j, 0);
                jetons_goal.insert(pair<int, jeton>(coords, s));
            }
        }
    }

    state s_goal(jetons_goal, 0);
    cout << "goal state:" << endl;
    cout << s_goal;
    cout << s_goal.hash() << endl;

    // 3. create a vector of all possible states (for heuristic calculation)
    set<state> states;
    state s_init_copy(s_init);
    states.insert(s_goal);
    while (states.size() <= 362880) {
        set<state>::iterator end = states.end();
        for (set<state>::iterator it = states.begin(); it != end; it++) {
            for (int i = -1; i <= 1; i++) {
                for (int j = -1; j <= 1; j++) {
                    try {
                        state next_state = it->get_next_state(i, j);
                        next_state.set_heuristic_value(it->get_heuristic_value()+1);
                        states.insert(next_state);
                        if (next_state == s_init_copy) {
                            cout << "goal state found" << endl;
                            s_init_copy = next_state;
                            goto end;
                        }
                    } catch (const char* msg) {
                        // cout << msg << endl;
                    }
                }
            }
        }
        cout << "number of states explored: " << states.size() << endl;
    }
    end:
    cout << "number of states explored: " << states.size() << endl;

    cout << "goal state:" << endl;
    cout << s_init_copy;
    // affiche(states);
    cout << "goal state parent:" << endl;
    cout << states;

    // for (int k = 0; k < states.size(); k++) {
    //     state s = states.find(k)->second;
    //     for (int i = -1; i <= 1; i++) {
    //         for (int j = -1; j <= 1; j++) {
    //             try {
    //                 state next_state = s.get_next_state(i, j);
    //                 next_state.set_heuristic_value(s.get_heuristic_value()+1);
    //                 states.insert(pair<int, state>(states.size()+1,next_state));
    //                 if (next_state == s_init_copy) {
    //                     cout << "goal state found" << endl;
    //                     s_init_copy = next_state;
    //                     goto end;
    //                 }
    //             } catch (const char* msg) {
    //                 // cout << msg << endl;
    //             }
    //         }
    //     }
    //     if (states.size() > 362880)
    //         break;
    // }


    // end:
    // cout << "number of states explored: " << states.size() << endl;

    // cout << "goal state:" << endl;
    // cout << s_init_copy;
    // affiche_map(states);
    // cout << "goal state parent:" << endl;
    // cout << s_init_copy.get_historic();


    // 4. calculate the heuristic for each state (manathan distance)
    // for (int k = 0; k < states.size(); k++) {
    //     state s = states.find(k)->second;
    //     s.set_heuristic_value(manathan_distance(states, s));
    // }

    // 5. using A* algorithm to find the shortest path

    // set<state> open_set;
    // open_set.insert(s_init);
    // set<state> closed_set;

    // while (!open_set.empty()) {
    //     // find the state with the lowest f_score
    //     state current = *open_set.begin();
    //     for (set<state>::iterator it = open_set.begin(); it != open_set.end(); it++) {
    //         if (it->get_f_score() < current.get_f_score()) {
    //             current = *it;
    //         }
    //     }

    //     if (current == s_goal) {
    //         cout << "goal reached" << endl;
    //         break;
    //     }
    // }






    // set<jeton> jetons_goal;
    // for (int i = 0; i < 3; i++) {
    //     for (int j = 1; j <= 3; j++) {
    //         int value = j + 3*i;
    //         if (value < 9) {
    //             jeton s(i, j, value);
    //             jetons_goal.insert(s);
    //         }
    //     }
    // }
    // affiche(jetons_goal);

    // int NB_OF_STATES = 1;

    // // 2. Create a vector of all possible states (for heuristic calculation)
    // vector<state> states;
    // for (unsigned int i=0; i<NB_OF_STATES ; i++) {
    //     // Create a map of jetons for each state
    //     map<int, jeton> jetons;
    //     jetons.reserve(9);
    //     for (int i = 0; i < 3; i++) {
    //         for (int j = 1; j <= 3; j++) {
    //             int value = j + 3*i;
    //             if (value < 9) {
    //                 jeton s(i, j, value);
    //                 jetons.push_back(s);
    //             } else {
    //                 jeton s(i, j, 0);
    //                 jetons.push_back(s);
    //             }
    //         }
    //     }
    //     // Create a state with the map of jetons
    //     state s(jetons);
    //     states.push_back(s);
    //     cout << s;
    // }

    return 0;
}
