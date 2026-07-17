#include <stdio.h>
int main(){
	int i,j;
	int n;
	int a[100][100];
	scanf("%d",&n);
	for(i=0;i<n;i++)
	{
		for(j=0;j<=i;j++){
			if(j==0||i==j){a[i][j]=1;	}
			else a[i][j]=a[i-1][j]+a[i-1][j-1];
		}
	}
	for(i=0;i<n;i++)
	{
		for(j=0;j<=i;j++){
			printf("%d ",a[i][j]);
		}
		printf("\n");
	}
    return 0;
}