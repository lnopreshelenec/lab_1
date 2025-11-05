#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
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

    QStandardItemModel *model = new QStandardItemModel(this);
    model->setHorizontalHeaderLabels({"ФИО", "Организация", "Доклад", "Аннотация"});

    int row = 0;
    for (int i = 0; i < keeper.getSize(); ++i) {
        Conf* item = keeper.get(i);
        if (Speaker* speaker = dynamic_cast<Speaker*>(item)) {
            model->insertRow(row);
            model->setData(model->index(row, 0), QString(speaker->get_name()));
            model->setData(model->index(row, 1), QString(speaker->get_vuz()));
            model->setData(model->index(row, 2), QString(speaker->get_report()));
            model->setData(model->index(row, 3), QString(speaker->get_annotacion()));
            row++;
        }
    }
    ui->tableView->setModel(model);
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    ui->tableView->horizontalHeader()->setStretchLastSection(true);
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView->setAlternatingRowColors(true);

    ui->tableView->resizeColumnsToContents();
    ui->tableView->update();
}

void MainWindow::displayAdmins()
{
    if (ui->tableView_2->model()) {
        ui->tableView_2->model()->deleteLater();
    }
    QStandardItemModel *model = new QStandardItemModel(this);
    model->setHorizontalHeaderLabels({"ФИО", "Должность", "Область ответственности"});

    int row = 0;
    for (int i = 0; i < keeper.getSize(); ++i) {
        Conf* item = keeper.get(i);
        if (Admin* admin = dynamic_cast<Admin*>(item)) {
            model->insertRow(row);
            model->setData(model->index(row, 0), QString(admin->get_name()));
            model->setData(model->index(row, 1), QString(admin->get_position()));
            model->setData(model->index(row, 2), QString(admin->get_responsibility()));
            row++;
        }
    }
    ui->tableView_2->setModel(model);
    ui->tableView_2->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    ui->tableView_2->horizontalHeader()->setStretchLastSection(true);
    ui->tableView_2->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView_2->setAlternatingRowColors(true);
    ui->tableView_2->resizeColumnsToContents();
    ui->tableView_2->update();
}
void MainWindow::displayPrograms()
{
    if (ui->tableView_3->model()) {
        ui->tableView_3->model()->deleteLater();
    }
    QStandardItemModel *model = new QStandardItemModel(this);
    model->setHorizontalHeaderLabels({"Наименование мероприятия", "День", "Время"});

    int row = 0;
    for (int i = 0; i < keeper.getSize(); ++i) {
        Conf* item = keeper.get(i);
        if (Program* program = dynamic_cast<Program*>(item)) {
            model->insertRow(row);
            model->setData(model->index(row, 0), QString(program->get_name()));
            model->setData(model->index(row, 1), QString(program->get_day()));
            model->setData(model->index(row, 2), QString(program->get_time()));
            row++;
        }
    }
    ui->tableView_3->setModel(model);
    ui->tableView_3->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    ui->tableView_3->horizontalHeader()->setStretchLastSection(true);
    ui->tableView_3->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView_3->setAlternatingRowColors(true);
    ui->tableView_3->resizeColumnsToContents();
    ui->tableView_3->update();
}

void MainWindow::displayAll()
{
    if (ui->tableView_4->model()) {
        ui->tableView_4->model()->deleteLater();
    }
    QStandardItemModel *model = new QStandardItemModel(this);
    model->setHorizontalHeaderLabels({"Тип", "Наименование"});
    int row = 0;
    for (int i = 0; i < keeper.getSize(); ++i) {
        Conf* item = keeper.get(i);
        if (item) {
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
            model->insertRow(row);
            model->setData(model->index(row, 0), type);
            model->setData(model->index(row, 1), name);
            row++;
        }
    }
    ui->tableView_4->setModel(model);
    ui->tableView_4->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    ui->tableView_4->horizontalHeader()->setStretchLastSection(true);
    ui->tableView_4->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView_4->setAlternatingRowColors(true);
    ui->tableView_4->resizeColumnsToContents();
    ui->tableView_4->update();
}
