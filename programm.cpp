#include "programm.h"
#include <QDebug>

Program::Program() : Conf(), dayT("Unknown"), timeT("Unknown") {
    qDebug() << "Конструктор Program";
}

Program::~Program() {
    qDebug() << "Деструктор Program " << nameT;
}

QString Program::toString() const {
    int i;
    QString str = QString("%1 | %2 | %3 | %4")
    .arg(getType())
        .arg(nameT, 35)
        .arg(dayT, 32)
        .arg(timeT, 30);
    return str;
}

QString Program::get_day() const { return dayT; }
QString Program::get_time() const { return timeT; }

void Program::set_day(const QString& day) { dayT = day; }
void Program::set_time(const QString& time) { timeT = time; }
