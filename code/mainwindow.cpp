#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFile>
#include <QTextStream>
#include <QFileDialog>
#include "scanner.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    QString file_location = QFileDialog::getOpenFileName(
                this,
                tr("Open File"),
                "c://",
                tr("Text files (*.txt)")
                );
    QFile inputFile(file_location);
    inputFile.open(QIODevice::ReadOnly);

    QTextStream in(&inputFile);
    QString line = in.readAll();
    inputFile.close();
    scan(file_location.toStdString());
    ui->code_text_edit->setPlainText(line);
    QTextCursor cursor = ui->code_text_edit->textCursor();

    QFile scanner_out("./output_files/scanner_output.txt");
    scanner_out.open(QIODevice::ReadOnly);

    QTextStream scanner_in(&scanner_out);
    QString scanner_txt = scanner_in.readAll();
    scanner_out.close();

    ui->scanner_text_edit->setPlainText(scanner_txt);
}
