//INVCNT - Inversion Count
//Undefined_Error
//Dept. ICE, NSTU-11 batch
#include<bits/stdc++.h>
using namespace std;
#define sfint(a) scanf("%d",&a)
#define sf2int(a,b) scanf("%d%d",&a,&b)
#define SZ 10000005
#define MX 100000000
long long int tree[SZ]={0};

void update(long long int index,long long int x,int n)
{
	while(index<=n)
	{
		tree[index]+=x;
		index+=(index & (-index));
	}
}
long long int query(long long int index)
{
	long long int sum=0;
	while(index>0)
	{
		sum+=tree[index];
		index-=(index&(-index));
	}
	return sum;
}

int main()
{
	int x;
	sfint(x);
	long long int A[SZ],result;
	for(int t=1;t<=x;t++)
	{
		result=0;
		memset(tree,0,sizeof tree);
		int n;
		sfint(n);
		for(int i=1;i<=n;i++)
		{
			scanf("%lld",&A[i]);
		}
		for(int i=n;i>0;i--)
		{
			result+=query(A[i]);
//			cout<<" A[i] "<<A[i]<<" result "<<result<<endl;
			update(A[i],1,SZ);
		}
		printf("%lld\n",result);
	}
	return 0;
}
