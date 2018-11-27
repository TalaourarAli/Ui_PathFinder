#include "mainwindow.h"
#include "ui_mainwindow.h"
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QGridLayout *grid=ui->grid;
    //grid->setSpacing(50);
    grid->setGeometry(this->geometry());
    QPalette pal;
    pal.setColor(QPalette::Window, QColor(Qt::black));
    this->setFixedSize(600,640);
    creatMap();
    vector<Clickable *> V(si*si);
    for(size_t i=0;i<si;i++)
        for(size_t j=0;j<si;j++){
            QString s=QString::fromStdString(to_string(i));
            V[si*i+j]=new Clickable();
            int d=599/si;
            V[si*i+j]->setFixedSize(d,d);
            V[si*i+j]->setSizeIncrement(d,d);
            V[si*i+j]->setAutoFillBackground(true); // IMPORTANT!
            QPalette pal = V[si*i+j]->palette();
            pal.setColor(QPalette::Window, QColor(Qt::white));
            V[si*i+j]->setPalette(pal);
            grid->addWidget(V[si*i+j],int(i),int(j));
            grid->setMargin(10);
        }
    updater(V);
}
void MainWindow::updater(vector<Clickable *> V){
    point start,end;start.x=0;start.y=0;end.x=si-1;end.y=si-1;
    start.obs=false;
    end.obs=false;
    PFinder pf(v,start,end,si);
    p=pf.findPath("A*");
    clist=pf.getClosedList();
    cout<<"NB="<<pf.getnb()<<endl;
    for(point P:p){
        if(P.visited)
        {
            QPalette palb;
            palb.setColor(QPalette::Window, QColor(Qt::black));
            V[si*P.x+P.y]->setPalette(palb);
        }
        if(P.obs){
            QPalette paly;
            paly.setColor(QPalette::Window, QColor(Qt::gray));
            V[si*P.x+P.y]->setPalette(paly);
        }


    }
    for(auto elt:clist){
        QPalette palb;
        palb.setColor(QPalette::Window, QColor(Qt::red));
        V[si*elt.x+elt.y]->setPalette(palb);

    }
    QPalette palb,palg;
    palb.setColor(QPalette::Window, QColor(Qt::blue));
    V[si*start.x+start.y]->setPalette(palb);
    V[si*end.x+end.y]->setPalette(palb);
    ui->label->setText("Path length :"+ QString::fromStdString(to_string(clist.size())));
    ui->label_2->setText("Used method :"+pf.getUsed());
}

vector<point> MainWindow::creatMap(){
    for(size_t i=0;i<si;i++)
        for(size_t j=0;j<si;j++)
        {
            point p;
            p.x=i;
            p.y=j;

            if(((double) rand()/(RAND_MAX))<pers)p.obs=true;
            v.push_back(p);
        }
    /*for(size_t i=12;i<15;i++) //.cout=100;
                               //.obs=true;
        for(size_t j=13;j<25;j++)v[si*i+j].obs=true;//v[si*i+j].obs=true;

    for(size_t i=45;i<47;i++)
        for(size_t j=25;j<47;j++)v[si*i+j].obs=true;//v[si*i+j].obs=true;

    for(size_t i=15;i<26;i++)
        for(size_t j=30;j<37;j++)v[si*i+j].obs=true;

    for(size_t i=20;i<23;i++)
        for(size_t j=20;j<37;j++)v[si*j+i].obs=true;
*/
    return v;
}

MainWindow::~MainWindow()
{
    delete ui;
}
