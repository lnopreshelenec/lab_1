#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QFileDialog>
#include <typeinfo>
#include <typeindex>
#include <QMainWindow>
#include <QStandardItemModel>  // Для QStandardItemModel
#include <QTableView>          // Для QTableView
#include <QHeaderView>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // В конструкторе MainWindow после ui->setupUi(this);
    // connect(ui->addSpeaker, &QPushButton::clicked, this, &MainWindow::on_addSpeaker_clicked);
    // connect(ui->addAdmin, &QPushButton::clicked, this, &MainWindow::on_addAdmin_clicked);
    // connect(ui->addProgram, &QPushButton::clicked, this, &MainWindow::on_addProgram_clicked);
    // connect(ui->removeItem, &QPushButton::clicked, this, &MainWindow::on_removeItem_clicked);
    // connect(ui->saveToFile, &QPushButton::clicked, this, &MainWindow::on_saveToFile_clicked);
    // connect(ui->loadFromFile, &QPushButton::clicked, this, &MainWindow::on_loadFromFile_clicked);
    // connect(ui->clearAll, &QPushButton::clicked, this, &MainWindow::on_clearAll_clicked);
        updateDisplay();
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::on_addSpeaker_clicked()
{
    QString name = ui->lineEdit_6->text();
    QString organization = ui->lineEdit_29->text();
    QString report = ui->lineEdit_32->text();
    QString annotation = ui->lineEdit_33->text();

    if (name.isEmpty() || organization.isEmpty() || report.isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Заполните все обязательные поля");
        return;
    }

    Speaker* speaker = new Speaker(name, organization, report, annotation);
    keeper.add(speaker);

    // Очистка полей
    ui->lineEdit_6->clear();
    ui->lineEdit_29->clear();
    ui->lineEdit_32->clear();
    ui->lineEdit_33->clear();

    updateDisplay();
    QMessageBox::information(this, "Успех", "Выступающий добавлен");
}

void MainWindow::on_addAdmin_clicked()
{
    QString name = ui->lineEdit_34->text();
    QString position = ui->lineEdit_35->text();
    QString responsibility = ui->lineEdit_36->text();

    if (name.isEmpty() || position.isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Заполните ФИО и должность");
        return;
    }

    Admin* admin = new Admin();
    admin->set_name(name);
    admin->set_position(position);
    admin->set_responsibility(responsibility);
    keeper.add(admin);

    // Очистка полей
    ui->lineEdit_34->clear();
    ui->lineEdit_35->clear();
    ui->lineEdit_36->clear();

    updateDisplay();
    QMessageBox::information(this, "Успех", "Администратор добавлен");
}

void MainWindow::on_addProgram_clicked()
{
    QString name = ui->lineEdit_21->text();
    QString day = ui->comboBox_2->currentText();
    QString time = ui->lineEdit_37->text();

    if (name.isEmpty() || time.isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Заполните название и время");
        return;
    }

    Program* program = new Program();
    program->set_name(name);
    program->set_day(day);
    program->set_time(time);
    keeper.add(program);

    // Очистка полей
    ui->lineEdit_21->clear();
    ui->lineEdit_37->clear();

    updateDisplay();
    QMessageBox::information(this, "Успех", "Программа добавлена");
}

void MainWindow::on_removeItem_clicked()
{
    QString indexStr = ui->lineEdit_30->text();
    bool ok;
    int index = indexStr.toInt(&ok);

    if (!ok || index < 1 || index > keeper.getSize()) {
        QMessageBox::warning(this, "Ошибка", "Введите корректный номер элемента");
        return;
    }

    keeper.remove(index - 1);
    ui->lineEdit_30->clear();
    updateDisplay();
    QMessageBox::information(this, "Успех", "Элемент удален");
}

void MainWindow::on_saveToFile_clicked()
{
    QString filename = QFileDialog::getSaveFileName(this, "Сохранить файл", "", "Text files (*.txt)");
    if (!filename.isEmpty()) {
        keeper.save_file(filename);
        QMessageBox::information(this, "Успех", "Данные сохранены в файл: " + filename);
    }
}

void MainWindow::on_loadFromFile_clicked()
{
    QString filename = QFileDialog::getOpenFileName(this, "Загрузить файл", "", "Text files (*.txt)");
    if (!filename.isEmpty()) {
        keeper.load_file(filename);
        updateDisplay();
        QMessageBox::information(this, "Успех", "Данные загружены из файла: " + filename);
    }
}

void MainWindow::on_clearAll_clicked()
{
    keeper.clear();
    updateDisplay();
    QMessageBox::information(this, "Успех", "Все данные очищены");
}

void MainWindow::updateDisplay()
{
    displaySpeakers();
    displayAdmins();
    displayPrograms();
    displayAll();
}

void MainWindow::displaySpeakers()
{
    if (ui->tableView->model()) {
        ui->tableView->model()->deleteLater();
    }
    // ui->tableView->clear();
    // ui->textBrowser->append(" № | ФИО                 | Организация    | Доклад");
    // ui->textBrowser->append("───|─────────────────────|────────────────|─────────────────────────");
    QStandardItemModel *model = new QStandardItemModel(this);

    // Устанавливаем заголовки столбцов
    model->setHorizontalHeaderLabels({"ФИО", "Организация", "Доклад", "Аннотация"});

    int row = 0;
    for (int i = 0; i < keeper.getSize(); ++i) {
        Conf* item = keeper.get(i);
        if (Speaker* speaker = dynamic_cast<Speaker*>(item)) {
            // Добавляем строку в таблицу
            model->insertRow(row);

            // // Столбец №
            // model->setData(model->index(row, 0), row + 1);

            // Столбец ФИО
            model->setData(model->index(row, 0), QString(speaker->get_name()));

            // Столбец Организация
            model->setData(model->index(row, 1), QString(speaker->get_vuz()));

            // Столбец Доклад
            model->setData(model->index(row, 2), QString(speaker->get_report()));

            // Столбец Аннотация
            model->setData(model->index(row, 3), QString(speaker->get_annotacion()));

            row++;
        }
    }

    // Устанавливаем модель в tableView
    ui->tableView->setModel(model);

    // Настраиваем внешний вид таблицы
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    ui->tableView->horizontalHeader()->setStretchLastSection(true);
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView->setAlternatingRowColors(true);

    // Обновляем отображение
    ui->tableView->resizeColumnsToContents();
    ui->tableView->update();
}
//     for (int i = 0; i < keeper.getSize(); ++i) {
//         Conf* item = keeper.get(i);
//         if (Speaker* speaker = dynamic_cast<Speaker*>(item)) {
//              ui->tableView->append(speaker->toString());

//             // Для отображения в textBrowser нужно добавить соответствующий метод
//         }
//     }
// }

// void MainWindow::displayAdmins()
// {
//     ui->tableView_2->clear();
//     // ui->textBrowser_2->append(" № | ФИО                 | Должность      | Ответственность");
//     // ui->textBrowser_2->append("───|─────────────────────|────────────────|─────────────────────────");

//     for (int i = 0; i < keeper.getSize(); ++i) {
//         Conf* item = keeper.get(i);
//         if (Admin* admin = dynamic_cast<Admin*>(item)) {
//             // admin->display(i + 1);!!!!!
//             ui->tableView_2->append(admin->toString());

//         }
//     }
// }
void MainWindow::displayAdmins()
{
    // Очищаем существующую модель
    if (ui->tableView_2->model()) {
        ui->tableView_2->model()->deleteLater();
    }

    // Создаем модель для таблицы
    QStandardItemModel *model = new QStandardItemModel(this);

    // Устанавливаем заголовки столбцов
    model->setHorizontalHeaderLabels({"ФИО", "Должность", "Область ответственности"});

    int row = 0;
    for (int i = 0; i < keeper.getSize(); ++i) {
        Conf* item = keeper.get(i);
        if (Admin* admin = dynamic_cast<Admin*>(item)) {
            // Добавляем строку в таблицу
            model->insertRow(row);

            // // Столбец №
            // model->setData(model->index(row, 0), row + 1);

            // Столбец ФИО
            model->setData(model->index(row, 0), QString(admin->get_name()));

            // Столбец Должность
            model->setData(model->index(row, 1), QString(admin->get_position()));

            // Столбец Область ответственности
            model->setData(model->index(row, 2), QString(admin->get_responsibility()));

            row++;
        }
    }

    // Устанавливаем модель в tableView_2
    ui->tableView_2->setModel(model);

    // Настраиваем внешний вид таблицы
    ui->tableView_2->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    ui->tableView_2->horizontalHeader()->setStretchLastSection(true);
    ui->tableView_2->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView_2->setAlternatingRowColors(true);

    // Обновляем отображение
    ui->tableView_2->resizeColumnsToContents();
    ui->tableView_2->update();
}
// void MainWindow::displayPrograms()
// {
//     ui->tableView_3->clear();
//     // ui->textBrowser_3->append(" № | Наименование                  | День        | Время");
//     // ui->textBrowser_3->append("───|───────────────────────────────|─────────────|──────");

//     for (int i = 0; i < keeper.getSize(); ++i) {
//         Conf* item = keeper.get(i);
//         if (Program* program = dynamic_cast<Program*>(item)) {
//             ui->tableView_3->append(program->toString());
//             // program->display(i + 1);!!!!!
//         }
//     }
// }
void MainWindow::displayPrograms()
{
    // Очищаем существующую модель
    if (ui->tableView_3->model()) {
        ui->tableView_3->model()->deleteLater();
    }

    // Создаем модель для таблицы
    QStandardItemModel *model = new QStandardItemModel(this);

    // Устанавливаем заголовки столбцов
    model->setHorizontalHeaderLabels({"Наименование мероприятия", "День", "Время"});

    int row = 0;
    for (int i = 0; i < keeper.getSize(); ++i) {
        Conf* item = keeper.get(i);
        if (Program* program = dynamic_cast<Program*>(item)) {
            // Добавляем строку в таблицу
            model->insertRow(row);

            // // Столбец №
            // model->setData(model->index(row, 0), row + 1);

            // Столбец Наименование мероприятия
            model->setData(model->index(row, 0), QString(program->get_name()));

            // Столбец День
            model->setData(model->index(row, 1), QString(program->get_day()));

            // Столбец Время
            model->setData(model->index(row, 2), QString(program->get_time()));

            row++;
        }
    }

    // Устанавливаем модель в tableView_3
    ui->tableView_3->setModel(model);

    // Настраиваем внешний вид таблицы
    ui->tableView_3->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    ui->tableView_3->horizontalHeader()->setStretchLastSection(true);
    ui->tableView_3->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView_3->setAlternatingRowColors(true);

    // Обновляем отображение
    ui->tableView_3->resizeColumnsToContents();
    ui->tableView_3->update();
}
// void MainWindow::displayAll()
// {
//     ui->textBrowser_4->clear();
//     // ui->textBrowser_4->append(" № | Тип        | Наименование");
//     // ui->textBrowser_4->append("───|────────────|────────────────");

//     for (int i = 0; i < keeper.getSize(); ++i) {
//         Conf* item = keeper.get(i);
//         if (item) {
//             QString type;
//             if (dynamic_cast<Speaker*>(item)) type = "Выступающий";
//             else if (dynamic_cast<Admin*>(item)) type = "Администратор";
//             else if (dynamic_cast<Program*>(item)) type = "Программа";

//             QString line = QString("%1 | %2 | %3")
//                                .arg(i + 1, 3)
//                                .arg(type, -12)
//                                .arg(item->get_name(), -20);

//             ui->textBrowser_4->append(line);
//         }
//     }
// }
void MainWindow::displayAll()
{
    // Очищаем существующую модель
    if (ui->tableView_4->model()) {
        ui->tableView_4->model()->deleteLater();
    }

    // Создаем модель для таблицы
    QStandardItemModel *model = new QStandardItemModel(this);

    // Устанавливаем заголовки столбцов
    model->setHorizontalHeaderLabels({"Тип", "Наименование"});

    int row = 0;
    for (int i = 0; i < keeper.getSize(); ++i) {
        Conf* item = keeper.get(i);
        if (item) {
            // Определяем тип объекта
            QString type;
            QString name;

            if (Speaker* speaker = dynamic_cast<Speaker*>(item)) {
                type = "Выступающий";
                name = QString(speaker->get_name());
            }
            else if (Admin* admin = dynamic_cast<Admin*>(item)) {
                type = "Администратор";
                name = QString(admin->get_name());
            }
            else if (Program* program = dynamic_cast<Program*>(item)) {
                type = "Программа";
                name = QString(program->get_name());
            }

            // Добавляем строку в таблицу
            model->insertRow(row);


            // Столбец Тип
            model->setData(model->index(row, 0), type);

            // Столбец Наименование
            model->setData(model->index(row, 1), name);

            row++;
        }
    }

    // Устанавливаем модель в tableView_4
    ui->tableView_4->setModel(model);

    // Настраиваем внешний вид таблицы
    ui->tableView_4->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    ui->tableView_4->horizontalHeader()->setStretchLastSection(true);
    ui->tableView_4->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView_4->setAlternatingRowColors(true);

    // Обновляем отображение
    ui->tableView_4->resizeColumnsToContents();
    ui->tableView_4->update();
}
