#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

//modification

string chess_board[8][8] =
{
	{"wc1", "wh1", "we1", "wk", "wq", "we2", "wh2", "wc2"},
	{"ws1", "ws2", "ws3", "ws4", "ws5", "ws6", "ws7", "ws8"},
	{}, // \0
	{}, // \0
	{}, // \0
	{}, // \0
	{"bs1", "bs2", "bs3", "bs4", "bs5", "bs6", "bs7", "bs8"},
	{"bc1", "bh1", "be1", "bk", "bq", "be2", "bh2", "bc2"},
};

bool IsCheckMate(string team, string Chess_board[8][8] = chess_board, int row = -1, int column = -1);

struct position {
	int column, row;
	bool operator==(position post) {
		if (post.column == column && post.row == row)
			return true;
		else
			return false;
	}

	bool operator!=(position post) {
		if (post.column != column || post.row != row)
			return true;
		else
			return false;
	}

	void operator=(position post) {
		row = post.row;
		column = post.column;
	}

	position() {
		column = -1;
		row = 1;
	}
	position(int Column, int Row) {
		column = Column;
		row = Row;
	}

};

position FindIndex(string type, string Chess_board[8][8] = chess_board);

class Move {

private:

	int sign(int num) {
		int sign;
		if (num > 0)
			sign = 1;
		else if (num < 0)
			sign = -1;
		else
			sign = 0;

		return sign;
	}

	bool IsDigonal(int diff_column, int diff_row) // check if the move is diagonal
	{
		if (abs(diff_column) == abs(diff_row))
			return true;
		else
			return false;
	}

	bool IsHorizantal(int diff_column, int diff_row) {
		if (abs(diff_column) > 0 && diff_row == 0)
			return true;
		else
			return false;
	}

	bool IsVertical(int diff_column, int diff_row) {
		if (diff_column == 0 && abs(diff_row) > 0)
			return true;
		else
			return false;
	}

	bool CheckWay(int diff_column, int diff_row, position f_post, position i_post) {
		int one_column = sign(diff_column);
		int one_row = sign(diff_row);

		position cpy_i_post = i_post;

		cpy_i_post.column += one_column;
		cpy_i_post.row += one_row;

		while (f_post != cpy_i_post) {
			if (chess_board[cpy_i_post.row][cpy_i_post.column] != "")
			{
				return false;
			}
			else
			{
				cpy_i_post.row += one_row;
				cpy_i_post.column += one_column;
			}
		}

		return true;
	}

	bool CheckFinalPost(position f_post, char type) // type is the color
	{
		string chess_f_post = chess_board[f_post.row][f_post.column];

		if (chess_f_post != "")
		{
			if (type == 'w')
			{
				if (chess_f_post[0] == 'w') // if in f_post is white
					return false;
				else
					return true;
			}
			else if (type == 'b')
			{
				if (chess_f_post[0] == 'b') // if in f_post is black
					return false;
				else
					return true;
			}
		}
		else return true;// if empty

	}


public:

	string chess_type;
	position f_post, i_post;
	bool IsMoveValid(string chess_board[8][8] = chess_board) // precondition: initial position, final position and chess type; post condition: checked move;
	{
		int diff_row = f_post.row - i_post.row;
		int diff_column = f_post.column - i_post.column;

		switch (chess_type[1]) {
		case 'k':
			if ((abs(diff_column) == 1 || diff_column == 0) && (abs(diff_row) == 1 || diff_row == 0)) { // check move
				string team = "" + chess_type[0];
				if (IsCheckMate(team, chess_board, f_post.row, f_post.column)) {
					return false;
				}
				else
					return CheckFinalPost(f_post, chess_type[0]); // check final post
			}
			else { // if move not valid
				return false;
			}
			break;
		case 'q':
			if (IsDigonal(diff_column, diff_row)) // check move
			{
				if (CheckWay(diff_column, diff_row, f_post, i_post)) // check way
				{
					return CheckFinalPost(f_post, chess_type[0]);// check final position
				}
				else // if way is not clear
				{
					return false;
				}
			}

			else if (IsHorizantal(diff_column, diff_row)) { // check move
				if (CheckWay(diff_column, diff_row, f_post, i_post)) // check way
				{
					return CheckFinalPost(f_post, chess_type[0]);// check final position
				}
				else // if way is not clear
				{
					return false;
				}
			}
			else if (IsVertical(diff_column, diff_row)) { // check move
				if (CheckWay(diff_column, diff_row, f_post, i_post)) // check way
				{
					return CheckFinalPost(f_post, chess_type[0]);// check final position
				}
				else
				{
					return false;
				}
			}

			else // if move is not valid
			{
				return false;
			}
			break;

		case 'e':
			if (IsDigonal(diff_column, diff_row)) // check move
			{
				if (CheckWay(diff_column, diff_row, f_post, i_post)) // check way
				{
					return CheckFinalPost(f_post, chess_type[0]);// check final position
				}
				else // if way is not clear
				{
					return false;
				}
			}
			else // if move is not valid
			{
				return false;
			}
			break;

		case 'h':
			if ((abs(diff_column) == 2 && abs(diff_row) == 1) || (abs(diff_row) == 2 && abs(diff_column) == 1)) // check move
				return CheckFinalPost(f_post, chess_type[0]);// check final position

			else // if move is not valid
				return false;
			break;

		case 'c':
			if (IsHorizantal(diff_column, diff_row)) { // check move
				if (CheckWay(diff_column, diff_row, f_post, i_post)) // check way
				{
					return CheckFinalPost(f_post, chess_type[0]);// check final position
				}
				else // if way is not clear
				{
					return false;
				}
			}
			else if (IsVertical(diff_column, diff_row)) { // check move
				if (CheckWay(diff_column, diff_row, f_post, i_post)) // check way
				{
					return CheckFinalPost(f_post, chess_type[0]);// check final position
				}
				else
				{
					return false;
				}
			}

			else // if move is not valid
			{
				return false;
			}
			break;

		case 's':
			//cout << "in s case";
			if (chess_type[0] == 'w')
			{
				if (diff_row == 1 && diff_column == 0) // move one step ahead
				{
					if (chess_board[f_post.row][f_post.column] == "") // check way
						return true;
					else
						return false;
				}

				else if (diff_row == 1 && abs(diff_column) == 1) // kill diagonally
				{
					if (chess_board[f_post.row][f_post.column] != "") // check way
						//return CheckFinalPost(f_post, chess_type[0]);
						return true;
					else
						return false;
				}
				else if (diff_row == 2 && diff_column == 0)
				{
					position temp = FindIndex(chess_type);
					if (temp.row == 1) {
						if (CheckWay(diff_column, diff_row, f_post, i_post)) {
							if (chess_board[f_post.row][f_post.column] == "")
								return true;
							else
								return false;
						}
						else
							return false;
					}
					else
						return false;
				}

				else
					return false;
			}
			else if (chess_type[0] == 'b')
			{
				if (diff_row == -1 && diff_column == 0) // move one step ahead
				{
					if (chess_board[f_post.row][f_post.column] == "") // check way
						return true;
					else
						return false;
				}

				else if (diff_row == -1 && abs(diff_column) == 1) // kill diagonally
				{
					if (chess_board[f_post.row][f_post.column] != "") // check way
						return CheckFinalPost(f_post, chess_type[0]);
					else
						return false;
				}

				else if (diff_row == -2 && diff_column == 0) {
					position temp = FindIndex(chess_type);
					if (temp.row == 6) {
						if (CheckWay(diff_column, diff_row, f_post, i_post)) {
							if (chess_board[f_post.row][f_post.column] == "")
								return true;
							else
								return false;
						}
						else
							return false;
					}
					else
						return false;
				}

				else
					return false;
			}
			break;

		default:
			return false;
			break;

		}

	}

	void flip(string chess_board[8][8] = chess_board) {
		chess_board[f_post.row][f_post.column] = chess_board[i_post.row][i_post.column];
		chess_board[i_post.row][i_post.column] = "";
	}

	void reset() {
		chess_type = "";
	}


};

bool IsCheckMate(string team, string Chess_board[8][8], int row, int column) {
	Move move;
	string op_team = ("b" == team ? "w" : "b");
	if (row == -1 || column == -1)
		move.f_post = FindIndex(team + 'k');
	else {
		move.f_post.row = row;
		move.f_post.column = column;
	}
	char chess_types[6] = { 'k', 'q', 'e', 'h', 'c', 's' };
	for (int i = 0; i < 6; i++) {
		switch (chess_types[i]) {
		case 'k':
			move.chess_type = op_team + 'k';
			move.i_post = FindIndex(move.chess_type);
			if (move.IsMoveValid()) {
				return true;
			}
			break;
		case 'q':
			move.chess_type = op_team + 'q';
			move.i_post = FindIndex(move.chess_type);
			if (move.IsMoveValid()) {
				return true;
			}
			break;
		case 'e':
			for (char num = '1'; num <= '2'; num++) {
				move.chess_type = op_team + 'e' + num;
				move.i_post = FindIndex(move.chess_type);
				if (move.IsMoveValid()) {
					return true;
				}
			}
			break;
		case 'h':
			for (char num = '1'; num <= '2'; num++) {
				move.chess_type = op_team + 'h' + num;
				move.i_post = FindIndex(move.chess_type);
				if (move.IsMoveValid()) {
					return true;
				}
			}
			break;
		case 'c':
			for (char num = '1'; num <= '2'; num++) {
				move.chess_type = op_team + 'c' + num;
				move.i_post = FindIndex(move.chess_type);
				if (move.IsMoveValid()) {
					return true;
				}
			}
			break;
		case 's':
			for (char num = '1'; num <= '8'; num++) {
				move.chess_type = op_team + 's' + num;
				move.i_post = FindIndex(move.chess_type);
				if (move.IsMoveValid()) {
					return true;
				}
			}
			break;
		default:
			return true;
			break;
		}
	}

	return false;
}

bool IsIn(string type) {
	for (int row = 0; row < 8; row++)
	{
		for (int column = 0; column < 8; column++) {
			if (chess_board[row][column] == type)
				return true;
		}
	}

	return false;
}

void PrintBoard() {
	for (char ch = 'a'; ch <= 'h'; ch++) {
		cout << setw(6) << ch;
	}

	cout << endl << setw(3) << '|';

	for (int j = 0; j < 8; j++) {
		cout << "-----|";
	}

	cout << endl;

	for (int i = 0; i < 8; i++) {

		cout << i + 1 << setw(2) << '|';
		for (int j = 0; j < 8; j++) {
			cout << setw(4) << chess_board[i][j] << setw(2) << '|';
		}
		cout << endl << setw(3) << '|';

		for (int j = 0; j < 8; j++) {
			cout << "-----|";
		}

		cout << endl;

	}
}

void convertNum(char num, int& n) {
	n = (int)num - 49;
}

void convertCh(char ch, int& n) {
	n = (int)ch - 97;
}

bool CheckInput(Move move)
{
	if ((move.f_post.row >= 0 && move.f_post.row < 8) && (move.f_post.column >= 0 && move.f_post.column < 8) && (IsIn(move.chess_type)))
		return true;
	else return false;
}

position FindIndex(string type, string Chess_board[8][8])
{
	position result;

	result.row = -1;
	result.column = -1;

	for (int row = 0; row < 8; row++)
	{
		for (int column = 0; column < 8; column++) {
			if (Chess_board[row][column] == type)
			{
				result.row = row;
				result.column = column;
			}
		}
	}

	return result;

}

Move Input(char turn) {
	Move move;
	string s_move;
	move.chess_type = "initial";
	position init_post;
	init_post.row = -1;
	init_post.column = -1;
	move.f_post = init_post;
	move.i_post = init_post;
	bool IsMoveValid, IsInputValid;
	if (turn == 'w')
	{
		IsMoveValid = true; IsInputValid = true;
	CheckMateW:
		do {
			move.reset();
			system("cls");
			PrintBoard();
			if (IsCheckMate("w")) {
				cout << endl << "  Checkmate.";
			}

			if (!IsInputValid) {
				cout << endl << "  Invalid Input.";
			}
			else if (!IsMoveValid) {
				cout << endl << "  Invalid Move.";
			}

			cout << endl << setw(9) << "White: ";
			cin >> s_move;
			int size = s_move.length();
			move.chess_type += 'w';

			if (size == 4)
			{
				move.chess_type += s_move[0];
				move.chess_type += s_move[1];
				convertCh(s_move[2], move.f_post.column);
				convertNum(s_move[3], move.f_post.row);
			}
			else if (size == 3)
			{
				move.chess_type += s_move[0];
				convertCh(s_move[1], move.f_post.column);
				convertNum(s_move[2], move.f_post.row);
			}

			move.i_post = FindIndex(move.chess_type);
			IsMoveValid = (move.IsMoveValid() ? true : false);
			IsInputValid = (CheckInput(move) ? true : false);
		} while (!(move.IsMoveValid()) || !CheckInput(move));
		string dead_chess = chess_board[move.f_post.row][move.f_post.column];
		if (IsCheckMate("w"))
			goto skip;
		move.flip();
		if (IsCheckMate("w")) {
			IsMoveValid = false;
			chess_board[move.i_post.row][move.i_post.column] = move.chess_type;
			chess_board[move.f_post.row][move.f_post.column] = dead_chess;
			goto CheckMateW;
		}
		else {
			chess_board[move.i_post.row][move.i_post.column] = move.chess_type;
			chess_board[move.f_post.row][move.f_post.column] = dead_chess;
		}
	skip:;
	}

	else if (turn == 'b')
	{
		IsMoveValid = true; IsInputValid = true;
	CheckMateB:
		do {
			move.reset();
			system("cls");
			PrintBoard();
			if (IsCheckMate("b")) {
				cout << endl << "  Checkmate.";
			}
			if (!IsInputValid) {
				cout << endl << "  Invalid Input.";
			}
			else if (!IsMoveValid) {
				cout << endl << "  Invalid Move.";
			}
			cout << endl << setw(9) << "Black: ";
			cin >> s_move;
			int size = s_move.length();
			move.chess_type += 'b';

			if (size == 4)
			{
				move.chess_type += s_move[0];
				move.chess_type += s_move[1];
				convertCh(s_move[2], move.f_post.column);
				convertNum(s_move[3], move.f_post.row);
			}
			else if (size == 3)
			{
				move.chess_type += s_move[0];
				convertCh(s_move[1], move.f_post.column);
				convertNum(s_move[2], move.f_post.row);
			}

			move.i_post = FindIndex(move.chess_type);
			IsMoveValid = (move.IsMoveValid() ? true : false);
			IsInputValid = (CheckInput(move) ? true : false);
		} while (!(move.IsMoveValid()) || !CheckInput(move));
		string dead_chess = chess_board[move.f_post.row][move.f_post.column];
		if (IsCheckMate("b"))
			goto skip1;
		move.flip();
		if (IsCheckMate("b")) {
			IsMoveValid = false;
			chess_board[move.i_post.row][move.i_post.column] = move.chess_type;
			chess_board[move.f_post.row][move.f_post.column] = dead_chess;
			goto CheckMateB;
		}
		else {
			chess_board[move.i_post.row][move.i_post.column] = move.chess_type;
			chess_board[move.f_post.row][move.f_post.column] = dead_chess;
		}
	skip1:;
	}

	return move;
}

int main()
{
	Move move;
	string s_move;
	char turn = 'w';

	//game
	while (IsIn("wk") && IsIn("bk"))
	{
		move = Input(turn);
		cout << move.chess_type;
		move.flip();
		if (turn == 'w')
			turn = 'b';
		else if (turn == 'b')
			turn = 'w';
	}

	//end
	if (IsIn("wk")) {
		system("cls");
		PrintBoard();
		cout << endl << "  White wins!";

	}
	else
	{
		system("cls");
		PrintBoard();
		cout << endl << "  Black wins!";
	}


	return 0;
}