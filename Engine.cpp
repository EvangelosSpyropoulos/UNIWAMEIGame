#include "Engine.h"

#include <ncurses.h>
#include <fstream>
#include <string.h>

namespace Game{
    Engine::Engine(string mapFilename, string hiScoreFilename) {
        init();
        hiScore = new HiScore(hiScoreFilename);
        startGame(mapFilename);
    }
    
    void Engine::init() {
        initscr();
        cbreak();
        keypad(stdscr, true);
        halfdelay(5);
        renderer = new Renderer(&levelMap);
    }
    
    void Engine::startGame(string mapFilename) {
        try {
            loadLevelMap(mapFilename);            
        } catch (exception& e) {
            renderer->renderErrorScreen(e.what());
            return;
        }
        spawnObjects();
        renderer->renderNewLevel();
        startGameLoop();
    }
    
    void Engine::loadLevelMap(string mapFilename) {
        levelMap.resize(0);
        
        ifstream mapFile(mapFilename);
        if (!mapFile.is_open()) { throw ios::failure("Error opening" + mapFilename); }
        try {
            for (string line; getline(mapFile, line);) {
                levelMap.push_back(line);
            }
            mapWidth = levelMap[0].size();
            mapHeight = levelMap.size();
            mapFile.close();
        } catch (exception& e) {
            throw ios::failure("Error loading level map from " + mapFilename);
        }
    }
    
    void Engine::spawnObjects() {
        for (int i = 0; i < 10; i++) {
            spawnAtRandomPosition(GEM);
            gemCount++;
        }
        
        position potterPosition = spawnAtRandomPosition(POTTER);
        potter = new Potter(potterPosition, &levelMap);
        
        position gnomePosition = spawnAtRandomPosition(GNOME);
        gnome = new Gnome(gnomePosition, &levelMap);
        
        position traalPosition = spawnAtRandomPosition(TRAAL);
        traal = new Traal(traalPosition, &levelMap);
    }
    
    position Engine::spawnAtRandomPosition(char type) {
        srand(time(0));
        position spawnPosition;
        do {
            spawnPosition = position {
                rand() % mapWidth,
                rand() % mapHeight
            };
        } while (levelMap[spawnPosition.y][spawnPosition.x] != CORRIDOR);
        levelMap[spawnPosition.y][spawnPosition.x] = type;
        return spawnPosition;
    }
    
    void Engine::startGameLoop() {
        playing = true;
        gameWon = false;
        while (playing) {
            changedPositions.resize(0);
            processMovement(potter);
            processMovement(gnome, potter->getPosition());
            processMovement(traal, potter->getPosition());
            restorePickableObjects();
            renderer->process(changedPositions);
        }
        processScore();
    }
    
    void Engine::processMovement(Potter* player) {
        position playerPosition  = player->getPosition();
        direction relativeDirection = player->move();
        position newPosition = directionToPosition(playerPosition, relativeDirection);
        
        switch (levelMap[newPosition.y][newPosition.x]) {
            case GEM:
                pickUpGem();
                break;
            case SCRIPT:
                pickUpScript();
                break;
            case GNOME:
            case TRAAL:
                endGame();
                break;
        }
        
        levelMap[playerPosition.y][playerPosition.x] = CORRIDOR;
        levelMap[newPosition.y][newPosition.x] = POTTER;
        
        changedPositions.push_back(playerPosition);
        changedPositions.push_back(newPosition);
        
        player->setPosition(newPosition);
    }
    
    void Engine::processMovement(Moving* enemy, position playerPosition) {
        position enemyPosition  = enemy->getPosition();
        direction relativeDirection = enemy->move(playerPosition);
        position newPosition = directionToPosition(enemyPosition, relativeDirection);
        
        switch (levelMap[newPosition.y][newPosition.x]) {
            case GEM:
            case SCRIPT:
                objectsToRestore.push_back(newPosition);
                break;
            case POTTER:
                endGame();
                break;
        }
        
        levelMap[enemyPosition.y][enemyPosition.x] = CORRIDOR;
        levelMap[newPosition.y][newPosition.x] = enemy->getCharRepresentation();
        
        changedPositions.push_back(enemyPosition);
        changedPositions.push_back(newPosition);
        
        enemy->setPosition(newPosition);
    }
    
    void Engine::restorePickableObjects() {        
        if (gemCount == 0 && objectsToRestore.size() != 0) {
            position pos = objectsToRestore.at(0);
            if (levelMap[pos.y][pos.x] == CORRIDOR) {
                levelMap[pos.y][pos.x] = SCRIPT;
                changedPositions.push_back(pos);
                objectsToRestore.erase(objectsToRestore.begin());
            }
            return;
        }
        
        for (auto it = objectsToRestore.begin(); it != objectsToRestore.end();) {
            position pos = *it;
            if (levelMap[pos.y][pos.x] == CORRIDOR) {
                levelMap[pos.y][pos.x] = GEM;
                changedPositions.push_back(pos);
                it = objectsToRestore.erase(it);
            } else {
                it++;
            }
        }
    }
    
    void Engine::pickUpGem() {
        score += 10;
        gemCount--;
        
        if (gemCount == 0) {
            position scriptPosition = spawnAtRandomPosition(SCRIPT);
            changedPositions.push_back(scriptPosition);
        }
    }
    
    void Engine::pickUpScript() {
        score += 100;
        gameWon = true;
        endGame();
    }
    
    void Engine::endGame() {
        playing = false;
    }
    
    void Engine::processScore() {
        renderer->renderResultScreen(score, gameWon);
        if (hiScore->isHighScore(score)) {
            renderer->renderNameInputScreen();
            char name[11];
            inputName(name);
            try {
                *hiScore << name << score;
            } catch (exception& e) {
                renderer->renderErrorScreen(e.what());
                return;
            }
            auto hiScoreTable = hiScore->getHiScoreTable();
            renderer->renderHiScoreTableScreen(hiScoreTable);
        }
    }
    
    void Engine::inputName(char* name) {
        echo();
        nocbreak();
        getnstr(name, 10);
        noecho();
        cbreak();
    }
    
    Engine::~Engine() {
        if (renderer) { delete renderer; }
        if (hiScore) { delete hiScore; }
        if (potter) { delete potter; }
        if (gnome) { delete gnome; }
        if (traal) { delete traal; }
        endwin();
    }
}
