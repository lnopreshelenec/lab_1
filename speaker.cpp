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

// void Speaker::display() const {
//     qDebug() << "Выступающий" << "\n";
//     qDebug() << "ФИО:  " << nameT << "\n";
//     qDebug() << "Организация/ВУЗ: " << organization << "\n";
//     qDebug() << "Доклад: " << reportT << "\n";
//     qDebug() << "Аннотация доклада: " << annotationT << "\n";
//     qDebug() << "===============" << "\n";
// }
QString Speaker::toString()  const {
    int i;
    i++;
    QString str = QString("%1 | %2 | %3 | %4 | %5")
    .arg(i, 3)                      // № шириной 3
        .arg(nameT, -20)                    // ФИО шириной 20
        .arg(organization, -15)             // Организация шириной 15
        .arg(reportT, -25)                  // Доклад шириной 25
        .arg(annotationT.left(30) + "...", -33); // Аннотация (сокращенная)

    qDebug() << str;
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

Speaker::Speaker(){
    qDebug()  << "Создание просто Speaker" <<"\n" ;

}
