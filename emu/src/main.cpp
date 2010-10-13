#include <QtGui/QApplication>
#include "mainwindow.h"


#include <boost/python.hpp>

int main(int argc, char *argv[])
{
    try {
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    
    return a.exec();
    }
    catch (boost::python::error_already_set)
    {
        PyErr_Print();
        throw;
    }
}
