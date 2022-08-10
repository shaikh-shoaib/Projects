/*
 *=====================
 *   Sudoku Solver
 *=====================
 *
 * Author - Shoaibanwar Shaikh
 * Objective - Takes in Sudoku puzzles and outputs the solution.
*/

#include<iostream>
#include<fstream>
using namespace std;

/*
  *	This class provides a data structure which can hold and manipulate the values in a sudoku puzzle.
  *	In this file, we shall call this data structure the 'Sudoku Frame'.
*/

class SudokuSolver{

	public:
	int sudokuFrame[9][9]; //This pointer will hold all the values in the matrix.

	SudokuSolver(){
		menu();
		cout<<"\nCalculating possibilities...\n";
		cout<<"Backtracking across puzzle....\n";
		cout<<"Validating cells and values...\n\n";

	}
	private:
	void menu(){
		
		cout<<"\n======================\n";
		cout<<"    Sudoku Solver\n";
		cout<<"======================\n\n";

		cout<<"Welcome to Sudoku Solver!\n";
		cout<<"Before we start, you will have to input the puzzle into this program.\n\n";
		cout<<"You can either:-\n";
		cout<<"\t1. Input the puzzle by entering the values manually. (Enter 1)\n";
		cout<<"\t2. Input the puzzle by reading a file with values in it. (Enter 2)\n";
		cout<<"\t   The file must not have a name > 20 characters.\n";
		cout<<"\t   The file must be in the same directory as this C++ file.\n";
		cout<<"\t   The file must have all 81 values seperated with spaces.\n";
		cout<<"\t   Blank cells must be filled in as 0 (eg; 1 0 0 2 0 0 ...).\n";
		cout<<"\t   --> ";

		int option;
		cin>>option;

		if(option==1) readFrameValues();
		else if(option==2) readFrameValuesFile();
		else{
			while(true){
				cout<<"\nYou seem to have entered an invalid option. Try again.\n";
				cout<<"\t   --> ";
				cin>>option;

				if(option==1) readFrameValues();
				else if(option==2) readFrameValuesFile();
				else continue;

				break;
			}
		}

	}

	void readFrameValuesFile(){

		char filename[30]; //Getting filename.

		cout<<"\nEnter the name of the file that contains the Sudoku Puzzle.\n";
		cout<<"\t   --> ";
		cin>>filename;

		ifstream sudokuFile; //Opening file for reading.
		sudokuFile.open(filename,ios::in);

		for(int row=0; row<9; row++){ //Iterating over file values.
			for(int col=0; col<9; col++){
				int readValue;
		
				sudokuFile>>readValue;

				if(!(readValue>=0 && readValue<=9)){ //Checking bounds for input.
					cout<<"\nValue "<<((row*9)+col+1)<<" in "<<filename;
					cout<<" seems to be wrong! Correct the value and try again!\n";
					exit(1);
				}

				sudokuFrame[row][col]=readValue;

				if(sudokuFile.eof()) break; //Breaking if EOF is reached.
			}
		}
		//Gotta have a line which lets us check the frame for any errors
		sudokuFile.close();
	}

	/*
	  * Reads the values for the Sudoku Frame cell-by-cell.
	*/
	private:
	void readFrameValues(){
		cout<<"\nEnter the specified value when prompted.\n";
		cout<<"Enter 0 if cell is empty.\n\n";

		for(int row=0; row<9; row++){ //Iterating over cells to read vals.
			for(int col=0; col<9; col++){
				int enteredValue;

				cout<<"Enter value for cell["<<row+1<<"]["<<col+1<<"] --> ";
				cin>>enteredValue;

				if(!(enteredValue>=0 && enteredValue<=9)){ //Checking for bounds in input.
					while(true){ //We loop until valid input is read from user.
						cout<<"Oops! You seem to have entered a wrong value! Try again.\n";
						cout<<"Enter value for cell ["<<row+1<<"]["<<col+1<<"] --> ";
						cin>>enteredValue;

						if(enteredValue>=0 && enteredValue<=9) break;
					}
				}

				sudokuFrame[row][col]=enteredValue;
			}
			cout<<"-------\n";
		}
	}

	bool isSafe(int val, int x, int y, int grid[9][9]) {
        for(int i=0; i<9; i++) {
            if(grid[x][i] == val) {
                return false;
            }
            if(grid[i][y] == val) {
                return false;
            }
            if(grid[3*(x/3)+i/3][3*(y/3)+i%3]==val) {
                return false;
            }
        }
        return true;
    }
	public:
    bool solve(int grid[9][9]) {
        
        for(int row=0; row<9; row++) {
            for(int col=0; col<9; col++) {
                
                if(grid[row][col]==0) {
                    
                    for(int i=1; i<=9; i++) {
                        
                        if(isSafe(i, row, col, grid)) {
                            
                            grid[row][col] = i;
                            if(solve(grid)) {
                                return true;
                            }
                            else {
                                grid[row][col] = 0;
                            }
                        }
                    }
                    return false;
                }
            }
        }
    }
	/*
	  *	Displays the values stored in the frame with designs.
	*/
	public:
	void displayFrame(){

		cout<<"++=====================================++";

		for(int row=0; row<9; row++){
			int cellIter=1;

			cout<<"\n||";
			for(int col=0; col<9; col++){
				if(cellIter==3){
					cout<<" "<<sudokuFrame[row][col]<<" ";
					cout<<"||";
					cellIter=1;
				}
				else{
					cout<<" "<<sudokuFrame[row][col]<<"  ";
					cellIter++;	
				}
			}

			if(row%3!=2) cout<<"\n++-----------++-----------++-----------++";
			else cout<<"\n++=====================================++";
		}
	}
};

int main(){
	SudokuSolver ss;

	if(ss.solve(ss.sudokuFrame)) {
			cout<<"Your puzzle has been solved!\n\n";
			ss.displayFrame();
		}
		else {
			cout<<"The given values are incorrect, please check the given input! \n";
		}
		cout<<"\n\n";
	return 0;
}
