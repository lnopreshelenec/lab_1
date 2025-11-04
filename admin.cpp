#include "admin.h"
#include <QDebug>

Admin::Admin() : Conf(), positionT("Unknown"),
    responsibilityT("No responsibility") {
    qDebug() << "Конструктор Admin ";
}

Admin::~Admin() {
    qDebug() << " Деструктор Admin" << nameT;
}

void Admin::display() const {
    qDebug() << "Admin:" << nameT;
    qDebug() << "  Position:" << positionT;
    qDebug() << "  Responsibility:" << responsibilityT;
}



QString Admin::get_position() const { return positionT; }
QString Admin::get_responsibility() const { return responsibilityT; }

void Admin::set_position(const QString& position) {
    positionT = position;
}
void Admin::set_responsibility(const QString& responsibility) {
    responsibilityT = responsibility;
}
