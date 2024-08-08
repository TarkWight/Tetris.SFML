//
// Created by Tark Wight on 08.08.2024.
//

#include "Leaderboard.hpp"
#include <fstream>
#include <iostream>

Leaderboard::Leaderboard() {
    load();
}

void Leaderboard::load() {
    std::ifstream inputFile(filename);
    if (inputFile.is_open()) {
        nlohmann::json jsonData;
        inputFile >> jsonData;
        scores = jsonData.get<std::vector<ScoreEntry>>();
        inputFile.close();
    }
}

void Leaderboard::save() {
    std::ofstream outputFile(filename);
    if (outputFile.is_open()) {
        nlohmann::json jsonData = scores;
        outputFile << jsonData.dump(4); // Pretty print with 4 spaces
        outputFile.close();
    }
}

void Leaderboard::addScore(const std::string& playerName, int score) {
    ScoreEntry newEntry{ playerName, score };
    scores.push_back(newEntry);
    std::sort(scores.begin(), scores.end(), [](const ScoreEntry& a, const ScoreEntry& b) {
        return a.score > b.score;
    });
    if (scores.size() > 5) {
        scores.pop_back();
    }
    save();
}

void Leaderboard::print() const {
    std::cout << "Leaderboard:\n";
    for (const auto& entry : scores) {
        std::cout << entry.playerName << ": " << entry.score << "\n";
    }
}
