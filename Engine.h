#ifndef ENGINE_H
#define ENGINE_H

#include "SharedGameUtils.h"
#include "Renderer.h"
#include "HiScore.h"
#include "Moving.h"
#include "Potter.h"
#include "Gnome.h"
#include "Traal.h"

namespace Game {
    class Engine {
    public:
        Engine(string mapFilename, string hiScoreFilename);
        ~Engine();
    private:
        Renderer* renderer = nullptr;
        HiScore* hiScore = nullptr;
        vector<string> levelMap;
        int mapWidth;
        int mapHeight;
        Potter* potter = nullptr;
        Gnome* gnome = nullptr;
        Traal* traal = nullptr;
        int gemCount = 0;
        int score = 0;
        vector<position> changedPositions;
        vector<position> objectsToRestore;
        bool playing;
        bool gameWon;
        
        void init();
        void startGame(string mapFilename);
        void loadLevelMap(string mapFilename);
        void spawnObjects();
        position spawnAtRandomPosition(char type);
        void startGameLoop();
        void processMovement(Potter* player);
        void processMovement(Moving* enemy, position playerPosition);
        void restorePickableObjects();
        void pickUpGem();
        void pickUpScript();
        void endGame();
        void processScore();
        void inputName(char* name);
        bool validateName(char* name);
    };
}
#endif
