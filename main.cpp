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
//void lees(vector<vector<int>> m, int x, int y, int sx, int sy, int tx, int ty, bool H);
//void soukUp(vector<vector<int>> m, int x, int y, int sx, int sy, int tx, int ty);
coord traverse(vector <vector<int>> l, vector<vector<int>> &m, int x, int y, coord s, coord t);
void noFlooding (vector <vector<int>> l1, vector <vector<int>> l2, vector <vector<int>> l3, vector<vector<int>> &m, int x, int y, coord newSource, coord target);
//void floodL1(vector <vector<int>> &l1, vector<vector<int>> &m, int x, int y, coord newSource, coord target, int via);
//void floodL2(vector <vector<int>> &l2, vector<vector<int>> &m, int x, int y, coord newSource, coord target, int via);
//void floodCell(vector <vector<int>> &l, vector<vector<int>> &m, int x, int y, coord newSource, coord target, int via);
void flood(vector<vector<int>> &l1, vector<vector<int>> &l12, vector<vector<int>> &l3, int x, int y, coord newSource, coord target, int via);


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
    coord newSource = source;
    flood(l1, l2, l3, x, y, newSource, target, 10);
//    noFlooding(l1, l2, l3, m, x, y, newSource, target);

//    floodL2(l2, m, x, y, source, target, 10);
    
//    lees (l1, x, y, sx, sy, tx, ty, true);
//    cout << endl << endl << endl;
//    lees (l1, x, y, sx, sy, tx, ty, false);
//    printMatrix(l1, x, y);
    
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

//void soukUp(vector<vector<int>> m, int x, int y, int sx, int sy, int tx, int ty){
//
//}
//
//void lees(vector<vector<int>> m, int x, int y, int sx, int sy, int tx, int ty, bool H){
//    //horizontal layer
//    if (H){
//        for (int i=sx; i<=tx; i++){
//            for (int j = sy; j<=ty; j++){
//                m[i][j] = abs(sy - j) + abs(sx - i) * 10;
//            }
//        }
//    }
//    else {
//        for (int i=sx; i<=tx; i++){
//            for (int j = sy; j<=ty; j++){
//                m[i][j] = abs(sy - j)*10 + abs(sx - i);
//            }
//        }
//    }
//    printMatrix(m, x, y);
////    for (int i = sx; i<x; i++){
////        for (int j = sy; j<y; j++){
////            if(m[i][j] == 0){
////                    m[i][j] = 1 + max(m[i-1][j], max(m[i][j-1], max(m[i+1][j], m[i][j+1])));
////            }
////        }
////    }
//}

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
//
//void floodL1(vector <vector<int>> &l1, vector <vector<int>> l2, vector <vector<int>> l3, vector<vector<int>> &m, int x, int y, coord source, coord target, int via){
//    int count = 1;
////    for (int i=source.y; i<y-1; i++){
//        for (int j = source.x; j<x; j++){
//            if(l1[source.x][j] == 0){
////                if ((l2[i][j] + via == count)){
////                    l1[i][j] = count;
////                }
////                else
////                    if (j+1 < x){
//                        if (l1[source.x][j-1] + 1 == count)
//                            l1[source.y][j] = count;
////                    }
////                    else if (i-1 > 0){
////                        if (l1[i-1][j]+1 == count)
////                            l1[i][j] = count;
////                    }
//            }
//            count ++;
//        }
////    }
//    printMatrix(l1, x, y);
//    cout << endl << endl;
////    printMatrix(l2, x, y);
////    cout << endl << endl;
////    printMatrix(l3, x, y);
////    cout << endl << endl;
//}
//
//void floodL2(vector <vector<int>> &l2, vector<vector<int>> &m, int x, int y, coord source, coord target, int via){
//    int count = via * abs (2 - source.z);
//    //    for (int i=source.y; i<y-1; i++){
//    l2[source.y][source.x] = count;
//    count ++;
//    for (int i = 1; i<y; i++){
//        if(l2[i][source.x] == 0){
//            //                if ((l2[i][j] + via == count)){
//            //                    l1[i][j] = count;
//            //                }
//            //                else
//            //                    if (j+1 < x){
//            if (l2[i-1][source.x] + 1 == count)
//                l2[i][source.x] = count;
//            //                    }
//            //                    else if (i-1 > 0){
//            //                        if (l1[i-1][j]+1 == count)
//            //                            l1[i][j] = count;
//            //                    }
//        }
//        count ++;
//    }
//    //    }
//    printMatrix(l2, x, y);
//    cout << endl << endl;
//}
//
////void floodCell(vector <vector<int>> &l1, vector <vector<int>> &l2, vector <vector<int>> &l3, int count, int x, int y, coord newSource, coord target, int via){
////
////}

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
//        switch (newSource.z){
//            case(1):{

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
                        
//
//                        if (l3[i][j] == count){
//                            done3 = false;
//                            if(l1[i][j] == 0){
//                                l1[i][j] = count + 2 * via;
//                                if((j == target.y) && (i == target.x) && (target.z == 1))
//                                    done = true;
//                            }
//                            if(l2[j][i] == 0){
//                                l2[j][i] = count + via;
//                                if((j == target.y) && (i == target.x) && (target.z == 2))
//                                    done = true;
//                            }
//                            if((i+1<y) && (l3[i+1][j] == 0)){
//                                l3[i+1][j] = count+1;
//                                if((j == target.y) && ((i+1) == target.x) && (target.z == 3))
//                                    done = true;
//                            }
//                            if((i-1>=0) && (l3[i-1][j] == 0)){
//                                l3[i-1][j] = count+1;
//                                if((j == target.y) && ((i-1) == target.x) && (target.z == 3))
//                                    done = true;
//                            }
//                        }
                        
//                        if(l2[i][j] + via == count){
//                            l1[i][j] = count;
//                        }
//                        if (l3[i][j] + 2 * via == count){
//                            l1[i][j] = count;
//                        }
                    }
                }
//            }
//                break;
//            case(2):{
//                for (int i=0; i<x; i++){
//                    for (int j = 0; j<y; j++){
//                        if (l2[i][j] == count){
//                            done2 = false;
//                            if(l1[i][j] == 0){
//                                l2[i][j] = count + via;
//                            }
//                            if(l3[j][i] == 0){
//                                l3[j][i] = count + via;
//                            }
//                            if((i+1<y) && (l2[i+1][j] == 0)){
//                                l2[i+1][j] = count+1;
//                                if((j == target.y) && ((i+1) == target.x) && (target.z == 2))
//                                    done = true;
//                            }
//                            if((i-1>=0) && (l2[i-1][j] == 0)){
//                                l2[i-1][j] = count+1;
//                                if((j == target.y) && ((i-1) == target.x) && (target.z == 2))
//                                    done = true;
//                            }
//                        }
////                        else if(l1[i][j] + via == count){
////                            l2[i][j] = count;
////                        }
////                        else if (l3[i][j] + via == count){
////                            l2[i][j] = count;
////                        }
//                    }
//                }
//            }
//                break;
//            case (3):{
//                for (int i=0; i<x; i++){
//                    for (int j = 0; j<y; j++){
//                        if (l3[i][j] == count){
//                            done3 = false;
//                            if((i+1<y) && (l3[i+1][j] == 0)){
//                                l3[i+1][j] = count+1;
//                                if((j == target.y) && ((i+1) == target.x) && (target.z == 2))
//                                    done = true;
//                            }
//                            if((i-1>=0) && (l3[i-1][j] == 0)){
//                                l3[i-1][j] = count+1;
//                                if((j == target.y) && ((i-1) == target.x) && (target.z == 2))
//                                    done = true;
//                            }
//                        }
////                        else if(l2[i][j] + via == count){
////                            l3[i][j] = count;
////                        }
////                        else if (l1[i][j] + 2 * via == count){
////                            l3[i][j] = count;
////                        }
//                    }
//                }
//            }
//                break;
//        }
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
