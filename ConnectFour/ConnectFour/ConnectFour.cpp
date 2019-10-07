#include<iostream>
#include<sstream>
#include<string>

using namespace std;

int getTheColumnNumberOfBoard() {
	return 7;
}

int getTheRowNumberOfBoard() {
	return 6;
}

void creatABoard(int(*newBoard)[20]) {
	for (int i = 0; i <= 20; i++) {
		for (int j = 0; j <= 19; j++) {
			newBoard[i][j] = 50;
		}
	}
	//Prepare 21 row for an extra row to record the highest row with pieces of each column.
}
//Creat a board big enough for user to custom their own board in the future.

void printBoard(int(*board)[20], int columnNumber, int rowNumber) {
	for (int i = 0; i <= rowNumber; i++) {
		for (int j = 0; j <= columnNumber - 1; j++) {
			switch (board[i][j]) {
			case 25:
				cout << "\t" << '.';
				break;
			case 99:
				cout << "\t" << 'X';
				break;
			case -99:
				cout << "\t" << 'O';
				break;
			case 50:
				break;
			default:
				cout << "\t" << board[i][j];
			}
		}
		cout << endl;
	}
}
/** 25:empty grid
	99:grid with piece X
	-99:grid with piece O
	50:grid not used for user's setting
	1-20:used for record the highest row with pieces of each column on Row [rowNumber+1]
	**/

void initializeBoard(int(*board)[20], int columnNumber, int rowNumber, int* turn) {
	for (int j = 0; j <= columnNumber - 1; j++) {
		board[0][j] = j + 1;
	}
	for (int i = 1; i <= rowNumber; i++) {
		for (int j = 0; j <= columnNumber - 1; j++) {
			board[i][j] = 25;
		}
	}
	for (int j = 0; j <= columnNumber - 1; j++) {
		board[rowNumber + 1][j] = 0;
	}
	*turn = 0;
	printBoard(board, columnNumber, rowNumber);
}

//initialize the board according to the row and column number customed by user.

int checkNewPieceOnRow(int(*board)[20], int colunmNumber, int rowNumberOfNewPiece, int columnNumberOfNewPiece, int numberForWin) {
	int countForConnectPiece = 1;
	int columnNumberOfPieceChecked = columnNumberOfNewPiece - 1;
	int tokenOfPlayer = board[rowNumberOfNewPiece][columnNumberOfNewPiece - 1];

	while (columnNumberOfPieceChecked > 0 && countForConnectPiece < numberForWin) {
		if (board[rowNumberOfNewPiece][columnNumberOfPieceChecked - 1] == tokenOfPlayer) {
			columnNumberOfPieceChecked -= 1;
			countForConnectPiece += 1;
		}
		else {
			break;
		}
	}

	columnNumberOfPieceChecked = columnNumberOfNewPiece + 1;

	while (columnNumberOfPieceChecked <= colunmNumber && countForConnectPiece < numberForWin) {
		if (board[rowNumberOfNewPiece][columnNumberOfPieceChecked - 1] == tokenOfPlayer) {
			columnNumberOfPieceChecked += 1;
			countForConnectPiece += 1;
		}
		else {
			break;
		}
	}

	if (countForConnectPiece == 4) {
		return 1;
	}
	else {
		return 0;
	}
}

int checkNewPieceOnColumn(int(*board)[20], int rowNumber, int rowNumberOfNewPiece, int columnNumberOfNewPiece, int numberForWin) {
	int countForConnectPiece = 1;
	int rowNumberOfPieceChecked = rowNumberOfNewPiece - 1;
	int tokenOfPlayer = board[rowNumberOfNewPiece][columnNumberOfNewPiece - 1];

	while (rowNumberOfPieceChecked > 1 && countForConnectPiece < 4) {
		if (board[rowNumberOfPieceChecked][columnNumberOfNewPiece - 1] == tokenOfPlayer) {
			rowNumberOfPieceChecked -= 1;
			countForConnectPiece += 1;
		}
		else {
			break;
		}
	}

	rowNumberOfPieceChecked = rowNumberOfNewPiece + 1;

	while (rowNumberOfPieceChecked <= rowNumber + 1 && countForConnectPiece < 4) {
		if (board[rowNumberOfPieceChecked][columnNumberOfNewPiece - 1] == tokenOfPlayer) {
			rowNumberOfPieceChecked += 1;
			countForConnectPiece += 1;
		}
		else {
			break;
		}
	}

	if (countForConnectPiece == 4) {
		return 1;
	}
	else {
		return 0;
	}
}

int checkNewPieceOnDiagonal45Degree(int(*board)[20], int rowNumber, int columnNumber, int rowNumberOfNewPiece, int columnNumberOfNewPiece, int numberForWin) {
	int countForConnectPiece = 1;
	int rowNumberOfPieceChecked = rowNumberOfNewPiece + 1;
	int columnNunmberOfPieceChecked = columnNumberOfNewPiece - 1;
	int tokenOfPlayer = board[rowNumberOfNewPiece][columnNumberOfNewPiece - 1];

	while ((rowNumberOfPieceChecked <= rowNumber + 1 && columnNunmberOfPieceChecked > 0) && countForConnectPiece < 4) {
		if (board[rowNumberOfPieceChecked][columnNunmberOfPieceChecked - 1] == tokenOfPlayer) {
			rowNumberOfPieceChecked += 1;
			columnNunmberOfPieceChecked -= 1;
			countForConnectPiece += 1;
		}
		else {
			break;
		}
	}

	rowNumberOfPieceChecked = rowNumberOfNewPiece - 1;
	columnNunmberOfPieceChecked = columnNumberOfNewPiece + 1;

	while ((rowNumberOfPieceChecked > 1 && columnNunmberOfPieceChecked <= columnNumber) && countForConnectPiece < 4) {
		if (board[rowNumberOfPieceChecked][columnNumberOfNewPiece - 1] == tokenOfPlayer) {
			rowNumberOfPieceChecked -= 1;
			columnNunmberOfPieceChecked += 1;
			countForConnectPiece += 1;
		}
		else {
			break;
		}
	}

	if (countForConnectPiece == 4) {
		return 1;
	}
	else {
		return 0;
	}
}
int checkNewPieceOnDiagonal135Degree(int(*board)[20], int rowNumber, int columnNumber, int rowNumberOfNewPiece, int columnNumberOfNewPiece, int numberForWin) {
	int countForConnectPiece = 1;
	int rowNumberOfPieceChecked = rowNumberOfNewPiece + 1;
	int columnNunmberOfPieceChecked = columnNumberOfNewPiece + 1;
	int tokenOfPlayer = board[rowNumberOfNewPiece][columnNumberOfNewPiece - 1];

	while ((rowNumberOfPieceChecked <= rowNumber + 1 && columnNunmberOfPieceChecked <= columnNumber) && countForConnectPiece < 4) {
		if (board[rowNumberOfPieceChecked][columnNunmberOfPieceChecked - 1] == tokenOfPlayer) {
			rowNumberOfPieceChecked += 1;
			columnNunmberOfPieceChecked += 1;
			countForConnectPiece += 1;
		}
		else {
			break;
		}
	}

	rowNumberOfPieceChecked = rowNumberOfNewPiece - 1;
	columnNunmberOfPieceChecked = columnNumberOfNewPiece - 1;

	while ((rowNumberOfPieceChecked > 1 && columnNunmberOfPieceChecked > 0) && countForConnectPiece < 4) {
		if (board[rowNumberOfPieceChecked][columnNumberOfNewPiece - 1] == tokenOfPlayer) {
			rowNumberOfPieceChecked -= 1;
			columnNunmberOfPieceChecked -= 1;
			countForConnectPiece += 1;
		}
		else {
			break;
		}
	}
	if (countForConnectPiece == 4) {
		return 1;
	}
	else {
		return 0;
	}
}

int putNewPiece(int* playerToken, int(*board)[20], int columnNumber, int rowNumber) {
	
	int chosenColumn = 0;
	string input;
	cout << "Please choose a column by entering an integer between 1 and " << columnNumber << ":" << endl;
	while (getline(cin, input)) {
		stringstream inputContent(input);
		if ((inputContent >> chosenColumn) && inputContent.eof() && ((chosenColumn < (columnNumber + 1) && chosenColumn > 0))) {
			if (board[1][chosenColumn - 1] == 25) {
				break;
			}
			else {
				cout << "Column " << chosenColumn << " is filled, please choose another column:" << endl;
			}
		}
		else {
			cout << "This is not a integer or integer between 1 and " << columnNumber << ", please enter again:" << endl;
		}
	}
	int rowNumberOfNewPiece = rowNumber - board[rowNumber + 1][chosenColumn - 1];
	board[rowNumberOfNewPiece][chosenColumn - 1] = *playerToken;
	*playerToken = -*playerToken;
	board[rowNumber + 1][chosenColumn - 1] += 1;
	int winState = (checkNewPieceOnRow(board, columnNumber, rowNumberOfNewPiece, chosenColumn, 4)
		+ checkNewPieceOnColumn(board, rowNumber, rowNumberOfNewPiece, chosenColumn, 4)
		+ checkNewPieceOnDiagonal45Degree(board, rowNumber, columnNumber, rowNumberOfNewPiece, chosenColumn, 4)
		+ checkNewPieceOnDiagonal135Degree(board, rowNumber, columnNumber, rowNumberOfNewPiece, chosenColumn, 4)
		) * (*playerToken)
		;
	printBoard(board, columnNumber, rowNumber);
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

void addModToTheGame(bool*customOwnBoard,bool*wrapMod,bool*removeMod,bool*playWithAI){
	cout << "Input Y to start the mod setting, any other character will be considered as No." << endl;
	char answerFromUser = 'N';
	cin >> answerFromUser;
	if (answerFromUser == 'Y') {
		answerFromUser = 'N';
		cout << "Input Y to custom your own board, any other character will be considered as No." << endl;
		cin >> answerFromUser;
		if (answerFromUser == 'Y') {
			*customOwnBoard = 1;
		}
	}
}

void startAGame() {
	int connectFourBoard[21][20];
	int tokenOfPlayer = 99;
	int winState = 0; // 0:game is still going, 1: Player X win, 2:Player O win, 3: tie
	int turns = 0;
	int columnNumber = getTheColumnNumberOfBoard();
	int rowNumber = getTheRowNumberOfBoard();

	creatABoard(connectFourBoard);
	initializeBoard(connectFourBoard, columnNumber, rowNumber, &turns);
	while (winState == 0) {
		if (turns < 42) {
			winState = putNewPiece(&tokenOfPlayer, connectFourBoard, columnNumber, rowNumber);
			turns += 1;
		}
		else {
			break;
		}
	}
	switch (winState) {
	case 0:cout << "Game end in a draw!" << endl;
	case 1:cout << "Player O win the game!" << endl;
	case 2:cout << "Player X win the game!" << endl;
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
			system("cls");
			cin.clear();
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
		else {
			exit(0);
		}
	}

}

