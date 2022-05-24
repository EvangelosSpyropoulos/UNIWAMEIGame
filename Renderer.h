#ifndef RENDERER_H
#define RENDERER_H

#include "SharedGameUtils.h"

namespace Game {
    class Renderer {
    public:
        Renderer(vector<string>* levelMap);
        void renderNewLevel();
        void process(vector<position> changedPositions);
        void renderResultScreen(int score, bool gameWon);
        void renderNameInputScreen();
        void renderHiScoreTableScreen(vector<pair<string, int>> hiScoreTable);
        void renderErrorScreen(const char* errorMessage);
        void initializeColors();
        int getItemColor(char item);
        char getItemSymbol(char item);
        void mvAddItem(int row, int col, char item);
    private:
        vector<string>* levelMap;
    };
}
#endif
