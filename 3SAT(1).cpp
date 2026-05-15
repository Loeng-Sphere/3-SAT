// 3sat

#include <iostream>
//#include <cstdio>
#include <cstring>
#include <cmath>
#include <bits/stdc++.h>
//#include <cstdlib>
#include<ctime> 
// #include <vector>  

using namespace std ; 

int N , M ; 

int arr[1600000][5] ; 
int state[500000] ; 
vector <int> loc[500000] ; 
// vector <int> v ; 

bool equal ( int i  ) {
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
	return flag ; 
}

int energy () { // O(3*M)
	int res = 0 ; 
	for ( int i = 1 ; i <= M ; i++ ) 
		if ( equal(i) ) res++ ; 
	return res ; 
}

int delta ( int x ) { // O ( 3*m/n ) ~ O(1) 
	int res = 0 , r1 = 0 , r2 = 0 ; 
	for ( int y = 0 ; y < loc[x].size() ; y++ ) {
		int i = loc[x][y] ; 
		r1 += ( equal(i) == true ) ; 
	}
	state[x] *= -1 ; 
	for ( int y = 0 ; y < loc[x].size() ; y++ ) {
		int i = loc[x][y] ; 
		r2 += ( equal(i) == true ) ; 
	}
	state[x] *= -1 ; 
	res = r2 - r1 ; 
	return res ; 
}

void init () {
	for ( int i = 1 ; i <= N ; i++ ) {
		sort( loc[i].begin() , loc[i].end() ) ; 
		loc[i].erase(unique( loc[i].begin() , loc[i].end() ) , loc[i].end() ); 
		int t = rand()%2 ;
		if(t==0) t=-1;
		state[i] = 1 ; 	
	}
	return ; 
}

const double eps = 1e-8 ;
const double P = 0.9998 ;  

void sa () {
	
	double T = 4 ;//Nmax=85000;
	int oe , ne ; 
//	init() ; 
	oe = energy();  
	if ( oe == M ) return ; 
	int tt = 0 ; 
	cout << int( 100*N*log(N) ) << endl ; 
	for ( int i = 1 ; i <= int( 100*N*log(N) ); i++ ) {
		++tt ; 
		int x = rand()*rand()%N+1 ; 
		ne = oe + delta(x) ; 
		if ( ne == M ) {
			state[x] *= -1 ; 
			return ;
		}  
		if ( ne >= oe ) {
			oe = ne ; 
			state[x] *= -1 ; 
			T *= P ; 
		}
		else if ( rand() < RAND_MAX * exp( (ne-oe) / T ) ) {//RAND_MAX是一个在<cstdlib>中定义的常量，通常为326767 
			oe = ne ; 
			state[x] *= -1 ; 
			T *= P ; 
		}
		else 	T *= P ; 
	}
//	cout << "QAQ" << endl ; 
	return ; 
}

// 3*M*2*NlogN ~ 24 N^2 log N
// 96Nlog N 


int main () {
//	freopen("testData5.txt","r",stdin);
//	cin >> N >> M ; 
	srand(time(NULL)); 
	N = 1E5 ; M = N ; 
	for ( int i = 1 ; i <= M ; i++ ) 
		for ( int ii = 1 ; ii <= 3 ; ii++ ) {
			int t = rand()*rand()%N+1 ; 
			int sgn = rand()*rand()%2 ; 
			sgn -= sgn==0 ; 
			
			t = i ; 
			sgn = -1 ; 
			loc[t].push_back(i) ; 
			arr[i][ii] = t*sgn ; 
//			cin >> arr[i][ii] ; 
//			loc[abs(arr[i][ii])].push_back(i) ; 
		}

	init() ; 		
	sa() ;
	
	if ( energy() == M ) 	 for ( int i = 1 ; i <= N ; i++ ) 	  cout << (state[i]>0) << " "  ; 	
	else cout << "Solve: "<< energy() << " / " << M << endl ; 
	
	return 0 ; 
}
