#ifndef SUBJECT_H
#define SUBJECT_H

#include <vector>
#include <memory>

#include "../entities/Tile.h"
class Observer;

using namespace std;
class Subject {
    vector<Observer*> observers;
public:
    void attach(Observer* o);
    void detach(Observer* o);
    void notifyObservers();
    virtual ~Subject() = default;
};

#endif
