
#ifndef PFINDER_H
#define PFINDER_H
#include<vector>
#include<string>
#include<iostream>
#include<math.h>
#include<algorithm>
#include<QString>


typedef struct{

    size_t x=0,y=0;
    int prex=-1,prey=-1;
    bool visited=false,obs=false;
    double heur=0;
    double cout=0;

}point;
using namespace std;
class PFinder
{

    size_t nb=0,obss,si=50;
    vector<point> _map,entour,finalPath;
    QString used="";
    point init,goal,current;
    double calcP(point);
    size_t getPointByXY(size_t x,size_t y);
    void findentour();
    vector<point> openList;
    vector<point> closedList;
    bool haselt(vector<point>,point)const ;
public:
    QString getUsed(){return used;}
    size_t getnb(){return nb;}
    PFinder(vector<point>,point,point,size_t);
    void NextStep();
    point getCurrent();
    vector<point> findPath(const string="Classic");
    vector<point> getClosedList();
};
/*
 *
 * intégrer les 2 listes
 * a jouter l'heuristique (F,G,H)
 *
 *
 * */
#endif // PFINDER_H
