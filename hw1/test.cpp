#include <cstdio>
#include <cstdlib>

using namespace std;

void dfs( int step ){
	dfs( step + 1 ) ;
}

int main(){

	int n = 5 ;
	//scanf("%d",&n) ; 
	for(int i=0;i<n;++i){
		printf("%d\n",i);
	}
	dfs( 0 ) ;


	return 0; 
}
