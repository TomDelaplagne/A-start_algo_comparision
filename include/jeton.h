#pragma once

#include <iostream>
using namespace std;

class jeton {
private:
    int x, y;
    int value;
public:
    jeton(int x, int y, int value) : x(x), y(y), value(value) {};
    jeton(const jeton& j) {
        this->x = j.x;
        this->y = j.y;
        this->value = j.value;
    }
    void set_coords(int x, int y) {
        this->x = x;
        this->y = y;
    }
    pair<int, int> get_coods() const{
        pair<int, int> coords(this->x, this->y);
        return coords;
    }
    int get_value() const {return this->value;}
    bool operator<(const jeton& j2) const{
        return this->value < j2.get_value();
    }
    bool operator==(const jeton& j2) const{
        return this->value == j2.get_value();
    }
    bool operator!=(const jeton& j2) const{
        return this->value != j2.get_value();
    }
    ~jeton() {}
};

ostream& operator<< (ostream& stream, const jeton& j) {
    stream << "[" << j.get_value() << "]";
    return stream;
}