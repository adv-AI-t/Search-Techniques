#include<iostream>
#include<vector>

using namespace std;

void selection_sort(vector<int>&arr){

    int n = arr.size();

    int min_idx = 0;

    for(int i=0; i<n-1; i++){
        min_idx = i;
        for(int j=i+1; j<n; j++){
            if(arr[j]<arr[min_idx]) min_idx = j;
        }
        swap(arr[i], arr[min_idx]);
    }
}

int main(){
    vector<int> arr({3, 4, 6, 1, 2, 0, 10, -1});
    selection_sort(arr);
    for(auto item: arr){
        cout<<item<<"  ";
    }
    return 0;
}