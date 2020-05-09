#include "Piezas.h"
#include <vector>
/** CLASS Piezas
 * Class for representing a Piezas vertical board, which is roughly based
 * on the game "Connect Four" where pieces are placed in a column and 
 * fall to the bottom of the column, or on top of other pieces already in
 * that column. For an illustration of the board, see:
 *  https://en.wikipedia.org/wiki/Connect_Four
 *
 * Board coordinates [row,col] should match with:
 * [2,0][2,1][2,2][2,3]
 * [1,0][1,1][1,2][1,3]
 * [0,0][0,1][0,2][0,3]
 * So that a piece dropped in column 2 should take [0,2] and the next one
 * dropped in column 2 should take [1,2].
 **/


/**
 * Constructor sets an empty board (default 3 rows, 4 columns) and 
 * specifies it is X's turn first
 **/
Piezas::Piezas()
{
	for (int i = 0; i < BOARD_ROWS; i++){
		std::vector<Piece> vec;
		for (int x = 0; x < BOARD_COLS; x++){
			Piece t;
			t = Blank;
			vec.push_back(t);
		}
		board.push_back(vec);
	}
	//it is xs turn first
	turn = X;
}

/**
 * Resets each board location to the Blank Piece value, with a board of the
 * same size as previously specified
 **/
void Piezas::reset()
{

	for (int i = 0; i < BOARD_ROWS; i++){
		for (int x = 0; x < BOARD_COLS; x++){
			board[i][x] = Blank;
		}   
	}   

}

/**
 * Places a piece of the current turn on the board, returns what
 * piece is placed, and toggles which Piece's turn it is. dropPiece does 
 * NOT allow to place a piece in a location where a column is full.
 * In that case, placePiece returns Piece Blank value 
 * Out of bounds coordinates return the Piece Invalid value
 * Trying to drop a piece where it cannot be placed loses the player's turn
 **/ 
Piece Piezas::dropPiece(int column)
{
	//first check out of bounds place 
	if (column >= BOARD_COLS || column < 0){
		if (turn == X){
			turn = O;
		}
		else {
			turn = X;
		}
		return Invalid;
	}
	//then check if the column is full case
	if (board[0][column] != Blank){
		if (turn == X){
			turn = O;
		}
		else {
			turn = X;
		}
		return Blank;
	}
	int count = 0;
	//find lowest blank place in this column
	while ( count+1 < BOARD_ROWS && board[count+1][column] == Blank  ){
		count = count + 1;
	}
	//set that spot to turn piece, store turn piece before flip, flip, then return the stored previous turn piece

	board[count][column] = turn;
	Piece cp = turn;	
	if (turn == X){
		turn = O;
	}
	else {
		turn = X;
	}

	return cp;
}

/**
 * Returns what piece is at the provided coordinates, or Blank if there
 * are no pieces there, or Invalid if the coordinates are out of bounds
 **/
Piece Piezas::pieceAt(int row, int column)
{
        if (row < 0 || row >= BOARD_ROWS || column >= BOARD_COLS || column < 0 ){
          return Invalid;
	}

	return board[row][column];
}

/**
 * Returns which Piece has won, if there is a winner, Invalid if the game
 * is not over, or Blank if the board is filled and no one has won ("tie").
 * For a game to be over, all locations on the board must be filled with X's 
 * and O's (i.e. no remaining Blank spaces). The winner is which player has
 * the most adjacent pieces in a single line. Lines can go either vertically
 * or horizontally. If both X's and O's have the same max number of pieces in a
 * line, it is a tie.
 * We will signify this tie case with a blank piece. 
 **/
Piece Piezas::gameState()
{

	//max counts
	int xmax = 0;
	int omax = 0;
	for (int i = 0; i < BOARD_ROWS; i++){

		int xcount = 0;
		int ocount = 0;
		//scan horizontally to find maxes
		for (int x = 0; x < BOARD_COLS; x++){
			if (board[i][x] == X){
				ocount = 0;
				xcount += 1;
				if (xcount > xmax) {
					xmax = xcount;
				}
			}
			else if (board [i][x] == O){
				xcount = 0;
				ocount += 1;
				if (ocount > omax){
					omax = ocount;
				}
			}
			//found a blank piece then game is not over
			else if (board[i][x] == Blank){
                     return Invalid;
			}
		}

	}

	//vertical scan below
	for (int i = 0; i < BOARD_COLS; i++){
		int xcount = 0;
		int ocount = 0;
		for (int x = 0; x < BOARD_ROWS; x++){
                               if (board[x][i] == X){
                                ocount = 0;
				xcount += 1;
				if (xcount > xmax) {
					xmax = xcount;
				}
			}
			else if (board [x][i] == O){
				xcount = 0;
				ocount += 1;
				if (ocount > omax){
					omax = ocount;
				}
			}
		}
	}
	if (omax > xmax) {
               Piece ret = O;
		return ret;
	}
	else if (xmax > omax) {
		Piece ret = X;
		return ret;
	}
	//tie case 
	else {
		Piece ret = Blank;
		return ret;

	}
}
