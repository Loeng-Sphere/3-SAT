// 3sat

#include <iostream>
//#include <cstdio>
#include <cstring>
#include <cmath>
#include <bits/stdc++.h>
//#include <cstdlib>
#include<ctime> 

using namespace std ; 

int N , M ; 

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
		if ( flag ) ++res ; 
	}
	return res ; 
}

void init () {
	srand(time(NULL));
	for ( int i = 1 ; i <= N ; i++ ) {
//		int t = rand()%2 ;
//		t -= t == 0 ;  
		state[i] = -1 ; 	
	}
	return ; 
}

const double eps = 1e-8 ;
const double P = 0.9998 ;  

void sa () {
	
	double T = 4 ;
	int oe , ne ; 
	init() ; 
	oe = energy();  
	if ( oe == M ) return ; 
	
	while ( T > eps ) {
		int x = rand()%N+1 ; 
		state[x] *= -1 ; 
		ne = energy() ;
		if ( ne == M ) return ;  
		if ( ne >= oe ) {
			T *= P ; 
			oe = ne ; 
			continue ; 
		}
		else if ( rand() < RAND_MAX * exp( (ne-oe) / T ) ) {//RAND_MAX是一个在<cstdlib>中定义的常量，通常为326767 
			T *= P ; 
			oe = ne ; 
			continue ; 
		}
		else {
			state[x] *= -1 ; 	
			T *= P ; 
		}
	}
	
	return ; 
}


int main () {
//	freopen("testData5.txt","r",stdin);
	N = 300 , M = 300 ; 
//	cin >> N >> M ; 
	for ( int i = 1 ; i <= M ; i++ ) 
		for ( int ii = 1 ; ii <= 3 ; ii++ ) {
			arr[i][ii] = i ;  
//			cin >> arr[i][ii] ; 
		}
					
	sa() ; 
		
	if ( energy() == M ) 	for ( int i = 1 ; i <= N ; i++ ) cout << (state[i]>0) << " "  ; 	
	else cout << "Solve: "<< energy() << " / " << M << endl ; 
	
	return 0 ; 
}
