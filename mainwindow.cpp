#include "mainwindow.h"
#include "ui_mainwindow.h"
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QGridLayout *grid=ui->grid;
    grid->setSpacing(50);
    grid->setGeometry(this->geometry());
    QPalette pal;
    pal.setColor(QPalette::Window, QColor(Qt::black));
    this->setFixedSize(610,610);
    creatMap();
    vector<Clickable *> V(n*m);
    for(size_t i=0;i<n;i++)
        for(size_t j=0;j<m;j++){
            QString s=QString::fromStdString(to_string(i));
            V[n*i+j]=new Clickable();
            V[n*i+j]->setFixedSize(600/n,600/m);
            V[n*i+j]->setAutoFillBackground(true); // IMPORTANT!
            QPalette pal = V[n*i+j]->palette();
            pal.setColor(QPalette::Window, QColor(Qt::white));
            V[n*i+j]->setPalette(pal);
            grid->addWidget(V[m*i+j],int(i),int(j));
        }
    updater(V);
}
void MainWindow::updater(vector<Clickable *> V){
    point start,end;start.x=1;start.y=1;end.x=59;end.y=59;
    PFinder pf(v,start,end);
    p=pf.findPath();
    clist=pf.getClosedList();
    cout<<"NB="<<pf.getnb()<<endl;
    for(point P:p){
        if(P.visited)
        {
            QPalette palb;
            palb.setColor(QPalette::Window, QColor(Qt::black));
            V[m*P.x+P.y]->setPalette(palb);
        }
        if(P.obs){
            QPalette paly;
            paly.setColor(QPalette::Window, QColor(Qt::gray));
            V[m*P.x+P.y]->setPalette(paly);
        }


    }/*
    for(auto elt:clist){
        QPalette palb;
        palb.setColor(QPalette::Window, QColor(Qt::red));
        V[m*elt.x+elt.y]->setPalette(palb);

    }*/
    QPalette palb,palg;
    palb.setColor(QPalette::Window, QColor(Qt::blue));
    V[m*start.y+start.x]->setPalette(palb);
    palg.setColor(QPalette::Window, QColor(Qt::red));
    V[m*end.y+end.x]->setPalette(palg);
}

vector<point> MainWindow::creatMap(){

    for(size_t i=0;i<70;i++)
        for(size_t j=0;j<70;j++)
        {
            point p;
            p.x=i;
            p.y=j;
            v.push_back(p);
        }
    for(size_t i=12;i<15;i++) //.cout=100;
                               //.obs=true;
        for(size_t j=13;j<25;j++)

            v[m*i+j].obs=true;

    for(size_t i=25;i<27;i++)
        for(size_t j=25;j<35;j++)v[m*j+i].obs=true;
    for(size_t i=15;i<26;i++)
        for(size_t j=30;j<37;j++)v[m*i+j].obs=true;

    for(size_t i=20;i<23;i++)
        for(size_t j=20;j<37;j++)v[m*j+i].obs=true;

    for(size_t i=5;i<12;i++)
        for(size_t j=16;j<26;j++)v[m*j+i].obs=true;

    for(size_t i=40;i<45;i++)
        for(size_t j=50;j<55;j++)v[m*i+j].obs=true;

    return v;
}

MainWindow::~MainWindow()
{
    delete ui;
}
