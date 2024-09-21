#ifndef MAINGAMECONTROLLER_HPP
#define MAINGAMECONTROLLER_HPP

const int WIDTH = 10;
const int HEIGHT = 25;
const int FRAMERATE = 75;

#define Z_TETROMINO 0
#define L_TETROMINO 1
#define O_TETROMINO 2
#define S_TETROMINO 3
#define I_TETROMINO 4
#define J_TETROMINO 5
#define T_TETROMINO 6

#include <iostream>
#include <vector>
#include <cmath>
#include "../Views/MainMenuView.hpp"
#include <memory>
#include <time.h>
#include <thread>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>


class MainGameController {
public:
    MainGameController();
    ~MainGameController();
    void runGame();

protected:
    bool isMenuActive = true;
    int board[HEIGHT][WIDTH] = { 0 };
    std::vector<int> generateNewBag() {

        std::vector<int> template_bag;

        for (int i = 0; i < 7; i++) {

            template_bag.push_back(i);
        }

        std::vector<int> new_bag;

        while (template_bag.size() > 0) {

            int index = rand() % template_bag.size();
            int choose_piece = template_bag.at(index);
            template_bag.erase(template_bag.begin() + index);
            new_bag.push_back(choose_piece);
        }

        return new_bag;
    }

    class Piece {

    public:

        int x;
        int y;
        int rotation = 1;

        void Rotate(Piece center, int direction) {

            int x = this->y - center.y;
            int y = this->x - center.x;
            this->x = center.x + (x * -direction);
            this->y = center.y + (y * direction);

            this->rotation += direction;

            if (this->rotation > 4) this->rotation = 1;
            if (this->rotation < 1) this->rotation = 4;
        }
    };

    Piece piece[4], cache[4], ghost[4];

    int pieces[7][4] = {

       {3, 4, 5, 6},
       {2, 4, 6, 7},
       {2, 3, 4, 5},
       {2, 4, 5, 7},
       {1, 3, 5, 7},
       {3, 5, 6, 7},
       {2, 4, 5, 6}
    };

    class PieceLock {

    public:

        int x;
        int y;
        double animation = 0;
    };
   
    std::vector<std::vector<PieceLock>> pieces_lock;

    class Particle {

    public: Particle(int x, int y, int speed, int direction) {

        this->x = x;
        this->y = y;
        this->direction = direction;
        this->speed = speed;
    }

          double x;
          double y;
          int direction;
          double speed;
          double alpha = 255;
          sf::RectangleShape shape;

          void update(double time_per_frame) {

              double angle = this->direction * (cos(-1) / 180);
              this->x += this->speed * cos(angle) * time_per_frame;
              this->y += this->speed * sin(angle) * time_per_frame;
              this->alpha -= 400 * time_per_frame;
              this->speed += 100 * ((-this->speed) / 15) * time_per_frame;
          }

          void draw(sf::RenderWindow* window) {

              this->shape.setSize(sf::Vector2f(2, 2));
              this->shape.setFillColor(sf::Color(255, 255, 255, std::max((double)0, (double)this->alpha)));
              this->shape.setPosition(this->x, this->y);
              window->draw(this->shape);
          }
    };
    
    std::vector<Particle> particles;

    int sign(int num) {

        if (num < 0) return -1;
        else if (num > 0) return 1;
        else return 0;
    }

    void createParticle(std::vector<Particle>* particles) {

        for (int i = 0; i < 4; i++) {

            Particle particle((piece[i].x * 30) + 150 + 15 + (rand() % 60 - 30), (piece[i].y * 30) - 60 - 30, rand() % 250 + 150, 270 + (rand() % 60 - 30));
            particles->push_back(particle);
        }
    }

    bool isCollidedGhost() {

        for (int i = 0; i < 4; i++) {

            if (ghost[i].y >= HEIGHT) return false;
            else if (board[ghost[i].y][ghost[i].x]) return false;
        }
        return 1;
    }

    bool isCollided() {

        for (int i = 0; i < 4; i++) {

            if (piece[i].x < 0 || piece[i].x >= WIDTH || piece[i].y >= HEIGHT) return false;
            else if (board[piece[i].y][piece[i].x]) return false;
        }
        return 1;
    }

    bool isDead() {

        for (int i = 0; i < 4; i++) if (board[piece[i].y][piece[i].x]) return true;
        return false;
    }

    MainMenuView mainMenuView;

    void handleMainMenuEvent(const sf::Event& event);

    void startTetrisGame();

};

#endif // MAINGAMECONTROLLER_HPP