#include <gtest/gtest.h>
#include "../Utils/LeaderBoard.hpp"
#include <filesystem>
#include <fstream>

class LeaderBoardTest : public ::testing::Test {
protected:
    LeaderBoard leaderboard;

    void SetUp() override {
        // ������ ��� ���������� ����� ��� ������
        leaderboard.setFilename("test_scores.json");

        // ������� JSON-���� � ���������� �������
        std::ofstream file(leaderboard.getFullPath());
        file << R"([{"playerName":"Player 1","score":1000}, {"playerName":"Player 2","score":500}])";
        file.close();
    }

    void TearDown() override {
        // ������� ��������� ���� ����� ���������� ������� �����
        std::filesystem::remove(leaderboard.getFullPath());
    }
};

// ���� ��� ���������� ���������� � �������
TEST_F(LeaderBoardTest, AddScoreTest) {
    leaderboard.addScore("Player 3", 600);  // ����� ����� ����������� � 600 ������
    auto scores = leaderboard.getScores();

    EXPECT_EQ(scores[0].playerName, "Player 1");  // "Player 1" � 1000 ����� �������� �� 1 �����
    EXPECT_EQ(scores[0].score, 1000);
    EXPECT_EQ(scores[1].playerName, "Player 3");  // ����� ����� � 600 ����� ���������� ������
    EXPECT_EQ(scores[1].score, 600);
}


// ���� ��� ���������� ����� ������� ����������
TEST_F(LeaderBoardTest, AddLowerScoreTest) {
    leaderboard.addScore("Player 3", 600);  // ��������� ������ � 200 �����
    leaderboard.addScore("Player 4", 100);  // ������� �������� ������ � ������� ����������� (100)

    auto scores = leaderboard.getScores();

    EXPECT_EQ(scores[0].playerName, "Player 1");  // "Player 1" � 1000 ����� �������� �� 1 �����
    EXPECT_EQ(scores[0].score, 1000);
    EXPECT_EQ(scores[1].playerName, "Player 3");  // "Player 3" � 600 ����� �������� �� 2 �����
    EXPECT_EQ(scores[1].score, 600);
}


// ���� ��� ���������� ����� �������� ����������
TEST_F(LeaderBoardTest, AddHigherScoreTest) {
    leaderboard.addScore("Player 3", 1500);  // ����� ��������� ������ �������� ���-1
    auto scores = leaderboard.getScores();

    EXPECT_EQ(scores[0].playerName, "Player 3");
    EXPECT_EQ(scores[0].score, 1500);
    EXPECT_EQ(scores[1].playerName, "Player 1");  // ��������: "Player 1"
    EXPECT_EQ(scores[1].score, 1000);
}

// ���� ��� �������� ���������� � ��������
TEST_F(LeaderBoardTest, LoadAndSaveTest) {
    leaderboard.addScore("Player 3", 700);

    // ��������� ������� ���������
    leaderboard.save();

    // ������� ����� ������ LeaderBoard � ���������, ��� ������ ����������� ���������
    LeaderBoard newBoard;
    newBoard.setFilename("test_scores.json");
    newBoard.load();
    auto scores = newBoard.getScores();

    EXPECT_EQ(scores[0].playerName, "Player 1");  // ��������: "Player 1"
    EXPECT_EQ(scores[0].score, 1000);
    EXPECT_EQ(scores[1].playerName, "Player 3");
    EXPECT_EQ(scores[1].score, 700);
}
