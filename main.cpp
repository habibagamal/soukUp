#define m1 -1 //metal 1
#define m2 -2 //metal 2
#define m3 -3 //metal 3
#define v12 -4 //via m1-m2
#define v23 -5 //via m2-m3
#define v123 -6 //via m1-m2-m3

#include <iostream>
#include <vector>
#include <math.h>
using namespace std;
int x, y;

struct coord{int x; int y; int z;};

void printMatrix (vector<vector<int>> m, int x, int y);
coord traverse(vector <vector<int>> l, vector<vector<int>> &m, int x, int y, coord s, coord t);
void noFlooding (vector <vector<int>> l1, vector <vector<int>> l2, vector <vector<int>> l3, vector<vector<int>> &m, int x, int y, coord newSource, coord target);
void flood(vector<vector<int>> &l1, vector<vector<int>> &l12, vector<vector<int>> &l3, int x, int y, coord newSource, coord target, int via);
void backTracking(vector<vector<int>> &l1, vector<vector<int>> &l12, vector<vector<int>> &l3, int x, int y, coord newSource, coord target, int via);

int main(){
    //getting the input dimensions
    cout << "Please enter the y-dimension of the plane\n";
    cin >> x;
    cout << "Please enter the x-dimension of the plane\n";
    cin >> y;

    //initializations
    vector <int> rows(y);
    vector <vector <int>> l1(x,rows); //layer 1
    vector <vector <int>> l2(x,rows); //layer 2
    vector <vector <int>> l3(x,rows); //layer 3
    vector <vector <int>> m(x, rows);
    
    for (int i = 0; i<x; i++){
        for (int j = 0; j<y; j++){
            l1[i][j] = 0;
        }
    }
    
    l2 = l1;
    l3 = l1;
    m = l1;
    coord source, target;
    cout << "sx, sy, sz"<<endl;
    cin >> source.x >> source.y >> source.z;
    cout << "tx, ty, tz"<<endl;
    cin >> target.x >> target.y >> target.z;
    coord newSource;
    switch (source.z){
        case(1): newSource = traverse(l1, m, x, y, source, target);
            break;
        case (2): newSource = traverse(l2, m, x, y, source, target);
            break;
        case (3): newSource = traverse(l3, m, x, y, source, target);
            break;
    }
    newSource.z = ((newSource.z) % 3 )+ 1;
    cout << "New source is " << newSource.x << " " << newSource.y << " " << newSource.z << endl;
    flood(l1, l2, l3, x, y, newSource, target, 10);
    return 0;
}

void printMatrix (vector<vector<int>> m, int x, int y){
    for (int i = 0; i<x; i++){
        for (int j = 0; j<y; j++){
            cout <<m[i][j] << "\t";
        }
        cout << endl;
    }
}

coord traverse(vector <vector<int>> l, vector<vector<int>> &m, int x, int y, coord s, coord t){
    //vertical
    coord newSource;
    if (s.z  == 2){
        m[s.x][s.y] = -s.z;
        if (t.x > s.x){
            for (int i = s.x + 1; i<=t.x; i++){
                if (l[i][s.y] == 0)
                    m[i][s.y] = - s.z;
                else{
                    newSource.x = i;
                    newSource.y = s.y;
                    newSource.z = s.z;
                    return newSource;
                }
            }
        }
        else {
            for (int i = s.x + 1; i>=t.x; i--){
                if (l[i][s.y] == 0)
                    m[i][s.y] = - s.z;
                else{
//                    coord newSource;
                    newSource.x = i;
                    newSource.y = s.y;
                    newSource.z = s.z;
                    return newSource;
                }
            }
        }
        newSource.x = t.x;
        newSource.y = s.y;
        newSource.z = s.z;
    }
    //horizontal
    else{
        m[s.x][s.y] = -s.z;
        if (t.y > s.y){
            for (int j = s.y + 1; j <= t.y; j++){
                if (l[s.x][j] == 0)
                    m[s.x][j] = - s.z;
                else{
//                    coord newSource;
                    newSource.x = s.x;
                    newSource.y = j;
                    newSource.z = s.z;
                    return newSource;
                }
            }
        }
        else {
            for (int j = s.y + 1; j >= t.y; j--){
                if (l[s.x][j] == 0)
                    m[s.x][j] = - s.z;
                else{
//                    coord newSource;
                    newSource.x = s.x;
                    newSource.y = j;
                    newSource.z = s.z;
                    return newSource;
                }
            }
        }
        newSource.x = s.x;
        newSource.y = t.y;
        newSource.z = s.z;
    }
//    coord newSource;
//    newSource.x = newSource.y = newSource.z = -100;
    return newSource;
}

void noFlooding (vector<vector<int>> l1, vector<vector<int>> l2, vector<vector<int>> l3, vector<vector<int>> &m, int x, int y, coord newSource, coord target){
    int count = 0;
    while (count < 3){
        switch(newSource.z){
            case 1: newSource = traverse(l1, m, x, y, newSource, target);
                break;
            case 2:newSource = traverse(l2, m, x, y, newSource, target);
                break;
            case 3:
                newSource = traverse(l3, m, x, y, newSource, target);
                break;
            default:
                break;
        }
        printMatrix (m, x, y );
        cout << endl << endl;
        cout << newSource.x << endl;
        cout << newSource.y << endl;
        newSource.z = ((newSource.z) % 3 )+ 1;
        cout << newSource.z << endl;
        cout << endl << endl;
        count ++;
    }
}

void flood(vector<vector<int>> &l1, vector<vector<int>> &l2, vector<vector<int>> &l3, int x, int y, coord newSource, coord target, int via){
    int count = 1;
    bool done1, done2, done3 = true;
    bool done = false;
    switch(newSource.z){
        case (1):
            l1[newSource.x][newSource.y] = count;
            break;
        case (2):
            l2[newSource.x][newSource.y] = count;
            break;
        case (3):
            l3[newSource.x][newSource.y] = count;
            break;
    }
    while (!done && (count < (x+y+2*via))){
        done1 = true; done2 = true; done3 = true;
        done = false;
                for (int i=0; i<x; i++){
                    for (int j = 0; j<y; j++){
                        if (l1[j][i] == count){
                            done1 = false;
                            if(l2[j][i] == 0){
                                l2[j][i] = count + via;
                                if((j == target.x) && (i == target.y) && (target.z == 2))
                                    done = true;
                            }
                            if(l3[j][i] == 0){
                                if((j == target.x) && (i == target.y) && (target.z == 3))
                                    done = true;
                                l3[j][i] = count + 2 * via;
                            }
                            if((i+1<y) && (l1[j][i+1] == 0)){
                                l1[j][i+1] = count+1;
                                if((j == target.x) && ((i+1) == target.y) && (target.z == 1))
                                    done = true;
                            }
                            if((i-1>=0) && (l1[j][i-1] == 0)){
                                l1[j][i-1] = count+1;
                                if((j == target.x) && ((i-1) == target.y) && (target.z == 1))
                                    done = true;
                            }
                        }
                        if (l2[i][j] == count){
                            done2 = false;
                            if(l2[i][j] == 0){
                                l2[i][j] = count + via;
                                if((j == target.y) && (i == target.x) && (target.z == 2))
                                    done = true;
                            }
                            if(l3[i][j] == 0){
                                l3[i][j] = count + via;
                                if((j == target.y) && (i == target.x) && (target.z == 3))
                                    done = true;
                            }
                            if((i+1<y) && (l2[i+1][j] == 0)){
                                l2[i+1][j] = count+1;
                                if((j == target.y) && ((i+1) == target.x) && (target.z == 2))
                                    done = true;
                            }
                            if((i-1>=0) && (l2[i-1][j] == 0)){
                                l2[i-1][j] = count+1;
                                if((j == target.y) && ((i-1) == target.x) && (target.z == 2))
                                    done = true;
                            }
                        }
                        
                        if (l3[j][i] == count){
                            done1 = false;
                            if(l2[j][i] == 0){
                                l2[j][i] = count + via;
                                if((j == target.x) && (i == target.y) && (target.z == 2))
                                    done = true;
                            }
                            if(l1[j][i] == 0){
                                if((j == target.x) && (i == target.y) && (target.z == 1))
                                    done = true;
                                l1[j][i] = count + 2 * via;
                            }
                            if((i+1<y) && (l3[j][i+1] == 0)){
                                l3[j][i+1] = count+1;
                                if((j == target.x) && ((i+1) == target.y) && (target.z == 3))
                                    done = true;
                            }
                            if((i-1>=0) && (l3[j][i-1] == 0)){
                                l3[j][i-1] = count+1;
                                if((j == target.x) && ((i-1) == target.y) && (target.z == 3))
                                    done = true;
                            }
                        }
                    }
                }
        if (!done){
            done = done1 & done2 & done3 & (count%10 != 0);
        }
        if (done){
            cout << endl << count << endl;
        }
        count++; 
    }
    printMatrix(l1, x, y);
    cout << endl << endl << endl;
    printMatrix(l2, x, y);
    cout << endl << endl << endl;
    printMatrix(l3, x, y);
}
