#include "Keeper.h"
#include "speaker.h"
#include "admin.h"
#include "programm.h"


#include <QDebug>

// void Keeper::displayAll()
// {
//     if(this->len()==0){
//         qDebug()<<"Pass Keeper";
//     }
//     for(int i =0;i<this->len();++i){
//         this->at(i)->get_data()->show();
//     }
// }
Keeper::Keeper() {
    qDebug() << "Keeper constructor";
}

Keeper::~Keeper() {
    clear();
    qDebug() << "Keeper destructor";
}

void Keeper::add(Conf* item) {
    data.add(item);
}

void Keeper::remove(int index) {
    if (index >= 0 && index < data.len()) {
        Element<Conf*>* element = data.at(index);
        if (element) {
            delete element->get_data();
            data.remove(index);
        }
    }
}

void Keeper::displayAll() {
    if (data.len() == 0) {
        qDebug() << "Keeper is empty";
        return;
    }

    for (int i = 0; i < data.len(); ++i) {
        Element<Conf*>* element = data.at(i);
        if (element && element->get_data()) {
            element->get_data()->display(i + 1);
        }
    }
}

void Keeper::save_file(const QString& filename)  {
    QFile file(filename);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qDebug() << "Cannot open file for writing:" << filename;
        return;
    }

    QTextStream out(&file);
    out << data.len() << "\n";

    for (int i = 0; i < data.len(); ++i) {
        Element<Conf*>* element = data.at(i);
        if (element && element->get_data()) {
            out << element->get_data()->toString() << "\n";
        }
    }

    file.close();
    qDebug() << "Data saved to file:" << filename;
}

void Keeper::load_file(const QString& filename) {
    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Cannot open file for reading:" << filename;
        return;
    }

    clear();

    QTextStream in(&file);
    QString sizeStr = in.readLine();
    bool ok;
    int count = sizeStr.toInt(&ok);

    if (!ok || count < 0) {
        qDebug() << "Invalid file format";
        file.close();
        return;
    }

    for (int i = 0; i < count; ++i) {
        QString line = in.readLine();
        if (line.isNull()) break;

        Conf* obj = createObjectFromString(line);
        if (obj) {
            add(obj);
        }
    }

    file.close();
    qDebug() << "Data loaded from file:" << filename << "Items:" << data.len();
}

Conf* Keeper::createObjectFromString(const QString& line) {
    QStringList parts = line.split("|");
    if (parts.size() < 2) return nullptr;

    QString type = parts[0];

    if (type == "SPEAKER" && parts.size() == 5) {
        Speaker* speaker = new Speaker();
        speaker->set_name(parts[1]);
        speaker->set_vuz(parts[2]);
        speaker->set_report(parts[3]);
        speaker->set_annotacion(parts[4]);
        return speaker;
    }
    else if (type == "ADMIN" && parts.size() == 4) {
        Admin* admin = new Admin();
        admin->set_name(parts[1]);
        admin->set_position(parts[2]);
        admin->set_responsibility(parts[3]);
        return admin;
    }
    else if (type == "PROGRAM" && parts.size() == 4) {
        Program* program = new Program();
        program->set_name(parts[1]);
        program->set_day(parts[2]);
        program->set_time(parts[3]);
        return program;
    }

    return nullptr;
}

void Keeper::clear() {
    while (data.len() > 0) {
        Element<Conf*>* element = data.at(0);
        if (element && element->get_data()) {
            delete element->get_data();
        }
        data.remove(0);
    }
}

int Keeper::getSize() const {
    return data.len();
}

Conf* Keeper::get(int index)  {
    if (index >= 0 && index < data.len()) {
        Element<Conf*>* element = data.at(index);
        return element ? element->get_data() : nullptr;
    }
    return nullptr;
}

QString Keeper::getAllFormatted()  {
    QString result;

    if (data.len() == 0) {
        return "Список пуст";
    }

    for (int i = 0; i < data.len(); ++i) {
        Element<Conf*>* element = data.at(i);
        if (element && element->get_data()) {
            result += QString("Элемент %1:\n").arg(i + 1);
            // Для подробного вывода можно добавить специфичную логику
        }
    }

    return result;
}
