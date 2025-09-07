#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
using namespace std;
int partitionR(vector<long long>& a, int l, int r){
    int pivotIndex = l + rand() % (r - l + 1);
    swap(a[pivotIndex], a[r]);
    long long pivot = a[r];
    int i = l - 1;
    for(int j = l; j <= r - 1; ++j){
        if(a[j] <= pivot){
            ++i;
            swap(a[i], a[j]);
        }
    }
    swap(a[i+1], a[r]);
    return i+1;
}
long long randomizedSelect(vector<long long> a, int l, int r, int ith){
    while(true){
        if(l == r) return a[l];
        int q = partitionR(a, l, r);
        int k = q - l + 1;
        if(ith == k) return a[q];
        else if(ith < k) r = q - 1;
        else { ith = ith - k; l = q + 1; }
    }
}
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    srand((unsigned) time(NULL));
    int n;
    if(!(cin >> n)) return 0;
    vector<long long> a(n);
    for(int i = 0; i < n; ++i) cin >> a[i];
    int ith;
    cin >> ith;
    if(ith < 1 || ith > n){ cout << "Invalid i\n"; return 0; }
    cout << randomizedSelect(a, 0, n-1, ith) << "\n";
    return 0;
}
