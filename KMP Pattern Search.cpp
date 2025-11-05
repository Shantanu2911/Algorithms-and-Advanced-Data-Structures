#include <bits/stdc++.h>
using namespace std;

vector<int> lpsBuild(const string& p){
    vector<int> lps(p.size());
    int len=0;
    for(size_t i=1;i<p.size();){
        if(p[i]==p[len]) lps[i++]=++len;
        else if(len) len=lps[len-1];
        else lps[i++]=0;
    }
    return lps;
}

vector<int> kmp(const string& s,const string& p){
    if(p.empty()) return {};
    vector<int> lps=lpsBuild(p), res;
    int i=0,j=0;
    while(i<(int)s.size()){
        if(s[i]==p[j]){ i++; j++; if(j==(int)p.size()){ res.push_back(i-j); j=lps[j-1]; } }
        else if(j) j=lps[j-1];
        else i++;
    }
    return res;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    string s,p;
    getline(cin,s);
    getline(cin,p);
    auto pos=kmp(s,p);
    for(size_t i=0;i<pos.size();i++){
        if(i) cout<<" ";
        cout<<pos[i];
    }
    if(pos.empty()) cout<<"-1";
    cout<<"\n";
    return 0;
}
