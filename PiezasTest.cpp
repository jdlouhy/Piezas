/**
 * Unit Tests for Piezas
 **/

#include <gtest/gtest.h>
#include "Piezas.h"
class PiezasTest : public ::testing::Test
{
	protected:
		PiezasTest(){} //constructor runs before each test
		virtual ~PiezasTest(){} //destructor cleans up after tests
		virtual void SetUp(){} //sets up before each test (after constructor)
		virtual void TearDown(){} //clean up after each test, (before destructor) 
};

//sanity check test
TEST(PiezasTest, sanityCheck)
{
	ASSERT_TRUE(true);
}


//for place test, we need initial test, bounds checking, full case,  
//initial pieceat test
TEST(PiezasTest, placetest){

	Piezas p;

	p.dropPiece(0);

	Piece x = p.pieceAt(BOARD_ROWS-1,0);
	ASSERT_EQ(x,X);

}

//reset test
TEST(PiezasTest, resettest){

	Piezas p; 

	p.dropPiece(0);

	p.reset();

	Piece x = p.pieceAt(BOARD_ROWS-1,0);


	ASSERT_EQ(x,Blank);



}
//drops piece in negative col should result in invalid
TEST(PiezasTest, dropleftbounds) {

	Piezas p;

	Piece x = p.dropPiece(-1);

	ASSERT_EQ(x, Invalid);


}

TEST(PiezasTest, droprightbounds) {

        Piezas p;

        Piece x = p.dropPiece(BOARD_COLS+1);

        ASSERT_EQ(x, Invalid);


}
//drops piece in negative col on o's turn
TEST(PiezasTest, dropleftboundsoturn){
	Piezas p;

	p.dropPiece(0);

	Piece o = p.dropPiece(-1);

	ASSERT_EQ(o, Invalid);
}

//drop past full, make sure this comes back as blank
TEST(PiezasTest, droppastfull) {

	Piezas p;
   
        Piece z;

	for (int i = 0; i < BOARD_ROWS+1; i++) {
         z = p.dropPiece(0);
	}

	ASSERT_EQ(z, Blank);

}
//get piece at invalid spot-by row, not column check that this returns invalid
TEST(PiezasTest, invalidrowvalidcolumnpieceat) {

        Piezas p;

        Piece check = p.pieceAt(-1,0);

        ASSERT_EQ(check,Invalid);

}
//get piece at invalid spot-by row, not column check that this returns invalid
TEST(PiezasTest, invalidcolumnvalidrowpieceat) {

        Piezas p;

        Piece check = p.pieceAt(0,-1);

        ASSERT_EQ(check,Invalid);

}

//get piece at invalid spot-outside left bounds check that this returns invalid
TEST(PiezasTest, invalidpieceatoutsideleft) {

	Piezas p;

	Piece check = p.pieceAt(-1,-1);

	ASSERT_EQ(check,Invalid);

}
//get piece at invalid spot outside right bounds, check that this returns invalid
TEST(PiezasTest, invalidpieceatoutsideright) {

        Piezas p;

        Piece check = p.pieceAt(BOARD_ROWS+1,BOARD_COLS+1);

        ASSERT_EQ(check,Invalid);

}

//game not done yet test
TEST(PiezasTest, gamenotdoneyet) {
	Piezas p;
	p.dropPiece(0);
	p.dropPiece(0);

	Piece result = p.gameState();

	ASSERT_EQ(result, Invalid);

}

//X is winner, discovered horizontally
TEST(PiezasTest, Xiswinner) {
	Piezas p;
	//x turn goes first and then make every o turn invalid

	for (int i = 0; i < BOARD_ROWS; i++){
		for (int x = 0; x < BOARD_COLS; x++){
			p.dropPiece(x);
			p.dropPiece(-1);
		}   
	}   
	Piece result  = p.gameState();

	ASSERT_EQ(result, X);
}

//O is winner, discovered horizontally 
TEST(PiezasTest, Oiswinner){

	Piezas p;
	//o turn goes second so make every x turn invalid

	for (int i = 0; i < BOARD_ROWS; i++){
		for (int x = 0; x < BOARD_COLS; x++){
			p.dropPiece(-1);
			p.dropPiece(x);
		}
	}
	Piece result  = p.gameState();

	ASSERT_EQ(result, O);

}
//check for ties game state, switching between rows make sure wins are recognized correctly
//
TEST(PiezasTest, TieTestSwitchedRows){
	Piezas p;
	for (int i = 0; i < BOARD_ROWS; i++){
		for (int x = 0; x < BOARD_COLS; x++){
			p.dropPiece(x);
			p.dropPiece(x);
		}
	}
	Piece result  = p.gameState();
	ASSERT_EQ(result, Blank);
}
//similar tie case, but instead just alternate each
TEST(PiezasTest, TieTestRegular){
        Piezas p;
        for (int i = 0; i < BOARD_ROWS; i++){
                for (int x = 0; x < BOARD_COLS; x++){
                        p.dropPiece(x);
                }   
        }   
        Piece result  = p.gameState();
        ASSERT_EQ(result, Blank);
}
//scan to find that  x wins, vertical scan should catch the max
TEST(PiezasTest, VerticalScanXWins) {

	Piezas p;
	for (int i = 0; i < BOARD_COLS-1; i++) {
		for (int t = 0; t < BOARD_ROWS; t++) {
			p.dropPiece(i);
		}
	}
	//fill out xs for last one (makes x winner)
	for (int i = 0; i < BOARD_ROWS; i++) {
	        p.dropPiece(-1);
		p.dropPiece(BOARD_COLS-1);
	}

	Piece result = p.gameState();

	ASSERT_EQ(result, X);

}
//scan to find that  O wins, vertical scan should catch the max
TEST(PiezasTest, VerticalScanOWins) {

        Piezas p;

        for (int i = 0; i < BOARD_COLS-1; i++) {
                for (int t = 0; t < BOARD_ROWS; t++) {
                        p.dropPiece(i);
                }
        }
        //fill out os for last one (makes x winner)
        for (int i = 0; i < BOARD_ROWS; i++) {
                p.dropPiece(BOARD_COLS-1);
		p.dropPiece(-1);
        }

        Piece result = p.gameState();

        ASSERT_EQ(result, O);

}
