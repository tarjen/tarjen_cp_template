#include <bits/stdc++.h>
 
using namespace std;
typedef pair<int,int> pii;
const int N = 1010;
const int M = N*N;
int _w;
 
int n, m;
 
namespace G {
	int head[N], nxt[M], to[M], tot;
	void init() {
		tot = 0;
		memset(head, -1, sizeof head);
	}
	void link( int u, int v ) {
		to[tot] = v, nxt[tot] = head[u], head[u] = tot++;
		to[tot] = u, nxt[tot] = head[v], head[v] = tot++;
	}
}
 
///vertex
namespace VBCC {
	int dfn[N], dfs_clock, low[N], bcc_cnt, iscut[N];
	vector<int> bcc[N];
	set<int> bccno[N];
	stack<pii> stk;
	int bcc_edge[N];
 
	void dfs( int u, int fa ) {
		using namespace G;
		low[u] = dfn[u] = ++dfs_clock;
		int child = 0;
		for( int e = head[u]; ~e; e = nxt[e] ) {
			int v = to[e];
			if( v == fa ) continue;
			if( !dfn[v] ) {
				stk.push( pii(u, v) );
				dfs(v, u);
				++child;
				low[u] = min( low[u], low[v] );
				if( low[v] >= dfn[u] ) {
					iscut[u] = true;
					++bcc_cnt;
					bcc[bcc_cnt].clear();
					while(1) {
						pii e = stk.top(); stk.pop();
						++bcc_edge[bcc_cnt];
						if( bccno[e.first].count(bcc_cnt) == 0 ) {
							bccno[e.first].insert(bcc_cnt);
							bcc[bcc_cnt].push_back(e.first);
						}
						if( bccno[e.second].count(bcc_cnt) == 0 ) {
							bccno[e.second].insert(bcc_cnt);
							bcc[bcc_cnt].push_back(e.second);
						}
						if( e.first == u && e.second == v ) break;
					}
				}
			} else if( dfn[v] < dfn[u] ) {
				stk.push( pii(u, v) );
				low[u] = min( low[u], dfn[v] );
			}
		}
		if( fa == -1 && child == 1 ) iscut[u] = false;
	}
	void find_bcc() {
		memset(dfn, 0, sizeof dfn);
		dfs_clock = 0;
		for( int i = 0; i < N; ++i )
			bccno[i].clear();
		bcc_cnt = 0;
		memset(iscut, 0, sizeof iscut);
		memset(bcc_edge, 0, sizeof bcc_edge);
		for( int i = 1; i <= n; ++i )
			if( !dfn[i] )
				dfs(i, -1);
	}
}
 
///edge
namespace EBCC {
	int dfn[N], low[N], dfs_clock, bcc_cnt, bccno[N];
	stack<int> stk;
 
	void dfs( int u, int fa ) {
		using namespace G;
		dfn[u] = low[u] = ++dfs_clock;
		stk.push(u);
		for( int e = head[u]; ~e; e = nxt[e] ) {
			int v = to[e];
			if( v == fa ) continue;
			if( dfn[v] ) {
				low[u] = min( low[u], dfn[v] );
			} else {
				dfs(v, u);
				low[u] = min( low[u], low[v] );
			}
		}
		if( low[u] >= dfn[u] ) {
			++bcc_cnt;
			while(1) {
				int nod = stk.top(); stk.pop();
				bccno[nod] = bcc_cnt;
				if( nod == u ) break;
			}
		}
	}
	void find_bcc() {
		memset(dfn, 0, sizeof dfn);
		memset(low, 0, sizeof low);
		dfs_clock = bcc_cnt = 0;
		memset(bccno, 0, sizeof bccno);
		for( int i = 1; i <= n; ++i )
			if( !dfn[i] )
				dfs(1, -1);
	}
}
 
void cnode() {
	int ans = 0;
	for( int i = 1; i <= n; ++i )
		ans += (int)VBCC::iscut[i];
	printf( "%d ", ans );
}
 
void clink() {
	printf( "%d ", EBCC::bcc_cnt-1 );
}
 
int number_comp() {
	using namespace VBCC;
	return bcc_cnt;
}
 
int large_comp() {
	using namespace VBCC;
	int ans = 0;
	for( int i = 1; i <= bcc_cnt; ++i )
		ans = max(ans, bcc_edge[i]);
	return ans;
}
 
int main() {
	int T;
	_w = scanf( "%d", &T );
	while( T-- ) {
		_w = scanf( "%d%d", &n, &m );
		G::init();
		for( int i = 0; i < m; ++i ) {
			int u, v;
			_w = scanf( "%d%d", &u, &v );
			G::link(u, v);
		}
		VBCC::find_bcc();
		EBCC::find_bcc();
		cnode();
		clink();
		int p = number_comp();
		int q = large_comp();
		int g = __gcd(p, q);
		if( g != 0 ) p /= g, q /= g;
		printf( "%d %d\n", p, q );
	}
	return 0;
}