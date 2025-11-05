#include <bits/stdc++.h>
using namespace std;

struct BTreeNode{
    int t;
    bool leaf;
    vector<int> keys;
    vector<BTreeNode*> c;
    BTreeNode(int _t,bool _leaf):t(_t),leaf(_leaf){}
    BTreeNode* search(int k){
        int i=lower_bound(keys.begin(),keys.end(),k)-keys.begin();
        if(i<keys.size() && keys[i]==k) return this;
        if(leaf) return nullptr;
        return c[i]->search(k);
    }
    void splitChild(int i, BTreeNode* y){
        BTreeNode* z=new BTreeNode(y->t,y->leaf);
        int t=y->t;
        for(int j=0;j<t-1;j++) z->keys.push_back(y->keys[j+t]);
        if(!y->leaf) for(int j=0;j<t;j++) z->c.push_back(y->c[j+t]);
        int mid=y->keys[t-1];
        y->keys.resize(t-1);
        if(!y->leaf) y->c.resize(t);
        c.insert(c.begin()+i+1,z);
        keys.insert(keys.begin()+i,mid);
    }
    void insertNonFull(int k){
        int i=keys.size()-1;
        if(leaf){
            keys.insert(upper_bound(keys.begin(),keys.end(),k),k);
        }else{
            while(i>=0 && k<keys[i]) i--;
            i++;
            if((int)c[i]->keys.size()==2*t-1){
                splitChild(i,c[i]);
                if(k>keys[i]) i++;
            }
            c[i]->insertNonFull(k);
        }
    }
    void traverse(){
        int i;
        for(i=0;i<keys.size();i++){
            if(!leaf) c[i]->traverse();
            cout<<keys[i]<<" ";
        }
        if(!leaf) c[i]->traverse();
    }
};

struct BTree{
    BTreeNode* root=nullptr;
    int t;
    BTree(int _t):t(_t){}
    BTreeNode* search(int k){ return root?root->search(k):nullptr; }
    void insert(int k){
        if(!root){
            root=new BTreeNode(t,true);
            root->keys.push_back(k);
            return;
        }
        if((int)root->keys.size()==2*t-1){
            BTreeNode* s=new BTreeNode(t,false);
            s->c.push_back(root);
            s->splitChild(0,root);
            int i= (k>s->keys[0])?1:0;
            s->c[i]->insertNonFull(k);
            root=s;
        }else root->insertNonFull(k);
    }
    void traverse(){ if(root) root->traverse(); cout<<"\n"; }
};

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t; cin>>t;
    BTree bt(t);
    int n; cin>>n;
    for(int i=0;i<n;i++){ int x; cin>>x; bt.insert(x); }
    bt.traverse();
    int q; cin>>q;
    while(q--){
        int k; cin>>k;
        cout<<(bt.search(k)?"FOUND":"NOTFOUND")<<"\n";
    }
    return 0;
}
