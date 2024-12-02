#include <gtest/gtest.h>
#include "../include/NPCFactory.h"
#include "../include/Dragon.h"
#include "../include/Bull.h"
#include "../include/Toad.h"
#include "../include/ConsoleLogger.h"
#include "../include/FileLogger.h"
#include "../include/Subject.h"

TEST(NPCTest, CreationTest) {
    auto dragon = NPCFactory::createNPC("Дракон", "Smaug", 100, 200);
    EXPECT_NE(dragon, nullptr);
    EXPECT_EQ(dragon->getName(), "Smaug");
    EXPECT_EQ(dragon->getX(), 100);
    EXPECT_EQ(dragon->getY(), 200);
    EXPECT_EQ(dragon->getType(), "Дракон");

    auto bull = NPCFactory::createNPC("Бык", "Bullseye", 150, 200);
    EXPECT_NE(bull, nullptr);
    EXPECT_EQ(bull->getType(), "Бык");

    auto toad = NPCFactory::createNPC("Жаба", "Froggy", 200, 250);
    EXPECT_NE(toad, nullptr);
    EXPECT_EQ(toad->getType(), "Жаба");

    auto unknown = NPCFactory::createNPC("Неизвестный", "Unknown", 0, 0);
    EXPECT_EQ(unknown, nullptr);
}

TEST(NPCTest, InteractionTest) {
    Subject logger;
    auto consoleLogger = std::make_shared<ConsoleLogger>();
    logger.attach(consoleLogger);

    auto dragon = std::make_shared<Dragon>("Smaug", 100, 200);
    auto bull = std::make_shared<Bull>("Bullseye", 150, 200);
    auto toad = std::make_shared<Toad>("Froggy", 130, 220);

    dragon->interactWith(bull.get(), logger);
    EXPECT_FALSE(bull->isAlive());
    EXPECT_TRUE(dragon->isAlive());

    bull->interactWith(toad.get(), logger);
    EXPECT_TRUE(toad->isAlive()); 

    auto bull2 = std::make_shared<Bull>("Bull2", 200, 200);
    bull2->interactWith(toad.get(), logger);
    EXPECT_FALSE(toad->isAlive());
    EXPECT_TRUE(bull2->isAlive());
}

TEST(NPCTest, SaveLoadTest) {
    std::vector<std::shared_ptr<NPC>> npcs;
    npcs.push_back(NPCFactory::createNPC("Дракон", "Smaug", 100, 200));
    npcs.push_back(NPCFactory::createNPC("Бык", "Bullseye", 150, 200));
    npcs.push_back(NPCFactory::createNPC("Жаба", "Froggy", 200, 250));

    NPCFactory::saveToFile("test_npc_data.txt", npcs);

    auto loadedNPCs = NPCFactory::loadFromFile("test_npc_data.txt");
    EXPECT_EQ(loadedNPCs.size(), 3);
    EXPECT_EQ(loadedNPCs[0]->getName(), "Smaug");
    EXPECT_EQ(loadedNPCs[1]->getName(), "Bullseye");
    EXPECT_EQ(loadedNPCs[2]->getName(), "Froggy");

    std::remove("test_npc_data.txt");
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
