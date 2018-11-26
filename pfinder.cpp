#include "pfinder.h"
#define DEBUG2
PFinder::PFinder(vector<point> m, point p,point p2)
    :_map(m),init(p),goal(p2),current(p){
}
void PFinder::update(){
    for(size_t i=0;i<_map.size();i++)
        if(_map[i].x==current.x && _map[i].y==current.y)_map[i]=current;
}
double PFinder::calcP(point c){
    return //pow((init.x-c.x),2)+pow((init.y-c.y),2)+
            pow((goal.x-c.x),2)+pow((goal.y-c.y),2);
}

size_t PFinder::getPointByXY(size_t x,size_t y){
    for(size_t i=0;i<_map.size();i++)
        if(_map[i].x==x && _map[i].y==y)return i;
    throw string("erreur, not found, fct getPointByXY");
}

vector<point> PFinder::getCurrentEntourage(){

    return entour;

}

void PFinder::findentour(){
    vector<point> &v=entour;
    size_t cx=current.x;
    size_t cy=current.y;
#ifdef DEBUG
    cout<<"cx :"<<cx<<endl;
    cout<<"cy :"<<cy<<endl;
#endif
    try{
    size_t i=getPointByXY(cx-1,cy-1);
    v.push_back(_map[i]);
    i=getPointByXY(cx-1,cy);
    v.push_back(_map[i]);
    i=getPointByXY(cx-1,cy+1);
    v.push_back(_map[i]);
    i=getPointByXY(cx,cy-1);
    v.push_back(_map[i]);
    i=getPointByXY(cx,cy);
    v.push_back(_map[i]);
    i=getPointByXY(cx,cy+1);
    v.push_back(_map[i]);
    i=getPointByXY(cx+1,cy-1);
    v.push_back(_map[i]);
    i=getPointByXY(cx+1,cy);
    v.push_back(_map[i]);
    i=getPointByXY(cx+1,cy+1);
    v.push_back(_map[i]);
    }
    catch(string c){
        cout<<c<<endl;
        exit(-1);
    }

}

point PFinder::getCurrent(){
    return current;
}

void PFinder::NextStep(){
    findentour();
    auto best=calcP(current);
    point &Np=current;
    for(point &i:entour){
        if(!i.visited && !i.obs){
            //
            auto v=calcP(i);
            if(best>v){

                    best=v;
                    Np=i;
                    i.visited=true;
            }
            }
        if(i.obs)obss++;
    }
    current.visited=true;

#ifdef DEBUG
    cout<<"Next Point :"<<current.x << ":"<<current.y<<endl;
#endif

}

vector<point> PFinder::findPath(){
    while(current.x != goal.x || current.y != goal.y) {
        NextStep();
        nb++;
        update();
#ifdef DEBUG
    cout<<"calling NextStep!!!"<<endl;
#endif
    }
    cout<<"done!!\n";
    return _map;
}

void PFinder::showMap(){
    //cout<<"The Map :"<<endl;

}
