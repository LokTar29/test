#include <stdio.h>
int judge(int arr[1000][1000],int m,int n,int c,int d)
{
	for(int a=1;a<=n;a++)
		for(int b=1;b<=m;b++)
		{
			int sum1=0,sum2=0;
			for(int a1=0;a1<c;a1++)
			{
				if (n<a+a1) sum1 =1;
				sum1+=arr[a+a1][b];
			}
			for(int b1=0;b1<d;b1++)
			{
				if (m<b+b1) sum1 =1;
				sum1+=arr[a][b+b1];
			}
			if (0 == sum1) return 1;
			for(int a1=0;a1<c;a1++)
			{
				if (n<b+a1) sum2 =1;
				sum2+=arr[a][b+a1];
			}
			for(int b1=0;b1<d;b1++)
			{
				if (m<a+b1) sum2 =1;
				sum2+=arr[a+b1][b];
			}
			if (0 == sum2) return 1;
		}	
	return 0;
}

int main()
{
	int t,c,d,m,n,k,x,y;
	scanf("%d",&t);
	for(int i=0;i<t;i++)
	{
		int arr[1000][1000]={0};
		scanf("%d %d %d",&n,&m,&k);
		for(int j=0;j<k;j++)
		{
			scanf("%d %d",&x,&y);
			arr[x][y] = 1;
		}
		scanf("%d %d",&c,&d);
		printf("%s",judge(arr,m,n,c,d)?"YES":"NO");
	}
}
