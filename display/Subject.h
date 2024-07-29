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
    virtual std::shared_ptr<Tile> getTile(int row, int col) const = 0;
    virtual ~Subject() = default;
};

#endif
