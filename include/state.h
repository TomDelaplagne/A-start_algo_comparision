#pragma once
#include <iostream>
#include <map>
#include <cmath>
#include <set>
#include <list>
#include "jeton.h"

using namespace std;

class state {
private:
    map<int, jeton> jetons;
    list<int> historic;
public:
    state(void) {
        this->jetons = map<int, jeton>();
        this->historic = list<int>();
    }
    state(map<int, jeton> jetons) {
        this->jetons = jetons;
        this->historic = list<int>();
    };
    // constructor with map and historic
    state(map<int, jeton> jetons, list<int> historic) {
        this->jetons = jetons;
        this->historic = historic;
    };
    // constructor for recopie
    state(const state& s) {
        this->jetons = s.jetons;
        this->historic = s.historic;
    };
    int get_heuristic() const {
        int sum = 0;
        for (int k = 0; k < 9; k++) {
            // get the coords of the jeton
            pair<int, int> coords = this->jetons.find(k)->second.get_coods();
            int x = coords.first;
            int y = coords.second;

            // get the coords goal of the jeton
            int value = this->jetons.find(k)->second.get_value();
            int y_goal = value % 3;
            int x_goal = value / 3;

            // calculate the distance
            sum += abs(x - x_goal) + abs(y - y_goal);
        }

        return sum;
    }
    inline jeton operator[](int i) const {
        return this->jetons.find(i)->second;
    }
    inline map<int, jeton> get_jetons() const {
        return this->jetons;
    }
    state get_next_state(int i, int j) const {
        if (abs(i) == 1 && abs(j) == 1) {
            throw "You can't moove in diagonals.";
        } else if (!i && !j) {
            throw "You didn't moove at all";
        }
        for (int k = 0; k < 9; k++) {
            if (this->jetons.find(k)->second.get_value() == 0) {
                // get the coords of the empty jeton
                pair<int, int> coords = this->jetons.find(k)->second.get_coods();
                int x = coords.first;
                int y = coords.second;
                // create a new state with the jeton moved
                map<int, jeton> new_jetons = this->jetons;
                if ((x + i) > 2 || (x + i) < 0 || (y + j) > 2 || (y + j) < 0) {
                    throw "You can't moove out of the map";
                }
                int new_coords = (x + i)*3 + (y + j);
                // switch the jetons
                jeton tmp = new_jetons.find(new_coords)->second;
                tmp.set_coords(x, y);
                new_jetons.find(new_coords)->second = new_jetons.find(k)->second;
                new_jetons.find(new_coords)->second.set_coords(x + i, y + j);
                new_jetons.find(k)->second = tmp;

                state next_state(new_jetons, this->historic);

                next_state.historic.push_back(this->hash());

                return next_state;
            }
        }
        throw "No empty jeton found";
    }
    inline list<int> get_historic() const {
        return this->historic;
    }
    inline bool operator==(const state& s2) const{
        return this->hash() == s2.hash();
    }
    inline bool operator!=(const state& s2) const {
        return !(*this == s2);
    }
    inline bool operator<(const state& s2) const {
        return this->hash() < s2.hash();
    }
    inline int get_f_value() const {
        return this->get_heuristic() + this->historic.size();
    }
    int hash() const {
        int hash = 0;
        for (int i = 0; i < 9; i++) {
            hash += this->jetons.find(i)->second.get_value() * pow(10, i);
        }
        return hash;
    }
};

ostream& operator<< (ostream& stream, const state& s){
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            stream << s[j + i*3] << " ";
        }
        stream << endl;
    }
    return stream;
}

ostream& operator<< (ostream& stream, list<int> l) {
    for (list<int>::iterator it = l.begin(); it != l.end(); it++) {
        stream << *it << endl;
    }
    return stream;
}