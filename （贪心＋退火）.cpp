// 3sat

#include <iostream>
//#include <cstdio>
#include <cstring>
#include <cmath>
#include <bits/stdc++.h>
//#include <cstdlib>
#include<ctime> 

using namespace std ; 

int N , M,times,loop=0 ; 

int arr[16000][5] ; 
int state[5000] ; 

int energy () {
	int res = 0 ; 
	for ( int i = 1 ; i <= M ; i++ ) {
		bool flag = false ; 
		for ( int ii = 1 ; ii <= 3 ; ii++){
			int t = arr[i][ii] ; 
			if ( t > 0 ) {
				if ( state[t] <= 0 ) continue ; 
				flag = true ; 
				break ; 
			} else {
				t = -t ; 
				if ( state[t] >= 0 ) continue ; 
				flag = true ; 
				break ; 
			}
		}
		if ( flag ) res++ ; 
	}
	return res ; 
}

void init () {
	srand(time(NULL)+10*loop);
	for ( int i = 1 ; i <= N ; i++ ) {
		int t = rand()%2 ;
		if(t==0)
		t=-1;
		state[i] = t ; 	
	}
	loop++;
	return ; 
}

const double eps = 1e-8 ;
const double P = 0.9998 ;  

void sa () {
	
	double T = M/N ;//Under this circumstance,running times max is 80000,//T=4 in old program;
	int oe , ne ; 
	init() ; 
	oe = energy();  
	if ( oe == M ) return ; 
	int x; 
	times=0;
	for(int count=0;count< 100*N*log(N);count++){
		int m=RAND_MAX/N;
		while(1)
		{
			x=rand();
			if(x>m*N)
			continue;
			else
			{
			x=x%N+1;
			break;
			}
 		}//生成等概率的数据 
		state[x] *= -1 ; 
		ne = energy() ;
		if ( ne == M ) return ;  
		if ( ne >= oe ) {
			T *= P ; 
			oe = ne ; 
			continue ; 
		}
		else if (times>2*N*log(N)&&rand() < RAND_MAX * exp( (ne-oe) / T ) ) {//RAND_MAX是一个在<cstdlib>中定义的常量，通常为326767 
			T *= P ; 
			oe = ne ; 
			continue ; 
		}
		else {
			state[x] *= -1 ; 	
			T *= P ; 
		}
		times++;
	}
	
	return ; 
}


int main () {
	freopen("testData5.txt","r",stdin);
	cin >> N >> M ; 
	for ( int i = 1 ; i <= M ; i++ ) 
		for ( int ii = 1 ; ii <= 3 ; ii++ ) {
			cin >> arr[i][ii] ; 
		}
	for(int i=0;i<50;i++) 
	{				
	sa() ; 
	if ( energy() == M ) 	
	{
    cout<<  "times:"<<times<<endl;
	 for ( int i = 1 ; i <= N ; i++ ) 
	  cout<<(state[i]>0) << " "  ; 
	  cout<<endl;
//	  break;
	}	
	else cout << "times:"<<times<<"   Solve: "<< energy() << " / " << M << endl ; 
   }
	
	return 0 ; 
}
