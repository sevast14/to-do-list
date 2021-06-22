#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFile>
#include <QInputDialog>
#include <QFileDialog>
#include <QFont>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->statusbar->showMessage("No file selected");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionOpen_triggered()
{
    path = QFileDialog::getOpenFileName(this,"Open tasks file","./","*.txt");
    ui->statusbar->showMessage(path);

    if(path.size() != 0){
        tasks.clear();
        load(path);

        ui->List->clear();
        ui->List->addItems(tasks);
    }
}

void MainWindow::load(QString path)
{
    QFile f(path);

    if(!f.open(QIODevice::ReadOnly)){
        return;
    }

    QTextStream in(&f);

    QString line;
    QString task;

    while(!in.atEnd()){
        line = in.readLine();

        if(!task.isEmpty()){
            tasks.append(task);
        }
        task = line.simplified();
    }

    if(!task.isEmpty()){
        tasks.append(task);
    }
}

void MainWindow::on_actionSave_as_triggered(){
    path = QFileDialog::getSaveFileName(this,"save","./","*.txt");
    ui->statusbar->showMessage(path);

    if(path.size() != 0){
        QFile sFile(path);

        if(!sFile.open(QIODevice::WriteOnly)){
            return;
        }
        QTextStream out(&sFile);
        for(int i = 0; i < tasks.size(); i++){
            sFile.write(tasks[i].toUtf8());
            sFile.write(QString("\n").toUtf8());
        }
    }
}



void MainWindow::on_actionSave_triggered()
{
    if(path.size() != 0){
        QFile sFile(path);

        if(!sFile.open(QIODevice::WriteOnly)){
            return;
        }
        QTextStream out(&sFile);
        for(int i = 0; i < tasks.size(); i++){
            sFile.write(tasks[i].toUtf8());
            sFile.write(QString("\n").toUtf8());
        }
    }else{
        path = QFileDialog::getSaveFileName(this,"save","./","*.txt");
        ui->statusbar->showMessage(path);
        if(path.size() != 0){
            QFile sFile(path);

            if(!sFile.open(QIODevice::WriteOnly)){
                return;
            }
            QTextStream out(&sFile);
            for(int i = 0; i < tasks.size(); i++){
                sFile.write(tasks[i].toUtf8());
                sFile.write(QString("\n").toUtf8());
            }
        }
    }
}


void MainWindow::on_DeleteButton_clicked()
{
    QListWidgetItem *it = ui->List->takeItem(ui->List->currentRow());
    QString name = it->text();
    delete it;
    tasks.removeOne(name);
}

void MainWindow::on_NewTaskButton_clicked()
{
    bool ok;
    QString text = QInputDialog::getText(this, tr("New task"),
    tr("Task's name"), QLineEdit::Normal,
    "Title", &ok);

    if(ok && !text.isEmpty()){
        tasks.append(text);
        ui->List->clear();
        ui->List->addItems(tasks);
    }
}
