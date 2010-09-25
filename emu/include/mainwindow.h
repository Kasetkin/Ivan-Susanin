#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui/QMainWindow>

namespace Ui
{
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

public slots:
    void newFile();
    void openFile();
    void saveFile();
    void runRun();
    void runRunFile();
    void tabCloseRequested(int index);
    void loadFile(const QString &fileName);
};

#endif // MAINWINDOW_H
