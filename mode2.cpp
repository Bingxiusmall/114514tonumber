#include<bits/stdc++.h>
using namespace std;
int n=6,a[]={1,1,4,5,1,4},s[6][6],e;
string w;
struct Node{
	int val;
	string expr;
	bool opt;
	inline bool operator<(const Node &other) const{return val<other.val;}
};
map<int,Node> tmp;
set<Node> dp[6][6];
int main(){
	freopen("mode2.txt","w",stdout);
	cout<<"Use 114514+-*() (operators are optional)\n";
	for(int i=0;i<n;++i) s[i][i]=a[i],dp[i][i].insert((Node){a[i],to_string(a[i]),a[i]<0}),a[i]&&(dp[i][i].insert((Node){-a[i],a[i]<0?"-("+to_string(a[i])+")":"-"+to_string(a[i]),1}),0);
	for(int i=0;i<n;++i) for(int j=i+1;j<n;++j) s[i][j]=s[i][j-1]*10+a[j];
	for(int i=1;i<n;++i) for(int l=0,r=i;r<n;++l,++r){
		tmp.clear(),tmp[s[l][r]]=(Node){s[l][r],to_string(s[l][r]),s[l][r]<0},s[l][r]&&(tmp[-s[l][r]]=(Node){-s[l][r],s[l][r]<0?"-("+to_string(s[l][r])+")":"-"+to_string(s[l][r]),1},0);
		for(int k=l;k<r;++k) for(Node u:dp[l][k]) for(Node v:dp[k+1][r]) w=(v.expr[0]=='-'?u.expr+v.expr:u.expr+'+'+v.expr),e=u.val+v.val,(tmp.find(e)==tmp.end()||w.length()<tmp[e].expr.length())&&(tmp[e]=(Node){e,w,1},0),(tmp.find(-e)==tmp.end()||w.length()+3<tmp[-e].expr.length())&&(tmp[-e]=(Node){-e,"-("+w+")",1},0),w=(u.opt?"("+u.expr+")":u.expr)+"×"+(v.opt?"("+v.expr+")":v.expr),e=u.val*v.val,(tmp.find(e)==tmp.end()||w.length()<tmp[e].expr.length())&&(tmp[e]=(Node){e,w},0);
		for(auto p:tmp) dp[l][r].insert(p.second);
	}
	for(Node ans:dp[0][n-1]) if(ans.val>0) cout<<ans.val<<'='<<ans.expr<<'\n';
	return 0;
}
