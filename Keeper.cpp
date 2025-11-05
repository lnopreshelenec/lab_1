#include "Keeper.h"
#include "speaker.h"
#include "admin.h"
#include "programm.h"
#include "conf.h"

#include <QDebug>

Keeper::Keeper() {
    qDebug() << "Keeper Конструктор";
}

Keeper::~Keeper() {
    clear();
    qDebug() << "Keeper деструктор";
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
        qDebug() << "Keeper пустой";
        return;
    }

    for (int i = 0; i < data.len(); ++i) {
        Element<Conf*>* element = data.at(i);
        if (element && element->get_data()) {
            // element->get_data()->display(i + 1);!!!!!
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
    qDebug() << "Загружео в файл:" << filename;
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
        if (obj!=nullptr) {
            add(obj);
            // qDebug()<<"Pars str"<<obj->toString();
        }else{
        }
    }

    file.close();
    qDebug() << "Выгружено из файла:" << filename << "количество:" << data.len();
}

Conf* Keeper::createObjectFromString(const QString& line) {
    QStringList parts = line.split("|");
    if (parts.size() < 2) return nullptr;

    QString type = parts[0];
    if (type.trimmed() == QString("SPEAKER").trimmed() && parts.size() == 5) {
        Speaker* speaker = new Speaker();
        speaker->set_name(parts[1].trimmed());
        speaker->set_vuz(parts[2].trimmed());
        speaker->set_report(parts[3].trimmed());
        speaker->set_annotacion(parts[4].trimmed());
        return speaker;
    }
    else if (type.trimmed() == QString("ADMIN").trimmed() && parts.size() == 4) {
        Admin* admin = new Admin();
        admin->set_name(parts[1].trimmed());
        admin->set_position(parts[2].trimmed());
        admin->set_responsibility(parts[3].trimmed());
        return admin;
    }
    else if (type.trimmed() == QString("PROGRAM").trimmed() && parts.size() == 4) {
        Program* program = new Program();
        program->set_name(parts[1].trimmed());
        program->set_day(parts[2].trimmed());
        program->set_time(parts[3].trimmed());
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
        }
    }

    return result;
}
