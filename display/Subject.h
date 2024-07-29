#ifndef SUBJECT_H
#define SUBJECT_H

#include <vector>
#include <memory>

#include "../entities/Tile.h"
class Observer;

using namespace std;
class Subject {
    vector<std::shared_ptr<Observer>> observers;
public:
    void attach(std::shared_ptr<Observer> o);
    void detach(std::shared_ptr<Observer> o);
    void notifyObservers();
    virtual std::shared_ptr<Tile> getTile(int row, int col) const = 0;
    virtual ~Subject() = default;
};

#endif
