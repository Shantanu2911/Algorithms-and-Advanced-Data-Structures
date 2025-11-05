#include <bits/stdc++.h>
using namespace std;

struct Node{
    unordered_map<char, Node*> nxt;
    bool end=false;
};

struct SuffixTrie{
    Node* root=new Node();
    void insertSuffixes(const string& s){
        string t=s+"$";
        for(size_t i=0;i<t.size();i++){
            Node* cur=root;
            for(size_t j=i;j<t.size();j++){
                char ch=t[j];
                if(!cur->nxt.count(ch)) cur->nxt[ch]=new Node();
                cur=cur->nxt[ch];
            }
            cur->end=true;
        }
    }
    bool contains(const string& p){
        Node* cur=root;
        for(char ch: p){
            if(!cur->nxt.count(ch)) return false;
            cur=cur->nxt[ch];
        }
        return true;
    }
    vector<int> findAll(const string& s,const string& p){
        vector<int> res;
        for(int i=0;i+(int)p.size()<= (int)s.size();i++){
            bool ok=true;
            for(int j=0;j<(int)p.size();j++) if(s[i+j]!=p[j]){ ok=false; break; }
            if(ok) res.push_back(i);
        }
        return res;
    }
};

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    string s; getline(cin,s);
    SuffixTrie st;
    st.insertSuffixes(s);
    int q; cin>>q; cin.ignore();
    while(q--){
        string p; getline(cin,p);
        cout<<(st.contains(p)?"YES":"NO")<<"\n";
        auto pos=st.findAll(s,p);
        if(pos.empty()) cout<<"-1\n";
        else{
            for(size_t i=0;i<pos.size();i++){ if(i) cout<<" "; cout<<pos[i]; }
            cout<<"\n";
        }
    }
    return 0;
}
