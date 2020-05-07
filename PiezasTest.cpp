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

TEST(PiezasTest, sanityCheck)
{
	ASSERT_TRUE(true);
}


//for place test, we need initial test, bounds checking, full case,  

TEST(PiezasTest, placetest){

	Piezas p;

	p.dropPiece(0);

	Piece x = p.pieceAt(BOARD_ROWS-1,0);
       std::cout << x << endl;
       std::cout << X << endl;
	ASSERT_EQ(x,X);

}





//check for ties game state, make sure wins are recognized correctly
