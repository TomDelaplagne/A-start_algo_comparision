#pragma once

#include <vector>
#include <list>
#include <set>
#include <map>
#include <iostream>

using namespace std;

template <class T>
void affiche(vector<T>& vect) {
    cout << "Size = " << vect.size() << ", values = (";
    for (typename vector<T>::iterator p=vect.begin(); p!=vect.end(); p++) {
        cout << *p ;
        if (p != vect.end()-1)
            cout << ", ";
    }
    cout << "), ";
    cout << "Capacity = " << vect.capacity() << endl;
}

template <class T>
void affiche(list<T> L) {
    cout << "Size = " << L.size() << "(";
    typename list<T>::iterator p;
    for (p=L.begin(); p!=L.end(); p++) {
        cout << *p ;
        if (p != --L.end())
            cout << ",";
        else
            cout << ")" << endl;
    }
}

template <class T>
void affiche(set<T> S) {
    cout << "Size = " << S.size() << "(";
    typename set<T>::iterator p;
    for (p=S.begin(); p!=S.end(); p++) {
        cout << *p ;
        if (p != --S.end())
            cout << ",";
        else
            cout << ")" << endl;
    }
};


template <class T, class U>
void affiche_set(set<T, U> M) {
    cout << "Size = " << M.size() << "(";
    typename set<T, U>::iterator p;
    for (p=M.begin(); p!=M.end(); p++) {
        cout << *p ;
        if (p != --M.end())
            cout << ",";
        else
            cout << ")" << endl;
    }
};

template <class T, class U>
void affiche_map(map<T, U> M) {
    cout << "Size = " << M.size() << "(";
    typename map<T, U>::iterator p;
    for (p=M.begin(); p!=M.end(); p++) {
        cout << p->first << "=>" << p->second ;
        if (p != --M.end())
            cout << ",";
        else
            cout << ")" << endl;
    }
};