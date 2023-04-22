#include<iostream>
#include<queue>
#include<fstream>
using namespace std;
#define INF NULL

typedef struct _TrangThai{
	int coc1;
	int coc2;
	int coc3;
}TrangThai;

int visited[11][11][11]={};
int max_coc_1,max_coc_2,max_coc_3;

void markVisit(TrangThai *s){
	visited[s->coc1][s->coc2][s->coc3] = 1;
}

int isVisited(TrangThai *s){
	return visited[s->coc1][s->coc2][s->coc3];
}

TrangThai *SinhTrangThai(TrangThai *s,int case_i){
	if(s == NULL)	return NULL;
	TrangThai *newS=new TrangThai;
	int fl = 0;
	if(case_i==1){
	// coc 1-> coc 2
		if(s->coc1 +s->coc2 > max_coc_2){
			newS->coc1 = s->coc1 + s->coc2 - max_coc_2;
			newS->coc2 = max_coc_2;
			newS->coc3 = s->coc3;	
		}
		else fl =1;
	} else if(case_i==2){
		if(s->coc1 +s->coc2 <= max_coc_2){
			newS->coc1 = 0;
			newS->coc2 =s->coc1 +s->coc2;
			newS->coc3 = s->coc3;
		}
		else fl=1;
	//coc 1 -> coc 3
	} else if(case_i==3){
		if(s->coc1 +s->coc3 > max_coc_3){
			newS->coc1 = s->coc1 + s->coc3 - max_coc_3;
			newS->coc2 = s->coc2;
			newS->coc3 = max_coc_3;	
		}
		else fl =1;
	} else if(case_i==4){
		if(s->coc1 +s->coc3 <= max_coc_3){
			newS->coc1 = 0;
			newS->coc2 = s->coc2;
			newS->coc3 = s->coc1 +s->coc3;	
		}
		else fl=1;
	// coc 2-> coc 3
	} else if(case_i==5){
		if(s->coc2 +s->coc3 > max_coc_3){
			newS->coc1 = s->coc1;
			newS->coc2 = s->coc2 + s->coc3 - max_coc_3;	
			newS->coc3 = max_coc_3;
		}
		else fl =1;
	} else if(case_i==6){
		if(s->coc2 +s->coc3 <= max_coc_3){
			newS->coc1 = s->coc1;
			newS->coc2 = 0;
			newS->coc3 =s->coc2 +s->coc3;
		}
		else fl=1;
	// coc 2-> coc 1
	} else if(case_i==7){
		if(s->coc2 +s->coc1 > max_coc_1){
			newS->coc1 = max_coc_1;
			newS->coc2 = s->coc1 + s->coc2 - max_coc_1;
			newS->coc3 = s->coc3;		
		}
		else fl =1;
	} else if(case_i==8){
		if(s->coc2 +s->coc1 <= max_coc_1){
			newS->coc2 = 0;
			newS->coc1 = s->coc2 +s->coc1;
			newS->coc3 = s->coc3;
		}
		else fl=1;
	// coc 3-> coc 1
	} else if(case_i==9){
		if(s->coc1 +s->coc3 >= max_coc_1){
			newS->coc1 = max_coc_1;
			newS->coc3 = s->coc1 + s->coc3 - max_coc_1;
			newS->coc2 = s->coc2;	
		}
		else fl =1;
	} else if(case_i==10){
		if(s->coc1 +s->coc3 <= max_coc_1){
			newS->coc3 = 0;
			newS->coc1 = s->coc1 + s->coc3;	
			newS->coc2 = s->coc2;
		}
		else fl =1;
	// coc 3-> coc 2
	} else if(case_i==11){
		if(s->coc2 +s->coc3 >= max_coc_2){
			newS->coc2 = max_coc_2;
			newS->coc3 = s->coc2 + s->coc3 - max_coc_2;
			newS->coc1 = s->coc1;	
		}
		else fl =1;
	} else if(case_i==12){
		if(s->coc2 +s->coc3 <= max_coc_2){
			newS->coc3 = 0;
			newS->coc2 =s->coc2 +s->coc3;
			newS->coc1 = s->coc1;
		}
		else fl=1;
	}
	else fl=1;
	
	if(fl){
		delete newS;
		newS = NULL;
	}
	return newS;
}
void InTrangThai(ofstream &DoThi, TrangThai *s){
	DoThi<<"\" ";
	DoThi<<s->coc1<<", "<<s->coc2<<", "<<s->coc3;
	DoThi<<"\"";

}

int main(){
	max_coc_1 = 10;
	max_coc_2 = 7;
	max_coc_3 = 4;
	ofstream DoThi ("Do thi Bai toan do nuoc.dot");
	DoThi<<"digraph{"<<endl;
	queue<TrangThai*> q;
	TrangThai *KhoiDau = new TrangThai;
	KhoiDau->coc1 = 0;
	KhoiDau->coc2 = 7;
	KhoiDau->coc3 = 4;
	q.push(KhoiDau);
	markVisit(KhoiDau);
	TrangThai *tmp = NULL;
	int i,fl = 0;
	while (!q.empty()){
		TrangThai *s = q.front();
		q.pop();
		for (i=1;i<13;i++){
			tmp = SinhTrangThai(s,i);
			if ((tmp!=NULL)&&(!isVisited(tmp))) {
				q.push(tmp);
				markVisit(tmp);
				DoThi<<"	";
				InTrangThai(DoThi,s);
				DoThi<<"  ->  ";
				InTrangThai(DoThi,tmp);
				DoThi<<";"<<endl;
			}
		}
	}
	DoThi<<"}";
	DoThi.close();
	FILE *f = fopen("Do thi Bai toan do nuoc.dot","r");
	if(f != NULL)
		cout<<"Đã tạo file \"Do thi Bai toan do nuoc.dot\"	"<<endl;
	else 
		cout<<"Đã có lỗi khi tạo file .dot"<<endl;
	fclose(f);
	return 0;
}
