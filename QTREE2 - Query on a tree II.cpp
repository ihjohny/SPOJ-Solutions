//QTREE2 - Query on a tree II
//By MD.Imam Hossain Johny
//Dept. ICE, NSTU-11 batch
#include<bits/stdc++.h>
using namespace std;
#define SZ 100005
#define MX 100000000

int parent[SZ];
int level[SZ];
int dista[SZ];
int sp_table[SZ][22];
vector<pair<int,int> > gp[SZ];

void dfs(int from,int u,int lev,int di)
{
	parent[u]=from;
	level[u]=lev;
	dista[u]=dista[from]+di;
	for(int i=0;i<(int)gp[u].size();i++)
	{
		int v=gp[u][i].first;
		int d=gp[u][i].second;
		if(v==from) continue;
		dfs(u,v,lev+1,d);
	}
}

void lca_init(int N)
{
	memset(sp_table,-1,sizeof sp_table);
	for(int i=1;i<N;i++)
	{
		sp_table[i][0]=parent[i];
	}
	for(int j=1;(1<<j)<N;j++)
	{
		for(int i=1;i<N;i++)
		{
			if(sp_table[i][j-1]!=-1)
				sp_table[i][j]=sp_table[sp_table[i][j-1]][j-1];
		}
	}
}
 
int lca_query(int p, int q)
{
	int temp,log;
	if(level[p]<level[q])
	{
		temp=p;
		p=q;
		q=temp;
	}
	log=1;
	while(1)
	{
		int next=log+1;
		if((1<<next) > level[p]) break;
		log++;
	}
	
	for(int i=log;i>=0;i--)
	{
		if(level[p]-(1<<i)>=level[q])
				p=sp_table[p][i];
	}
	if(p==q)
		return p;
	for(int i=log;i>=0;i--)
	{
		if( sp_table[p][i]!=-1 && sp_table[p][i] != sp_table[q][i])
			p=sp_table[p][i],q=sp_table[q][i];
	}
	return parent[p];
}


int kth(int p,int q,int k)
{
	int lca=lca_query(p,q),d;
	if(p==lca)
	{
		d=level[q]-level[p]+1;
		k=d-k+1;
		int tmp;tmp=p;p=q;q=tmp;
	}
	else if(q==lca);
	else
	{
		if(level[p]-level[lca]+1 <k)
		{
			d=level[p]+level[q]-2*(level[lca])+1;
			k=d-k+1;
			int tmp;tmp=p;p=q;q=tmp;
		}
		else;
	}
	int log=1;
	for(log=1;(1<<log)<=level[p];log++);
	log--;k--;
	for(int i=log;i>=0;i--) 
	{
		if((1<<i)<=k)
		{
			p=sp_table[p][i];
			k-=(1<<i);
		}
	}
	return p;
}

int main()
{
	int x;
	scanf("%d",&x);
	for(int t=1;t<=x;t++)
	{
		memset(parent,0,sizeof parent);
		memset(level,0,sizeof level);
		memset(dista,0,sizeof dista);
		memset(gp,0,sizeof gp);
		
		int n,u,v,c;
		long long int ans=0;
		char str[SZ];
		scanf("%d",&n);
		for(int i=1;i<n;i++)
		{
			scanf("%d%d%d",&u,&v,&c);
			gp[u].push_back(make_pair(v,c));
		}
		dfs(1,1,0,0);
		lca_init(n+1);
		
		while(1)
		{
			scanf("%s",str);
			if(!strcmp(str,"DONE")) break;
			else if(!strcmp(str,"DIST"))
			{
				scanf("%d%d",&u,&v);
				int L=lca_query(u,v);
				ans=dista[u]+dista[v]-2*dista[L];
				printf("%lld\n",ans);
			}
			else
			{
				scanf("%d%d%d",&u,&v,&c);
				ans=kth(u,v,c);
				printf("%lld\n",ans);
			}
		} 
	}
	return 0;
}
