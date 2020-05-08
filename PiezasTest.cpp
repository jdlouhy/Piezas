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

Piece z = p.pieceAt(-1,-1);

ASSERT_EQ(z,Invalid);

}




//check for ties game state, make sure wins are recognized correctly
