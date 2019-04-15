//macros
#define m1 -1 //metal 1
#define m2 -2 //metal 2
#define m3 -3 //metal 3
#define v12 -4 //via m1-m2
#define v23 -5 //via m2-m3
#define v123 -6 //via m1-m2-m3

//includes
#include <iostream>
#include <vector>
#include <math.h>
using namespace std;

//structs
struct coord{int x; int y; int z;};

//global variables
int cells = 0;
int route = -10;

//function declarations
void input(coord &source, coord &target, int x, int y);
void printMatrix (vector<vector<int>> m, int x, int y);
coord traverse(vector <vector<int>> &l,  int x, int y, coord s, coord t);
void noFlooding (vector <vector<int>> l1, vector <vector<int>> l2, vector <vector<int>> l3, int x, int y, coord newSource, coord target);
void flood(vector<vector<int>> &l1, vector<vector<int>> &l2, vector<vector<int>> &l3, int x, int y, coord newSource, coord target, int via, int count0);
void backTracking(vector<vector<int>> &l1, vector<vector<int>> &l2, vector<vector<int>> &l3, int x, int y, coord source, coord target, int via, coord source1);
void backToLife(vector<vector<int>> &l1, vector<vector<int>> &l2, vector<vector<int>> &l3, int x, int y);
void classicalImplementation(vector<vector<int>> &l1, vector<vector<int>> &l2, vector<vector<int>> &l3, int x, int y, coord source, coord target, int via);

//main
int main(){
    int x, y;
    
    //getting the input dimensions
    int via;
    
    cout << "Please enter cost of via\n";
    cin >> via;
    cout << "Please enter the x-dimension of the plane\n";
    cin >> x;
    cout << "Please enter the y-dimension of the plane\n";
    cin >> y;

    //initializations
    vector <int> rows(y);
    vector <vector <int>> l1(x,rows); //layer 1
    vector <vector <int>> l2(x,rows); //layer 2
    vector <vector <int>> l3(x,rows); //layer 3
    
    for (int i = 0; i<x; i++){
        for (int j = 0; j<y; j++){
            l1[i][j] = 0;
        }
    }
    
    l2 = l1;
    l3 = l1;
    
    coord source, target;
    source.x = source.y = source.z = target.x = target.y = target.z = 0;
    
    while (source.x >= 0 && source.y >= 0 && source.z >= 0 && target.x >= 0 && target.y >= 0 && target.z >= 0){
        input(source, target, x, y);
        if (source.x >= 0 && source.y >= 0 && source.z >= 0 && target.x >= 0 && target.y >= 0 && target.z >= 0)
            classicalImplementation(l1, l2, l3, x, y, source, target, via);
        route--;

    }
    return 0;
}

//function definitions
void input(coord &source, coord &target, int x, int y){
    do{
        cout << "Enter x coordinate of source\n";
        cin >> source.x;
    } while((source.x >= 0) && (source.x >= x));
    
    do {
        cout << "Enter y coordinate of source\n";
        cin >> source.y;
    } while ((source.y >= 0) && (source.y >= y));
    
    do {
        cout << "Enter z coordinate of source\n";
        cin >> source.z;
    } while((source.z > 0) && (source.z != 1) && (source.z != 2) && (source.z != 3));
    
    do{
        cout << "Enter x coordinate of target\n";
        cin >> target.x;
    } while((target.x >= 0) && (target.x >= x));
    
    do {
        cout << "Enter y coordinate of target\n";
        cin >> target.y;
    } while ((target.y >= 0) && (target.y >= y));
    
    do {
        cout << "Enter z coordinate of target\n";
        cin >> target.z;
    } while((target.z > 0) && (target.z != 1) && (target.z != 2) && (target.z != 3));
}

void printMatrix (vector<vector<int>> m, int x, int y){
    for (int i = 0; i<x; i++){
        for (int j = 0; j<y; j++){
            cout <<m[i][j] << "\t";
        }
        cout << endl;
    }
}

coord traverse(vector <vector<int>> &l, int x, int y, coord s, coord t){
    //vertical
    coord newSource;
    if (s.z  == 2){
        l[s.x][s.y] = route;
        if (t.x > s.x){
            for (int i = s.x + 1; i<=t.x; i++){
                if (l[i][s.y] == 0){
                    l[i][s.y] = route;
                    cells ++;
                }
                else{
                    newSource.x = i-1;
                    newSource.y = s.y;
                    newSource.z = s.z;
                    return newSource;
                }
            }
        }
        else {
            for (int i = s.x + 1; i>t.x; i--){
                if (l[i][s.y] == 0){
                    l[i][s.y] = route;
                    cells ++;
                }
                else{
                    newSource.x = i-1;
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
        l[s.x][s.y] = route;
        if (t.y > s.y){
            for (int j = s.y + 1; j <= t.y; j++){
                if (l[s.x][j] == 0){
                    l[s.x][j] = route;
                    cells ++;
                }
                else{
                    newSource.x = s.x;
                    newSource.y = j-1;
                    newSource.z = s.z;
                    return newSource;
                }
            }
        }
        else {
            for (int j = s.y + 1; j >= t.y; j--){
                if (l[s.x][j] == 0){
                    l[s.x][j] = route;
                    cells ++;
                }
                else{
                    newSource.x = s.x;
                    newSource.y = j-1;
                    newSource.z = s.z;
                    return newSource;
                }
            }
        }
        newSource.x = s.x;
        newSource.y = t.y;
        newSource.z = s.z;
    }
    return newSource;
}

void noFlooding (vector<vector<int>> l1, vector<vector<int>> l2, vector<vector<int>> l3, int x, int y, coord newSource, coord target){
    int count = 0;
    while (count < 3){
        switch(newSource.z){
            case 1: newSource = traverse(l1, x, y, newSource, target);
                break;
            case 2:newSource = traverse(l2, x, y, newSource, target);
                break;
            case 3:
                newSource = traverse(l3, x, y, newSource, target);
                break;
            default:
                break;
        }
        printMatrix (l1, x, y );
        cout << endl << endl;
        printMatrix (l2, x, y );
        cout << endl << endl;
        printMatrix (l3, x, y );
        cout << endl << endl;
        cout << newSource.x << endl;
        cout << newSource.y << endl;
        newSource.z = ((newSource.z) % 3 )+ 1;
        cout << newSource.z << endl;
        cout << endl << endl;
        count ++;
    }
}

void flood(vector<vector<int>> &l1, vector<vector<int>> &l2, vector<vector<int>> &l3, int x, int y, coord newSource, coord target, int via, int count0){
    int count = count0;
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
                        if (l1[i][j] == count){
                            done1 = false;
                            if(l2[i][j] == 0){
                                l2[i][j] = count + via;
                                if((i == target.x) && (j == target.y) && (target.z == 2))
                                    done = true;
                            }
                            if(l3[i][j] == 0){
                                if((j == target.y) && (i == target.x) && (target.z == 3))
                                    done = true;
                                l3[i][j] = count + 2 * via;
                            }
                            if((j+1<y) && (l1[i][j+1] == 0)){
                                l1[i][j+1] = count+1;
                                if((i == target.x) && ((j+1) == target.y) && (target.z == 1))
                                    done = true;
                            }
                            if((j-1>=0) && (l1[i][j-1] == 0)){
                                l1[i][j-1] = count+1;
                                if((i == target.x) && ((j-1) == target.y) && (target.z == 1))
                                    done = true;
                            }
                        }
                        
                        
                        if (l2[i][j] == count){
                            done2 = false;
                            if(l1[i][j] == 0){
                                l1[i][j] = count + via;
                                if((j == target.y) && (i == target.x) && (target.z == 1))
                                    done = true;
                            }
                            if(l3[i][j] == 0){
                                l3[i][j] = count + via;
                                if((j == target.y) && (i == target.x) && (target.z == 3))
                                    done = true;
                            }
                            if((i+1<x) && (l2[i+1][j] == 0)){
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
                        
                        if (l3[i][j] == count){
                            done1 = false;
                            if(l2[i][j] == 0){
                                l2[i][j] = count + via;
                                if((i == target.x) && (j == target.y) && (target.z == 2))
                                    done = true;
                            }
                            if(l1[i][j] == 0){
                                if((i == target.x) && (j == target.y) && (target.z == 1))
                                    done = true;
                                l1[i][j] = count + 2 * via;
                            }
                            if((j+1<y) && (l3[i][j+1] == 0)){
                                l3[i][j+1] = count+1;
                                if((i == target.x) && ((j+1) == target.y) && (target.z == 3))
                                    done = true;
                            }
                            if((j-1>=0) && (l3[i][j-1] == 0)){
                                l3[i][j-1] = count+1;
                                if((i == target.x) && ((j-1) == target.y) && (target.z == 3))
                                    done = true;
                            }
                        }
                    }
                }
        if (done){
            cout << endl << count << endl;
        }
        count++;
        if (count == 22)
            cout << "hello" << endl;
    }
}

void backTracking(vector<vector<int>> &l1, vector<vector<int>> &l2, vector<vector<int>> &l3, int x, int y, coord source, coord target, int via, coord source1){
    int count = 0;
    switch (target.z){
        case(1): {
            count = l1[target.x][target.y];
            cells ++;
        }
            break;
        case(2): {
            count = l2[target.x][target.y];
            cells ++;
        }
            break;
        case(3): {
            count = l3[target.x][target.y];
            cells ++;
        }
            break;
    }
    int i = target.x;
    int j = target.y;
    int z = target.z;
    while(i!=source.x | j!=source.y | z!=source.z){
        //horizontal
        if(z==1){
            if((j-1 > 0) && (l1[i][j-1] == (count - 1)) && (l1[i][j-1] >= 0)){
                l1[i][j-1] = route;
                j--;
                count--;
                cells ++;
            }
            else if ((j+1 > y) && (l1[i][j+1] == (count - 1)) && (l1[i][j+1] >= 0)){
                l1[i][j+1] = route;
                j++;
                count--;
                cells ++;
            }
            else if(l2[i][j] == (count-via) && (l2[i][j] >= 0)){
                z = 2;
                count -= via;
                l2[i][j] = v12;
                l1[i][j] = v12;
                cells ++;
                cells ++;
            }
        }
        else if (z == 3){
            if((j-1 > 0) && (l3[i][j-1] == (count - 1)) && (l3[i][j-1] >= 0)){
                l3[i][j-1] = route;
                j--;
                count--;
                cells ++;
            }
            else if ((j+1 > y) && (l3[i][j+1] == (count - 1)) && (l3[i][j+1] >= 0)){
                l3[i][j+1] = route;
                j++;
                count--;
                cells ++;
            }
            else if(l2[i][j] == (count-via) && (l2[i][j] >= 0)){
                z = 2;
                count-=via;
                l2[i][j] = v23;
                l3[i][j] = v23;
                cells ++;
                cells ++;
            }
        }
        //vertical
        else {
            if((i-1 > 0) && (l2[i-1][j] == (count - 1)) && (l2[i-1][j] >= 0)){
                l2[i-1][j] = route;
                i--;
                count--;
                cells ++;
            }
            else if ((i+1 < x) && (l2[i+1][j] == (count - 1)) && (l2[i+1][j] >= 0)){
                l2[i+1][j] = route;
                i++;
                count--;
                cells ++;
            }
            else if(l3[i][j] == (count-via) && (l3[i][j] >= 0)){
                z = 3;
                count-=via;
                l3[i][j] = v23;
                l2[i][j] = v23;
                cells ++;
                cells ++;
            }
            else if(l1[i][j] == (count-via) && (l1[i][j] >= 0)){
                l1[i][j] = v12;
                l2[i][j] = v12;
                z = 1;
                count-=via;
                cells ++;
                cells ++;
            }
        }
    }
    switch (source.z){
        case(1): {
            l1[source.x][source.y] = v12;
            l2[source.x][source.y] = v12;
            cells ++;
        }
            break;
        case(2): {
            switch(source1.z){
                case(1):{
                    l1[source.x][source.y] = v12;
                    l2[source.x][source.y] = v12;
                    cells ++;
                }
                    break;
                case(3):{
                    l3[source.x][source.y] = v23;
                    l2[source.x][source.y] = v23;
                    cells ++;
                }
                    break;
            }
        }
            break;
        case(3): {
            l3[source.x][source.y] = v23;
            l2[source.x][source.y] = v23;
            cells ++;
        }
            break;
    }
}

void backToLife(vector<vector<int>> &l1, vector<vector<int>> &l2, vector<vector<int>> &l3, int x, int y){
    for (int i=0; i<x; i++){
        for(int j=0; j<y; j++){
            if(l1[i][j] > 0)
                l1[i][j] = 0;
            if(l2[i][j] > 0)
                l2[i][j] = 0;
            if(l3[i][j] > 0)
                l3[i][j] = 0;
        }
    }
}

void classicalImplementation(vector<vector<int>> &l1, vector<vector<int>> &l2, vector<vector<int>> &l3, int x, int y, coord source, coord target, int via){
    l1[4][7] = -7;
    coord newSource;
    
    switch (source.z){
        case(1): newSource = traverse(l1, x, y, source, target);
            break;
        case (2): newSource = traverse(l2, x, y, source, target);
            break;
        case (3): newSource = traverse(l3, x, y, source, target);
            break;
    }
    int count0 = 0;
    if ((newSource.x == target.x) && (newSource.y == target.y) && (newSource.z == target.z))
        cout << "DONEEEE" << endl;
    else {
        if(newSource.z < target.z){
            newSource.z = ((newSource.z) % 3 )+ 1;
            count0 = 1 + via;
        }
        else if (newSource.z > target.z){
            newSource.z = ((newSource.z - 1) % 3 );
            count0 = 1 + via;
        }
        else if ((newSource.z == target.z) && ((target.z == 1) || (target.z == 3)) && (newSource.x != target.x)){
            newSource.z = 2;
            count0 = 1 + via;
        }
        else if ((newSource.z == target.z) && (target.z == 2) && (newSource.y != target.y)){
            newSource.z = ((newSource.z) % 3 )+ 1;
            count0 = 1 + via;
        }

        cout << "New source is " << newSource.x << " " << newSource.y << " " << newSource.z << endl;
       
        flood(l1, l2, l3, x, y, newSource, target, via, count0);
        
        backTracking(l1, l2, l3, x, y, newSource, target, via, source);
        backToLife(l1, l2, l3, x, y);
        
        printMatrix(l1, x, y);
        cout << endl << endl;
        printMatrix(l2, x, y);
        cout << endl << endl;
        printMatrix(l3, x, y);
        cout << endl << endl;
    }
}
