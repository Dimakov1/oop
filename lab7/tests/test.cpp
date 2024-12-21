#include <gtest/gtest.h>
#include "../include/NPC.h"
#include "../include/Dragon.h"
#include "../include/Bull.h"
#include "../include/Toad.h"
#include "../include/NPCFactory.h"
#include <memory>

TEST(NPCTest, CreationTest) {
    auto dragon = NPCFactory::createNPC("Dragon", 1, 50, 50);
    EXPECT_NE(dragon, nullptr);
    EXPECT_EQ(dragon->getType(), "Dragon");
    EXPECT_EQ(dragon->getId(), 1);
    EXPECT_EQ(dragon->getX(), 50);
    EXPECT_EQ(dragon->getY(), 50);

    auto bull = NPCFactory::createNPC("Bull", 2, 30, 30);
    EXPECT_NE(bull, nullptr);
    EXPECT_EQ(bull->getType(), "Bull");

    auto toad = NPCFactory::createNPC("Toad", 3, 10, 10);
    EXPECT_NE(toad, nullptr);
    EXPECT_EQ(toad->getType(), "Toad");

    auto unknown = NPCFactory::createNPC("Unknown", 4, 0, 0);
    EXPECT_EQ(unknown, nullptr);
}

TEST(NPCTest, MovementTest) {
    auto dragon = std::make_shared<Dragon>(1, 50, 50);
    dragon->setPosition(200, -50); 
    EXPECT_EQ(dragon->getX(), 99); 
    EXPECT_EQ(dragon->getY(), 0); 

    auto bull = std::make_shared<Bull>(2, 0, 0);
    bull->setPosition(-10, 150);
    EXPECT_EQ(bull->getX(), 0);  
    EXPECT_EQ(bull->getY(), 99); 

    auto toad = std::make_shared<Toad>(3, 99, 99);
    toad->setPosition(50, 50);
    EXPECT_EQ(toad->getX(), 50);
    EXPECT_EQ(toad->getY(), 50);
}

TEST(NPCTest, CanAttackTest) {
    auto dragon = std::make_shared<Dragon>(1, 50, 50);
    auto bull = std::make_shared<Bull>(2, 50, 50);
    auto toad = std::make_shared<Toad>(3, 50, 50);

    EXPECT_TRUE(dragon->canAttack(bull));
    EXPECT_FALSE(dragon->canAttack(toad));

    EXPECT_TRUE(bull->canAttack(toad));
    EXPECT_FALSE(bull->canAttack(dragon));

    EXPECT_FALSE(toad->canAttack(dragon));
    EXPECT_FALSE(toad->canAttack(bull));
}

TEST(NPCTest, BattleTest) {
    std::mt19937 rng(42); 
    std::uniform_int_distribution<int> diceRoll(1, 6);

    auto dragon = std::make_shared<Dragon>(1, 50, 50);
    auto bull = std::make_shared<Bull>(2, 50, 50);

    int attack = diceRoll(rng);
    int defense = diceRoll(rng);

    if (attack > defense) {
        bull->setAlive(false);
    } else {
        dragon->setAlive(false);
    }

    EXPECT_FALSE(bull->isAlive());
    EXPECT_TRUE(dragon->isAlive());
}

TEST(NPCTest, ToadSurvivalTest) {
    auto dragon = std::make_shared<Dragon>(1, 50, 50);
    auto toad = std::make_shared<Toad>(2, 50, 50);

    EXPECT_FALSE(dragon->canAttack(toad));

    EXPECT_TRUE(toad->isAlive());
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
