#include <iostream>
#include <vector>

using namespace std;


int win_check(int board[100][100][3], int n, int m){
    int sum = 0;
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            sum = 0;
            if(board[i][j][2] == 1 && board[i][j][1] == 0){
                for(int k=i-1;k>=0;k--){
                    if(board[k][j][2] == 0)
                        sum += board[k][j][0];
                    if(board[k][j][0] == 0)
                        if(sum >= board[i][j][0])
                            return -1;
                        else
                            return 0;
                }
                if(sum != board[i][j][0]){
                    return 0;
                }
            }
            else if(board[i][j][2] == 1 && board[i][j][1] == 1){
                for(int k=j+1;k<m;k++){
                    if(board[i][k][2] == 0)
                        sum += board[i][k][0];
                    if(board[i][k][0] == 0)
                        if(sum >= board[i][j][0])
                            return -1;
                        else
                            return 0;
                }
                if(sum != board[i][j][0]){
                    return 0;
                }
            }
            else if(board[i][j][2] == 1 && board[i][j][1] == 2){
                for(int k=i+1;k<n;k++){
                    if(board[k][j][2] == 0)
                        sum += board[k][j][0];
                    if(board[k][j][0] == 0)
                        if(sum >= board[i][j][0])
                            return -1;
                        else
                            return 0;
                }
                if(sum != board[i][j][0]){
                    return 0;
                }
            }
            else if(board[i][j][2] == 1 && board[i][j][1] == 3){
                for(int k=j-1;k>=0;k--){
                    if(board[i][k][2] == 0)
                        sum += board[i][k][0];
                    if(board[i][k][0] == 0)
                        if(sum >= board[i][j][0])
                            return -1;
                        else
                            return 0;
                }
                if(sum != board[i][j][0]){
                    return 0;
                }
            }

        }
    }
    return 1;
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


bool backtracking(int board[100][100][3], int n, int m){
    int win = win_check(board, n, m);
    if(win == 1){
        return true;
    }else if(win == -1){
        return false;
    }
    int mrv[n][m];
    for(int i=0;i<n;i++)
        for(int j=0;j<m;j++){
            mrv[i][j] = 0;
            if(board[i][j][2] == 0 && board[i][j][0] == 0)
                mrv[i][j] = can_number(board, n, m, i, j).size();                
        }
    
    int x, y;
    while(true){
        int min=10;
        for(int i=0;i<n;i++)
            for(int j=0;j<m;j++){
                if(mrv[i][j] != 0){
                    if(min > mrv[i][j]){
                        x = i;
                        y = j;
                        min = mrv[i][j];
                    }
                }
            }
        
        if(min == 10){
            break;
        }
        vector<int> can = can_number(board, n, m, x, y);
        for(int k=0;k<can.size();k++){
            board[x][y][0] = can[k];
            if(backtracking(board, n, m))
                return true;
            board[x][y][0] = 0;
        }
        mrv[x][y] = 0;
    }
    


    return false;
}


int main(){
    int n,m;
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
            }else{
                board[i][j][2] = -1;
            }
        }
    if(backtracking(board, n, m)){
        for(int i=0;i<n;i++){
            for(int j=0;j<m;j++)
                cout << board[i][j][0] << "\t";
            cout << endl;
        }
    }

}
