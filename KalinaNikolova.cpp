#include <iostream>
#include<vector>
#include<string>
#include <windows.h>
using namespace std;

class Figures {
public:
	string symbol;
	short  owner;
	Figures(short _owner, string _symbol):owner(_owner),symbol(_symbol) {
	}
	virtual void HowItMovesOrAttackes(short currentRow, char currentColumn, Figures* board[10][8]) = 0;
	virtual bool allowToMove(short currentRow, char currentColumn, short newRow, char newColumn, Figures* board[10][8]) = 0;
	virtual bool allowToAttack(short currentRow, char currentColumn, short newRow, char newColumn, Figures* board[10][8]) = 0;
	virtual void promote(short currentRow, char currentColumn, short newRow, char newColumn, Figures* board[10][8]) = 0;
	virtual vector<short>canTheAttackBeBlocked(vector<short>& vec, short figuresRow, char figuresColumn, short kingRow, char kingColumn, short row, char column, Figures* board[10][8]) = 0;
	void icon() {
		cout << symbol;
	}
	void movement(short currentRow, char currentColumn, short newRow, char newColumn, Figures* board[10][8]) {
		board[newRow][newColumn] = board[currentRow][currentColumn];
	}
	void putEmptySquare(short currentRow, char currentColumn, Figures* board[10][8]) {
		board[currentRow][currentColumn] = board[9][2];
	}
	bool isSquareEmpty(short i, char j, Figures* board[10][8]) {
		if (board[i][j]->owner == 3) {
			return true;
		}
		return false;
	}
	~Figures() {};
};
class Board {
public:
	Figures* board[10][8];
	~Board() {};
};
class EmptySquare : public Figures {
public:
	EmptySquare(short int _owner = 3, string _symbol = "  ") :Figures(_owner, _symbol) {
	}
	void HowItMovesOrAttackes(short currentRow, char currentColumn, Figures* board[10][8]) {}
	bool allowToMove(short currentRow, char currentColumn, short newRow, char newColumn, Figures* board[10][8]) {
		return true;
	}
	bool allowToAttack(short currentRow, char currentColumn, short newRow, char newColumn, Figures* board[10][8]) {
		return true;
	}
	void promote(short currentRow, char currentColumn, short newRow, char newColumn, Figures* board[10][8]) {}
	vector<short>canTheAttackBeBlocked(vector<short>& vec, short figuresRow, char figuresColumn, short kingRow, char kingColumn, short row, char column, Figures* board[10][8]) {
		return vec;
	}
	~EmptySquare() {};
};
class WhitePawn :public Figures {
public:
	WhitePawn(short int _owner = 1, string _symbol = "Wp") :Figures(_owner, _symbol) {
	}
	void HowItMovesOrAttackes(short currentRow, char currentColumn, Figures* board[10][8]) {
		cout << "\nA pawn moves straight forward one square, if that square is vacant."
			"\nIf it has not yet moved, a pawn also has the option of moving two squares straight forward, provided both squares are vacant. Pawns cannot move backwards"
			"\nA pawn can capture an enemy piece on either of the two squares diagonally in front of the pawn.\n";
	}
	bool allowToMove(short currentRow, char currentColumn, short newRow, char newColumn, Figures* board[10][8]) {
		if (board[currentRow][currentColumn]->owner == 1) {
			if (board[5][currentColumn]->owner == 3 && currentRow == 6 && newRow == 4 && currentColumn == newColumn) {
				return true;
			}
			else if (currentRow - newRow == 1 && currentColumn == newColumn) {
				return true;
			}
			return false;
		}
		else {
			if (board[2][currentColumn]->owner == 3 && currentRow == 1 && newRow == 3 && currentColumn == newColumn) {
				return true;
			}
			else if (newRow - currentRow == 1 && currentColumn == newColumn) {
				return true;
			}
			return false;
		}
	}
	bool allowToAttack(short currentRow, char currentColumn, short newRow, char newColumn, Figures* board[10][8]) {
		if (board[currentRow][currentColumn]->owner == 1) {
			if (currentRow - newRow == 1&&((currentColumn - newColumn == 1)|| (newColumn - currentColumn == 1))) {
					return true;
			}
			return false;
		}
		else {
			if (newRow - currentRow == 1&&((currentColumn - newColumn == 1)|| (newColumn - currentColumn == 1))) {
				return true;
			}
			return false;
		}
	}
    void promote(short currentRow, char currentColumn, short newRow, char newColumn, Figures* board[10][8]) {
		if (newRow == 7) {
			cout << "\nCongratulations! You can promote your rawn\n";
			cout << "\nFor Rook press 1,\n for Knight press 2,\n for Bishop press 3,\n for Queen press 4.\n";
			short promote;
			cin >> promote;
			switch (promote) {
			case 1:board[newRow][newColumn] = board[8][7]; break;
			case 2:board[newRow][newColumn] = board[8][6]; break;
			case 3:board[newRow][newColumn] = board[8][5]; break;
			case 4:board[newRow][newColumn] = board[8][4]; break;
			}
		}
		else if (newRow == 0) {
			cout << "\nCongratulations! You can promote your rawn\n";
			cout << "\nFor Rook press 1,\n for Knight press 2,\n for Bishop press 3,\n for Queen press 4.\n";
			short promote;
			cin >> promote;
			switch (promote) {
			case 1:board[newRow][newColumn] = board[8][0]; break;
			case 2:board[newRow][newColumn] = board[8][1]; break;
			case 3:board[newRow][newColumn] = board[8][2]; break;
			case 4:board[newRow][newColumn] = board[8][3]; break;
			}
		}

	}
	vector<short>canTheAttackBeBlocked(vector<short>& vec, short figuresRow, char figuresColumn, short kingRow, char kingColumn, short row, char column, Figures* board[10][8]) {
		return vec;
	}
	~WhitePawn() {};
};
class BlackPawn :public WhitePawn {
public:
	BlackPawn(short int _owner = 2, string _symbol = "Bp") :WhitePawn(_owner, _symbol) {
	}
	~BlackPawn() {};
};
class WhiteKnight :public Figures {
public:
	WhiteKnight(short int _owner = 1, string _symbol = "Wk") :Figures(_owner, _symbol) {
	}
	void HowItMovesOrAttackes(short currentRow, char currentColumn, Figures* board[10][8]) {
		cout << "\nA knight moves to the nearest square not on the same rank, file, or diagonal.\n";
	}
	bool allowToMove(short currentRow, char currentColumn, short newRow, char newColumn, Figures* board[10][8]) {
		short a = currentRow - newRow;
		short b = currentColumn - newColumn;
		short c = abs(a) - abs(b);
		if (c==1||c==-1){
			return true;
		}
		return false;
	}
	bool allowToAttack(short currentRow, char currentColumn, short newRow, char newColumn, Figures* board[10][8]) {
		if (board[currentRow][currentColumn]->allowToMove(currentRow, currentColumn, newRow, newColumn, board) == true) {
			return true;
		}
		return false;
	}
	void promote(short currentRow, char currentColumn, short newRow, char newColumn, Figures* board[10][8]) {}
	vector<short>canTheAttackBeBlocked(vector<short>& vec, short figuresRow, char figuresColumn, short kingRow, char kingColumn, short row, char column, Figures* board[10][8]) {
		return vec;
	}
	~WhiteKnight() {};
};
class BlackKnight :public WhiteKnight {
public:
	BlackKnight(short int _owner = 2, string _symbol = "Bk") :WhiteKnight(_owner, _symbol) {
	}
	~BlackKnight() {};
};
class WhiteBishop :public Figures {
public:
	WhiteBishop(short int _owner = 1, string _symbol = "Wb") :Figures(_owner, _symbol) {
	}
	void HowItMovesOrAttackes(short currentRow, char currentColumn, Figures* board[10][8]) {
		cout << "\nA bishop moves any number of vacant squares diagonally.\n";
	}
	bool allowToMove(short currentRow, char currentColumn, short newRow, char newColumn, Figures* board[10][8]) {
		short counter = 0;
		if (abs(currentRow - newRow)==abs(currentColumn - newColumn)) {
			if (currentRow < newRow && currentColumn > newColumn) {
				for (short i = currentRow + 1; i < newRow; i++) {
					char j = currentColumn - i + currentRow;
					if (isSquareEmpty(i, j, board) == true) {
						counter++;
					}
				}
			}
			else if (currentRow < newRow && currentColumn < newColumn) {
				for (short i = currentRow + 1; i < newRow; i++) {
					char j = currentColumn + i - currentRow;
					if (isSquareEmpty(i, j, board) == true) {
						counter++;
					}
				}
			}
			else if (currentRow > newRow && currentColumn > newColumn) {
				for (short i = currentRow - 1; i > newRow; i--) {
					char j = currentColumn + i - currentRow;
					if (isSquareEmpty(i, j, board) == true) {
						counter++;
					}
				}
			}
			else if (currentRow > newRow && currentColumn < newColumn) {
				for (short i = currentRow - 1; i > newRow; i--) {
					char j = currentColumn - i + currentRow;
					if (isSquareEmpty(i, j, board) == true) {
						counter++;
					}
				}
			}
		}
		if (counter + 1 == abs(currentRow - newRow)) {
			return true;
		}
		return false;
	}
	bool allowToAttack(short currentRow, char currentColumn, short newRow, char newColumn, Figures* board[10][8]){ 
		if (board[currentRow][currentColumn]->allowToMove(currentRow, currentColumn, newRow, newColumn, board) == true) {
			return true;
		}
		return false;
	}
	void promote(short currentRow, char currentColumn, short newRow, char newColumn, Figures* board[10][8]) {}
	vector<short>canTheAttackBeBlocked(vector<short>& vec, short figuresRow, char figuresColumn, short kingRow, char kingColumn, short row, char column, Figures* board[10][8]) {
		if (figuresRow < kingRow && figuresColumn > kingColumn) {
			for (short i = figuresRow + 1; i <= kingRow; i++) {
				char j = figuresColumn - i + figuresRow;
				if (board[i][j]->owner == 3) {
					if (board[row][column]->allowToMove(row, column, i, j, board) == true) {
						vec.push_back(1);
					}
				}
			}
		}
		else if (figuresRow < kingRow && figuresColumn < kingColumn) {
			for (short i = figuresRow + 1; i <= kingRow; i++) {
				char j = figuresColumn + i - figuresRow;
				if (board[i][j]->owner == 3) {
					if (board[row][column]->allowToMove(row, column, i, j, board) == true) {
						vec.push_back(1);
					}
				}
			}
		}
		else if (figuresRow > kingRow && figuresColumn > kingColumn) {
			for (short i = figuresRow - 1; i >= kingRow; i--) {
				char j = figuresColumn + i - figuresRow;
				if (board[i][j]->owner == 3) {
					if (board[row][column]->allowToMove(row, column, i, j, board) == true) {
						vec.push_back(1);
					}
				}
			}
		}
		else if (figuresRow > kingRow && figuresColumn < kingColumn) {
			for (short i = figuresRow - 1; i >= kingRow; i--) {
				char j = figuresColumn - i + figuresRow;
				if (board[i][j]->owner != 3) {
					if (board[i][j]->owner == 3) {
						if (board[row][column]->allowToMove(row, column, i, j, board) == true) {
							vec.push_back(1);
						}
					}
				}
			}
		}
		return vec;
	}
	~WhiteBishop() {};
};
class BlackBishop :public WhiteBishop {
public:
	BlackBishop(short int _owner = 2, string _symbol = "Bb") :WhiteBishop(_owner, _symbol) {
	}
	~BlackBishop() {};
};
class WhiteRook :public Figures {
public:
	WhiteRook(short int _owner = 1, string _symbol = "Wr") :Figures(_owner, _symbol) {
	}
	void HowItMovesOrAttackes(short currentRow, char currentColumn, Figures* board[10][8]) {
		cout << "\nA rook moves any number of vacant squares horizontally or vertically.\n";
	}
	bool allowToMove(short currentRow, char currentColumn, short newRow, char newColumn, Figures* board[10][8]) {
		short counter = 0;
		if (currentRow == newRow) {
			if (currentColumn > newColumn) {
				short i = currentRow;
				for (char j = currentColumn - 1; j > newColumn; j--) {
					if (isSquareEmpty(i, j, board) == true) {
						counter++;
					}
				}
			}
			else if (currentColumn < newColumn) {
				short i = currentRow;
				for (char j = currentColumn + 1; j < newColumn; j++) {
					if (isSquareEmpty(i, j, board) == true) {
						counter++;
					}
				}
			}
		}
		else if (newColumn == currentColumn) {
			if (currentRow > newRow) {
				for (short i = currentRow - 1; i > newRow; i--) {
					char j = newColumn;
					if (isSquareEmpty(i, j, board) == true) {
						counter++;
					}
				}
			}
			else if (currentRow < newRow) {
				for (short i = currentRow + 1; i < newRow; i++) {
					char j = newColumn;
					if (isSquareEmpty(i, j, board) == true) {
						counter++;
					}
				}
			}
			if (counter + 1 == abs(currentRow - newRow)) {
				return true;
			}
		}
		return false;
	}
	bool allowToAttack(short currentRow, char currentColumn, short newRow, char newColumn, Figures* board[10][8]) {
		if (board[currentRow][currentColumn]->allowToMove(currentRow, currentColumn, newRow, newColumn, board) == true) {
			return true;
		}
		return false;
	}
	void promote(short currentRow, char currentColumn, short newRow, char newColumn, Figures* board[10][8]) {}
	vector<short>canTheAttackBeBlocked(vector<short>& vec, short figuresRow, char figuresColumn, short kingRow, char kingColumn, short row, char column, Figures* board[10][8]) {
		if (figuresRow == kingRow) {
			if (figuresColumn > kingColumn) {
				short i = figuresRow;
				for (char j = figuresColumn - 1; j >= kingColumn; j--) {
					if (board[i][j]->owner == 3) {
						if (board[row][column]->allowToMove(row, column, i, j, board) == true) {
							vec.push_back(1);
						}
					}
				}
			}
			else if (figuresColumn < kingColumn) {
				short i = figuresRow;
				for (char j = figuresColumn + 1; j <= kingColumn; j++) {
					if (board[i][j]->owner == 3) {
						if (board[row][column]->allowToMove(row, column, i, j, board) == true) {
							vec.push_back(1);
						}
					}
				}
			}
		}
		else if (kingColumn == figuresColumn) {
			if (figuresRow > kingRow) {
				for (short i = figuresRow - 1; i >= kingRow; i--) {
					char j = kingColumn;
					if (board[i][j]->owner == 3) {
						if (board[row][column]->allowToMove(row, column, i, j, board) == true) {
							vec.push_back(1);
						}
					}
				}
			}
			else if (figuresRow < kingRow) {
				for (short i = figuresRow + 1; i <= kingRow; i++) {
					char j = kingColumn;
					if (board[i][j]->owner == 3) {
						if (board[row][column]->allowToMove(row, column, i, j, board) == true) {
							vec.push_back(1);
						}
					}
				}
			}
		}
		return vec;
	}
	~WhiteRook() {};
};
class BlackRook :public WhiteRook {
public:
	BlackRook(short int _owner = 2, string _symbol = "Br") :WhiteRook(_owner, _symbol) {
	}
	~BlackRook() {};
};
class WhiteQueen :public Figures {
public:
	WhiteQueen(short int _owner = 1, string _symbol = "Wq") :Figures(_owner, _symbol) {
	}
	void HowItMovesOrAttackes(short currentRow, char currentColumn, Figures* board[10][8]) {
		cout << "\nThe queen moves any number of vacant squares horizontally, vertically, or diagonally.\n";
	}
	bool allowToMove(short currentRow, char currentColumn, short newRow, char newColumn, Figures* board[10][8]) {
		int counter = 0;
		if (newRow == currentRow || newColumn == currentColumn) {
			if (currentRow == newRow) {
				if (currentColumn > newColumn) {
					short i = currentRow;
					for (char j = currentColumn - 1; j > newColumn; j--) {
						if (isSquareEmpty(i, j, board) == true) {
							counter++;
						}
					}
				}
				else if (currentColumn < newColumn) {
					short i = currentRow;
					for (char j = currentColumn + 1; j < newColumn; j++) {
						if (isSquareEmpty(i, j, board) == true) {
							counter++;
						}
					}
				}
			}
			else if (newColumn == currentColumn) {
				if (currentRow > newRow) {
					for (short i = currentRow - 1; i > newRow; i--) {
						char j = newColumn;
						if (isSquareEmpty(i, j, board) == true) {
							counter++;
						}
					}
				}
				else if (currentRow < newRow) {
					for (short i = currentRow + 1; i < newRow; i++) {
						char j = newColumn;
						if (isSquareEmpty(i, j, board) == true) {
							counter++;
						}
					}
				}
			}
			if (counter + 1 == abs(currentRow - newRow) || counter + 1 == abs(currentColumn - newColumn)) {
				return true;
			}
		}
		else if (abs(currentRow - newRow) == abs(currentColumn - newColumn)) {
			if (currentRow < newRow && currentColumn > newColumn) {
				for (short i = currentRow + 1; i < newRow; i++) {
					char j = currentColumn - i + currentRow;
					if (isSquareEmpty(i, j, board) == true) {
						counter++;
					}
				}
			}
			else if (currentRow < newRow&& currentColumn < newColumn) {
				for (short i = currentRow + 1; i < newRow; i++) {
					char j = currentColumn + i - currentRow;
					if (isSquareEmpty(i, j, board) == true) {
						counter++;
					}
				}
			}
			else if (currentRow > newRow && currentColumn > newColumn) {
				for (short i = currentRow - 1; i > newRow; i--) {
					char j = currentColumn + i - currentRow;
					if (isSquareEmpty(i, j, board) == true) {
						counter++;
					}
				}
			}
			else if (currentRow > newRow && currentColumn < newColumn) {
				for (short i = currentRow - 1; i > newRow; i--) {
					char j = currentColumn - i + currentRow;
					if (isSquareEmpty(i, j, board) == true) {
						counter++;
					}
				}
			}
			if (counter + 1 == abs(currentRow - newRow)) {
				return true;
			}
		}
		return false;
		}
	bool allowToAttack(short currentRow, char currentColumn, short newRow, char newColumn, Figures * board[10][8]) {
			if (board[currentRow][currentColumn]->allowToMove(currentRow, currentColumn, newRow, newColumn, board) == true) {
				return true;
			}
			return false;
		}
	void promote(short currentRow, char currentColumn, short newRow, char newColumn, Figures * board[10][8]) {}
	vector<short>canTheAttackBeBlocked(vector<short> & vec, short figuresRow, char figuresColumn, short kingRow, char kingColumn, short row, char column, Figures * board[10][8]) {
			if (kingRow == figuresRow || kingColumn == figuresColumn) {
						if (figuresRow == kingRow) {
							if (figuresColumn > kingColumn) {
								short i = figuresRow;
								for (char j = figuresColumn - 1; j >= kingColumn; j--) {
									if (board[i][j]->owner == 3) {
										if (board[row][column]->allowToMove(row, column, i, j, board) == true) {
											vec.push_back(1);
										}
									}
								}
							}
							else if (figuresColumn < kingColumn) {
								short i = figuresRow;
								for (char j = figuresColumn + 1; j <= kingColumn; j++) {
									if (board[i][j]->owner == 3) {
										if (board[row][column]->allowToMove(row, column, i, j, board) == true) {
											vec.push_back(1);
										}
									}
								}
							}
						}
						else if (kingColumn == figuresColumn) {
							if (figuresRow > kingRow) {
								for (short i = figuresRow - 1; i >= kingRow; i--) {
									char j = kingColumn;
									if (board[i][j]->owner == 3) {
										if (board[row][column]->allowToMove(row, column, i, j, board) == true) {
											vec.push_back(1);
										}
									}
								}
							}
							else if (figuresRow < kingRow) {
								for (short i = figuresRow + 1; i <= kingRow; i++) {
									char j = kingColumn;
									if (board[i][j]->owner == 3) {
										if (board[row][column]->allowToMove(row, column, i, j, board) == true) {
											vec.push_back(1);
										}
									}
								}
							}
						}
			}
			if (figuresRow < kingRow && figuresColumn > kingColumn) {
				for (short i = figuresRow + 1; i <= kingRow; i++) {
					char j = figuresColumn - i + figuresRow;
					if (board[i][j]->owner == 3) {
						if (board[row][column]->allowToMove(row, column, i, j, board) == true) {
							vec.push_back(1);
						}
					}
				}
			}
			else if (figuresRow < kingRow && figuresColumn < kingColumn) {
				for (short i = figuresRow + 1; i <= kingRow; i++) {
					char j = figuresColumn + i - figuresRow;
					if (board[i][j]->owner == 3) {
						if (board[row][column]->allowToMove(row, column, i, j, board) == true) {
							vec.push_back(1);
						}
					}
				}
			}
			else if (figuresRow > kingRow && figuresColumn > kingColumn) {
				for (short i = figuresRow - 1; i >= kingRow; i--) {
					char j = figuresColumn + i - figuresRow;
					if (board[i][j]->owner == 3) {
						if (board[row][column]->allowToMove(row, column, i, j, board) == true) {
							vec.push_back(1);
						}
					}
				}
			}
			else if (figuresRow > kingRow && figuresColumn < kingColumn) {
				for (short i = figuresRow - 1; i >= kingRow; i--) {
					char j = figuresColumn - i + figuresRow;
					if (board[i][j]->owner != 3) {
						if (board[i][j]->owner == 3) {
							if (board[row][column]->allowToMove(row, column, i, j, board) == true) {
								vec.push_back(1);
							}
						}
					}
				}
			}
			return vec;
		}
	~WhiteQueen() {};
	};
class BlackQueen :public WhiteQueen {
public:
	BlackQueen(short int _owner = 2, string _symbol = "Bq") :WhiteQueen(_owner, _symbol) {
	}
	~BlackQueen() {};
};
class WhiteKing :public Figures {
public:
	WhiteKing(short int _owner = 1, string _symbol = "WK") :Figures(_owner, _symbol) {
	}
	void HowItMovesOrAttackes(short currentRow, char currentColumn, Figures* board[10][8]) {
		cout << "\nThe king moves exactly one square horizontally, vertically, or diagonally. A special move with the king known as castling is allowed only once per player, per game.\n";
	}
	bool allowToMove(short currentRow, char currentColumn, short newRow, char newColumn, Figures* board[10][8]) {
		if (board[currentRow][currentColumn]->owner == 1) {
			if ((currentRow - newRow == 0 || currentRow - newRow == 1 || currentRow - newRow == -1) && (currentColumn - newColumn == 1 || currentColumn - newColumn == 0 || currentColumn - newColumn == -1))
			{
				board[newRow][newColumn] = board[currentRow][currentColumn];
				for (short i = 0; i < 8; i++) {
					for (char j = 0; j < 8; j++) {
						if (board[i][j]->owner == 2) {
							if (board[i][j]->allowToAttack(i, j, newRow, newColumn, board) == true) {
								board[newRow][newColumn]->putEmptySquare(newRow, newColumn, board);
								return false;
							}
						}
					}
				}
				return true;
			}
			if (currentRow == newRow && newRow == 7 && currentColumn == 4 && newColumn == 2 && board[7][3]->owner == 3 && board[7][2]->owner == 3 && board[7][1]->owner == 3 && board[7][0]->symbol == "Wr") {
				board[newRow][newColumn] = board[currentRow][currentColumn];
				for (short i = 0; i < 8; i++) {
					for (char j = 0; j < 8; j++) {
						if (board[i][j]->owner == 2) {
							if (board[i][j]->allowToAttack(i, j, newRow, newColumn, board) == true) {
								board[newRow][newColumn]->putEmptySquare(newRow, newColumn, board);
								return false;
							}
						}
					}
				}
				board[7][3] = board[8][0];
				board[7][0]->putEmptySquare(7, 0, board);
				return true;
			}
			if (currentRow == newRow && newRow == 7 && currentColumn == 4 && newColumn == 6 && board[7][5]->owner == 3 && board[7][6]->owner == 3 && board[7][7]->symbol == "Wr") {
				board[newRow][newColumn] = board[currentRow][currentColumn];
				for (short i = 0; i < 8; i++) {
					for (char j = 0; j < 8; j++) {
						if (board[i][j]->owner == 2) {
							if (board[i][j]->allowToAttack(i, j, newRow, newColumn, board) == true) {
								board[newRow][newColumn]->putEmptySquare(newRow, newColumn, board);
								return false;
							}
						}
					}
				}
				board[7][5] = board[8][0];
				board[7][7]->putEmptySquare(7, 7, board);
				return true;
			}
			return false;
		}
		else {
			if ((currentRow - newRow == 0 || currentRow - newRow == 1 || currentRow - newRow == -1) && (currentColumn - newColumn == 1 || currentColumn - newColumn == 0 || currentColumn - newColumn == -1))
			{
				board[newRow][newColumn] = board[currentRow][currentColumn];
				for (short i = 0; i < 8; i++) {
					for (char j = 0; j < 8; j++) {
						if (board[i][j]->owner == 1) {
							if (board[i][j]->allowToAttack(i, j, newRow, newColumn, board) == true) {
								board[newRow][newColumn]->putEmptySquare(newRow, newColumn, board);
								return false;
							}
						}
					}
				}
				return true;
			}
			if (currentRow == newRow && newRow == 0 && currentColumn == 4 && newColumn == 2 && board[0][3]->owner == 3 && board[0][2]->owner == 3 && board[0][1] && board[0][0]->symbol == "Br") {
				board[newRow][newColumn] = board[currentRow][currentColumn];
				for (short i = 0; i < 8; i++) {
					for (char j = 0; j < 8; j++) {
						if (board[i][j]->owner == 1) {
							if (board[i][j]->allowToAttack(i, j, newRow, newColumn, board) == true) {
								board[newRow][newColumn]->putEmptySquare(newRow, newColumn, board);
								return false;
							}
						}
					}
				}
				board[0][3] = board[8][7];
				board[0][0]->putEmptySquare(0, 0, board);
				return true;
			}
			if (currentRow == newRow && newRow == 0 && currentColumn == 4 && newColumn == 6 && board[0][5]->owner == 3 && board[0][6]->owner == 3 && board[0][7]->symbol == "Br") {
				board[newRow][newColumn] = board[currentRow][currentColumn];
				for (short i = 0; i < 8; i++) {
					for (char j = 0; j < 8; j++) {
						if (board[i][j]->owner == 1) {
							if (board[i][j]->allowToAttack(i, j, newRow, newColumn, board) == true) {
								board[newRow][newColumn]->putEmptySquare(newRow, newColumn, board);

								return false;
							}
						}
					}
				}
				board[0][5] = board[8][7];
				board[0][0]->putEmptySquare(0, 7, board);
				return true;
			}
			return false;
		}
	 }
	bool allowToAttack(short currentRow, char currentColumn, short newRow, char newColumn, Figures* board[10][8]) {
		 if (board[currentRow][currentColumn]->owner==1) {
			 if ((currentRow - newRow == 0 || currentRow - newRow == 1 || currentRow - newRow == -1) && (currentColumn - newColumn == 1 || currentColumn - newColumn == 0 || currentColumn - newColumn == -1))
			 {
				 board[newRow][newColumn] = board[currentRow][currentColumn];
				 for (short i = 0; i < 8; i++) {
					 for (char j = 0; j < 8; j++) {
						 if (board[i][j]->owner == 2) {
							 if (board[i][j]->allowToAttack(i, j, newRow, newColumn, board) == true) {
								 board[newRow][newColumn]->putEmptySquare(newRow, newColumn, board);
								 return false;
							 }
						 }
					 }
				 }
				 return true;
			 }
			 return false;
		 }
		 else {
			 if ((currentRow - newRow == 0 || currentRow - newRow == 1 || currentRow - newRow == -1) && (currentColumn - newColumn == 1 || currentColumn - newColumn == 0 || currentColumn - newColumn == -1))
			 {
				 board[newRow][newColumn] = board[currentRow][currentColumn];
				 for (short i = 0; i < 8; i++) {
					 for (char j = 0; j < 8; j++) {
						 if (board[i][j]->owner == 1) {
							 if (board[i][j]->allowToAttack(i, j, newRow, newColumn, board) == true) {
								 board[newRow][newColumn]->putEmptySquare(newRow, newColumn, board);
								 return false;
							 }
						 }
					 }
				 }
				 return true;
			 }
			 return false;
		 }
	}
	void promote(short currentRow, char currentColumn, short newRow, char newColumn, Figures* board[10][8]) {}
	vector<short>canTheAttackBeBlocked(vector<short>& vec, short figuresRow, char figuresColumn, short kingRow, char kingColumn, short row, char column, Figures* board[10][8]) {
		return vec;
	}
	~WhiteKing() {};
};
class BlackKing :public WhiteKing {
public:
	BlackKing(short int _owner = 2, string _symbol = "BK") :WhiteKing(_owner, _symbol) {
	}
	~BlackKing() {};
};
class Game :public Board {
	WhitePawn WP; WhiteKnight WK; WhiteBishop WB; WhiteRook WR; WhiteQueen WQ; WhiteKing Wk; 
	BlackPawn BP; BlackKnight BK; BlackBishop BB; BlackRook BR; BlackQueen BQ; BlackKing Bk; EmptySquare EM;
public:
	Game() {}
	vector<int>possibleEscapeMoves;
	vector<int>movesMade1;
	vector<int>movesMade2;
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	void fillBoard() {
		for (short i = 0; i < 10; i++) {
			for (short j = 0; j < 8; j++) {
				if ((i == 0 && j == 0) || (i == 0 && j == 7) || (i == 8 && j == 7)) {
					Figures* ptr = &BR;
					board[i][j] = ptr;
				}
				else if ((i == 0 && j == 1) || (i == 0 && j == 6) || (i == 8 && j == 6)) {
					Figures* ptr = &BK;
					board[i][j] = ptr;
				}
				else if ((i == 0 && j == 2) || (i == 0 && j == 5) || (i == 8 && j == 5)) {
					Figures* ptr = &BB;
					board[i][j] = ptr;
				}
				else if ((i == 0 && j == 3) || (i == 8 && j == 4)) {
					Figures* ptr = &BQ;
					board[i][j] = ptr;
				}
				else if (i == 0 && j == 4) {
					Figures* ptr = &Bk;
					board[i][j] = ptr;
				}
				else if (i == 1 || (i == 9 && j == 0)) {
					Figures* ptr = &BP;
					board[i][j] = ptr;
				}
				else if (i == 6 || (i == 9 && j == 1)) {
					Figures* ptr = &WP;
					board[i][j] = ptr;
				}
				else if ((i == 7 && j == 0) || (i == 7 && j == 7) || (i == 8 && j == 0)) {
					Figures* ptr = &WR;
					board[i][j] = ptr;
				}
				else if ((i == 7 && j == 1) || (i == 7 && j == 6) || (i == 8 && j == 1)) {
					Figures* ptr = &WK;
					board[i][j] = ptr;
				}
				else if ((i == 7 && j == 2) || (i == 7 && j == 5) || (i == 8 && j == 2)) {
					Figures* ptr = &WB;
					board[i][j] = ptr;
				}
				else if ((i == 7 && j == 3) || (i == 8 && j == 3)) {
					Figures* ptr = &WQ;
					board[i][j] = ptr;
				}
				else if (i == 7 && j == 4) {
					Figures* ptr = &Wk;
					board[i][j] = ptr;
				}
				else {
					Figures* ptr = &EM;
					board[i][j] = ptr;
				}
			}
		}
	}
	void printBoard1() {
		string a = "               ";   //15
		string b = "---";
		cout << endl << endl << endl;
		cout << a << b;
		cout << '|';
		for (char i = 'A'; i < 'I'; i++)
		{
			cout << ' ' << i << '|';
		}
		cout << b;
		cout << endl;
		cout << a;
		for (short i = 0; i < 10; i++) {
			cout << b;
		}
		cout << '-';
		cout << endl;
		int number = 8;
		for (short i = 0; i < 8; i++) {
			cout << a;
			cout << '-' << number << '-' << '|';
			for (short j = 0; j < 8; j++) {
				if ((i + j) % 2 == 0) {
					if (board[i][j]->owner == 1 || board[i][j]->owner == 3) {
						SetConsoleTextAttribute(hConsole, 241);
					}
					else {
						SetConsoleTextAttribute(hConsole, 244);
					}
				}
				else {
					if (board[i][j]->owner == 1 || board[i][j]->owner == 3) {
						SetConsoleTextAttribute(hConsole, 1);
					}
					else {
						SetConsoleTextAttribute(hConsole, 4);
					}
				}
				board[i][j]->icon();
				SetConsoleTextAttribute(hConsole, 7);
				cout << '|';
			}
			cout << '-' << number << '-';
			number--;
			cout << endl;
			cout << a;
			for (short i = 0; i < 10; i++) {
				cout << b;
			}
			cout << '-';
			cout << endl;
		}
		cout << a << b << '|';
		for (char i = 'A'; i < 'I'; i++)
		{
			cout << ' ' << i << '|';
		}
		cout << b;
		cout << endl << endl;
		SetConsoleTextAttribute(hConsole, 1);
		cout << "             Player 1-white(W),";
		SetConsoleTextAttribute(hConsole, 4);
		cout << "Player 2 - black(B)\n\n";
		SetConsoleTextAttribute(hConsole, 7);
		cout << "       p-pawn; r-rook; k-knight; b-bishop; q-queen; K-king.\n";
		cout << endl << endl;
	}
	void printBoard2() {
		string a = "               ";  //15
		string b = "---";
		cout << endl << endl << endl;
		cout << a << b;
		cout << '|';
		for (char i = 'H'; i >= 'A'; i--)
		{
			cout << ' ' << i << '|';
		}
		cout << b;
		cout << endl;
		cout << a;
		for (short i = 0; i < 9; i++) {
			cout << b;
		}
		cout << '-';
		cout << endl;
		int number = 1;
		for (short i = 7; i >= 0; i--) {
			cout << a;
			cout << '-' << number << '-' << '|';
			for (short j = 7; j >= 0; j--) {
				if ((i + j) % 2 == 0) {
					if (board[i][j]->owner == 1 || board[i][j]->owner == 3) {
						SetConsoleTextAttribute(hConsole, 241);
					}
					else {
						SetConsoleTextAttribute(hConsole, 244);
					}
				}
				else {
					if (board[i][j]->owner == 1 || board[i][j]->owner == 3) {
						SetConsoleTextAttribute(hConsole, 1);
					}
					else {
						SetConsoleTextAttribute(hConsole, 4);
					}
				}
				board[i][j]->icon();
				SetConsoleTextAttribute(hConsole, 7);
				cout << '|';
			}
			cout << '-' << number << '-';
			number++;
			cout << endl;
			cout << a;
			for (short i = 0; i < 9; i++) {
				cout << b;
			}
			cout << '-';
			cout << endl;
		}
		cout << a << b << '|';
		for (char i = 'H'; i >= 'A'; i--)
		{
			cout << ' ' << i << '|';
		}
		cout << b;
		cout << endl << endl;;
		SetConsoleTextAttribute(hConsole, 1);
		cout << "             Player 1-white(W),";
		SetConsoleTextAttribute(hConsole, 4);
		cout << "Player 2 - black(B)\n\n";
		SetConsoleTextAttribute(hConsole, 7);
		cout << "       p-pawn; r-rook; k-knight; b-bishop; q-queen; K-king.\n";
		cout << endl << endl;
	}
	void swap(short x, char y, short x1, char y1, Figures* board[10][8]) {
		board[x1][y1]->movement(x1, y1, 9, 7, board);
		board[x][y]->movement(x, y, x1, y1, board);
		board[x][y]->putEmptySquare(x, y, board);
	}
	void swapBack(short x, char y, short x1, char y1, Figures* board[10][8]) {
		board[x1][y1]->movement(x1, y1, x, y, board);
		board[9][7]->movement(9, 7, x1, y1, board);
	}
	bool player1(short x, char y, short x1, char y1) {
		if (board[x1][y1]->owner == 3) {
			if (board[x][y]->allowToMove(x, y, x1, y1, board) == true) {
				board[x1][y1]->movement(x, y, x1, y1, board);
				board[x][y]->putEmptySquare(x, y, board);
				board[x1][y1]->promote(x, y, x1, y1, board);
				return true;
			}
		}
		else if (board[x1][y1]->owner == 2) {
			if (board[x][y]->allowToAttack(x, y, x1, y1, board) == true) {
				board[x1][y1]->movement(x, y, x1, y1, board);
				board[x][y]->putEmptySquare(x, y, board);
				board[x1][y1]->promote(x, y, x1, y1, board);
				return true;
			}
		}
		return false;
	}
	bool player2(short x, char y, short x1, char y1) {
		if (board[x1][y1]->owner == 3) {
			if (board[x][y]->allowToMove(x, y, x1, y1, board) == true) {
				board[x1][y1]->movement(x, y, x1, y1, board);
				board[x][y]->putEmptySquare(x, y, board);
				board[x1][y1]->promote(x, y, x1, y1, board);
				return true;
			}
		}
		else if (board[x1][y1]->owner == 1) {
			if (board[x][y]->allowToAttack(x, y, x1, y1, board) == true) {
				board[x1][y1]->movement(x, y, x1, y1, board);
				board[x][y]->putEmptySquare(x, y, board);
				board[x1][y1]->promote(x, y, x1, y1, board);
				return true;
			}
		}
		return false;
	}
	bool isBlackKingUnderAttack() {
		for (short kingRow = 0; kingRow < 8; kingRow++) {
			for (char kingColumn = 0; kingColumn < 8; kingColumn++) {
				if (board[kingRow][kingColumn]->symbol == "BK") {
					for (short i = 0; i < 8; i++) {
						for (char j = 0; j < 8; j++) {
							if (board[i][j]->owner == 1) {
								if (board[i][j]->allowToAttack(i, j, kingRow, kingColumn, board) == true) {
									return true;
								}
							}
						}
					}
					return false;
				}
			}
		}
	}
	bool isWhiteKingUnderAttack() {
		for (short kingRow = 8; kingRow >=0; kingRow--) {
			for (char kingColumn = 0; kingColumn < 8; kingColumn++) {
				if (board[kingRow][kingColumn]->symbol == "WK") {
					for (short i = 0; i < 8; i++) {
						for (char j = 0; j < 8; j++) {
							if (board[i][j]->owner == 2) {
								if (board[i][j]->allowToAttack(i, j, kingRow, kingColumn, board) == true) {
									return true;
								}
							}
						}
					}
					return false;
				}
			}
		}
	}
	bool willKingUnderAttack(short x, char y, short x1, char y1, Figures* board[10][8]){
	swap(x, y, x1, y1, board);
	    if(board[x1][y1]->owner==1){
		    if (isWhiteKingUnderAttack() == true) {
			    swapBack(x, y, x1, y1, board);
			    return true;
		}
	}
	else {
			if (isBlackKingUnderAttack() == true) {
				swapBack(x, y, x1, y1, board);
				return true;
			}
	}
	swapBack(x, y, x1, y1, board);
	return false;
	}
	vector<short> possibleEscapeMovesBlackKing(vector<short>possibleMoves, short figuresRow, char figuresColumn, short kingRow, char kingColumn, Figures* board[10][8]) {
		for (short row = 0; row < 8; row++) {
			for (char column = 0; column < 8; column++) {
				if (board[row][column]->owner == 3) {
					if (board[kingRow][kingColumn]->allowToMove(kingRow, kingColumn, row, column, board) == true) {
						possibleMoves.push_back(1);
					}
				}
				else if (board[row][column]->owner == 2) {
					if (willKingUnderAttack(row, column, figuresRow, figuresColumn, board) == false) {
						if (board[row][column]->allowToAttack(row, column, figuresRow, figuresColumn, board) == true) {
							possibleMoves.push_back(1);
						}
						else if(board[figuresRow][figuresColumn]->canTheAttackBeBlocked(possibleMoves, figuresRow, figuresColumn, kingRow, kingColumn, row, column, board).size()!=0) {
							possibleMoves.push_back(1);
						}
					}
				}
				else if (board[row][column]->owner == 1) {
					if (board[kingRow][kingColumn]->allowToAttack(kingRow, kingColumn, row, column, board) == true) {
						possibleMoves.push_back(1);
					}
				}
			}
		}
		return possibleMoves;
	}
	vector<short> possibleEscapeMovesWhiteKing(vector<short>possibleMoves, short figuresRow, char figuresColumn, short kingRow, char kingColumn, Figures* board[10][8]) {
		for (short row = 0; row < 8; row++) {
			for (char column = 0; column < 8; column++) {
				if (board[row][column]->owner == 3) {
					if (board[kingRow][kingColumn]->allowToMove(kingRow, kingColumn, row, column, board) == true) {
						possibleMoves.push_back(1);
					}
				}
				else if (board[row][column]->owner == 1) {
					if (willKingUnderAttack(row, column, figuresRow, figuresColumn, board) == false) {
						if (board[row][column]->allowToAttack(row, column, figuresRow, figuresColumn, board) == true) {
							possibleMoves.push_back(1);
						}
						else if (board[figuresRow][figuresColumn]->canTheAttackBeBlocked(possibleMoves, figuresRow, figuresColumn, kingRow, kingColumn, row, column, board).size() != 0) {
							possibleMoves.push_back(1);
						}
					}
				}
				else if (board[row][column]->owner == 2) {
					if (board[kingRow][kingColumn]->allowToAttack(kingRow, kingColumn, row, column, board) == true) {
						possibleMoves.push_back(1);
					}
				}
			}
		}
		return possibleMoves;
	}
	void countingPoints() {
		short counterPlayer1 = 0;
		short counterPlayer2 = 0;
		for (short row = 0; row < 8; row++) {
			for (short column = 0; column < 8; column++) {
				if (board[row][column]->owner == 1) {
					if (board[row][column]->symbol == "Wp") {
						counterPlayer1 += 1;
					}
					else if (board[row][column]->symbol == "Wr") {
						counterPlayer1 += 5;
					}
					else if (board[row][column]->symbol == "Wk") {
						counterPlayer1 += 3;
					}
					else if (board[row][column]->symbol == "Wb") {
						counterPlayer1 += 3;
					}
					else if (board[row][column]->symbol == "Wq") {
						counterPlayer1 += 9;
					}
					else if (board[row][column]->symbol == "WK") {
						counterPlayer1 += 11;
					}
				}
				else if (board[row][column]->owner == 2) {
					if (board[row][column]->symbol == "Bp") {
						counterPlayer2 += 1;
					}
					else if (board[row][column]->symbol == "Br") {
						counterPlayer2 += 5;
					}
					else if (board[row][column]->symbol == "Bk") {
						counterPlayer2 += 3;
					}
					else if (board[row][column]->symbol == "Bb") {
						counterPlayer2 += 3;
					}
					else if (board[row][column]->symbol == "Bq") {
						counterPlayer2 += 9;
					}
					else if (board[row][column]->symbol == "BK") {
						counterPlayer2 += 11;
					}
				}
			}
		}
		string a = "                  "; //18
		cout << endl << a << "Player 1- " << (counterPlayer1 + (50 - counterPlayer2)) << ':' << (counterPlayer2 + (50 - counterPlayer1)) << " -Player 2\n\n";
	}
	void movesMade(vector<int>& madeMoves, short x, char y, short x1, char y1) {
		madeMoves.push_back(y);
		madeMoves.push_back(x);
		madeMoves.push_back(y1);
		madeMoves.push_back(x1);
	}
	void printMadeMoves(vector<int>vec) {
		int e = vec.size();
		char column1;
		char column2;
		int row1;
		int row2;
		for (int i = 0; i < e; i += 4) {
			column1 = vec[i] + 97;
			row1 = 8 - vec[i + 1];
			column2 = vec[i + 2] + 97;
			row2 = 8 - vec[i + 3];
			cout << column1 << row1 << '-' << column2 << row2 << ';';
		}
	}
    bool getCoordinatesPlayer1() {
		short a = 0;
		while (a == 0) {
			int e = movesMade1.size();
			if (e > 0) {
				cout << "player 1, moves you have made: ";
				printMadeMoves(movesMade1);
			}
			try {
				cout << "\nPlayer 1, you have to enter current position of your piece and then where you want to move it.\n( a letter from A to H and a number from 1 to 8 - for ecample A1)\n ";
				cout << "\nIf you want to quite - enter 99. If you want to offer a draw - press 88\n";
				cout << endl;
				short x, x1;
				char y, y1;
				cout << "Please, choose your curren position: ";
				cout << endl;
				cin >> y >> x;
				if (y == '9' && x == 9) {
					return false;
				}
				else if (y == '8' && x == 8) {
					cout << "\nPlayer 2, player 1 is offering a draw, if you want to except press 1, if you want to reject press 2\n";
					short draw;
					cin >> draw;
					switch (draw) {
					case 1: cout << "Player 1, player 2 excepted your offer";
						return false;
					case 2:cout << "Player 1, player 2 rejected your offer";
						break;
					}
				}
				else {
					if (y <= 'A' && y >= 'H') {
						y -= 65;
					}
					else if (y >= 'a' && y <= 'h') {
						y -= 97;
					}
					x = 8 - x;
					if (x < 0 || x>7 || y < 0 || y>7) {
						throw 1;
					}
					else if (board[x][y]->owner != 1) {
						throw 'a';
					}
					cout << "Please, choose your new position: ";
					cout << endl;
					cin >> y1 >> x1;
					if (y1 <= 'A' && y1 >= 'H') {
						y1 -= 65;
					}
					else if (y1 >= 'a' && y1 <= 'h') {
						y1 -= 97;
					}
					x1 = 8 - x1;
					if (x1 < 0 || x1>7 || y1 < 0 || y1>7) {
						throw 1;
					}
					else if (board[x][y]->symbol != "WK") {
						if (willKingUnderAttack(x, y, x1, y1, board) == true) {
							throw 2.2;
						}
					}
					if (player1(x, y, x1, y1) == true) {
						if (isBlackKingUnderAttack() == true) {
							if (possibleEscapeMoves.size() == 0) {
								printBoard1();
								cout << "\nPlayer 2, you do not have any valid moves.\n";
								cout << "\nPlayer 1, congratulations, you won!\n";
								possibleEscapeMoves.empty();
								return false;
							}
							else {
								cout << "\nPlayer 2, be careful! CHESS!\n";
							}
						}
						else
						    movesMade(movesMade1, x, y, x1, y1);
							printBoard2();
							countingPoints();
							return true;
						}
					else {
						board[x][y]->HowItMovesOrAttackes(x, y, board);
					}
				}
			}
			catch (int mistake) {
				cout << "There is no such position on the board. Try again.";
			}
			catch (char mistake) {
				cout << "The piece you try to move is not yours or it is an empty square. Try again";
			}
			catch (float mistake) {
				cout << "You have to protect your king! Try again";
			}
		}
	}
	bool getCoordinatesPlayer2() {
		short a = 0;
		while (a == 0) {
			int e = movesMade2.size();
			if (e > 0) {
				cout << "Player 2, moves you have made: ";
				printMadeMoves(movesMade2);
			}
			try {
				cout << "\nPlayer 2, you have to enter current position of your piece and then where you want to move it.\n( a letter from A to H and a number from 1 to 8 - for ecample A1)\n ";
				cout << "\nIf you want to quite - enter 99. If you want to offer a draw - press 88\n";
				cout << endl;
				short x, x1;
				char y, y1;
				cout << "Please, choose your curren position: ";
				cout << endl;
				cin >> y >> x;
				if (y == '9' && x == 9) {
					return false;
				}
				else if (y == '8' && x == 8) {
					cout << "\nPlayer 1, player 2 is offering a draw, if you want to except press 1, if you want to reject press 2\n";
					short draw;
					cin >> draw;
					switch (draw) {
					case 1: cout << "Player 2, player 1 excepted your offer";
						return false;
					case 2:cout << "Player 2, player 1 rejected your offer";
						break;
					}
				}
				else {
					if (y <= 'A' && y >= 'H') {
						y -= 65;
					}
					else if (y >= 'a' && y <= 'h') {
						y -= 97;
					}
					x = 8 - x;
					if (x < 0 || x>7 || y < 0 || y>7) {
						throw 1;
					}
					else if (board[x][y]->owner != 2) {
						throw 'a';
					}
					else if (board[x][y]->symbol != "BK") {
						if (willKingUnderAttack(x, y, x, y, board) == true) {
							throw 2.2;
						}
					}
					cout << "Please, choose your new position: ";
					cout << endl;
					cin >> y1 >> x1;
					if (y1 <= 'A' && y1 >= 'H') {
						y1 -= 65;
					}
					else if (y1 >= 'a' && y1 <= 'h') {
						y1 -= 97;
					}
					x1 = 8 - x1;
					if (x1 < 0 || x1>7 || y1 < 0 || y1>7) {
						throw 1;
					}
					if (player2(x, y, x1, y1) == true) {
						if (isWhiteKingUnderAttack() == true) {
							if (possibleEscapeMoves.size() == 0) {
								printBoard2();
								cout << "\nPlayer 1, you do not have any valid moves.\n";
								cout << "\nPlayer 2, congratulations, you won!\n";
								possibleEscapeMoves.empty();
								return false;
							}
							else {
								cout << "\nPlayer 1, be careful! CHESS!\n";
							}
						}
						else
						movesMade(movesMade2, x, y, x1, y1);
						printBoard1();
						countingPoints();
						return true;
					}
					else {
						board[x][y]->HowItMovesOrAttackes(x, y, board);
					}
				}
			}
			catch (int mistake) {
				cout << "There is no such position on the board. Try again.";
			}
			catch (char mistake) {
				cout << "The piece you try to move is not yours or it is an empty square. Try again";
			}
			catch (float mistake) {
				cout << "You have to protect your king! Try again";
			}
		}
	}
	bool play() {
		while (true) {
			if (getCoordinatesPlayer1() == false) {
				return false;
			}
			else if (getCoordinatesPlayer2() == false) {
				return false;
			}
		}
	};
	void endGame() {
		cout << "\nThank you for your time!\n";
	}
	~Game() {};
};
int main() {
	Game game;
	game.fillBoard();
	game.printBoard1();
	game.countingPoints();
	cout << "Do you want to play?" << endl;
	cout << "For Yes - press Y or y" << endl;
	cout << "For No - press N or n" << endl;
	char a;
	cin >> a;
	switch (a) {
	case 'Y':game.play();
		game.endGame();
		break;
	case 'y':game.play();
		game.endGame();
		break;
	case 'N':game.endGame(); break;
	case 'n':game.endGame();
	}
	return 0;
}
