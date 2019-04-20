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
int vias;
int route = -10;
int s_value, t_value;

//function declarations
bool input(coord &source, coord &target, int x, int y);
void printMatrix (vector<vector<int>> m, int x, int y);
coord traverse(vector <vector<int>> &l,  int x, int y, coord s, coord t);
void noFlooding (vector <vector<int>> l1, vector <vector<int>> l2, vector <vector<int>> l3, int x, int y, coord newSource, coord target);
bool flood(vector<vector<int>> &l1, vector<vector<int>> &l2, vector<vector<int>> &l3, int x, int y, coord newSource, coord target, int via, int count0, bool isSource);
bool backTracking(vector<vector<int>> &l1, vector<vector<int>> &l2, vector<vector<int>> &l3, int x, int y, coord source, coord target, int via, coord source1);
void backToLife(vector<vector<int>> &l1, vector<vector<int>> &l2, vector<vector<int>> &l3, int x, int y);
void undoTraversal(vector<vector<int>> &l, int x, int y, coord s, coord t);
void classicalImplementationWithSwap(vector<vector<int>> &l1, vector<vector<int>> &l2, vector<vector<int>> &l3, int x, int y, coord source, coord target, int via);

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
        if (!input(source, target, x, y))
            return 0;
        if (source.x >= 0 && source.y >= 0 && source.z >= 0 && target.x >= 0 && target.y >= 0 && target.z >= 0)
            classicalImplementation(l1, l2, l3, x, y, source, target, via);
        route--;

    }
    return 0;
}

//function definitions
bool input(coord &source, coord &target, int x, int y){
    do{
        cout << "Enter x coordinate of source\n";
        cin >> source.x;
    } while((source.x >= 0) && (source.x >= x));
    
    if(source.x < 0 )
        return false;
    
    do {
        cout << "Enter y coordinate of source\n";
        cin >> source.y;
    } while ((source.y >= 0) && (source.y >= y));
    
    if(source.y < 0 )
        return false;
    
    do {
        cout << "Enter z coordinate of source\n";
        cin >> source.z;
    } while((source.z > 0) && (source.z != 1) && (source.z != 2) && (source.z != 3));
    
    if(source.z < 0 )
        return false;
    
    do{
        cout << "Enter x coordinate of target\n";
        cin >> target.x;
    } while((target.x >= 0) && (target.x >= x));
    
    if(target.x < 0 )
        return false;
    
    do {
        cout << "Enter y coordinate of target\n";
        cin >> target.y;
    } while ((target.y >= 0) && (target.y >= y));
    
    if(target.y < 0 )
        return false;
    
    do {
        cout << "Enter z coordinate of target\n";
        cin >> target.z;
    } while((target.z > 0) && (target.z != 1) && (target.z != 2) && (target.z != 3));
    
    if(target.z < 0 )
        return false;
    return true;
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
            for (int i = s.x - 1; i >= t.x; i--){
                if (l[i][s.y] == 0){
                    l[i][s.y] = route;
                }
                else{
                    newSource.x = i+1;
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
            for (int j = s.y - 1; j >= t.y; j--){
                if (l[s.x][j] == 0){
                    l[s.x][j] = route;
                }
                else{
                    newSource.x = s.x;
                    newSource.y = j+1;
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

bool flood(vector<vector<int>> &l1, vector<vector<int>> &l2, vector<vector<int>> &l3, int x, int y, coord newSource, coord target, int via, int count0, bool isSource){
    int count = count0;
    switch(newSource.z){
        case (1):{
            if (isSource)
                l1[newSource.x][newSource.y] = count;
            else if (l1[newSource.x][newSource.y] == 0)
                l1[newSource.x][newSource.y] = count;
            else
                return false;
        }
            break;
        case (2):{
            if (isSource)
                l2[newSource.x][newSource.y] = count;
            else if (l2[newSource.x][newSource.y] == 0)
                l2[newSource.x][newSource.y] = count;
            else
                return false;
        }
            break;
        case (3):{
            if (isSource)
                l3[newSource.x][newSource.y] = count;
            else if (l3[newSource.x][newSource.y] == 0)
                l3[newSource.x][newSource.y] = count;
            else
                return false;
        }
            break;
    }
    int imin, imax, jmin, jmax;
    imin = imax = newSource.x;
    jmin = jmax = newSource.y;
    while (count < (x+y+2*via)){
//    while(count < 100){
//                for (int i= imin; i<= imax; i++){
//                    for (int j = jmin; j <= jmax; j++){
        for (int i = 0; i<x; i++){
            for (int j = 0; j<y; j++){
                        if (l1[i][j] == count){
                            
                            if((i == target.x) && (j == target.y) && (target.z == 2)){
                                l2[i][j] = count + via;
                                return true;
                            }
                            if(l2[i][j] == 0){
                                l2[i][j] = count + via;
                            }
                            
                            if((i == target.x) && ((j+1) == target.y) && (target.z == 1)){
                                l1[i][j+1] = count+1;
                                return true;
                            }
                            if((j+1<y) && (l1[i][j+1] == 0)){
                                jmax = j+1;
//                                i= imin;
                                l1[i][j+1] = count+1;
                            }
                            
                            if((i == target.x) && ((j-1) == target.y) && (target.z == 1)){
                                l1[i][j-1] = count+1;
                                return true;
                            }
                            if((j-1>=0) && (l1[i][j-1] == 0)){
                                jmin = j-1;
//                                i = imin;
//                                j = jmin;
                                l1[i][j-1] = count+1;
                            }
                        }
                        
                        
                        if (l2[i][j] == count){
                            
                            if((j == target.y) && (i == target.x) && (target.z == 1)){
                                l1[i][j] = count + via;
                                return true;
                            }
                            if(l1[i][j] == 0){
                                l1[i][j] = count + via;
                                
                            }
                            
                            if((j == target.y) && (i == target.x) && (target.z == 3)){
                                l3[i][j] = count + via;
                                return true;
                            }
                            if(l3[i][j] == 0){
                                l3[i][j] = count + via;
                            }
                            
                            if((j == target.y) && ((i+1) == target.x) && (target.z == 2)){
                                l2[i+1][j] = count+1;
                                return true;
                            }
                            if((i+1<x) && (l2[i+1][j] == 0)){
                                imax = i + 1;
//                                j = jmin;
                                l2[i+1][j] = count+1;
                            }
                            
                            if((j == target.y) && ((i-1) == target.x) && (target.z == 2)){
                                l2[i-1][j] = count+1;
                                return true;
                            }
                            if((i-1>=0) && (l2[i-1][j] == 0)){
                                    imin = i-1;
                                    //                                j = jmin;
                                    //                                i = imin;
                                    l2[i-1][j] = count+1;
                            }
                        }
                        
                        if (l3[i][j] == count){
                    
                            if((i == target.x) && (j == target.y) && (target.z == 2)){
                                l2[i][j] = count + via;
                                return true;
                            }
                            if(l2[i][j] == 0){
                                l2[i][j] = count + via;
                            }
                            
                            if((i == target.x) && ((j+1) == target.y) && (target.z == 3)){
                                l3[i][j+1] = count+1;
                                return true;
                            }
                            if((j+1<y) && (l3[i][j+1] == 0)){
                                    jmax = j + 1;
                                    //                                i = imin;
                                    l3[i][j+1] = count+1;
                            }
                            
                            if((i == target.x) && ((j-1) == target.y) && (target.z == 3)){
                                l3[i][j-1] = count+1;
                                return true;
                            }
                            if((j-1>=0) && (l3[i][j-1] == 0)){
                                    jmin = j-1;
//                                    i = imin;
//                                    j = jmin;
                                    l3[i][j-1] = count+1;
                            }
                        }
                    }
                }
        count++;

    }
    return false;
}

bool backTracking(vector<vector<int>> &l1, vector<vector<int>> &l2, vector<vector<int>> &l3, int x, int y, coord source, coord target, int via, coord source1){
    int count = 0;
    switch (target.z){
        case(1): {
            count = l1[target.x][target.y];
            l1[target.x][target.y] = route;
        }
            break;
        case(2): {
            count = l2[target.x][target.y];
            l2[target.x][target.y] = route;
        }
            break;
        case(3): {
            count = l3[target.x][target.y];
            l3[target.x][target.y] = route;
        }
            break;
    }

    if (count <= 0)
        return false;
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
            }
            else if ((j+1 < y) && (l1[i][j+1] == (count - 1)) && (l1[i][j+1] >= 0)){
                l1[i][j+1] = route;
                j++;
                count--;
            }
            else if(l2[i][j] == (count-via) && (l2[i][j] >= 0)){
                z = 2;
                count -= via;
                l2[i][j] = route;
                l1[i][j] = route;
//                l2[i][j] = v12;
//                l1[i][j] = v12;
                vias ++;
            }
        }
        else if (z == 3){
            if((j-1 > 0) && (l3[i][j-1] == (count - 1)) && (l3[i][j-1] >= 0)){
                l3[i][j-1] = route;
                j--;
                count--;
            }
            else if ((j+1 < y) && (l3[i][j+1] == (count - 1)) && (l3[i][j+1] >= 0)){
                l3[i][j+1] = route;
                j++;
                count--;
            }
            else if(l2[i][j] == (count-via) && (l2[i][j] >= 0)){
                z = 2;
                count-=via;
//                l2[i][j] = v23;
//                l3[i][j] = v23;
                l2[i][j] = route;
                l3[i][j] = route;
                vias ++;
            }
        }
        //vertical
        else {
            if((i-1 > 0) && (l2[i-1][j] == (count - 1)) && (l2[i-1][j] >= 0)){
                l2[i-1][j] = route;
                i--;
                count--;
            }
            else if ((i+1 < x) && (l2[i+1][j] == (count - 1)) && (l2[i+1][j] >= 0)){
                l2[i+1][j] = route;
                i++;
                count--;
            }
            else if(l3[i][j] == (count-via) && (l3[i][j] >= 0)){
                z = 3;
                count-=via;
//                l3[i][j] = v23;
//                l2[i][j] = v23;
                l3[i][j] = route;
                l2[i][j] = route;
                vias ++;
            }
            else if(l1[i][j] == (count-via) && (l1[i][j] >= 0)){
//                l1[i][j] = v12;
//                l2[i][j] = v12;
                l1[i][j] = route;
                l2[i][j] = route;
                z = 1;
                count-=via;
                vias ++;
            }
        }
    }

    return true;
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
            if (l1[i][j] == route)
                cells++;
            if (l2[i][j] == route)
                cells++;
            if (l3[i][j] == route)
                cells++;
        }
    }
}

void classicalImplementation(vector<vector<int>> &l1, vector<vector<int>> &l2, vector<vector<int>> &l3, int x, int y, coord source, coord target, int via){
    coord newSource;
    cells = 0;
    vias = 0;
    bool isSource = true;
    
    switch (source.z){
        case(1): {
            s_value = l1[source.x][source.y];
            newSource = traverse(l1, x, y, source, target);
        }
            break;
        case (2): {
            s_value = l2[source.x][source.y];
            newSource = traverse(l2, x, y, source, target);
        }
            break;
        case (3): {
            s_value = l3[source.x][source.y];
            newSource = traverse(l3, x, y, source, target);
        }
            break;
    }

    switch (target.z){
        case(1): {
            t_value = l1[target.x][target.y];
        }
            break;
        case (2): {
            t_value = l2[target.x][target.y];
        }
            break;
        case (3): {
            t_value = l3[target.x][target.y];
        }
            break;
    }
    
    
    int count0 = 1;
    if ((newSource.x == target.x) && (newSource.y == target.y) && (newSource.z == target.z)){
        printMatrix(l1, x, y);
        cout << endl << endl;
        printMatrix(l2, x, y);
        cout << endl << endl;
        printMatrix(l3, x, y);
        cout << endl << endl;
    }
    else {
        if(newSource.z < target.z){
            newSource.z = ((newSource.z) % 3 )+ 1;
            vias++;
            count0 = 1 + via;
            isSource = false;
        }
        else if (newSource.z > target.z){
            newSource.z = ((newSource.z - 1) % 3 );
            vias++;
            count0 = 1 + via;
            isSource = false;
        }
        else if ((newSource.z == target.z) && ((target.z == 1) || (target.z == 3)) && (newSource.x != target.x)){
            newSource.z = 2;
            vias++;
            count0 = 1 + via;
            isSource = false;
        }
        else if ((newSource.z == target.z) && (target.z == 2) && (newSource.y != target.y)){
            newSource.z = ((newSource.z) % 3 )+ 1;
            count0 = 1 + via;
            vias++;
            isSource = false;
        }

        flood(l1, l2, l3, x, y, newSource, target, via, count0, isSource);
        cout << "FLODDING" << endl;
        printMatrix(l1, x, y);
        cout << endl << endl;
        printMatrix(l2, x, y);
        cout << endl << endl;
        printMatrix(l3, x, y);
        cout << endl << endl;
        if (backTracking(l1, l2, l3, x, y, newSource, target, via, source)){
            backToLife(l1, l2, l3, x, y);
        
            cout << "BACKTRACKING" << endl;
            printMatrix(l1, x, y);
            cout << endl << endl;
            printMatrix(l2, x, y);
            cout << endl << endl;
            printMatrix(l3, x, y);
            cout << endl << endl;
            cout << "Cost = " << (cells + vias * via) << endl;
        } else {
            cout << "No Path available" << endl;
            backToLife(l1, l2, l3, x, y);
            cells = 0;
            switch (source.z){
                case(1): undoTraversal(l1, x, y, source, newSource);
                    break;
                case (2): undoTraversal(l2, x, y, source, newSource);
                    break;
                case (3): undoTraversal(l3, x, y, source, newSource);
                    break;
            }
            switch (target.z){
                case(1): {
                    l1[target.x][target.y] = t_value;
                }
                    break;
                case(2): {
                    l2[target.x][target.y] = t_value;
                }
                    break;
                case(3): {
                    l3[target.x][target.y] = t_value;
                }
                    break;
            }
            route++;
            printMatrix(l1, x, y);
            cout << endl << endl;
            printMatrix(l2, x, y);
            cout << endl << endl;
            printMatrix(l3, x, y);
            cout << endl << endl;
        }
    }
}

void undoTraversal(vector<vector<int>> &l,  int x, int y, coord s, coord t){
    if (s.z  == 2){
        if (t.x > s.x){
            for (int i = s.x + 1; i<=t.x; i++){
                if (l[i][s.y] == route){
                    l[i][s.y] = 0;
                }
            }
        }
        else {
            for (int i = s.x + 1; i>=t.x; i--){
                if (l[i][s.y] == route){
                    l[i][s.y] = 0;
                }
            }
        }
    }
    //horizontal
    else{
        if (t.y > s.y){
            for (int j = s.y + 1; j <= t.y; j++){
                if (l[s.x][j] == route){
                    l[s.x][j] = 0;
                }
            }
        }
        else {
            for (int j = s.y + 1; j >= t.y; j--){
                if (l[s.x][j] == route){
                    l[s.x][j] = 0;
                }
            }
        }
    }
    l[s.x][s.y] = s_value;
}

void classicalImplementationWithSwap(vector<vector<int>> &l1, vector<vector<int>> &l2, vector<vector<int>> &l3, int x, int y, coord source, coord target, int via){
    coord newSource;
    cells = 0;
    vias = 0;
    bool isSource = true;
    
    switch (source.z){
        case(1): {
            s_value = l1[source.x][source.y];
            newSource = traverse(l1, x, y, source, target);
        }
            break;
        case (2): {
            s_value = l2[source.x][source.y];
            newSource = traverse(l2, x, y, source, target);
        }
            break;
        case (3): {
            s_value = l3[source.x][source.y];
            newSource = traverse(l3, x, y, source, target);
        }
            break;
    }
    
    switch (target.z){
        case(1): {
            t_value = l1[target.x][target.y];
        }
            break;
        case (2): {
            t_value = l2[target.x][target.y];
        }
            break;
        case (3): {
            t_value = l3[target.x][target.y];
        }
            break;
    }
    
    
    int count0 = 1;
    if ((newSource.x == target.x) && (newSource.y == target.y) && (newSource.z == target.z)){
        printMatrix(l1, x, y);
        cout << endl << endl;
        printMatrix(l2, x, y);
        cout << endl << endl;
        printMatrix(l3, x, y);
        cout << endl << endl;
    }
    else {
        if(newSource.z < target.z){
            newSource.z = ((newSource.z) % 3 )+ 1;
            vias++;
            count0 = 1 + via;
            isSource = false;
        }
        else if (newSource.z > target.z){
            newSource.z = ((newSource.z - 1) % 3 );
            vias++;
            count0 = 1 + via;
            isSource = false;
        }
        else if ((newSource.z == target.z) && ((target.z == 1) || (target.z == 3)) && (newSource.x != target.x)){
            newSource.z = 2;
            vias++;
            count0 = 1 + via;
            isSource = false;
        }
        else if ((newSource.z == target.z) && (target.z == 2) && (newSource.y != target.y)){
            newSource.z = ((newSource.z) % 3 )+ 1;
            count0 = 1 + via;
            vias++;
            isSource = false;
        }
        flood(l1, l2, l3, x, y, newSource, target, via, count0, isSource);
        cout << "FLODDING" << endl;
        printMatrix(l1, x, y);
        cout << endl << endl;
        printMatrix(l2, x, y);
        cout << endl << endl;
        printMatrix(l3, x, y);
        cout << endl << endl;
        if (backTracking(l1, l2, l3, x, y, newSource, target, via, source)){
            backToLife(l1, l2, l3, x, y);
            
            cout << "BACKTRACKING" << endl;
            printMatrix(l1, x, y);
            cout << endl << endl;
            printMatrix(l2, x, y);
            cout << endl << endl;
            printMatrix(l3, x, y);
            cout << endl << endl;
            cout << "Cost = " << (cells + vias * via) << endl;
        } else {
            cout << "No Path available" << endl;
            backToLife(l1, l2, l3, x, y);
            cells = 0;
            switch (source.z){
                case(1): undoTraversal(l1, x, y, source, newSource);
                    break;
                case (2): undoTraversal(l2, x, y, source, newSource);
                    break;
                case (3): undoTraversal(l3, x, y, source, newSource);
                    break;
            }
            switch (target.z){
                case(1): {
                    l1[target.x][target.y] = t_value;
                }
                    break;
                case(2): {
                    l2[target.x][target.y] = t_value;
                }
                    break;
                case(3): {
                    l3[target.x][target.y] = t_value;
                }
                    break;
            }
            route++;
            printMatrix(l1, x, y);
            cout << endl << endl;
            printMatrix(l2, x, y);
            cout << endl << endl;
            printMatrix(l3, x, y);
            cout << endl << endl;
        }
    }
}
