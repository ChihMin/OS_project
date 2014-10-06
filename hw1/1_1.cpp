#include <cstdio>
#include <cstdlib>

using namespace std;

int main(){
	int s[100] ; 
	int n ; 
	scanf("%d", &n) ; 

	for(int i=0;i<n;++i)
		scanf("%d",&s[i]);

	for(int i=n-1;i>=0;--i)
		printf("%d\n",s[i]); 
	

	return 0 ; 
}
