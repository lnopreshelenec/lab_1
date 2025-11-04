#ifndef KEEPER_H
#define KEEPER_H

#include "conf.h"
#include <QString>
#include <stdexcept>

// Класс для хранения и управления объектами конференции
class Keeper {
public:
    Keeper();
    ~Keeper();

    Keeper(const Keeper& other);

    void add(Conf* item);
    void remove(int index);
    void displayAll() const;
    void save_file(const QString& filename) const;
    void load_file(const QString& filename);
    // int getSize() const;
    Conf* get(int index) const;
private:
    void clear();
    
};

#endif
