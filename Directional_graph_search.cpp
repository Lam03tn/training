#include<iostream>
#include<fstream>
#include<vector>
#include<list>
#include<queue>
#include<algorithm>
#include<string>
#include<stack>
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
        vector<Vertex> stk;
        vector<int> lowlink;
        vector<int> index;
        int dfsCount;
        int num_strongconnect;

    void resize_lowlink_and_index(){
        lowlink.resize(vertices.size() );
        index.resize(vertices.size() );
    }    

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
            cout<<temp.vertexId<<","<<"("<<temp.vertexName<<") "<<"-->";
            temp.printEdgeList();
        }
    }
    
    void addEdge(Vertex fromVertex, Vertex toVertex){
        for(int i =0; i < vertices.size(); i ++){
            if(vertices.at(i).vertexName == fromVertex.vertexName){
                Edge edge(toVertex.vertexId, toVertex.vertexName);
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
            cout<<"\n";
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

    void Lien_thong_manh(){
        num_strongconnect = 0;
        dfsCount = 0;
        resetBool();
        resize_lowlink_and_index();
        int length = vertices.size();
        for(int i =0; i < length; i ++){
            Vertex v = vertices.at(i);
            if(!visit.at(v.vertexId) ){
                visit.at(v.vertexId) = true;
                strongconnect(v);
            }
        }
    }
  
    void strongconnect(Vertex v){
        lowlink.at(v.vertexId ) =dfsCount;
        index.at(v.vertexId ) = dfsCount;
        dfsCount ++;
        stk.push_back(v);
        for(auto x : v.edgeList){
            Vertex w = vertices.at(x.edgeId);
            if(!visit.at(w.vertexId) ){
                visit.at(w.vertexId) = true;
                strongconnect(w);
                lowlink.at(v.vertexId) = min(lowlink.at(v.vertexId) , lowlink.at(w.vertexId));
            }
            else{   
                for(int i =0 ; i < stk.size(); i ++){
                    if(stk.at(i).vertexName == w.vertexName)
                    {                       
                        lowlink.at(v.vertexId) = min(lowlink.at(v.vertexId ), index.at(w.vertexId ) ) ;   
                    }
                }
            }
        }
        if(index.at(v.vertexId) == lowlink.at(v.vertexId) ){
            while(1){
                Vertex tmp = stk.back();
                stk.pop_back();
                if(tmp.vertexName == v.vertexName){ 
                    break;
                }    
            }
            num_strongconnect ++;
        }
    }

    int So_thanh_phan_lien_thong_manh(){
        int count = 0;
        int a[10000]={};
        for(int i =0 ; i < vertices.size(); i ++){
            Vertex tmp = vertices.at(i);
            if(!a[lowlink.at(tmp.vertexId)]){
                a[lowlink.at(tmp.vertexId)] = 1;
                count ++;
            }
        }

        return count;
    }

    int Dem_cung(){
        int count = 0;
        for(int i = 0; i < vertices.size(); i ++){
            Vertex x = vertices.at(i);
            for(auto x : x.edgeList){
                count ++;
            }
        }
        return count;
    }
    
    
};

/*
int check(string v1,string v2){
    vector<char> c;
    for(int i = 1;i < 5; i ++){
        c.push_back(v1[i]);
    }
    int k = 0;
    while(1){
        for(int i =0; i < c.size(); i ++){
            if(v2[k] == c.at(i) ){
                c.erase(c.begin() + i);
                break;
            }
        }
        k++;
        if(k == 5)  break; 
    }
    if(c.empty())   return 1;
    return 0;
};
*/

int check(string a, string b){
    string a1 = a;
    int count=0;
    for(int i = 0; i <5;i++){
        for(int j = 1; j < 5;j++){
            if(b[i]==a1[j]){
                count++;
                a1[j]='A';
                break;
            }
        }
    }
    if(count >= 4) return 1;
    return 0;
}

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
//   g.printfGraph();
    g.Lien_thong_manh();
    int option;
    do{
        cout<<"\n";
        cout<<" Chon hanh dong de thuc hien -- Nhap so.\n Nhan \"0\" de thoat \" \n"<<endl;
        cout << "1. Dem so thanh phan lien thong manh" << endl;
        cout << "2. Tim cac tu cung thanh phan lien thong manh" << endl;
        cout << "3. Tim mot duong di ngan nhat tu dinh u den dinh v" << endl;
        cin >> option;
        
        if(option == 1){
            cout<< "So thanh phan lien thong manh la : "<< g.num_strongconnect<<"\n"<< endl;

        }
        if(option == 2)
        {
            string u;
            cout<<"* Nhap vao 1 dinh: ";cin>>u;
            Vertex temp = g.getVertexFromVertexName(u);
            if(temp.vertexId < 0){
                cout << "Dinh da nhap khong thuoc do thi"<<"\n";
                continue;
            }    
            cout<<"* Cac dinh cung thuoc thanh phan lien thong manh:\n";
            for(int i = 0; i < g.vertices.size(); i ++){
                Vertex x = g.vertices.at(i);
                if(g.lowlink.at(x.vertexId) == g.lowlink.at(temp.vertexId)){
                    cout<<"  "<<x.vertexName<<" ";
                }
            }
            cout<<"\n";

        }
        if(option == 3)
        {
            string begin,end;
            cout<<"* Nhap dinh bat dau:";cin>>begin;
            cout<<"* Nhap dinh ket thuc:";cin>>end;
            Vertex b = g.getVertexFromVertexName(begin);
            Vertex e = g.getVertexFromVertexName(end);
            if(b.vertexId <0 || e.vertexId < 0){
                cout<<"Dinh khong thuoc do thi."<<endl;
                continue;
            }
            g.findPath(b,e);
        }
    }while(option != 0);
  
    input_file.close();

    return 0;
}