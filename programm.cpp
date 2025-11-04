#include "programm.h"
#include <QDebug>

Program::Program() : Conf(), dayT("Unknown"), timeT("Unknown") {
    qDebug() << "Конструктор Program";
}

Program::~Program() {
    qDebug() << "Деструктор Program " << nameT;
}

void Program::display() const {
    qDebug() << "Program:" << nameT;
    qDebug() << "  Day:" << dayT;
    qDebug() << "  Time:" << timeT;
}


QString Program::get_day() const { return dayT; }
QString Program::get_time() const { return timeT; }

void Program::set_day(const QString& day) { dayT = day; }
void Program::set_time(const QString& time) { timeT = time; }
