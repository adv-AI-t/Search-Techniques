#include<iostream>
#include<vector>

using namespace std;

bool isSafe(int row, int col, vector<vector<int> >board, int n){

    for(int i=0; i<n; i++){
        if(board[row][i] || board[i][col]) return false;
    }

    int x = row;
    int y = col;
    while(x>=0 && y>=0){
        if(board[x][y]) return false;
        x--;
        y--;
    }

    x = row;
    y = col;
    while(x>=0 && y<n){
        if(board[x][y]) return false;
        x--;
        y++;
    }

    x = row;
    y = col;
    while(x<n && y<n){
        if(board[x][y]) return false;
        x++;
        y++;
    }

    x = row;
    y = col;
    while(x<n && y>=0){
        if(board[x][y]) return false;
        x++;
        y--;
    }

    return true;
}

bool solveNQueens(int col, vector<vector<int> >&board, int n){
    if(col == n) return true;

    for(int i=0; i<n; i++){
        if(isSafe(i, col, board, n)){
            
            board[i][col] = 1;

            if(solveNQueens(col+1, board, n)){
                return true;
            }

            board[i][col] = 0;
        }
    }

    return false;
}

void printSolution(vector<vector<int> >&board, int n){
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            cout<<board[i][j]<<" ";
        }
        cout<<endl<<endl;
    }
}

int main(){
    int n;
    cin>>n;

    vector<vector<int> >board;

    for(int i=0; i<n; i++){
        vector<int> row(n, 0);
        board.push_back(row);
    }

    if(solveNQueens(0, board, n)){
        printSolution(board, n);
        return 0;
    }

    return 1;
}