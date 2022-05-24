#include "Renderer.h"

#include <ncurses.h>
#include <thread>
#include <chrono>

namespace Game {
    Renderer::Renderer(vector<string>* levelMap) {
        noecho();
        start_color();
        initializeColors();
        this->levelMap = levelMap;
    }
    
    void Renderer::renderNewLevel() {
        clear();
        for (int row = 0; row < levelMap->size(); row++) {
            for (int col = 0; col < (*levelMap)[row].size(); col++) {
                char item = (*levelMap)[row][col];
                mvAddItem(row, col, item);
            }
        }
        refresh();
    }
    
    void Renderer::process(vector<position> changedPositions) {
        for (position pos: changedPositions) {
            char item = (*levelMap)[pos.y][pos.x];
            mvAddItem(pos.y, pos.x, item);
        }
        refresh();
    }
    
    void Renderer::renderResultScreen(int score, bool gameWon) {
        clear();
        mvprintw(0, 0, (gameWon ? "You Won!" : "Game Over!"));
        mvprintw(1, 0, "You scored %d points!", score);
        refresh();
        this_thread::sleep_for(chrono::seconds(3));
    }
    
    void Renderer::renderNameInputScreen() {
        clear();
        mvprintw(0, 0, "Please enter your name: ");
        refresh();
    }
    
    void Renderer::renderHiScoreTableScreen(vector<pair<string, int>> hiScoreTable) {
        clear();
        mvprintw(0, 7, "HIGH SCORES");
        mvprintw(1, 0, "Name");
        mvprintw(1, 20, "Score");
        int row = 2;
        for (auto p : hiScoreTable) {
            mvprintw(row, 0, p.first.c_str());
            mvprintw(row, 20, "%d", p.second);
            row++;
        }
        refresh();
        this_thread::sleep_for(chrono::seconds(3));
    }
    
    void Renderer::renderErrorScreen(const char* errorMessage) {
        clear();
        mvprintw(0, 0, errorMessage);
        mvprintw(1, 0, "Terminating game...");
        refresh();
        this_thread::sleep_for(chrono::seconds(3));
    }

    void Renderer::initializeColors() {
        init_pair(0, COLOR_BLACK, COLOR_BLACK);
        init_pair(1, COLOR_WHITE, COLOR_BLACK);
        init_pair(2, COLOR_YELLOW, COLOR_BLACK);
        init_pair(3, COLOR_GREEN, COLOR_BLACK);
        init_pair(4, COLOR_BLUE, COLOR_BLACK);
        init_pair(5, COLOR_RED, COLOR_BLACK);
    }
    
    int Renderer::getItemColor(char item) {
        switch (item) {
            case CORRIDOR:
                return 0;
            case WALL:
                return 1;
            case SCRIPT:
                return 2;
            case GEM:
                return 3;
            case POTTER:
                return 4;
            case GNOME:
            case TRAAL:
                return 5;
            default:
                return 0;
        }
    }
    
    char Renderer::getItemSymbol(char item) {
        switch (item) {
            case WALL:
                return '|';
            default:
                return item;
        }
    }
    
    void Renderer::mvAddItem(int row, int col, char item) {
        attron(COLOR_PAIR(getItemColor(item)));
        mvaddch(row, col, getItemSymbol(item));
        attroff(COLOR_PAIR(getItemColor(item)));
    }
}
