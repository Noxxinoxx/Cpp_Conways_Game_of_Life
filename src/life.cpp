//compiled with g++.;

//preference I like  to have the main function first in the code.;
//this means you can follow the code chronological.;

//why use templating for the function that uses grid?;
//well I used it because if I want to redefined the grid<type> later and dont use chars as the values in the grid i can just change it.;
//and I dont need to change the functions input parameters.;
//templates are a very powerful tool in cpp just because it lets you have one function that suppors diffrent types of input parameters.;

//using & sign in the parameters for some function is just a reference witch cant be NULL. thats why i used it. It prevents parameter input of type NULL.;
//if the parameters is NULL then the function cant proceed and the code would crash.;

// fixa const grid


#include <iostream>
#include <fstream>
#include "grid.h"
#include "lifeutil.h"

using namespace std;



//function declaration
bool quit();

template <typename T>
Grid<T> tick(const Grid<T>& grid);

void readFile(ifstream & file);

template <typename T>
void animate(Grid<T>& grid);

template <typename T>
void printGrid(const Grid<T>& grid);

template <typename T>
Grid<T> nextGen(const Grid<T>& grid) ;

template <typename T>
int countNeighbors(const Grid<T>& grid, int x, int y);

int main() {
    int row; 
    int col;
    bool gameplayLoop = true;
    //the files that you can use are defined in the res folder of the project.
    string resDir = "/home/melah344/Desktop/tddd86-noaan869-melah344-main/Lab1/labb1/life/res/";


    ifstream fileReader;
    string nameOfFile;
    string line;
    
    cout << "Grid input file name? "; 
    cin >> nameOfFile;


    fileReader.open((resDir + nameOfFile).c_str()); 


    getline(fileReader,line);
    row = atoi(&line[0]);
    getline(fileReader,line);
    col = atoi(&line[0]);


    Grid<char> grid(row, col);
    for(int x = 0; x < row; x++) {
        getline(fileReader,line);
        for(int y = 0; y < col; y++) {
            grid.set(x,y,line[y]);
        }
    }

    printGrid(grid);

    fileReader.close();

    while(gameplayLoop) {
        string gameOption;
        //game options
        cout << "a)nimate, t)ick, q)uit? "; 
        cin >> gameOption;

        //this will be in a gameplay loop.
        if(gameOption == "q") {
            gameplayLoop = false;
        }else if(gameOption == "a") {
            animate(grid);
        }else if(gameOption == "t") {
            grid = tick(grid);
        }
    }  

    cout << "Have a nice Life! "  << endl;
    return 0;
}

/*
*   prints the grid 
*/
template  <typename T>
void printGrid(const Grid<T>& grid) {
    for(int x = 0; x < grid.numRows(); x++) {
        for(int y = 0; y < grid.numCols(); y++) {
            cout << grid.get(x,y); 
        }
        cout << "\n";
    }
}
/*
* calculate the next generation depening on the state. 
*/
template  <typename T>
Grid<T> nextGen(const Grid<T>& grid) {
    
    Grid<T> nextGrid(grid.numRows(), grid.numCols());
     
    for(int row = 0; row < grid.numRows(); row++) {
        for(int col = 0; col < grid.numCols(); col++) {
           
            //edges calcs
            char state = grid.get(row,col);
            
            if(col == 0|| col == grid.numCols() - 1|| row == 0 || row == grid.numRows() - 1) {
               
                nextGrid.set(row,col,state);
            
            }else {
                 
                int neighbors = countNeighbors(grid, row,col);

                //rules.
                if(state == '-' && neighbors == 3) {
                    nextGrid.set(row,col, 'X');
                }else if(state == 'X' && (neighbors < 2 || neighbors > 3)) {
                    nextGrid.set(row,col, '-');
                
                }else if(state == 'X' && neighbors == 2) {
                    nextGrid.set(row,col,state);
                }else if(state == 'X' && neighbors == 3) {
                    nextGrid.set(row,col,state);
                }
                else {
                    nextGrid.set(row,col, '-');
                }
            }
        
        }
    }
    return nextGrid;
}

/*
*  counts all the neigbors around 
*/
template <typename T>
int countNeighbors(const Grid<T>& grid, int x, int y) {
    int sum = 0; 
    for(int i = -1; i < 2; i++) {
        for(int j = -1; j < 2; j++) {
            if(grid.inBounds(i + x, j + y)) {
                if(grid.get(i + x , j + y) == 'X') {
                    sum += 1;
                }
            }
        }
    }

    if(grid.get(x, y) == 'X') {
        sum -= 1;
    }
    return sum;

} 
/*
* animation function will animate the life game and preform a next generation every 100 ms.  
*/
template <typename T>
void animate(Grid<T>& grid) {

    while(true) {
        printGrid(grid);
        pause(100);
        clearConsole();
        Grid<T> grid1 = nextGen(grid);
        grid = grid1;
    }


}
/*
* will prefrom one new generator on command. 
*/
template <typename T>
Grid<T> tick(const Grid<T>& grid) {
    Grid<T> grid1 = nextGen(grid);
    printGrid(grid1); 
    return grid1;
}
