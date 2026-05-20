#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "baseconverter.h"
#include <QFileDialog>
#include <QFile>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->ConvertBut, &QPushButton::clicked, this, &MainWindow::Convert);
    connect(ui->ReverseBut, &QPushButton::clicked, this, &MainWindow::Reverse);
    connect(ui->openFileButton, &QPushButton::clicked, this, &MainWindow::OpenFile);
    connect(ui->SaveBut, &QPushButton::clicked, this, &MainWindow::SaveInFile);
    ui->Result->setStyleSheet(
        "background-color: #2b2b2b;"
        "color: white;"
        "border-radius: 10px;"
        "padding: 5px;"
    );
    ui->Result->setReadOnly(true);

    ui->Result->setFont(QFont("Consolas", 11));

    ui->DigitEnter->setLineWrapMode(QPlainTextEdit::NoWrap);

    ui->Result->setStyleSheet(
        "QPlainTextEdit {"
        "background-color: #1e1e1e;"
        "color: #dcdcdc;"
        "border: 2px solid #3c3c3c;"
        "border-radius: 10px;"
        "padding: 8px;"
        "selection-background-color: #3a6ea5;"
        "selection-color: white;"
        "}"
        "QScrollBar:vertical {"
        "background: #2b2b2b;"
        "width: 12px;"
        "margin: 0px;"
        "}"
        "QScrollBar::handle:vertical {"
        "background: #5a5a5a;"
        "border-radius: 5px;"
        "min-height: 20px;"
        "}"
        "QScrollBar::handle:vertical:hover {"
        "background: #777777;"
        "}"
        "QScrollBar::add-line:vertical,"
        "QScrollBar::sub-line:vertical {"
        "height: 0px;"
        "}"
        "QScrollBar:horizontal {"
        "background: #2b2b2b;"
        "height: 12px;"
        "margin: 0px;"
        "}"
        "QScrollBar::handle:horizontal {"
        "background: #5a5a5a;"
        "border-radius: 5px;"
        "min-width: 20px;"
        "}"
        "QScrollBar::handle:horizontal:hover {"
        "background: #777777;"
        "}"
        "QScrollBar::add-line:horizontal,"
        "QScrollBar::sub-line:horizontal {"
        "width: 0px;"
        "}"
        );
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::Convert()
{
    BaseConverter converter;
    std::string digit = ui->DigitEnter->toPlainText().toStdString();
    double p = ui->PEnter->text().toDouble();
    double q = ui->QEnter->text().toDouble();
    //qDebug() << QString::fromStdString(converter.convert(digit, p, q));

    ui->Result->setPlainText(QString::fromStdString(converter.convert(digit, p, q)));
}

void MainWindow::Reverse()
{
    QString temp = ui->PEnter->text();
    ui->PEnter->setText(ui->QEnter->text());
    ui->QEnter->setText(temp);
}

void MainWindow::OpenFile()
{
    QString path = QFileDialog::getOpenFileName(
        this,
        "Выберите txt файл",
        "",
        "Text Files (*.txt)"
        );

    if (!path.isEmpty()) {

        QFile file(path);

        if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {

            QTextStream in(&file);

            QString text = in.readAll();

            ui->DigitEnter->setPlainText(text);

            file.close();
        }
    }
}

void MainWindow::SaveInFile()
{
    QString path = QFileDialog::getSaveFileName(
        this,
        "Сохранить файл",
        "",
        "Text Files (*.txt)"
        );

    if (path.isEmpty())
        return;

    QFile file(path);

    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox::critical(
            this,
            "Ошибка",
            "Не удалось открыть файл для записи:\n" + path
            );
        return;
    }

    QTextStream out(&file);
    out << ui->Result->toPlainText();

    file.close();

    QMessageBox::information(
        this,
        "Успех",
        "Файл успешно сохранён"
        );
}


