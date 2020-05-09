/**
 * Unit Tests for Piezas
 **/

#include <gtest/gtest.h>
#include "Piezas.h"
#include <iostream>
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
//drops piece in negative col on o's turn
TEST(PiezasTest, dropleftboundsoturn){
	Piezas p;

	p.dropPiece(0);

	Piece o = p.dropPiece(-1);

	ASSERT_EQ(o, Invalid);



}

//drop past full
TEST(PiezasTest, droppastfull) {

	Piezas p;
	p.dropPiece(0);
	p.dropPiece(0);
	p.dropPiece(0);
	Piece z = p.dropPiece(0);

	ASSERT_EQ(z, Blank);

}

//get piece at invalid spot- check that this returns invalid
TEST(PiezasTest, invalidpieceat) {

	Piezas p;

	Piece check = p.pieceAt(-1,-1);

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

//X is winner
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

//O is winner 
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

//check for ties game state, make sure wins are recognized correctly
TEST(PiezasTest, TieTest){
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

TEST(PiezasTest, VerticalScanXWins) {

Piezas p;
//fill first column 

for (int i = 0; i < BOARD_ROWS; i++){
p.dropPiece(0);
}

for (int x = 0; x < BOARD_ROWS; x++){
for (int i = 1; i < BOARD_COLS; i++){
p.dropPiece(-1);
p.dropPiece(i);
}
}
Piece result = p.gameState();

ASSERT_EQ(result, X);

}
