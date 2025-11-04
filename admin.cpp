#include "admin.h"
#include <QDebug>

Admin::Admin() : Conf(), positionT("Unknown"),
    responsibilityT("No responsibility") {
    qDebug() << "Конструктор Admin ";
}

Admin::~Admin() {
    qDebug() << " Деструктор Admin" << nameT;
}

// void Admin::display() const {
//     qDebug() << "Admin:" << nameT;
//     qDebug() << "  Position:" << positionT;
//     qDebug() << "  Responsibility:" << responsibilityT;
// }

QString Admin::toString() const {
    int i;
    QString str = QString("%1 | %2 | %3 | %4")
    .arg(i++, 4)                      // %4d - номер шириной 4 символа
        .arg(nameT, -20)                    // %-20s - имя шириной 20
        .arg(positionT, -15)                // %-15s - должность шириной 15
        .arg(responsibilityT, -25);         // %-25s - ответственность шириной 25

    qDebug() << str;
}

QString Admin::get_position() const { return positionT; }
QString Admin::get_responsibility() const { return responsibilityT; }

void Admin::set_position(const QString& position) {
    positionT = position;
}
void Admin::set_responsibility(const QString& responsibility) {
    responsibilityT = responsibility;
}
