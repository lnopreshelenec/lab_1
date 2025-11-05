#include "programm.h"
#include <QDebug>

Program::Program() : Conf(), dayT("Unknown"), timeT("Unknown") {
    qDebug() << "Конструктор Program";
}

Program::~Program() {
    qDebug() << "Деструктор Program " << nameT;
}

// void Program::display() const {
//     qDebug() << "Program:" << nameT;
//     qDebug() << "  Day:" << dayT;
//     qDebug() << "  Time:" << timeT;
// }
QString Program::toString() const {
    int i;
    QString str = QString("%1 | %2 | %3 | %4")
    .arg(getType())                      // %4d - номер шириной 4 символа
        .arg(nameT, 35)                    // %-25s - название шириной 25
        .arg(dayT, 32)                     // %-12s - день шириной 12
        .arg(timeT, 30);                    // %-8s - время шириной 8

    // qDebug() << str;
    return str;
}

QString Program::get_day() const { return dayT; }
QString Program::get_time() const { return timeT; }

void Program::set_day(const QString& day) { dayT = day; }
void Program::set_time(const QString& time) { timeT = time; }
