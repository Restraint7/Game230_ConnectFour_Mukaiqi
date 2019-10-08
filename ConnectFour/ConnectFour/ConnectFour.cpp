#include<iostream>
#include<sstream>
#include<string>
#include<algorithm>


using namespace std;

const int BIGGESTCOLUMNNUMBER = 20;
const int BIGGESTROWNUMBER = 20;
const int TOKENOFGRIDWITHPIECE = 99;
const int TOKENOFGRIDNOTUSED = 50;
const int TOKENOFEMPTYGRID = 25;

int getAInteger(int upperOfTheNumber) {
	int integer;
	string input;
	cout << "Please enter an integer between 1 and " << upperOfTheNumber << ":" << endl;
	while (getline(cin, input)) {
		stringstream inputContent(input);
		if ((inputContent >> integer) && inputContent.eof() && ((integer < (upperOfTheNumber + 1) && integer > 0))) {
			return integer;
		}
		else {
			cout << "This is not a integer or integer between 1 and " << upperOfTheNumber << ", please enter again:" << endl;
		}
	}
}

int getTheNumberOfColumn(){
	cout << "Please set Column number." << endl;
	return getAInteger(BIGGESTCOLUMNNUMBER);
}

int getTheNumberOfRow() {
	cout << "Please set Row number." << endl;
	return getAInteger(BIGGESTCOLUMNNUMBER);
}

int getTheNumberRequiredToWin(int columnNumber,int rowNumber) {
	cout << "Please set the number required to win." << endl;
	return getAInteger(min(columnNumber,rowNumber));
}

void creatABoard(int(*newBoard)[BIGGESTCOLUMNNUMBER]) {
	for (int i = 0; i <= BIGGESTROWNUMBER; i++) {
		for (int j = 0; j <= BIGGESTCOLUMNNUMBER-1; j++) {
			newBoard[i][j] = TOKENOFGRIDNOTUSED;
		}
	}
	//Prepare 22 row for an extra row to record the highest row with pieces of each column.
}
//Creat a board big enough for user to custom their own board in the future.

void printBoard(int(*board)[BIGGESTCOLUMNNUMBER], int columnNumber, int rowNumber) {
	for (int i = 0; i <= rowNumber; i++) {
		for (int j = 0; j <= columnNumber - 1; j++) {
			switch (board[i][j]) {
			case TOKENOFEMPTYGRID:
				cout << "\t" << '.';
				break;
			case TOKENOFGRIDWITHPIECE:
				cout << "\t" << 'X';
				break;
			case -TOKENOFGRIDWITHPIECE:
				cout << "\t" << 'O';
				break;
			case TOKENOFGRIDNOTUSED:
				break;
			default:
				cout << "\t" << board[i][j];
			}
		}
		cout << endl;
	}
}	
/**
	1-20:used for record the highest row with pieces of each column on Row [rowNumber+1] and 
	**/

void initializeBoard(int(*board)[BIGGESTCOLUMNNUMBER], int columnNumber, int rowNumber, int* turn) {
	for (int j = 0; j <= columnNumber - 1; j++) {
		board[0][j] = j + 1;
	}
	for (int i = 1; i <= rowNumber; i++) {
		for (int j = 0; j <= columnNumber - 1; j++) {
			board[i][j] = TOKENOFEMPTYGRID;
		}
	}
	for (int j = 0; j <= columnNumber - 1; j++) {
		board[rowNumber + 1][j] = 0;
	}
	*turn = 0;
	printBoard(board, columnNumber, rowNumber);
}

//initialize the board according to the row and column number customed by user.

int checkNewPieceOnRow(int(*board)[BIGGESTCOLUMNNUMBER], int columnNumber, int rowNumberOfNewPiece, int columnNumberOfNewPiece, int numberRequiredToWin,bool playWrapMod, int tokenOfPlayer) {
	int countForConnectPiece = 1;
	int columnNumberOfPieceChecked = columnNumberOfNewPiece - 1;
	int checkTimes = 0;

	while ((playWrapMod?checkTimes < numberRequiredToWin: columnNumberOfPieceChecked > 0) && countForConnectPiece < numberRequiredToWin) {
		columnNumberOfPieceChecked == 0 ?columnNumberOfPieceChecked = columnNumber:NULL;
		if (board[rowNumberOfNewPiece][columnNumberOfPieceChecked - 1] == tokenOfPlayer) {
			columnNumberOfPieceChecked -= 1;
			countForConnectPiece += 1;
			checkTimes += 1;
		}
		else {
			checkTimes = numberRequiredToWin;
			break;
		}
	}

	columnNumberOfPieceChecked = columnNumberOfNewPiece + 1;
	checkTimes = 0;

	while ((playWrapMod?checkTimes<numberRequiredToWin:columnNumberOfPieceChecked < columnNumber + 1) && countForConnectPiece < numberRequiredToWin) {
		columnNumberOfPieceChecked == columnNumber + 1 ? columnNumberOfPieceChecked = 1:NULL;
		if (board[rowNumberOfNewPiece][columnNumberOfPieceChecked - 1] == tokenOfPlayer) {
			columnNumberOfPieceChecked += 1;
			countForConnectPiece += 1;
			checkTimes += 1;
		}
		else {
			checkTimes = numberRequiredToWin;
			break;
		}
	}

	if (countForConnectPiece == numberRequiredToWin) {
		return 1;
	}
	else {
		return 0;
	}
}

int checkNewPieceOnColumn(int(*board)[BIGGESTCOLUMNNUMBER], int rowNumber, int rowNumberOfNewPiece, int columnNumberOfNewPiece, int numberRequiredToWin, bool playWrapMod, int tokenOfPlayer) {
	int countForConnectPiece = 1;
	int rowNumberOfPieceChecked = rowNumberOfNewPiece + 1;
	int checkTimes = 0;
	
	while (rowNumberOfPieceChecked < rowNumber + 1 && countForConnectPiece < numberRequiredToWin) {
		if (board[rowNumberOfPieceChecked][columnNumberOfNewPiece - 1] == tokenOfPlayer) {
			rowNumberOfPieceChecked += 1;
			countForConnectPiece += 1;
		}
		else {
			if (playWrapMod && rowNumberOfNewPiece == 1) {
				rowNumberOfPieceChecked = rowNumber;
				while (checkTimes < 4 && countForConnectPiece < numberRequiredToWin) {
					if (board[rowNumberOfPieceChecked][columnNumberOfNewPiece - 1] == tokenOfPlayer) {
						rowNumberOfPieceChecked -= 1;
						countForConnectPiece += 1;
						checkTimes += 1;
					}
					else {
						checkTimes = numberRequiredToWin;
						break;
					}
				}
			}
			break;
		}
	}

	if (countForConnectPiece == numberRequiredToWin) {
		return 1;
	}
	else {
		return 0;
	}
}

int checkNewPieceOnDiagonal45Degree(int(*board)[BIGGESTCOLUMNNUMBER], int rowNumber, int columnNumber, int rowNumberOfNewPiece, int columnNumberOfNewPiece, int numberRequiredToWin, bool playWrapMod,int tokenOfPlayer) {
	int countForConnectPiece = 1;
	int columnNumberOfPieceChecked = columnNumberOfNewPiece - 1;
	int rowNumberOfPieceChecked = rowNumberOfNewPiece + 1;
	int checkTimes = 0;

	while (((playWrapMod ? checkTimes < numberRequiredToWin : rowNumberOfPieceChecked < rowNumber + 1 )&& 
		(playWrapMod ? checkTimes < numberRequiredToWin : columnNumberOfPieceChecked > 0)) &&
		countForConnectPiece < numberRequiredToWin) {
		columnNumberOfPieceChecked == 0 ? columnNumberOfPieceChecked = columnNumber:NULL;
		rowNumberOfPieceChecked == rowNumber+1 ? rowNumberOfPieceChecked = 1:NULL;
		if (board[rowNumberOfPieceChecked][columnNumberOfPieceChecked - 1] == tokenOfPlayer) {
			rowNumberOfPieceChecked += 1;
			columnNumberOfPieceChecked -= 1;
			countForConnectPiece += 1;
			checkTimes += 1;
		}
		else {
			checkTimes = numberRequiredToWin;
			break;
		}
	}

	rowNumberOfPieceChecked = rowNumberOfNewPiece - 1;
	columnNumberOfPieceChecked = columnNumberOfNewPiece + 1;
	checkTimes = 0;

	while (((playWrapMod ? checkTimes<numberRequiredToWin : rowNumberOfPieceChecked > 1) && 
		(playWrapMod ? checkTimes < numberRequiredToWin : columnNumberOfPieceChecked < columnNumber + 1)) && 
		countForConnectPiece < numberRequiredToWin) {
		columnNumberOfPieceChecked == columnNumber +1 ? columnNumberOfPieceChecked = 1:NULL;
		rowNumberOfPieceChecked == 0 ? rowNumberOfPieceChecked = rowNumber:NULL;
		if (board[rowNumberOfPieceChecked][columnNumberOfPieceChecked - 1] == tokenOfPlayer) {
			rowNumberOfPieceChecked -= 1;
			columnNumberOfPieceChecked += 1;
			countForConnectPiece += 1;
		}
		else {
			checkTimes = numberRequiredToWin;
			break;
		}
	}

	if (countForConnectPiece == numberRequiredToWin) {
		return 1;
	}
	else {
		return 0;
	}
}
int checkNewPieceOnDiagonal135Degree(int(*board)[BIGGESTCOLUMNNUMBER], int rowNumber, int columnNumber, int rowNumberOfNewPiece, int columnNumberOfNewPiece, int numberRequiredToWin, bool playWrapMod,int tokenOfPlayer) {
	int countForConnectPiece = 1;
	int rowNumberOfPieceChecked = rowNumberOfNewPiece + 1;
	int columnNumberOfPieceChecked = columnNumberOfNewPiece + 1;
	int checkTimes = 0;

	while ((playWrapMod ? checkTimes < numberRequiredToWin : (rowNumberOfPieceChecked < rowNumber + 1) && 
		(playWrapMod ? checkTimes < numberRequiredToWin : columnNumberOfPieceChecked < columnNumber + 1)) &&
		countForConnectPiece < numberRequiredToWin) {
		columnNumberOfPieceChecked == columnNumber + 1 ? columnNumberOfPieceChecked = 1 : NULL;
		rowNumberOfPieceChecked == rowNumber + 1 ? rowNumberOfPieceChecked = 1 : NULL;
		if (board[rowNumberOfPieceChecked][columnNumberOfPieceChecked - 1] == tokenOfPlayer) {
			rowNumberOfPieceChecked += 1;
			columnNumberOfPieceChecked += 1;
			countForConnectPiece += 1;
			checkTimes += 1;
		}
		else {
			checkTimes = numberRequiredToWin;
			break;
		}
	}

	rowNumberOfPieceChecked = rowNumberOfNewPiece - 1;
	columnNumberOfPieceChecked = columnNumberOfNewPiece - 1;
	checkTimes = 0;

	while ((playWrapMod ? checkTimes < numberRequiredToWin : (rowNumberOfPieceChecked > 1) &&
		(playWrapMod ? checkTimes < numberRequiredToWin : columnNumberOfPieceChecked > 0)) &&
		countForConnectPiece < numberRequiredToWin) {
		columnNumberOfPieceChecked == 0 ? columnNumberOfPieceChecked = columnNumber : NULL;
		rowNumberOfPieceChecked == 1 ? rowNumberOfPieceChecked = rowNumber: NULL;
		if (board[rowNumberOfPieceChecked][columnNumberOfPieceChecked - 1] == tokenOfPlayer) {
			rowNumberOfPieceChecked -= 1;
			columnNumberOfPieceChecked -= 1;
			countForConnectPiece += 1;
			checkTimes += 1;
		}
		else {
			checkTimes = numberRequiredToWin;
			break;
		}
	}
	if (countForConnectPiece == numberRequiredToWin) {
		return 1;
	}
	else {
		return 0;
	}
}

int getChosenColumn(int(*board)[BIGGESTCOLUMNNUMBER], int columnNumber) {
	int chosenColumn = getAInteger(columnNumber);
	while (abs(board[1][chosenColumn - 1]) == TOKENOFGRIDWITHPIECE) {
		cout << "Column " << chosenColumn << " is filled, please choose another column." << endl;
		chosenColumn = getAInteger(columnNumber);
	}
	return chosenColumn;
}

int putNewPiece(int tokenOfPlayer, int chosenColumn,int(*board)[BIGGESTCOLUMNNUMBER], int columnNumber, int rowNumber,int numberRequiredToWin,bool playWrapMod) {
	int rowNumberOfNewPiece = rowNumber - board[rowNumber + 1][chosenColumn - 1];
	board[rowNumberOfNewPiece][chosenColumn - 1] = tokenOfPlayer;
	board[rowNumber + 1][chosenColumn - 1] += 1;
	int winState = (checkNewPieceOnRow(board, columnNumber, rowNumberOfNewPiece, chosenColumn, numberRequiredToWin,playWrapMod,tokenOfPlayer)
		+ checkNewPieceOnColumn(board, rowNumber, rowNumberOfNewPiece, chosenColumn, numberRequiredToWin,playWrapMod,tokenOfPlayer)
		+ checkNewPieceOnDiagonal45Degree(board, rowNumber, columnNumber, rowNumberOfNewPiece, chosenColumn, numberRequiredToWin,playWrapMod,tokenOfPlayer)
		+ checkNewPieceOnDiagonal135Degree(board, rowNumber, columnNumber, rowNumberOfNewPiece, chosenColumn, numberRequiredToWin,playWrapMod,tokenOfPlayer)
		) * (tokenOfPlayer);
	if (winState > 0) {
		return 1;
	}
	else if (winState < 0) {
		return 2;
	}
	else {
		return 0;
	}
}

//get the column that player put a new piece in and check whether the value that player put in is legal. 

int removeAPiece(int(*board)[BIGGESTCOLUMNNUMBER], int columnNumber, int rowNumber, int numberRequiredToWin, bool playWrapMod) {
	int chosenColumn = getAInteger(columnNumber);
	while ((board[rowNumber+1][chosenColumn - 1]) == 0) {
		cout << "Column " << chosenColumn << " is empty, please choose another column." << endl;
		chosenColumn = getAInteger(columnNumber);
	}
	int tokenRecord[BIGGESTCOLUMNNUMBER] = { 0 };
	int newNumberOfEachPiece = 0;
	int numberOfRemainPiece = board[rowNumber + 1][chosenColumn - 1] -1;
	board[rowNumber + 1][chosenColumn - 1] = 0;
	board[rowNumber][chosenColumn - 1] = TOKENOFEMPTYGRID;
	int winState = 0;
	int winStateBuffer = 0;
	// In case 2 players will win together.
	while(newNumberOfEachPiece < numberOfRemainPiece) {
		tokenRecord[newNumberOfEachPiece] = board[rowNumber - newNumberOfEachPiece - 1][chosenColumn - 1];
		board[rowNumber - newNumberOfEachPiece-1][chosenColumn-1] = TOKENOFEMPTYGRID;
		newNumberOfEachPiece += 1;
	}
	newNumberOfEachPiece = 0;
	while (newNumberOfEachPiece < numberOfRemainPiece) {
		winStateBuffer = putNewPiece(tokenRecord[newNumberOfEachPiece], chosenColumn, board, columnNumber, rowNumber, numberRequiredToWin, playWrapMod);
		newNumberOfEachPiece += 1;
		if (winStateBuffer != 0 && winStateBuffer != winState) {
			if (winState == 0) {
				winState = winStateBuffer;
			}
			else {
				return 3;
			}
		}
	}
	return winState;
}

void addModToTheGame(bool*customOwnBoard,bool*playWrapMod,bool*removeMod,bool*playWithAI){
	cout << "Input Y to start the mod setting, any other character will be considered as No." << endl;
	char answerFromUser = 'N';
	cin >> answerFromUser;
	if (answerFromUser == 'Y') {
		answerFromUser = 'N';
		cout << "Input Y to CUSTOM YOUR OWN BOARD, input S to skip this and after settings,any other character will be considered as No." << endl;
		cin >> answerFromUser;
		switch (answerFromUser) {
		case 'Y':*customOwnBoard = 1; answerFromUser = 'N'; break;
		case 'S':return;
		}
		cout << "Input Y to play with WRAP MOD, input S to skip this and after settings,any other character will be considered as No." << endl;
		cin >> answerFromUser;
		switch (answerFromUser) {
		case 'Y':*playWrapMod = 1; answerFromUser = 'N'; break;
		case 'S':return;
		}
		cout << "Input Y to play with REMOVE MOD, input S to skip othis and after settings, any other character will be considered as No." << endl;
		cin >> answerFromUser;
		switch (answerFromUser) {
		case 'Y':*removeMod = 1; answerFromUser = 'N'; break;
		case 'S':return;
		}
		cout << "Input Y to play with AI,any other character will be considered as No." << endl;
		cin >> answerFromUser;
		switch (answerFromUser) {
		case 'Y':*playWithAI = 1; answerFromUser = 'N'; break;
		}
	}
}

void startAGame() {
	int connectFourBoard[BIGGESTROWNUMBER+1][BIGGESTCOLUMNNUMBER];
	int winState = 0; // 0:game is still going, 1: Player X win, 2:Player O win, 3: tie
	int turns = 0;
	bool customBoard = 0;
	bool playWarpMod = 0;
	bool playRemoveMod = 1;
	bool playWithAI = 0;

	creatABoard(connectFourBoard);

	//addModToTheGame(&customBoard,&playWarpMod,&playRemoveMod,&playWithAI);
	//cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

	int columnNumber = (customBoard ? getTheNumberOfColumn() : 7);
	int rowNumber = (customBoard ? getTheNumberOfRow() : 6);
	int numberRequiredToWin = (customBoard ? getTheNumberRequiredToWin(columnNumber,rowNumber) : 4);

	initializeBoard(connectFourBoard, columnNumber, rowNumber, &turns);

	while (winState == 0) {
		if (playRemoveMod) {
			cout << "Enter R to remove a piece or enter P to put a piece." << endl;
			char action = 'N';
			string input;
			while (getline(cin, input)) {
				if (input.length() == 1 && (input[0]=='R'||input[0]=='P')) {
					action = input[0];
					break;
				}
				else {
					cout << "Only R and P is legal, please enter again." << endl;
				}
			}
			switch (action) {
			case 'R':
				winState = removeAPiece(connectFourBoard, columnNumber, rowNumber, numberRequiredToWin, playWarpMod); 
				turns += 1; 
				break;
			case 'P':
				winState = putNewPiece((turns % 2 ? -TOKENOFGRIDWITHPIECE : TOKENOFGRIDWITHPIECE), getChosenColumn(connectFourBoard,columnNumber),connectFourBoard, columnNumber, rowNumber, numberRequiredToWin, playWarpMod); 
				turns += 1; 
				break;
			}
		}else if (turns<columnNumber*rowNumber) {
			winState = putNewPiece((turns%2?-TOKENOFGRIDWITHPIECE:TOKENOFGRIDWITHPIECE), getChosenColumn(connectFourBoard, columnNumber), connectFourBoard, columnNumber, rowNumber,numberRequiredToWin,playWarpMod);
			turns += 1;
		}
		else {
			break;
		}
		printBoard(connectFourBoard, columnNumber, rowNumber);
	}

	switch (winState) {
	case 1:cout << "Player X win the game!" << endl; break;
	case 2:cout << "Player O win the game!" << endl; break;
	case 3:cout << "Game end in a draw!" << endl; break;
	default:break;
	}

}

int main() {
	bool wantANewGame = 1;
	while (wantANewGame) {
		startAGame();
		wantANewGame = 0;
		cout << "Input Y to start a new game, any other character will end this program." << endl;
		char answerFromUser = 'N';
		cin >> answerFromUser;
		if (answerFromUser == 'Y') {
			wantANewGame = 1;
			answerFromUser == 'N';
			system("cls");
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
		else {
			exit(0);
		}
	}

}

