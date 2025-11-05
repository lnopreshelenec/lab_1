#include "admin.h"
#include <QDebug>

Admin::Admin() : Conf(), positionT("Unknown"),
    responsibilityT("No responsibility") {
    qDebug() << "Конструктор Admin ";
}

Admin::~Admin() {
    qDebug() << " Деструктор Admin" << nameT;
}


QString Admin::toString() const {
    // int i;
    QString str = QString("%1 | %2 | %3 | %4")
    .arg(getType())
        .arg(nameT, 40)
        .arg(positionT, 45)
        .arg(responsibilityT, 35);
    return str;
}

QString Admin::get_position() const { return positionT; }
QString Admin::get_responsibility() const { return responsibilityT; }

void Admin::set_position(const QString& position) {
    positionT = position;
}
void Admin::set_responsibility(const QString& responsibility) {
    responsibilityT = responsibility;
}
