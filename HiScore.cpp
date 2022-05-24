#include "HiScore.h"

namespace Game{
    HiScore::HiScore(string hiScoreFilename) {
        this->hiScoreFilename = hiScoreFilename;
        retrieveTable();
    }
    
    void HiScore::retrieveTable() {
        ifstream hiScoreIFStream(hiScoreFilename);
        
        // normal when high scores are stored in new file
        if (!hiScoreIFStream.is_open()) { return; }
        
        while (true) {
            string name;
            int score;
            hiScoreIFStream >> name;
            if (hiScoreIFStream.eof()) { break; } // name holds newline
            hiScoreIFStream >> score;
            pair<string, int> entry(name, score);
            hiScoreTable.push_back(entry);
        }
        hiScoreIFStream.close();
    }
    
    void HiScore::storeTable() {
        ofstream hiScoreOFStream(hiScoreFilename, ios_base::trunc);
        if (!hiScoreOFStream.is_open()) { throw ios::failure("Error opening " + hiScoreFilename); }
        try {
            for (auto p : hiScoreTable) {
                hiScoreOFStream << p.first << " " << p.second << '\n';
            }
        } catch (exception& e) {
            throw ios::failure("Error writing scores to " + hiScoreFilename);
        }
        hiScoreOFStream.close();
    }
    
    bool HiScore::isHighScore(int score) const {
        if (hiScoreTable.size() < 5) { return true; }
        return score > hiScoreTable.back().second;
    }
    
    HiScore& HiScore::operator<<(char* name) {
        currentPlayerName = string(name);
        return *this;
    }
    
    HiScore& HiScore::operator<<(int score) {
        currentPlayerScore = score;
        try { addHighScore(); } catch (exception& e) { throw; }
        return *this;
    }
    
    void HiScore::addHighScore() {
        if (currentPlayerName.empty()) { return; }
        pair<string, int> entry(currentPlayerName, currentPlayerScore);
        
        if (hiScoreTable.empty()) {
            hiScoreTable.push_back(entry);
        } else {
            for (auto it = hiScoreTable.begin(); it != hiScoreTable.end(); it++) {
                if (currentPlayerScore > (*it).second) {
                    hiScoreTable.insert(it, entry);
                    break;
                } else if (it == hiScoreTable.end() - 1) { // Lowest score in table
                    hiScoreTable.push_back(entry);
                    break;
                }
            }
        }
        
        if (hiScoreTable.size() > maxTableEntries) {
            hiScoreTable.resize(maxTableEntries);
        }
        
        try { storeTable(); } catch (exception& e) { throw; }
    }
}

