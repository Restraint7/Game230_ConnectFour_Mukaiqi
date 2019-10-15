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
const int TOKENOFWINSTATE = 999;
const int TOKENOFTIEGAME = 1000;

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
			cout << "This is not a integer or integer between 1 and " << upperOfTheNumber << ", please enter again." << endl;
		}
	}
}

int getTheNumberOfColumn(){
	cout << "Please set the Column number." << endl;
	return getAInteger(BIGGESTCOLUMNNUMBER);
}

int getTheNumberOfRow() {
	cout << "Please set the Row number." << endl;
	return getAInteger(BIGGESTCOLUMNNUMBER);
}

int getTheNumberRequiredToWin(int columnNumber,int rowNumber) {
	cout << "Please set the number required to win." << endl;
	return getAInteger(min(columnNumber,rowNumber));
}

void creatABoard(int(*newBoard)[BIGGESTCOLUMNNUMBER+2]) {
	for (int i = 0; i <= BIGGESTROWNUMBER+1; i++) {
		for (int j = 0; j <= BIGGESTCOLUMNNUMBER+1; j++) {
			newBoard[i][j] = TOKENOFGRIDNOTUSED;
		}
	}
	//Prepare 22 row for an extra row to record the highest row with pieces of each column.
}
//Creat a board big enough for user to custom their own board in the future.
void addModToTheGame(bool* customOwnBoard, bool* playWrapMod, bool* removeMod, bool* playWithAI) {
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

void printBoard(int(*board)[BIGGESTCOLUMNNUMBER+2], int columnNumber, int rowNumber) {
	for (int i = 0; i <= rowNumber; i++) {
		for (int j = 1; j <= columnNumber; j++) {
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

void initializeBoard(int(*board)[BIGGESTCOLUMNNUMBER+2], int columnNumber, int rowNumber) {
	for (int j = 1; j <= columnNumber; j++) {
		board[0][j] = j;
	}
	for (int i = 1; i <= rowNumber; i++) {
		for (int j = 1; j <= columnNumber; j++) {
			board[i][j] = TOKENOFEMPTYGRID;
		}
	}
	for (int j = 1; j <= columnNumber; j++) {
		board[rowNumber + 1][j] = 0;
	}
	printBoard(board, columnNumber, rowNumber);
}

//initialize the board according to the row and column number customed by user.
class ConnectFourBoard {
public:
	int boardForPlay[BIGGESTROWNUMBER + 2][BIGGESTCOLUMNNUMBER + 2]{ 0 };
	int columnNumber;
	int rowNumber;
	int numberRequiredToWin;
	bool customBoard = 0;
	bool playWrapMod = 0;
	bool playRemoveMod = 0;
	bool playWithAI = 0;

	ConnectFourBoard() {
		creatABoard(boardForPlay);
		addModToTheGame(&customBoard, &playWrapMod, &playRemoveMod, &playWithAI);
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		columnNumber = (customBoard ? getTheNumberOfColumn() : 7);
		rowNumber = (customBoard ? getTheNumberOfRow() : 6);
		numberRequiredToWin = (customBoard ? getTheNumberRequiredToWin(columnNumber, rowNumber) : 4);
		initializeBoard(boardForPlay, columnNumber, rowNumber);
	}
};

int checkNewPieceOnRow(ConnectFourBoard &boardSetting, int rowNumberOfNewPiece, int columnNumberOfNewPiece, int tokenOfPlayer) {
	int countForConnectPiece = 1;
	int columnNumberOfPieceChecked = columnNumberOfNewPiece - 1;
	int checkTimes = 0; //Used for wrapmod
	int emptyNumber = 0; //Used for AI,connected piece with empty grid in each side will get more point

	while ((boardSetting.playWrapMod?checkTimes < boardSetting.numberRequiredToWin: columnNumberOfPieceChecked > 0) && countForConnectPiece < boardSetting.numberRequiredToWin) {
		columnNumberOfPieceChecked == 0 ?columnNumberOfPieceChecked = boardSetting.columnNumber:NULL;
		int valueOfThisGrid = 0;
		if (boardSetting.boardForPlay[rowNumberOfNewPiece][columnNumberOfPieceChecked] == tokenOfPlayer) {
			columnNumberOfPieceChecked -= 1;
			countForConnectPiece += 1;
			checkTimes += 1;
		}
		else {
			break;
		}
	}
	if (boardSetting.boardForPlay[rowNumberOfNewPiece][columnNumberOfPieceChecked] == TOKENOFEMPTYGRID) {
		emptyNumber += 1;
	}

	columnNumberOfPieceChecked = columnNumberOfNewPiece + 1;
	checkTimes = 0;

	while ((boardSetting.playWrapMod?checkTimes< boardSetting.numberRequiredToWin:columnNumberOfPieceChecked < boardSetting.columnNumber + 1) && countForConnectPiece < boardSetting.numberRequiredToWin) {
		columnNumberOfPieceChecked == boardSetting.columnNumber + 1 ? columnNumberOfPieceChecked = 1:NULL;
		if (boardSetting.boardForPlay[rowNumberOfNewPiece][columnNumberOfPieceChecked] == tokenOfPlayer) {
			columnNumberOfPieceChecked += 1;
			countForConnectPiece += 1;
			checkTimes += 1;
		}
		else {
			break;
		}
	}

	if (boardSetting.boardForPlay[rowNumberOfNewPiece][columnNumberOfPieceChecked+1] == TOKENOFEMPTYGRID) {
		emptyNumber += 1;
	}
	return ((countForConnectPiece == boardSetting.numberRequiredToWin) ? TOKENOFWINSTATE : emptyNumber * pow(countForConnectPiece, 3));
	//return the evaluation of this grid(used for AI)
}

int checkNewPieceOnColumn(ConnectFourBoard& boardSetting, int rowNumberOfNewPiece, int columnNumberOfNewPiece, int tokenOfPlayer) {
	int countForConnectPiece = 1;
	int rowNumberOfPieceChecked = rowNumberOfNewPiece + 1;
	int checkTimes = 0;
	int emptyNumber = 0;
	
	while (rowNumberOfPieceChecked < boardSetting.rowNumber+1  && countForConnectPiece < boardSetting.numberRequiredToWin) {
		if (boardSetting.boardForPlay[rowNumberOfPieceChecked][columnNumberOfNewPiece] == tokenOfPlayer) {
			rowNumberOfPieceChecked += 1;
			countForConnectPiece += 1;
		}
		else {
			if (boardSetting.playWrapMod && rowNumberOfNewPiece == 1) {
				rowNumberOfPieceChecked = boardSetting.rowNumber;
				while (checkTimes < boardSetting.numberRequiredToWin && countForConnectPiece < boardSetting.numberRequiredToWin) {
					if (boardSetting.boardForPlay[rowNumberOfPieceChecked][columnNumberOfNewPiece] == tokenOfPlayer) {
						rowNumberOfPieceChecked -= 1;
						countForConnectPiece += 1;
						checkTimes += 1;
					}
					else {
						checkTimes = boardSetting.numberRequiredToWin;
						break;
					}
				}
			}
			break;
		}
	}

	if (boardSetting.boardForPlay[rowNumberOfPieceChecked][columnNumberOfNewPiece] == TOKENOFEMPTYGRID) {
		emptyNumber += 1;
	}

	return ((countForConnectPiece == boardSetting.numberRequiredToWin) ? TOKENOFWINSTATE : emptyNumber * pow(countForConnectPiece, 3));
}

int checkNewPieceOnDiagonal45Degree(ConnectFourBoard& boardSetting, int rowNumberOfNewPiece, int columnNumberOfNewPiece, int tokenOfPlayer) {
	int countForConnectPiece = 1;
	int columnNumberOfPieceChecked = columnNumberOfNewPiece - 1;
	int rowNumberOfPieceChecked = rowNumberOfNewPiece + 1;
	int checkTimes = 0;
	int emptyNumber = 0;

	while (((boardSetting.playWrapMod ? checkTimes < boardSetting.numberRequiredToWin : rowNumberOfPieceChecked < boardSetting.rowNumber + 1 )&&
		(boardSetting.playWrapMod ? checkTimes < boardSetting.numberRequiredToWin : columnNumberOfPieceChecked > 0)) &&
		countForConnectPiece < boardSetting.numberRequiredToWin) {
		columnNumberOfPieceChecked == 0 ? columnNumberOfPieceChecked = boardSetting.columnNumber:NULL;
		rowNumberOfPieceChecked == boardSetting.rowNumber+1 ? rowNumberOfPieceChecked = 1:NULL;
		if (boardSetting.boardForPlay[rowNumberOfPieceChecked][columnNumberOfPieceChecked] == tokenOfPlayer) {
			rowNumberOfPieceChecked += 1;
			columnNumberOfPieceChecked -= 1;
			countForConnectPiece += 1;
			checkTimes += 1;
		}
		else {
			checkTimes = boardSetting.numberRequiredToWin;
			break;
		}
	}

	if (boardSetting.boardForPlay[rowNumberOfPieceChecked][columnNumberOfPieceChecked] == TOKENOFEMPTYGRID) {
		emptyNumber += 1;
	}
	rowNumberOfPieceChecked = rowNumberOfNewPiece - 1;
	columnNumberOfPieceChecked = columnNumberOfNewPiece + 1;
	checkTimes = 0;

	while (((boardSetting.playWrapMod ? checkTimes< boardSetting.numberRequiredToWin : rowNumberOfPieceChecked > 1) &&
		(boardSetting.playWrapMod ? checkTimes < boardSetting.numberRequiredToWin : columnNumberOfPieceChecked < boardSetting.columnNumber + 1)) &&
		countForConnectPiece < boardSetting.numberRequiredToWin) {
		columnNumberOfPieceChecked == boardSetting.columnNumber +1 ? columnNumberOfPieceChecked = 1:NULL;
		rowNumberOfPieceChecked == 0 ? rowNumberOfPieceChecked = boardSetting.rowNumber:NULL;
		if (boardSetting.boardForPlay[rowNumberOfPieceChecked][columnNumberOfPieceChecked] == tokenOfPlayer) {
			rowNumberOfPieceChecked -= 1;
			columnNumberOfPieceChecked += 1;
			countForConnectPiece += 1;
		}
		else {
			checkTimes = boardSetting.numberRequiredToWin;
			break;
		}
	}

	if (boardSetting.boardForPlay[rowNumberOfPieceChecked][columnNumberOfPieceChecked] == TOKENOFEMPTYGRID) {
		emptyNumber += 1;
	}
	return ((countForConnectPiece == boardSetting.numberRequiredToWin) ? TOKENOFWINSTATE : emptyNumber * pow(countForConnectPiece, 3));
}
int checkNewPieceOnDiagonal135Degree(ConnectFourBoard& boardSetting, int rowNumberOfNewPiece, int columnNumberOfNewPiece, int tokenOfPlayer) {
	int countForConnectPiece = 1;
	int rowNumberOfPieceChecked = rowNumberOfNewPiece + 1;
	int columnNumberOfPieceChecked = columnNumberOfNewPiece + 1;
	int checkTimes = 0;
	int emptyNumber = 0;

	while ((boardSetting.playWrapMod ? checkTimes < boardSetting.numberRequiredToWin : (rowNumberOfPieceChecked < boardSetting.rowNumber + 1) &&
		(boardSetting.playWrapMod ? checkTimes < boardSetting.numberRequiredToWin : columnNumberOfPieceChecked < boardSetting.columnNumber + 1)) &&
		countForConnectPiece < boardSetting.numberRequiredToWin) {
		columnNumberOfPieceChecked == boardSetting.columnNumber + 1 ? columnNumberOfPieceChecked = 1 : NULL;
		rowNumberOfPieceChecked == boardSetting.rowNumber + 1 ? rowNumberOfPieceChecked = 1 : NULL;
		if (boardSetting.boardForPlay[rowNumberOfPieceChecked][columnNumberOfPieceChecked] == tokenOfPlayer) {
			rowNumberOfPieceChecked += 1;
			columnNumberOfPieceChecked += 1;
			countForConnectPiece += 1;
			checkTimes += 1;
		}
		else {
			checkTimes = boardSetting.numberRequiredToWin;
			break;
		}
	}
	if (boardSetting.boardForPlay[rowNumberOfPieceChecked][columnNumberOfPieceChecked] == TOKENOFEMPTYGRID) {
		emptyNumber += 1;
	}
	rowNumberOfPieceChecked = rowNumberOfNewPiece - 1;
	columnNumberOfPieceChecked = columnNumberOfNewPiece - 1;
	checkTimes = 0;

	while ((boardSetting.playWrapMod ? checkTimes < boardSetting.numberRequiredToWin : (rowNumberOfPieceChecked > 1) &&
		(boardSetting.playWrapMod ? checkTimes < boardSetting.numberRequiredToWin : columnNumberOfPieceChecked > 0)) &&
		countForConnectPiece < boardSetting.numberRequiredToWin) {
		columnNumberOfPieceChecked == 0 ? columnNumberOfPieceChecked = boardSetting.columnNumber : NULL;
		rowNumberOfPieceChecked == 1 ? rowNumberOfPieceChecked = boardSetting.rowNumber: NULL;
		if (boardSetting.boardForPlay[rowNumberOfPieceChecked][columnNumberOfPieceChecked] == tokenOfPlayer) {
			rowNumberOfPieceChecked -= 1;
			columnNumberOfPieceChecked -= 1;
			countForConnectPiece += 1;
			checkTimes += 1;
		}
		else {
			checkTimes = boardSetting.numberRequiredToWin;
			break;
		}
	}
	if(boardSetting.boardForPlay[rowNumberOfPieceChecked][columnNumberOfPieceChecked] == TOKENOFEMPTYGRID) {
		emptyNumber += 1;
	}
	return ((countForConnectPiece == boardSetting.numberRequiredToWin) ? TOKENOFWINSTATE : emptyNumber * pow(countForConnectPiece, 3));
}

int getChosenColumn(int(*board)[BIGGESTCOLUMNNUMBER+2], int columnNumber) {
	int chosenColumn = getAInteger(columnNumber);
	while (abs(board[1][chosenColumn]) == TOKENOFGRIDWITHPIECE) {
		cout << "Column " << chosenColumn << " is filled, please choose another column." << endl;
		chosenColumn = getAInteger(columnNumber);
	}
	return chosenColumn;
}

int calculateValueOfChosenGrid(int tokenOfPlayer, int rowNumberOfNewPiece,int chosenColumn, ConnectFourBoard &boardSetting) {
	return (checkNewPieceOnRow(boardSetting,rowNumberOfNewPiece,chosenColumn,tokenOfPlayer)
		+ checkNewPieceOnColumn(boardSetting, rowNumberOfNewPiece, chosenColumn, tokenOfPlayer)
		+ checkNewPieceOnDiagonal45Degree(boardSetting, rowNumberOfNewPiece, chosenColumn, tokenOfPlayer)
		+ checkNewPieceOnDiagonal135Degree(boardSetting, rowNumberOfNewPiece, chosenColumn, tokenOfPlayer))
		* (tokenOfPlayer / TOKENOFGRIDWITHPIECE);
}

int putNewPiece(int tokenOfPlayer, int chosenColumn,ConnectFourBoard &boardSetting) {
	int rowNumberOfNewPiece = boardSetting.rowNumber - boardSetting.boardForPlay[boardSetting.rowNumber + 1][chosenColumn];
	boardSetting.boardForPlay[rowNumberOfNewPiece][chosenColumn] = tokenOfPlayer;
	boardSetting.boardForPlay[boardSetting.rowNumber + 1][chosenColumn] += 1;
	int winState = calculateValueOfChosenGrid(tokenOfPlayer, rowNumberOfNewPiece, chosenColumn, boardSetting);
	if (winState >= 500) {
		return TOKENOFWINSTATE;
	}
	else if (winState <= -500) {
		return -TOKENOFWINSTATE;
	}
	else {
		return winState;
	}
}

int removeAPiece(ConnectFourBoard &boardSetting) {
	int chosenColumn = getAInteger(boardSetting.columnNumber);
	while ((boardSetting.boardForPlay[boardSetting.rowNumber+1][chosenColumn]) == 0) {
		cout << "Column " << chosenColumn << " is empty, please choose another column." << endl;
		chosenColumn = getAInteger(boardSetting.columnNumber);
	}
	int tokenRecord[BIGGESTROWNUMBER] = { 0 };
	int newNumberOfEachPiece = 0;
	int numberOfRemainPiece = boardSetting.boardForPlay[boardSetting.rowNumber + 1][chosenColumn] -1;
	boardSetting.boardForPlay[boardSetting.rowNumber + 1][chosenColumn] = 0;
	boardSetting.boardForPlay[boardSetting.rowNumber][chosenColumn] = TOKENOFEMPTYGRID;
	int winState = 0;
	int winStateBuffer = 0;
	// In case 2 players will win together.
	while(newNumberOfEachPiece < numberOfRemainPiece) {
		tokenRecord[newNumberOfEachPiece] = boardSetting.boardForPlay[boardSetting.rowNumber - newNumberOfEachPiece - 1][chosenColumn];
		boardSetting.boardForPlay[boardSetting.rowNumber - newNumberOfEachPiece-1][chosenColumn] = TOKENOFEMPTYGRID;
		newNumberOfEachPiece += 1;
	}
	newNumberOfEachPiece = 0;
	while (newNumberOfEachPiece < numberOfRemainPiece) {
		winStateBuffer = putNewPiece(tokenRecord[newNumberOfEachPiece], chosenColumn, boardSetting);
		newNumberOfEachPiece += 1;
		if (abs(winStateBuffer) == TOKENOFWINSTATE && winStateBuffer != winState) {
			if (winState == 0) {
				winState = winStateBuffer;
			}
			else {
				return TOKENOFTIEGAME;
			}
		}
	}
	return winState;
}

int evaluateTheValueOfTheColumn(int tokenOfPlayer, int chosenColumn, ConnectFourBoard &boardSetting) {
	int valueOfThisColumn = 0;
	int rowNumberOfVirtualPiece = boardSetting.rowNumber - boardSetting.boardForPlay[boardSetting.rowNumber + 1][chosenColumn];//put a virtual piece for calculate the value of next step
	if (boardSetting.boardForPlay[boardSetting.rowNumber + 1][chosenColumn] == boardSetting.rowNumber) {
		return valueOfThisColumn=0;
	}
	else{
		valueOfThisColumn += abs(calculateValueOfChosenGrid(tokenOfPlayer, rowNumberOfVirtualPiece, chosenColumn, boardSetting));
		valueOfThisColumn += abs(calculateValueOfChosenGrid(-tokenOfPlayer, rowNumberOfVirtualPiece, chosenColumn, boardSetting));
		if (boardSetting.boardForPlay[boardSetting.rowNumber + 1][chosenColumn] == boardSetting.rowNumber - 1) {
			return valueOfThisColumn;
		}
		else {
			putNewPiece(tokenOfPlayer, chosenColumn, boardSetting);//Put the virtual piece
			valueOfThisColumn -= abs(calculateValueOfChosenGrid(tokenOfPlayer, rowNumberOfVirtualPiece-1, chosenColumn, boardSetting))/2;//Next step get less value
			valueOfThisColumn -= abs(calculateValueOfChosenGrid(-tokenOfPlayer, rowNumberOfVirtualPiece-1, chosenColumn, boardSetting))/2;
			boardSetting.boardForPlay[boardSetting.rowNumber + 1][chosenColumn] -= 1;
			boardSetting.boardForPlay[rowNumberOfVirtualPiece][chosenColumn] = TOKENOFEMPTYGRID;//Remove virtual piece
			return valueOfThisColumn;
		}	
	}
}

int putAPieceByAI(int tokenOfPlayer, ConnectFourBoard boardSetting) {
	int mostValuableColumn = boardSetting.columnNumber/2 + 1;//if board is empty, put in the millde.
	for (int j = 1; j <= boardSetting.columnNumber; j++) {
		if (evaluateTheValueOfTheColumn(tokenOfPlayer,j, boardSetting)>
			evaluateTheValueOfTheColumn(tokenOfPlayer,mostValuableColumn, boardSetting)){
			mostValuableColumn = j;	
			}
	}
	return mostValuableColumn;
}
//




void startAGame() {
	int winState = 0; // 0:game is still going, 1: Player X win, 2:Player O win, 3: tie
	int turns = 0;
	ConnectFourBoard connectFour;
	int moveFirst = 1;

	if (connectFour.playWithAI) {
		cout << "input 1 to move FIRST, input 2 to move SECOND." << endl;
		moveFirst = getAInteger(2);
	}

	while (abs(winState) < 500) {
		if (connectFour.playRemoveMod) {
			cout << "Enter R to remove a piece or enter P to put a piece." << endl;
			char action = 'N';
			int checkBoardIsEmpty = 0;
			for (int j = 1; j <= connectFour.columnNumber; j++) {
				checkBoardIsEmpty += connectFour.boardForPlay[connectFour.rowNumber + 1][j];
			}
			string input;
			while (getline(cin, input)) {
				if (input.length() == 1 && ((input[0]=='R'&& checkBoardIsEmpty !=0)||input[0]=='P')) {
					action = input[0];
					break;
				}
				else if(input[0] == 'R' && checkBoardIsEmpty == 0){
					cout << "Board is empty, you can not remove a piece now.Please enter again." << endl;
				}
				else{
					cout << "Only R and P is legal, please enter again." << endl;
				}
			}
			switch (action) {
			case 'R':
				winState = removeAPiece(connectFour);
				turns += 1; 
				break;
			case 'P':
				winState = putNewPiece((turns % 2 ? -TOKENOFGRIDWITHPIECE : TOKENOFGRIDWITHPIECE), getChosenColumn(connectFour.boardForPlay, connectFour.columnNumber),connectFour);
				turns += 1; 
				break;
			}
		}else if (turns< connectFour.columnNumber* connectFour.rowNumber) {
			if (connectFour.playWithAI) {
				if ((turns + moveFirst) % 2) {
					winState = putNewPiece(TOKENOFGRIDWITHPIECE, getChosenColumn(connectFour.boardForPlay, connectFour.columnNumber), connectFour);
					turns += 1;
				}
				else {
					int columnAIChosen = putAPieceByAI(-TOKENOFGRIDWITHPIECE, connectFour);
					cout << "AI put piece on column " << columnAIChosen << endl;
					winState = putNewPiece(-TOKENOFGRIDWITHPIECE,columnAIChosen , connectFour);
					turns += 1;
				}
			}
			else {
				cout << "Player " << ((turns % 2) ? "O" : "X") << "'s turn!";
				winState = putNewPiece((turns % 2 ? -TOKENOFGRIDWITHPIECE : TOKENOFGRIDWITHPIECE), getChosenColumn(connectFour.boardForPlay, connectFour.columnNumber), connectFour);
				turns += 1;
			}	
		}
		else {
			winState = TOKENOFWINSTATE;
			break;
		}
		printBoard(connectFour.boardForPlay, connectFour.columnNumber, connectFour.rowNumber);
	}

	switch (winState) {
	case TOKENOFWINSTATE:cout << "Player X win the game!" << endl; turns = 0; break;
	case -TOKENOFWINSTATE:cout << "Player O win the game!" << endl; turns = 0; break;
	case TOKENOFTIEGAME:cout << "Game end in a draw!" << endl; turns = 0; break;
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
			answerFromUser = 'N';
			system("cls");
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
		else {
			exit(0);
		}
	}

}

