#ifndef MAINGAMECONTROLLER_HPP
#define MAINGAMECONTROLLER_HPP

#include "../Views/MainMenuView.hpp"
#include <cmath>
#include <iostream>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <thread>
#include <vector>

/// ������ �������� ���� ������� � ������.
const int WIDTH = 10;

/// ������ �������� ���� ������� � ������.
const int HEIGHT = 25;

/// ������� ��������� ��� �������� �����.
const int FRAMERATE = 75;

/// ����������� ��� ��������� ����� ���������.
constexpr auto Z_TETROMINO = 0;
constexpr auto L_TETROMINO = 1;
constexpr auto O_TETROMINO = 2;
constexpr auto S_TETROMINO = 3;
constexpr auto I_TETROMINO = 4;
constexpr auto J_TETROMINO = 5;
constexpr auto T_TETROMINO = 6;

/// ������� ���������� ��� ���������� ������� ������� � ���������.
class MainGameController {
public:
    /// �����������. �������������� ��������� ����.
    MainGameController();

    /// ����������. ����������� �������.
    ~MainGameController();

    /// ������ ��������� �������� �����.
    void runGame();

protected:
    /// ����, �����������, �������� �� ������� ����.
    bool isMenuActive = true;

    /// ������� ���� �������, �������������� � ���� ���������� �������.
    /// �������� 0 �������� ������ ������, �� ������� �������� � ����������� �����.
    int board[HEIGHT][WIDTH] = { 0 };

    /// ��������� ��������� ������������������ ��������� � �������������� "�����".
    /// ������� �����������, ��� � ������ ������������������ ����� ��� ���� ���������.
    /// \return ������ � ��������� � ��������� �������.
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

    /// ������������� ������ ����� ���������.
    class Piece {
    public:
        /// ���������� X �� ������� ����.
        int x;

        /// ���������� Y �� ������� ����.
        int y;

        /// ������� ������ �������� (�� 1 �� 4).
        int rotation = 1;

        /// ������� ����� ������ ��������� ������.
        /// \param center ����, ������ �������� ���������� �������.
        /// \param direction ����������� ��������: ������������� � �� ������� �������, ������������� � ������.
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


    /// ������, �������������� ������� ���������, ��� � "�������" (���������� ���������).
    Piece piece[4], cache[4], ghost[4];

    /// ��������� ������, �������� ���������� ������ ��� ������� ���� ���������.
    /// ������ ��������� ����������� ������� �� 4 ������.
    int pieces[7][4] = {
        {3, 4, 5, 6},   ///< Z-�������� ���������
        {2, 4, 6, 7},   ///< L-�������� ���������
        {2, 3, 4, 5},   ///< O-�������� ��������� (�������)
        {2, 4, 5, 7},   ///< S-�������� ���������
        {1, 3, 5, 7},   ///< I-�������� ��������� (�����)
        {3, 5, 6, 7},   ///< J-�������� ���������
        {2, 4, 5, 6}    ///< T-�������� ���������
    };

    /// ������������� ���������������� ��������� �� ������� ����.
    class PieceLock {
    public:
        /// ���������� X ���������������� �����.
        int x;

        /// ���������� Y ���������������� �����.
        int y;

        /// ��������� �������� ���������� (������������ ��� ���������� ��������).
        double animation = 0;
    };

    /// ������ ��������������� ��������� �� ������� ����.
    std::vector<std::vector<PieceLock>> pieces_lock;

    /// ������������� ������� ��� ���������� �������� (��������, �������).
    class Particle {
    public:
        /// �����������. �������������� ������� � ��������, ��������� � ������������.
        /// \param x ��������� ���������� X.
        /// \param y ��������� ���������� Y.
        /// \param speed ��������� �������� �������.
        /// \param direction ��������� ����������� ������� � ��������.
        Particle(int x, int y, int speed, int direction) {
            this->x = x;
            this->y = y;
            this->direction = direction;
            this->speed = speed;
        }

        /// ���������� X �������.
        double x;

        /// ���������� Y �������.
        double y;

        /// ����������� �������� ������� � ��������.
        int direction;

        /// �������� �������� �������.
        double speed;

        /// �������� �����-������ ��� ������� ��������� (������������).
        double alpha = 255;

        /// ����� ������� ��� ���������.
        sf::RectangleShape shape;

        /// ���������� ������� � ������������ ������� �� ������ ������� �����.
        /// \param time_per_frame ����� � �������� � ������� ���������� ���������� �����.
        void update(double time_per_frame) {
            double angle = this->direction * (cos(-1) / 180);
            this->x += this->speed * cos(angle) * time_per_frame;
            this->y += this->speed * sin(angle) * time_per_frame;
            this->alpha -= 400 * time_per_frame;
            this->speed += 100 * ((-this->speed) / 15) * time_per_frame;
        }

        /// ��������� ������� � ������� ����.
        /// \param window ��������� �� ���� SFML.
        void draw(sf::RenderWindow* window) {
            this->shape.setSize(sf::Vector2f(2, 2));
            this->shape.setFillColor(sf::Color(255, 255, 255, std::max((double)0, (double)this->alpha)));
            this->shape.setPosition(this->x, this->y);
            window->draw(this->shape);
        }
    };
    
    /// ������ ������ ��� ���������� �������� (��������, ������ ������).
    std::vector<Particle> particles;

    /// ��������������� ������� ��� ��������� ����� �����.
    /// \param num ����� ��� ��������.
    /// \return -1, ���� ����� �������������; 1, ���� �������������; 0, ���� ����� ����.
    int sign(int num) {
        if (num < 0) return -1;
        else if (num > 0) return 1;
        else return 0;
    }

    /// ������ ������� ��� ���������� �������� ��� ���������� ������.
    /// \param particles ������ �� ������ ������, � ������� ����� ��������� ����� �������.
    void createParticle(std::vector<Particle>* particles) {
        for (int i = 0; i < 4; i++) {
            /// ��������� ����� ������� � ���������� ������������ � ������������ ��������.
            Particle particle((piece[i].x * 30) + 150 + 15 + (rand() % 60 - 30),
                (piece[i].y * 30) - 60 - 30,
                rand() % 250 + 150,
                270 + (rand() % 60 - 30));
            particles->push_back(particle);
        }
    }

    /// ���������, �� ���������� �� "�������" ��������� � ������� �����.
    /// "�������" � ��� ���������, ������������, ��� ������ �����������.
    /// \return True, ���� ��� ������������, ����� False.
    bool isCollidedGhost() {
        for (int i = 0; i < 4; i++) {
            if (ghost[i].y >= HEIGHT) return false;
            else if (board[ghost[i].y][ghost[i].x]) return false;
        }
        return true;
    }

    /// ���������, �� ����������� �� ������� ��������� � ������� ����� ��� ������� �������.
    /// \return True, ���� ��� ������������, ����� False.
    bool isCollided() {
        for (int i = 0; i < 4; i++) {
            /// �������� ������ �� ������� �������� ����.
            if (piece[i].x < 0 || piece[i].x >= WIDTH || piece[i].y >= HEIGHT) return false;
            /// �������� �� ������� ����� � ���������� �������.
            else if (board[piece[i].y][piece[i].x]) return false;
        }
        return true;
    }

    /// ���������, �� ����������� �� ���� (���� ������� ��������� �� ����� ���� ���������).
    /// \return True, ���� ���� ���������, ����� False.
    bool isDead() {
        for (int i = 0; i < 4; i++) {
            if (board[piece[i].y][piece[i].x]) return true;
        }
        return false;
    }

    /// ������ �������� ���� ����.
    MainMenuView mainMenuView;

    /// ������������ ������� �������� ����.
    /// \param event �������, ������� ��������� ����������.
    void handleMainMenuEvent(const sf::Event& event);

    /// ��������� ����� ���� � ������.
    void startTetrisGame();
};

#endif // MAINGAMECONTROLLER_HPP