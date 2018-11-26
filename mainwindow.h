#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QCoreApplication>
#include <string>
#include <vector>
#include <iostream>
#include "pfinder.h"
#include<QObject>
#include<math.h>
#include<clklabel.h>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    vector<point> p;
    size_t n=70,m=70;
    size_t indice;
    vector<point> v,clist;

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    vector<point> creatMap();
    void updater(vector<Clickable*>);
private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
