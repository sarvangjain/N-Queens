#include<bits/stdc++.h>
#include <sys/time.h>
using namespace std;

int n;


//This Function is used to initialize the chessboard
void initialSetup(vector<int> &position, vector<vector<char>> &board)
{
	// initializing an empty board(with no queen)
	for (int i = 0; i < n; i++)
	{
		vector<char>tmp(n, '.');
		board[i] = tmp;
	}
	//putting queens randomly in each column
	for (int i = 0; i < n; i++) {

		// Getting a random row index
		position[i] = (rand()) % n;

		// Placing a queen on the obtained place in chessboard.
		board[position[i]][i] = 'Q';
	}

}

//This function is used to Print the specified board
void printBoard(vector<int>position, vector<vector<char>>board)
{
	//printing all the boxes of the board
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			cout << board[i][j] << " ";
		}
		cout << endl;
	}
}

//This function is used to Copy the board in a new empty vector
void copyPos_genBoard(vector<int>&p1, vector<int>&p2, vector<vector<char>>&b)
{
	//copying the original positions of the queens on the board p2 to p1
	for (int i = 0; i < n; i++)
		p1[i] = p2[i];
	for (int i = 0; i < n; i++)
	{
		vector<char>tmp(n, '.');
		b[i] = tmp;
	}
	//putting the queens int the new wmpty board
	for (int i = 0; i < n; i++) {
		b[p1[i]][i] = 'Q';
	}
}

//This Function is used to calculate the objective(heuristic value) of the state
int calculateObjective(vector<vector<char>> &board, vector<int> &position)
{
	int heuristic  = 0;
	for (int i = 0; i < n; i++)
	{
		for (int j = i + 1; j < n; j++)
		{
			//increasing the heuristic whenever we fing two queens in the same row
			if (position[i] == position[j])
				heuristic++;
			//increasing the heuristic whenever we fing two queens in the same diagonal
			else if (abs(position[i] - position[j]) == j - i)
				heuristic++;
		}
	}
	return heuristic;
}
//This function is used to find the most optimal board we could get by changing the position of any 1 queen
void getOptimal(vector<int> &position, vector<vector<char>> &board)
{
	vector <vector<char>> opBoard(n);
	vector<int> opPos(n);

	copyPos_genBoard(opPos, position, opBoard);

	// Initializing the optimal value of the board

	int opObjective = calculateObjective(opBoard, opPos);

	// Declaring and initializing neighbour board and neighbour position

	vector<int> neighbourPos(n);
	vector<vector<char>> neighbourBoard(n);
	copyPos_genBoard(neighbourPos, position, neighbourBoard);

	// Checking all the possible positions of the queen on the board

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {

			// Condition for skipping the present state

			if (j != position[i]) {

				neighbourPos[i] = j;
				neighbourBoard[neighbourPos[i]][i] = 'Q';
				neighbourBoard[position[i]][i] = '.';

				// Calculating the objective
				// value of the neighbour.

				int temp = calculateObjective(neighbourBoard, neighbourPos);

				//if the new objective(temp) is better than orignal than updating the original

				if (temp <= opObjective) {
					opObjective = temp;
					copyPos_genBoard(opPos, neighbourPos, opBoard);
				}

				//Returning to the intial configeration

				neighbourBoard[neighbourPos[i]][i] = 0;
				neighbourPos[i] = position[i];
				neighbourBoard[position[i]][i] = 1;
			}
		}
	}

	//Copying the optimal board to the initial board
	copyPos_genBoard(position, opPos, board);
}

// Checks whether there are any threatening positions
int calcThreats(int *board, int numOfQueens) {

	// Set count to 0
	int count = 0;

	for (int row = 0; row < numOfQueens - 1; row++) {
		for (int col = row + 1; col < numOfQueens; col++) {
			// Checking vertical queens for threats
			if (board[row] == board[col]) {
				count++;
			}
			// Checking diagonal threats
			if (board[row] - board[col] == row - col) {
				count++;
			}
			if (board[row] - board[col] == col - row) {
				count++;
			}
		}
	}

	return count;
}

// Function to print the board
void printBoard(int *board, int numOfQueens) {

	for (int i = 0; i < numOfQueens; i++) {
		for (int j = 0; j < numOfQueens; j++) {

			// Place the queens on the board
			if (j == board[i]) {
				cout << "Q ";
			}
			// Place '.' for the remaining positions
			else {
				cout << ". ";
			}
		}
		cout << endl;
	}
}

//makes a new board from the current state, so makes a new state in the form of a board
int* generateboard(int *board, int numOfQueens) {

	//create a placement vector
	vector<int> choiceToPlace;


	//sees if there are any attacks and gets the count
	int attack = calcThreats(board, numOfQueens);
	//arbitray variable for comparison
	int k;

	//make new board
	int *boardOut;
	//make it equal to the amount of queens the player chose
	boardOut = new int[numOfQueens];

	//make boardOut the same as the current board
	for (int i = 0; i < numOfQueens; i++) {
		boardOut[i] = board[i];
	}

	for (int i = 0; i < numOfQueens; i++) {

		//empty the vector
		choiceToPlace.clear();
		//put the i value into the placement vector
		choiceToPlace.push_back(boardOut[i]);
		//store the value in a ttemp variable
		//ttemp = boardOut[i];

		//row
		for (int j = 0; j < numOfQueens; j++) {

			//set i value of board to j
			boardOut[i] = j;
			//get value of k through calcThreats function
			k = calcThreats(boardOut, numOfQueens);

			//if k equals attack
			if (k == attack) {

				//put the value of j in the placement vector
				choiceToPlace.push_back(j);
				printBoard(boardOut, numOfQueens);

			}
			//if k is less than attack
			if (k < attack) {

				//empty the placement vector
				choiceToPlace.clear();
				//put the j value into the placement vector
				choiceToPlace.push_back(j);
				//set attack to k
				attack = k;

			}
		}
		//i value of boardOut becomes a random placement equal to the size of placement vector
		boardOut[i] = choiceToPlace[rand() % choiceToPlace.size()];
	}
	//return the new board
	return boardOut;
}



//finds the next place to move to, if there is no place to move to then it will restart with a new board
bool findNextState(int *board, int numOfQueens) {

	//get the original calculated value and set that to mainCalculate
	int isAttack = calcThreats(board, numOfQueens);
	//ttemporary board
	int *ttempboard;
	//ttempboard is a new board

	ttempboard = generateboard(board, numOfQueens);

	//if new calcThreats is less than the original calculated value
	if (calcThreats(ttempboard, numOfQueens) < isAttack) {
		//fill board with the value from ttempboard
		for (int p = 0; p < numOfQueens; p++) {
			//fill board with ttempboard Values
			board[p] = ttempboard[p];
		}
		//returns true as it is still searching for the correct answer
		return true;
	}
	//returns false if it has found the solution
	return false;
}

//creates a random board to work off of
void initialBoardSetup(int *board, int numOfQueens) {

	for (int i = 0; i < numOfQueens; i++) {
		//random placement of the queens
		board[i] = rand() % numOfQueens;
	}

}

float initialttemp = 1000;
float finalttemp = 10;
float ttemp = initialttemp;

//makes a new board from the current state, so makes a new state in the form of a board
int* generateboardAnneal(int *board, int numOfQueens) {


	//placement vector
	vector<int> placement;
	//place to place the queen
	int place = calcThreats(board, numOfQueens);
	//ttempPlacement
//	int ttempPlace;
	//to store the new placement of the queen ttemp
	int newPlace;
	//create a new output board
	int* boardOut;
	//fill the board with values
	boardOut = new int[numOfQueens];

//	int newCost;

	//make the boardOut the same as the current board
	for (int i = 0; i < numOfQueens; i++) {
		boardOut[i] = board[i];
	}

	while (ttemp > finalttemp) {
		for (int i = 0; i < numOfQueens; i++) {
			placement.clear();
			placement.push_back(boardOut[i]);
			//place = boardOut[i];
			for (int j = 0; j < numOfQueens; j++) {
				boardOut[i] = j;
				newPlace = calcThreats(boardOut, numOfQueens);
				if (newPlace == place) {
					placement.push_back(j);
				}
				//if the new place is worse then the original place
				else if (newPlace < place) {
					float rando = (rand() / (float)RAND_MAX * 1);
					//ttemp placement higher means more likely to take the worse option
					if (rando > (exp(calcThreats(boardOut, numOfQueens) - calcThreats(board, numOfQueens) / ttemp))) {
						placement.push_back(j);
					}
					else {
						placement.clear();
						placement.push_back(j);
						place = newPlace;
					}
				}


			}
			//i value of boardOut becomes a random placement equal to the size of placement vector
			boardOut[i] = placement[rand() % placement.size()];;
		}
		ttemp = ttemp - 0.05f;
		//cout << ttemp << endl;

	}
	return boardOut;
}

bool findNextStateAnneal(int *board, int numOfQueens) {

	//get the original calculated value and set that to mainCalculate
	int isAttack = calcThreats(board, numOfQueens);
	//ttemporary board
	int *ttempboard;

	//ttempboard is a new board

	ttempboard = generateboardAnneal(board, numOfQueens);

	//if new calcThreats is less than the original calculated value
	if (calcThreats(ttempboard, numOfQueens) < isAttack) {
		//fill board with the value from ttempboard
		for (int p = 0; p < numOfQueens; p++) {
			//fill board with ttempboard Values
			board[p] = ttempboard[p];
		}
		return true;
	}
	return false;
}

//This function is used to find the optimal solution using hillClimbing algorithm
void hillClimbing(vector<int> &position, vector<vector<char>> &board)
{
	vector<int> neighbourPos(n);
	vector<vector<char>> neighbourBoard(n);
	copyPos_genBoard(neighbourPos, position, neighbourBoard);
	int hill_opt = INT_MAX;
	//Till we find a better board with
	//better heuristic value we reiterate
	// the while loop and stop until we
	// reach a maxima.(loacal or global)
	//(board which have less heuristic value than any board we can move on to)
	while (1)
	{
		copyPos_genBoard(position, neighbourPos, board);
		neighbourBoard = board;
		getOptimal(neighbourPos, neighbourBoard);
		int temp = calculateObjective(neighbourBoard, neighbourPos);
		board = neighbourBoard;
		//If the new board has better heuristic value than the older one
		if (temp < hill_opt) {
			hill_opt = temp;
		}
		else
			//if the new board is not better than older one we stop
			break;

	}
}
//This function is used to find the optimal solution using of hill climbing with randomRestart
void hillClimbingWithRandomRestart(vector<int> &position, vector<vector<char>> &board)
{
	int fincount = -1;
	int limit = 100;
	vector<int> finpos(n);
	vector<vector<char>> finboard(n);
	//finding the board with the least no. of queens been attacked
	while (limit-- && fincount != 0 )
	{
		hillClimbing(position, board);
		int currentobj = calculateObjective(board, position);
		//initial condition
		if (fincount == -1)
		{
			fincount = currentobj;
			finpos = position;
			finboard = board;
		}
		//if the no. of queens been ataacked in the new restart is better
		else if (currentobj < fincount)
		{
			fincount = currentobj;
			finpos = position;
			finboard = board;
		}
		//if this is the last iteration
		if (limit)
			initialSetup(position, board);
	}
	//Copying the optimal board to the initial board
	position = finpos;
	board = finboard;
}


// Simulated Annealing Algorithm to Solve N-Queens

void simAnnealing(int numOfQueens) {

	// Allocate memory to the initial board
	int *board;
	board = new int[numOfQueens];

	// Generating an initial random board
	initialBoardSetup(board, numOfQueens);
	//while there are still attacks that can be made
	while (calcThreats(board, numOfQueens) != 0) {
		if (findNextStateAnneal(board, numOfQueens) == false) {
			printBoard(board, numOfQueens);
			ttemp = initialttemp;
			generateboardAnneal(board, numOfQueens);
			//cout << "Still Thinking" << endl;
			//initialBoardSetup(board, numOfQueens);
		}
	}
	cout << endl << "simulated annealing" << endl;

	// Print the Final Board (Solution)
	printBoard(board, numOfQueens);
	int threats = calcThreats(board, numOfQueens);

	cout << endl << "Threats in this board are: " << threats << endl;
}
int main()
{
	srand(time(NULL)); // for the random function
	cout << "Please enter the number of queens you want to place" << endl;
	cin >> n;
	// posotion vector for storing state
	vector<int> position(n);
	// board vector of vector (matrix);
	vector<vector<char>> board(n);
	cout << "Initial Board" << endl;
	// call initialSetup for random organization
	initialSetup(position, board);
	// printing initial board
	printBoard(position, board);
	cout << "Threats in this board are:" << calculateObjective(board, position)  << endl;
	cout << endl << endl;
	struct timeval start, end;

	// start timer.
	gettimeofday(&start, NULL);

	hillClimbing(position, board);
	gettimeofday(&end, NULL);

	// Calculating total time taken by the program.
	double time_taken;

	time_taken = (end.tv_sec - start.tv_sec) * 1e6;
	time_taken = (time_taken + (end.tv_usec -
	                            start.tv_usec)) * 1e-6;

	cout << "Hill Climbing" << endl;
	printBoard(position, board);
	cout << endl;
	cout << "Time taken by program is : " << fixed
	     << time_taken << setprecision(6);
	cout << " sec" << endl;
	cout << "Threats in this board are:" << calculateObjective(board, position)  << endl;
	cout << endl << endl;
	struct timeval start1, end1;

	// start timer.
	gettimeofday(&start1, NULL);
	hillClimbingWithRandomRestart(position, board);
	gettimeofday(&end1, NULL);

	// Calculating total time taken by the program.
	double time_taken1;

	time_taken1 = (end1.tv_sec - start1.tv_sec) * 1e6;
	time_taken1 = (time_taken1 + (end1.tv_usec -
	                              start1.tv_usec)) * 1e-6;


	cout << "Random Restart Hill Climbing" << endl;
	printBoard(position, board);
	cout << endl;
	cout << "Time taken by program is : " << fixed
	     << time_taken1 << setprecision(6);
	cout << " sec" << endl;
	cout << "Threats in this board are:" << calculateObjective(board, position)  << endl;
	cout << endl;

	initialttemp = 1000;
	ttemp = initialttemp;


	struct timeval start2, end2;

	// start timer.
	gettimeofday(&start2, NULL);
	simAnnealing(n);
	gettimeofday(&end2, NULL);

	// Calculating total time taken by the program.
	double time_taken2;

	time_taken2 = (end2.tv_sec - start2.tv_sec) * 1e6;
	time_taken2 = (time_taken2 + (end2.tv_usec -
	                              start2.tv_usec)) * 1e-6;
	cout << "Time taken by program is : " << fixed
	     << time_taken2 << setprecision(6);
	cout << " sec" << endl;
	return 0;
}