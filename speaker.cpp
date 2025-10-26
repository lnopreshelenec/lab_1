#include "speaker.h"
#include <iostream>
#include <limits>
void Speaker::set_vuz(const string& vuz) {
    organization = vuz;
}

void Speaker::set_report(const string& report) {
    reportT = report;
}

void Speaker::set_annotacion(const string& annotacion) {
    annotationT = annotation;
}
void Speaker::get_name(const string& name){
    nameT = name
}

string Speaker::get_vuz() const {
    return organization;
}

string Speaker::get_report() const {
    return reportT;
}

string Speaker::get_annotacion() const {
    return annotationT;
}
string Speaker::get_name() const {
    return nameT;
}
void Speaker::display() const {
    cout << "Выступающий" << endl;
    cout << "ФИО:  " << nameT << endl;
    cout << "Организация/ВУЗ: " << organization << endl;
    cout << "Доклад: " << reportT << endl;
    cout << "Аннотация доклада: " << annotationT << endl;
    cout << "===============" << endl;
}

peaker::Speaker(const string& name, const string& vuz,
                 const string& report, const string& annotation)
    : nameT(name),                    // Вызов конструктора базового класса
      organization(organization),    // Инициализация организации
      reportT(report),           // Инициализация названия доклада
      annotationT(annotation) { // Инициализация аннотации
    cout << "ФИО: " << name << endl;
}
Speaker::~Speaker() {
    cout << "Удаление выступающих: " << nameT << std::endl;
}