#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_actionOpen_triggered();

    void on_actionSave_triggered();

    void on_actionSave_as_triggered();

    void on_DeleteButton_clicked();

    void on_NewTaskButton_clicked();

private:
    Ui::MainWindow *ui;
    QStringList tasks;
    QString path;
    void load(QString path);
};
#endif // MAINWINDOW_H
