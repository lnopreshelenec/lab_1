#ifndef KEEPER_H
#define KEEPER_H

#include "conf.h"
#include "list.h"
#include <QString>
#include <QFile>
#include <QTextStream>
#include <QDebug>


// Класс для хранения и управления объектами конференции
class Keeper : List<Conf*>{
public:
    Keeper();
    ~Keeper();

    void add(Conf* item);
    void remove(int index);

    void displayAll();
    void save_file(const QString& filename) ;
    void load_file(const QString& filename);
    void clear();
    int getSize() const;
    Conf* get(int index) ;
    QString getAllFormatted() ;
private:
    // void clear();
    List<Conf*> data;
    Conf* createObjectFromString(const QString& line);
};

#endif

