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
            pal.setColor(QPalette::Window, QColor(Qt::red));
            V[n*i+j]->setPalette(pal);
            grid->addWidget(V[m*i+j],int(i),int(j));
        }
    updater(V);
}
void MainWindow::updater(vector<Clickable *> V){
    point start,end;start.x=1;start.y=1;end.x=48;end.y=48;
    PFinder pf(v,start,end);
    p=pf.findPath();
    cout<<"NB="<<pf.getnb()<<endl;
    for(point P:p){
        if(P.visited)
        {
            QPalette palb;
            palb.setColor(QPalette::Window, QColor(Qt::green));
            V[m*P.x+P.y]->setPalette(palb);
        }
        if(P.obs){
            QPalette paly;
            paly.setColor(QPalette::Window, QColor(Qt::yellow));
            V[m*P.x+P.y]->setPalette(paly);
        }
    }
    QPalette palb,palg;
    palb.setColor(QPalette::Window, QColor(Qt::black));
    V[m*start.y+start.x]->setPalette(palb);
    palg.setColor(QPalette::Window, QColor(Qt::blue));
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
    for(size_t i=12;i<15;i++){
        for(size_t j=11;j<25;j++)v[m*i+j].obs=true;
    }
    return v;
}

MainWindow::~MainWindow()
{
    delete ui;
}
