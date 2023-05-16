#include <gtest/gtest.h>
#include <vector>

#include "battleship.h"

//Error codes: -2: "tile is not on board or has already been fired at", 2: hit (target is a ship), -1: miss (target is empty), -3: "should never trigger"

std::vector<int> tester(100, 0);
std::vector<int> tester2(100, 1);
std::vector<int> tester3(100, 2);
TEST(TileShoot, GoodTests){
	EXPECT_EQ(tileShoot(50, tester), -1);
	EXPECT_EQ(tileShoot(50, tester2), 2);
	EXPECT_EQ(tileShoot(5, tester), -1);
	EXPECT_EQ(tileShoot(5, tester2), 2);
}

TEST(TileShoot, BadTests){
	EXPECT_EQ(tileShoot(10000, tester), -2);
	EXPECT_EQ(tileShoot(10000, tester2), -2);
	EXPECT_EQ(tileShoot(50, tester3), -2);
	EXPECT_EQ(tileShoot(0, tester3), -2);
}

TEST(TileShoot, EdgeTests){
	EXPECT_EQ(tileShoot(100, tester), -2);
	EXPECT_EQ(tileShoot(99, tester), -1);
	EXPECT_EQ(tileShoot(0, tester), -1);
	EXPECT_EQ(tileShoot(0, tester2), 2);
	EXPECT_EQ(tileShoot(99, tester2), 2);
	EXPECT_EQ(tileShoot(-1, tester), -2);
	EXPECT_EQ(tileShoot(-1, tester2), -2);

}