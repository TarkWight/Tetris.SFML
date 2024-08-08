//
// Created by Tark Wight on 08.08.2024.
//

#ifndef LEADERBOARD_HPP
#define LEADERBOARD_HPP

#include <vector>
#include <string>
#include <nlohmann/json.hpp>

struct ScoreEntry {
    std::string playerName;
    int score;

    NLOHMANN_DEFINE_TYPE_INTRUSIVE(ScoreEntry, playerName, score)
};

class Leaderboard {
private:
    std::vector<ScoreEntry> scores;
    const std::string filename = "leaderboard.json";

public:
    Leaderboard();
    void load();
    void save();
    void addScore(const std::string& playerName, int score);
    void print() const;
};

#endif // LEADERBOARD_HPP


