#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QFileDialog>
#include <typeinfo>
#include <typeindex>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // В конструкторе MainWindow после ui->setupUi(this);
    connect(ui->addSpeaker, &QPushButton::clicked, this, &MainWindow::on_addSpeaker_clicked);
    connect(ui->addAdmin, &QPushButton::clicked, this, &MainWindow::on_addAdmin_clicked);
    connect(ui->addProgram, &QPushButton::clicked, this, &MainWindow::on_addProgram_clicked);
    connect(ui->removeItem, &QPushButton::clicked, this, &MainWindow::on_removeItem_clicked);
    connect(ui->saveToFile, &QPushButton::clicked, this, &MainWindow::on_saveToFile_clicked);
    connect(ui->loadFromFile, &QPushButton::clicked, this, &MainWindow::on_loadFromFile_clicked);
    connect(ui->clearAll, &QPushButton::clicked, this, &MainWindow::on_clearAll_clicked);
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
    ui->textBrowser->clear();
    ui->textBrowser->append(" № | ФИО                 | Организация    | Доклад");
    ui->textBrowser->append("───|─────────────────────|────────────────|─────────────────────────");

    for (int i = 0; i < keeper.getSize(); ++i) {
        Conf* item = keeper.get(i);
        if (Speaker* speaker = dynamic_cast<Speaker*>(item)) {
            // speaker->display(i + 1);!!!!!
            // Для отображения в textBrowser нужно добавить соответствующий метод
        }
    }
}

void MainWindow::displayAdmins()
{
    ui->textBrowser_2->clear();
    ui->textBrowser_2->append(" № | ФИО                 | Должность      | Ответственность");
    ui->textBrowser_2->append("───|─────────────────────|────────────────|─────────────────────────");

    for (int i = 0; i < keeper.getSize(); ++i) {
        Conf* item = keeper.get(i);
        if (Admin* admin = dynamic_cast<Admin*>(item)) {
            // admin->display(i + 1);!!!!!
        }
    }
}

void MainWindow::displayPrograms()
{
    ui->textBrowser_3->clear();
    ui->textBrowser_3->append(" № | Наименование                  | День        | Время");
    ui->textBrowser_3->append("───|───────────────────────────────|─────────────|──────");

    for (int i = 0; i < keeper.getSize(); ++i) {
        Conf* item = keeper.get(i);
        if (Program* program = dynamic_cast<Program*>(item)) {
            // program->display(i + 1);!!!!!
        }
    }
}

void MainWindow::displayAll()
{
    ui->textBrowser_4->clear();
    ui->textBrowser_4->append(" № | Тип        | Наименование");
    ui->textBrowser_4->append("───|────────────|────────────────");

    for (int i = 0; i < keeper.getSize(); ++i) {
        Conf* item = keeper.get(i);
        if (item) {
            QString type;
            if (dynamic_cast<Speaker*>(item)) type = "Выступающий";
            else if (dynamic_cast<Admin*>(item)) type = "Администратор";
            else if (dynamic_cast<Program*>(item)) type = "Программа";

            QString line = QString("%1 | %2 | %3")
                               .arg(i + 1, 3)
                               .arg(type, -12)
                               .arg(item->get_name(), -20);

            ui->textBrowser_4->append(line);
        }
    }
}
