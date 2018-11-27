#include "pfinder.h"
#define DEBUG2
PFinder::PFinder(vector<point> m, point p,point p2,size_t _si)
    :_map(m),init(p),goal(p2),current(p),si(_si){
}
double PFinder::calcP(point c){
    return //pow((init.x-c.x),2)+pow((init.y-c.y),2)+
            sqrt(pow((goal.x-c.x),2)+pow((goal.y-c.y),2));
}

size_t PFinder::getPointByXY(size_t x,size_t y){
    return si*x+y;
}

void PFinder::findentour(){
    entour.clear();
    size_t cx=current.x;
    size_t cy=current.y;
    if(cy>0)entour.push_back(_map[getPointByXY(cx,cy-1)]);

    if(cx<si-1)entour.push_back(_map[getPointByXY(cx+1,cy)]);
    if(cx<si-1 &&cy<si-1)entour.push_back(_map[getPointByXY(cx+1,cy+1)]);
    if(cx>0 &&cy<si-1)entour.push_back(_map[getPointByXY(cx-1,cy+1)]);
    if(cx>0 &&cy>0)entour.push_back(_map[getPointByXY(cx-1,cy-1)]);
    if(cy<si-1)entour.push_back(_map[getPointByXY(cx,cy+1)]);

    if(cx>0 )entour.push_back(_map[getPointByXY(cx-1,cy)]);
    if(cx<si-1 &&cy>0)entour.push_back(_map[getPointByXY(cx+1,cy-1)]);
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

}

bool PFinder::haselt(vector<point> v,point p) const {
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
       bool sol;
       openList.push_back(init);
        cout<<"using A* methode"<<endl;
        used="A* Algorithme";
        while(!openList.empty()){
            sol=false;
            auto i=getlowest(openList);
            current=openList[i];
            openList.erase(openList.begin()+i);
            if(current.x==goal.x && current.y==goal.y) {break;}
            else{
                findentour();
                for(point &e:entour){
                    //if(!)
                    if(!((haselt(closedList,e)&& e.cout>current.cout)
                        ||(haselt(openList,e)&& e.cout>current.cout)
                                ||e.obs)){
                        sol=true;
                        e.cout+=current.cout+1.0;
                        e.heur=e.cout+calcP(e);
                        e.prex=int(current.x);
                        e.prey=int(current.y);
                        openList.push_back(e);
                        nb++;
                    }
                }
                if(!sol) {
                    cout<<"no solution !!"<<endl; exit(-1);
                }
            }
            current.visited=true;
            closedList.push_back(current);
            _map[si*current.x+current.y]=current;
        }
        }
    else{
        cout<<"using classic methode"<<endl;
        used="classic methode";
    while(current.x != goal.x || current.y != goal.y) {
        //Astar();
        NextStep();
        finalPath.push_back(current);
        _map[si*current.x+current.y]=current;
        nb++;

#ifdef DEBUG
    cout<<"calling NextStep!!!"<<endl;
#endif
    }}
    cout<<"done!!\n";
    return _map;
}

vector<point> PFinder::getClosedList(){
    point temp=current;
    while(temp.prex >=0 || temp.prey >=0){
        finalPath.push_back(temp);
        temp=_map[si*temp.prex+temp.prey];
    }

    return finalPath;
}

