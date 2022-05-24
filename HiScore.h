#ifndef HI_SCORE_H
#define HI_SCORE_H

#include <fstream>
#include <vector>
#include <string>

using namespace std;

namespace Game {
    class HiScore {
    public:
        HiScore(string hiScoreFilename);
        bool isHighScore(int score) const;
        void retrieveTable();
        void storeTable();
        HiScore& operator<<(char* name);
        HiScore& operator<<(int score);
        vector<pair<string, int>> getHiScoreTable() const { return hiScoreTable; }
    private:
        string hiScoreFilename;
        vector<pair<string, int>> hiScoreTable;
        string currentPlayerName;
        int currentPlayerScore;
        const int maxTableEntries = 5;
        
        void addHighScore();
    };
}

#endif
