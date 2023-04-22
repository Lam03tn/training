#include<iostream>
#include<fstream>
#include<vector>
#include<list>
#include<queue>
#include<string>
#define INF -999999
using namespace std;


class Edge{
    public:
        string edgeName; 
        int edgeId;
    Edge(){};
    Edge(int eId,string nearbyVertex){
        edgeName = nearbyVertex;
        edgeId = eId;
    }
};

class Vertex{
    public:
        int vertexId;
        string vertexName;
        list<Edge> edgeList;
    Vertex(){};

    Vertex(int vId,string vName){
        vertexName = vName;
        vertexId = vId;
    }

    void printEdgeList(){
        for (auto x: edgeList) {
            cout << x.edgeId<<", "<<x.edgeName;
        }
        cout<<endl;
    }
};

class Graph{
    public:
        vector<Vertex> vertices;
        vector<bool> visit;
    void setFalseBool(){
        for(int i = 0; i <vertices.size(); i ++){
            visit.push_back(false);
        }
    }

    void resetBool(){
        for(int i = 0; i <vertices.size(); i ++){
            visit.at(i) = false;
        }
    }

    typedef struct _pathVertex{
        Vertex V;
        struct _pathVertex *preV;
    }pathVertex;
    
    Vertex getVertexFromId(int vId){
        Vertex temp;
        for(int i =0; i < vertices.size(); i ++){
            temp = vertices.at(i);
            if(temp.vertexId == vId)
                return temp;
        }
        temp.vertexName = "\0";
        temp.vertexId = INF;
        return temp;
    }

    Vertex getVertexFromVertexName(string vName){
        Vertex temp;
        for(int i =0; i < vertices.size(); i ++){
            temp = vertices.at(i);
            if(temp.vertexName == vName)
                return temp;
        }
        temp.vertexName = "\0";
        temp.vertexId = INF;
        return temp;
    }

    void addVertex(Vertex newVertex){
        vertices.push_back(newVertex);
    }

    void printfGraph(){
        for(int i = 0; i <vertices.size();i++){
            Vertex temp;
            temp = vertices.at(i);
            cout<<temp.vertexId<<","<<"("<<temp.vertexName<<")"<<"-->";
            temp.printEdgeList();
        }
    }
    
    void addEdge(Vertex fromVertex, Vertex toVertex){
        for(int i =0; i < vertices.size(); i ++){
            if(vertices.at(i).vertexName == fromVertex.vertexName){
                Edge edge(toVertex.vertexId, toVertex.vertexName);
                vertices.at(i).edgeList.push_back(edge);
            }
            if(vertices.at(i).vertexName == toVertex.vertexName){
                Edge edge(fromVertex.vertexId, fromVertex.vertexName);
                vertices.at(i).edgeList.push_back(edge);
            }
        }
    }
    
    void BFS(Vertex v){
        queue<Vertex> q;
        q.push(v);
        visit.at(v.vertexId) = true;
        while(!q.empty()){
            Vertex tmp = q.front();
            q.pop();
            for(auto x: tmp.edgeList){
                if(!visit.at( x.edgeId) ){
                    Vertex nextV =getVertexFromId( x.edgeId);
                    q.push(nextV );
                    visit.at( x.edgeId) = true;
                }
            }
        }
    }

    int So_thanh_phan_lien_thong(){
        int count = 0;
        resetBool();
        for(int i =0 ; i <vertices.size(); i ++){
            Vertex tmp =vertices.at(i);
            if(!visit.at(tmp.vertexId)){
                BFS(tmp);
                count++;
            }
        }
        return count;
    }

    void findPath(Vertex first,Vertex final){
        resetBool();
        queue<pathVertex*> q;
        pathVertex *p = new pathVertex;
        p->V = first;
        p->preV = NULL;
        pathVertex *r = p;
        q.push(p);
        visit.at(first.vertexId) = true;
        bool flag = false;
        while(!q.empty()){
            pathVertex *tmp = q.front();
            q.pop();
            for(auto x: (tmp->V).edgeList){
                if(!visit.at( x.edgeId) ){
                    pathVertex *temp = new pathVertex;
                    Vertex nextV = getVertexFromId( x.edgeId);
                    temp->preV =tmp;
                    temp->V = nextV;
                    q.push(temp);
                    visit.at( x.edgeId) = true;
                    if(nextV.vertexName == final.vertexName){
                        p = temp;
                        flag = true;
                        break;
                    }
                }
            }
            if(p != r){
                break;
            }
            
        }
        if(flag) {
            while(1){   
                cout<<p->V.vertexName; 
                if(p->preV == NULL)   break;
                p = p->preV;
                cout<<" <-- ";
            }
            cout<<endl; 
        }  
        else{
            cout<<"Khong co duong di tu \""<<first.vertexName<<"\" "<<"den \"" <<final.vertexName<<"\""<<endl;
        }
    }
};

int check(string v1,string v2){
    if( v1[0] != v2[0] && v1[1] == v2[1] && v1[2] == v2[2] && v1[3] == v2[3] && v1[4] == v2[4] )    return 1;
    if( v1[0] == v2[0] && v1[1] != v2[1] && v1[2] == v2[2] && v1[3] == v2[3] && v1[4] == v2[4] )    return 1;
    if( v1[0] == v2[0] && v1[1] == v2[1] && v1[2] != v2[2] && v1[3] == v2[3] && v1[4] == v2[4] )    return 1;
    if( v1[0] == v2[0] && v1[1] == v2[1] && v1[2] == v2[2] && v1[3] != v2[3] && v1[4] == v2[4] )    return 1;
    if( v1[0] == v2[0] && v1[1] == v2[1] && v1[2] == v2[2] && v1[3] == v2[3] && v1[4] != v2[4] )    return 1;
    return 0;
};



int main(){
    string filename("sgb-words.txt");
    string vName;
    Graph g;
    ifstream input_file(filename);
    if (!input_file.is_open()) {
        cerr << "Could not open the file - '"
             << filename << "'" << endl;
        return EXIT_FAILURE;
    }
    int id = 0;
    while (getline(input_file, vName)){
        Vertex newVertex(id,vName);
        g.addVertex(newVertex);
        id++;
    }
    int k = 0;
    g.setFalseBool();
    while(1){
        Vertex temp = g.vertices.at(k);
        for(int i = 0; i <g.vertices.size(); i ++){
            if(temp.vertexName == g.vertices.at(i).vertexName)
                continue;
            if( check(temp.vertexName, g.vertices.at(i).vertexName) )
                g.addEdge(temp, g.vertices.at(i));
        }
        k++;
        if(k == g.vertices.size())  break;
    }

    int option;
    
    do{
        cout<<"\n";
        cout<<"Chon hanh dong de thuc hien -- Nhap so.\n Nhan \"0\" de thoat \" \n"<<endl;
        cout << "1. Dem so thanh phan lien thong" << endl;
        cout << "2. Tim mot duong di ngan nhat tu dinh u den dinh v" << endl;
        cin >> option;

        if(option == 1){
            cout<< "So thanh phan lien thong manh la : "<< g.So_thanh_phan_lien_thong()<<"\n"<< endl;

        }
        
        if(option == 2)
        {   
            string begin,end;
            cout<<"Nhap dinh bat dau:";cin>>begin;
            cout<<"Nhap dinh ket thuc:";cin>>end;
            Vertex b = g.getVertexFromVertexName(begin);
            Vertex e = g.getVertexFromVertexName(end);
            if(b.vertexId <0 || e.vertexId < 0){
                cout<<"Dinh khong thuoc do thi."<<endl;
            }
            g.findPath(b,e);
        }
    }while(option != 0);
    
    input_file.close();
    return 0;
}