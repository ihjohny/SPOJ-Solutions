//MULTQ3 - Multiples of 3
//Undefined_Error
//Dept. ICE, NSTU-11 batch
#include<bits/stdc++.h>
using namespace std;
#define sfint(a) scanf("%d",&a)
#define sf2int(a,b) scanf("%d%d",&a,&b)
#define sf3int(a,b,c) scanf("%d%d%d",&a,&b,&c)
#define ll long long 
#define SZ 100005
#define MX 100000000
struct info
{
	int prop;
	int sum[3];
	info()
	{
		prop=0;
		sum[0]=0;
		sum[1]=0;
		sum[2]=0;
	}
}tree[SZ*3];


void init(int node,int b,int e)
{
	if(b==e)
	{
		tree[node].sum[0]=1;
		return ;
	}
	int mid=(b+e)/2;
	int left=(node*2);
	int right=(node*2)+1;
	init(left,b,mid);
	init(right,mid+1,e);
	
	tree[node].sum[0]=tree[left].sum[0]+tree[right].sum[0];
	
}

void toggle(int node)
{
			int tmp=tree[node].sum[0];
			tree[node].sum[0]=tree[node].sum[2];
			tree[node].sum[2]=tree[node].sum[1];
			tree[node].sum[1]=tmp;
			return ;
}

void update(int node,int b,int e,int i,int j,int value)
{
	if(i>e || j<b)
		return;
	if(b>=i && e<=j)
	{
		tree[node].prop+=value;
		swap(tree[node].sum[0], tree[node].sum[1]);
		swap(tree[node].sum[0], tree[node].sum[2]);
		return;
	}
	int left=node*2;
	int right=(node*2)+1;
	int mid=(b+e)/2;
	

	update(left,b,mid,i,j,value);
	update(right,mid+1,e,i,j,value);
	
	tree[node].sum[1]=tree[left].sum[1]+tree[right].sum[1];
	tree[node].sum[2]=tree[left].sum[2]+tree[right].sum[2];
	tree[node].sum[0]=tree[left].sum[0]+tree[right].sum[0];
	
	switch(tree[node].prop % 3) {
		case 1:
			swap(tree[node].sum[0], tree[node].sum[1]);
			swap(tree[node].sum[0], tree[node].sum[2]);
		break;
		case 2:
			swap(tree[node].sum[0], tree[node].sum[1]);
			swap(tree[node].sum[1], tree[node].sum[2]);
		break;
	}
	
	return ;
}

int query(int node,int b,int e,int i,int j,int carry=0)
{
	if(i>e || j<b) return 0;
	if(b>=i && e<=j)
	{

		switch(carry % 3) {
			case 0: return tree[node].sum[0];
			case 1: return tree[node].sum[2];
			case 2: return tree[node].sum[1];
		}
		return 0; 
	}
	
	int Left = node << 1;
    int Right = (node << 1) + 1;
    int mid = (b + e) >> 1;
    
    int p1 = query(Left, b, mid, i, j,carry+tree[node].prop);
    int p2 = query(Right, mid + 1, e, i, j,carry+tree[node].prop);
    
    return p1+p2;
}

int main()
{
		int n,q,choice,i,j;
		sf2int(n,q);
		memset(tree,0,sizeof tree);
		init(1,1,n);
		for(int ii=0;ii<q;ii++)
		{
			sf3int(choice,i,j);
			if(!choice)
			{
				//update
				update(1,1,n,i+1,j+1,1);
			}
			else
			{
				//ans
				int ans=query(1,1,n,i+1,j+1);
				printf("%d\n",ans);
			}
		}
	return 0;
}
