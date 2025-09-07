#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
using namespace std;
long long compCount;
int partitionR(vector<long long>& a, int l, int r){
    int pivotIndex = l + rand() % (r - l + 1);
    swap(a[pivotIndex], a[r]);
    long long pivot = a[r];
    int i = l - 1;
    for(int j = l; j <= r - 1; ++j){
        ++compCount;
        if(a[j] <= pivot){
            ++i;
            swap(a[i], a[j]);
        }
    }
    swap(a[i+1], a[r]);
    return i+1;
}
void randQuick(vector<long long>& a, int l, int r){
    if(l < r){
        int p = partitionR(a, l, r);
        randQuick(a, l, p-1);
        randQuick(a, p+1, r);
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
    compCount = 0;
    if(n > 0) randQuick(a, 0, n-1);
    for(int i = 0; i < n; ++i){
        if(i) cout << ' ';
        cout << a[i];
    }
    cout << "\n" << compCount << "\n";
    return 0;
}
