#include<cstdio>
#include<iostream>
#include<cstring>
#include<stdlib.h>
int field[1025][1025];
int killed[1025][1025];

int xarr[] {0,-1,-1,-1,0,1,1,1};
int yarr[] {1, 1, 0, -1, -1, -1, 0 ,1};
using namespace std;

int main(){
	int t;
	scanf("%d",&t);
	while(t--){
		
		memset(field, 0 , sizeof(field[0][0])*1025*1025);
		memset(killed, 0 , sizeof(killed[0][0])*1025*1025);
		int d,n;
		int x, y,pop;
		scanf("%d", &d);
		scanf("%d", &n);
		for(int i=0; i<n ; i++){
			scanf("%d %d %d", &x, &y, &pop);
			field[x][y] = pop;
			//killed[x][y] = pop;
			int xpos, ypos;
			for(int ii=x-d; ii<= x+d; ii++){
				for(int jj=y-d; jj <= y+d; jj++){
					if(ii < 0 || jj < 0 || ii > 1024 || jj > 1024)
						continue;
					killed[ii][jj] += field[x][y];
				}
			}
		}
					
		int valX, valY, result;
		int max = 0;
		for(int i=0; i< 1025; i++){
			for(int j=0; j< 1025; j++){
				if(killed[i][j] > max){
					max = killed[i][j];
					valX = i;
					valY = j;
				}
			}
		}
	
		printf("%d %d %d\n", valX , valY , max);
	
		/*
		cout << "\n\n";
		for(int i=0; i< 10; i++){
			for(int j=0; j < 10; j++){
				cout << killed[i][j] << "\t";
			}
			cout << "\n";
		}*/
		
	}

	return 0;
}
