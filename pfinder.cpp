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
            sqrt(pow((goal.x-c.x),2)+pow((goal.y-c.y),2));
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
    //i=getPointByXY(cx+1,cy);
    v.push_back(_map[getPointByXY(cx+1,cy)]);
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
    auto best=calcP(current);
    findentour();
    point &Np=current;
    for(point &i:entour)
        if(i.x==goal.x && i.y==goal.y){
            cout<<"found goal"<<endl;
            current=i;
            current.visited=true;
            goto here;
        }
     for(point &i:entour){
        if(!i.visited && !i.obs){
            auto v=calcP(i);
            if(best>v){
                    best=v;
                    Np=i;
                    i.visited=true;
            }

        if(i.obs)obss++;}
    }
    here : current.visited=true;

#ifdef DEBUG
    cout<<"Next Point :"<<current.x << ":"<<current.y<<endl;
#endif

}

bool haselt(vector<point> v,point p){
    for(auto &V:v)
        if(V.x==p.x && V.y==p.y)return true;

    return false;

}
size_t getlowest(vector<point> v){
    size_t ret=0;
    point pmin=v[0];
    for(size_t i=0;i<v.size();i++)
        if(v[i].heur<pmin.heur){pmin=v[i];ret=i;}

    return ret;
}
vector<point> PFinder::findPath(const string s){
   if(s=="A*"){
       openList.push_back(init);
        cout<<"using A* methode"<<endl;
        while(!openList.empty()){
            auto i=getlowest(openList);
            current=openList[i];
            openList.erase(openList.begin()+i);
            //cout<<"open size :"<<openList.size()<<endl;
            if(current.x==goal.x && current.y==goal.y) {cout<<"goal\n";break;}
            else{
                findentour();
                for(point &e:entour){
                    if(!(
                              (haselt(closedList,e)&& e.cout<current.cout)
                              ||(haselt(openList,e)&& e.cout<current.cout)
                                )){
                        e.cout+=current.cout+1;
                        e.heur=e.cout+calcP(e);
                        openList.push_back(e);
                        nb++;
                    }
                }
            }
            //current.visited=true;
            closedList.push_back(current);
            finalPath.push_back(current);
            //cout<<"closed :"<<closedList.size()<<endl;
            update();
            cout<<"next !! x:y="<<current.x<<":"<<current.y<<endl;
            //cout<<"yep"<<endl;
        }
        }
    else{
        cout<<"using classic methode"<<endl;
    while(current.x != goal.x || current.y != goal.y) {
        //Astar();
        NextStep();
        cout<<"next !! x:y="<<current.x<<":"<<current.y<<endl;
        update();
        nb++;

#ifdef DEBUG
    cout<<"calling NextStep!!!"<<endl;
#endif
    }}
    cout<<"done!!\n";
    return _map;
}

vector<point> PFinder::getClosedList(){
    return finalPath;
}

void PFinder::showMap(){
    //cout<<"The Map :"<<endl;

}
