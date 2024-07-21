#ifndef SUBJECT_H
#define SUBJECT_H

#include <vector>
#include "Tile.h"
class Observer;

using namespace std;
class Subject {
    vector<Observer*> observers;
public:
    void attach(Observer* o);
    void detach(Observer* o);
    void notifyObservers();
    virtual Tile* getTile(int row, int col) const = 0;
    virtual ~Subject() = default;
};

#endif