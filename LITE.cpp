//LITE spoj
//By MD.Imam Hossain Johny
//Dept. ICE, NSTU-11 batch
#include<bits/stdc++.h>
using namespace std;
#define SZ 100005
int arra[SZ];
struct info
{
	int sum;
	int prop;
}tree[SZ*3];
void update(int node,int b,int e,int i,int j)
{
	if(b>j || e<i)
		return ;
	if(b>=i && e<=j)
	{
			tree[node].prop ^=1;
			tree[node].sum=e-b+1-tree[node].sum;
		return ;
	}
	int mid=(b+e)/2;
	int left=(node*2);
	int right=(node*2)+1;
	update(left,b,mid,i,j);
	update(right,mid+1,e,i,j);
	
	if(tree[node].prop)	
		tree[node].sum=e-b+1-tree[left].sum-tree[right].sum;
	else 
		tree[node].sum=tree[left].sum+tree[right].sum;
}

///*
int query(int Node, int ri, int rj, int i, int j) {
	if(i==ri && j==rj) return tree[Node].sum;
	int m = (ri + rj) >> 1, ret, L = Node << 1, R = L + 1;
	if(j <= m) ret = query(L, ri, m, i, j);
	else if(i > m) ret = query(R, m+1, rj, i, j);
	else {
		ret = query(L, ri, m, i, m);
		ret += query(R, m+1, rj, m+1, j);
	}
	if(tree[Node].prop) return j - i + 1 - ret;
	return ret;
}
//*/
/*
int query(int node, int b,int e,int i,int j)
{
	if(b>j || e<i)
		return 0;
	if(b>=i && e<=j)
	{	
		if(tree[node].prop)
			return (j-i+1)-tree[node].sum;
		else
			return tree[node].sum;
	}
	int mid=(b+e)/2;
	int left=(node*2);
	int right=(node*2)+1;
	int p1=query(left,b,mid,i,j);
	int p2=query(right,mid+1,e,i,j);
	
	//if(tree[node].prop) return j-i+1-p1-p2;
	return p1+p2;
}
*/
int main()
{
	memset(arra,0,sizeof arra);
	memset(tree,0,sizeof tree);
	int n,m;
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++)
	{
		int op,s,e,ans;
		scanf("%d%d%d",&op,&s,&e);
		if(!op)
		{
			update(1,1,n,s,e);
		}
		else
		{
			ans=query(1,1,n,s,e);
			printf("%d\n",ans);
		}
	}
	return 0;
}
