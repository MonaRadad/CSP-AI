#include <iostream>
#include <vector>

using namespace std;

bool win_check(int board[100][100][3], int n, int m, bool last){
    int sum = 0;
    bool flag_zero = false;
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            sum = 0;
            flag_zero = false;
            if(board[i][j][2] == 1 && board[i][j][1] == 0){
                for(int k=i-1;k>=0;k--){
                    if(board[k][j][2] == 0)
                        sum += board[k][j][0];
                    if(board[k][j][0] == 0)
                        flag_zero = true;
                }
                if(flag_zero && sum == board[i][j][0])
                    return false;
                else if(sum > board[i][j][0])
                    return false;
                else if(last && sum != board[i][j][0])
                    return false;
            }
            else if(board[i][j][2] == 1 && board[i][j][1] == 1){
                for(int k=j+1;k<m;k++){
                    if(board[i][k][2] == 0)
                        sum += board[i][k][0];
                    if(board[i][k][0] == 0)
                        flag_zero = true;
                }
                if(flag_zero && sum == board[i][j][0])
                    return false;
                else if(sum > board[i][j][0])
                    return false;
                else if(last && sum != board[i][j][0])
                    return false;
            }
            else if(board[i][j][2] == 1 && board[i][j][1] == 2){
                for(int k=i+1;k<n;k++){
                    if(board[k][j][2] == 0)
                        sum += board[k][j][0];
                    if(board[k][j][0] == 0)
                        flag_zero = true;
                }
                if(flag_zero && sum == board[i][j][0])
                    return false;
                else if(sum > board[i][j][0])
                    return false;
                else if(last && sum != board[i][j][0])
                    return false;
            }
            else if(board[i][j][2] == 1 && board[i][j][1] == 3){
                for(int k=j-1;k>=0;k--){
                    if(board[i][k][2] == 0)
                        sum += board[i][k][0];
                    if(board[i][k][0] == 0)
                        flag_zero = true;
                }
                if(flag_zero && sum == board[i][j][0])
                    return false;
                else if(sum > board[i][j][0])
                    return false;
                else if(last && sum != board[i][j][0])
                    return false;
            }

        }
    }
    return true;

}

vector<int> can_number(int board[100][100][3], int n, int m, int pi, int pj){
    int numbers[9] = {1, 2, 3, 4, 5, 6 ,7 ,8 ,9};
    vector<int> out;
    bool flag;
    for(int i=8;i>=0;i--){
        flag = false;
        for(int j=0; j<m; j++){
            if(board[pi][j][2] == 0 && numbers[i] == board[pi][j][0]){
                flag = true;
            }
        }
        if(flag)
            continue;
        for(int j=0; j<n;j++){
            if(board[j][pj][2] == 0 && numbers[i] == board[j][pj][0]){
                flag = true;
            }
        }
        if(flag)
            continue;
        out.push_back(numbers[i]);
    }
    return out;
}


bool backtracking(int board[100][100][3], int n, int m, int dep){
    if(dep == 0 && win_check(board, n, m, true)){
        return true;
    }else if(win_check(board, n, m, false) == false){
        return false;
    }
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            if(board[i][j][2] == 0 && board[i][j][0] == 0){
                vector<int> can = can_number(board, n, m, i, j);
                for(int k=0;k<can.size();k++){
                    board[i][j][0] = can[k];
                    if(backtracking(board, n, m, dep-1))
                        return true;
                    board[i][j][0] = 0;
                }
            }

        }
    }
    return false;
}


int main(){
    int n,m;
    int dep=0;
    int board[100][100][3];
    cin >> n >> m;
    for(int i=0;i<n;i++)
        for(int j=0;j<m;j++){
            cin >> board[i][j][0];
            if(board[i][j][0] > 0){
                cin >> board[i][j][1];
                board[i][j][2] = 1;
            }else if(board[i][j][0] == 0){
                board[i][j][2] = 0;
                dep++;
            }else{
                board[i][j][2] = -1;
            }
        }
    if(backtracking(board, n, m, dep)){
        for(int i=0;i<n;i++){
            for(int j=0;j<m;j++)
                cout << board[i][j][0] << "\t";
            cout << endl;
        }
    }

}
