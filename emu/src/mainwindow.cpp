#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QIcon>
#include <QTextEdit>
#include <QTextOption>
#include <Qsci/qscilexerpython.h>
#include <Qsci/qsciscintilla.h>

#include "world.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    
    QMenu *fileMenu = new QMenu(tr("&File"), this);
    menuBar()->addMenu(fileMenu);
    fileMenu->addAction(tr("&New"), this, SLOT(newFile()),
                        QKeySequence(tr("Ctrl+N",
                                         "File|New")));
    QMenu *runMenu = new QMenu(tr("&Run"), this);
    menuBar()->addMenu(runMenu);
    runMenu->addAction(tr("&Run"), this, SLOT(runRun()),
                        QKeySequence(tr("Ctrl+R",
                                         "Run|Run")));
    connect(ui->tabWidget, SIGNAL(tabCloseRequested(int)), this, SLOT(tabCloseRequested(int)));


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::newFile()
{
    QsciScintilla * editor = new QsciScintilla();
    editor->setPaper(QColor(1,81,107));
    editor->setMarginLineNumbers(1,true);
    editor->setAutoIndent(true);
    editor->setLexer(new QsciLexerPython());
    editor->setFolding(QsciScintilla::PlainFoldStyle);
    editor->setAutoCompletionThreshold(2);
    editor->setAutoCompletionSource(QsciScintilla::AcsAll);
    ui->tabWidget->addTab(editor, QIcon(), QString("New file"));

}

void MainWindow::runRun()
{
    QsciScintilla *active = dynamic_cast<QsciScintilla*>(ui->tabWidget->currentWidget());

    QString text = active->text();


    const char * script = text.toAscii().data();
    environment::world * w = new environment::world("Virtual world");
    //w->run_script(script);
    w->run_file("../../s.py");


}

void MainWindow::tabCloseRequested(int index)
{
    ui->tabWidget->removeTab(index);
}
