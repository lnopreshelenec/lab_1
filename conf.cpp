#include "conf.h"
#include <QDebug>



Conf::Conf() /*: nameT("Unknown")*/ {
    qDebug() << "Конструктор Conf" << nameT;
}
Conf::~Conf() {
    qDebug() << "Деструктор Conf" << nameT;
}

QString Conf::get_name() const {
    return nameT;
}

void Conf::set_name(const QString& name) {
    nameT = name;
}
