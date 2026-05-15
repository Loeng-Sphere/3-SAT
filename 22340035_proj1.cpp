// 3sat
//贪心+退火+partial Energy 
#include <iostream>
//#include <cstdio>
#include <cstring>
#include <cmath>
#include <bits/stdc++.h>
//#include <cstdlib>
#include<ctime> 
using namespace std ; 

template <class T>
class VecList{
    private:
        int capacity;
        int length;
        T* arr;
        void doubleListSize(){
            T * oldArr = arr;
            arr = new T[2*capacity];
            capacity = 2 * capacity;
            for(int i=0;i<length;i++){
                arr[i] = oldArr[i];
            }
            delete [] oldArr;
        }
    public:
        VecList(){
            length = 0;
            capacity = 100;
            arr = new T[capacity];
        }
        VecList(T* a, int n){
            length = n;
            capacity = 100 + 2*n;
            arr = new T[capacity];
            for(int i=0;i<n;i++){
                arr[i] = a[i];
            }
        }
        ~VecList(){
            delete [] arr;
        }
        int getLength(){
            return length;
        }
        bool isEmpty(){
            return length==0;
        }
        void insertEleAtPos(int i, T x){
            if(length==capacity)
                doubleListSize();
            if(i > length || i < 0)
                throw "Illegal position";
            for(int j=length;j>i;j--)
                arr[j] = arr[j-1];
            arr[i] = x;
            length++;
        } 
        T deleteEleAtPos(int i){
            if(i >= length || i < 0)
                throw "Illegal position";
            T tmp = arr[i];
            for(int j=i;j<length-1;j++)
                arr[j] = arr[j+1];
            length--;
            return tmp;
        }
        void setEleAtPos(int i, T x){
            if(i >= length || i < 0)
                throw "Illegal position";
            arr[i] = x;
        }
        T getEleAtPos(int i){
            if(i >= length || i < 0)
                throw "Illegal position";
            return arr[i];
        }
        int locateEle(T x){
            for(int i=0;i<length;i++){
                if(arr[i]==x)
                    return i;
            }
            return -1;
        }
        void printList(){
            for(int i=0;i<length;i++)
                cout << arr[i] << " ";
        }
};

int N , M,times,loop=0 ; 

int arr[1300][5] ; 
int state[1300] ; 
VecList<VecList<int>* > V;

int energy () {
	int sum = 0 ; 
	for ( int i = 1 ; i <= M ; i++ ) {
		bool flag = false ; 
		for ( int j = 1 ; j <= 3 ; j++){
			int t = arr[i][j] ; 
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
		if ( flag ) sum++ ; 
	}
	return sum ; 
}

int EX(int x)//Energy with respect to X
{
	int sum=0;
	for(int i=0;i<V.getEleAtPos(x)->getLength();i++)
	{
		int ii=V.getEleAtPos(x)->getEleAtPos(i);
		bool flag = false ; 
		for ( int j = 1 ; j <= 3 ; j++){
			int t = arr[ii][j] ; 
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
		if ( flag ) sum++ ; 
	}
	return sum;
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
	int oe,nex,oex; 
	init() ; 
	oe = energy();  
	if ( oe == M ) return ; 
	int x; 
	times=0;
	for(int count=0;count<50*N*log(N);count++){
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
 		}//生成等概率的数据 ,并随机一个x改变它的bool值 
 		//从这里开始计算旧的x相关的命题的真命题数 
 		oex=EX(x);
// 		cout<<x<<":"<<oex<<endl;
		state[x] *= -1 ; 
		nex=EX(x);
//			cout<<x<<":"<<nex<<endl;
		if ( oe+nex-oex == M ) return ;  
		if ( nex >= oex ) {
			T *= P ; 
			oe = oe+nex-oex ; 
			continue ; 
		}
		else if (times>2*N*log(N)&&rand() < RAND_MAX * exp( (nex-oex) / T ) ) {//RAND_MAX是一个在<cstdlib>中定义的常量，通常为326767 
			T *= P ; 
			oe = oe+nex-oex ; 
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
	freopen("testData.txt","r",stdin);
	cin >> N >> M ; 
	for(int i=0;i<=N;i++)
	{
		V.insertEleAtPos(i,new VecList<int>());
	}
	for ( int i = 1 ; i <= M ; i++ ) 
		for ( int j = 1 ; j <= 3 ; j++ ) {
			cin >> arr[i][j] ; 
			V.getEleAtPos(abs(arr[i][j]))->insertEleAtPos(V.getEleAtPos(abs(arr[i][j]))->getLength(),i);
		}
	for(int i=0;;i++) 
	{				
	sa() ; 
	if ( energy() == M ) 	
	{
//    cout<<  "times:"<<times<<endl;
	 for ( int i = 1 ; i <= N ; i++ ) 
	  cout<<(state[i]>0) << " "  ; 
	  cout<<endl;
	  break;
	}	
//	else cout << "times:"<<times<<"   Solve: "<< energy() << " / " << M << endl ; 
   }
//    for(int i=1;i<=5;i++)
//    {
//    	cout<<E_wrt_X(i)<<endl;
//	}
//	
	return 0 ; 
}
