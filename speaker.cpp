#include "speaker.h"
#include <QDebug>

void Speaker::set_vuz(const QString& vuz) {
    organization = vuz;
}

void Speaker::set_report(const QString& report) {
    reportT = report;
}



QString Speaker::get_vuz() const {
    return organization;
}

QString Speaker::get_report() const {
    return reportT;
}
void Speaker::set_annotacion(const QString& annotacion) {
    annotationT = annotacion;
}

QString Speaker::get_annotacion() const {
    return annotationT;
}

void Speaker::display() const {
    qDebug() << "Выступающий" << "\n";
    qDebug() << "ФИО:  " << nameT << "\n";
    qDebug() << "Организация/ВУЗ: " << organization << "\n";
    qDebug() << "Доклад: " << reportT << "\n";
    qDebug() << "Аннотация доклада: " << annotationT << "\n";
    qDebug() << "===============" << "\n";
}

Speaker::Speaker(const QString& name, const QString& vuz, const QString& report, const QString& annotation)
    : organization(vuz),
      reportT(report),
      annotationT(annotation) {
    qDebug()  << "Создание Speaker" << name <<"\n" ;
    // set_name(name);
}
Speaker::~Speaker() {
    qDebug() << "Удаление выступающих: " << nameT << "\n";
}
