#include "speaker.h"
#include <iostream>
#include <limits>
void Speaker::set_vuz(const QString& vuz) {
    organization = vuz;
}

void Speaker::set_report(const QString& report) {
    reportT = report;
}

// void Speaker::set_annotacion(const string& annotacion) {
//     annotationT = annotacion;
// }
// void Speaker::get_name() const {
//     return nameT;
// }

// string Speaker::get_vuz() const {
//     return organization;
// }

// string Speaker::get_report() const {
//     return reportT;
// }

// string Speaker::get_annotacion() const {
//     return annotationT;
// }
// string Speaker::get_name() const {
//     return nameT;
// }
// void Speaker::display() const {
//     qDebug() << "Выступающий" << endl;
//     qDebug() << "ФИО:  " << nameT << endl;
//     qDebug() << "Организация/ВУЗ: " << organization << endl;
//     qDebug() << "Доклад: " << reportT << endl;
//     qDebug() << "Аннотация доклада: " << annotationT << endl;
//     qDebug() << "===============" << endl;
// }

// Speaker::Speaker(const string& name, const string& vuz,
//                  const string& report, const string& annotation)
//     : nameT(name),                    // Вызов конструктора базового класса
//       organization(organization),    // Инициализация организации
//       reportT(report),           // Инициализация названия доклада
//       annotationT(annotation) { // Инициализация аннотации
//     cout << "ФИО: " << name << endl;
// }
// Speaker::~Speaker() {
//     cout << "Удаление выступающих: " << nameT << std::endl;
// }
