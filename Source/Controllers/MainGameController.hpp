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

/// Ширина игрового поля Тетриса в блоках.
const int WIDTH = 10;

/// Высота игрового поля Тетриса в блоках.
const int HEIGHT = 25;

/// Целевой фреймрейт для игрового цикла.
const int FRAMERATE = 75;

/// Определения для различных типов тетромино.
constexpr auto Z_TETROMINO = 0;
constexpr auto L_TETROMINO = 1;
constexpr auto O_TETROMINO = 2;
constexpr auto S_TETROMINO = 3;
constexpr auto I_TETROMINO = 4;
constexpr auto J_TETROMINO = 5;
constexpr auto T_TETROMINO = 6;

/// Главный контроллер для управления игровой логикой и событиями.
class MainGameController {
public:
    /// Конструктор. Инициализирует состояние игры.
    MainGameController();

    /// Деструктор. Освобождает ресурсы.
    ~MainGameController();

    /// Запуск основного игрового цикла.
    void runGame();

protected:
    /// Флаг, указывающий, активное ли главное меню.
    bool isMenuActive = true;

    /// Игровое поле Тетриса, представленное в виде двумерного массива.
    /// Значение 0 означает пустую ячейку, не нулевые значения — заполненные блоки.
    int board[HEIGHT][WIDTH] = { 0 };

    /// Генерация случайной последовательности тетромино с использованием "сумки".
    /// Система гарантирует, что в каждой последовательности будут все типы тетромино.
    /// \return Вектор с тетромино в случайном порядке.
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

    /// Представление одного блока тетромино.
    class Piece {
    public:
        /// Координата X на игровом поле.
        int x;

        /// Координата Y на игровом поле.
        int y;

        /// Текущая стадия поворота (от 1 до 4).
        int rotation = 1;

        /// Поворот блока вокруг заданного центра.
        /// \param center Блок, вокруг которого происходит поворот.
        /// \param direction Направление поворота: положительное — по часовой стрелке, отрицательное — против.
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


    /// Массив, представляющий текущее тетромино, кэш и "призрак" (визуальная подсказка).
    Piece piece[4], cache[4], ghost[4];

    /// Двумерный массив, задающий координаты блоков для каждого типа тетромино.
    /// Каждый тетромино представлен набором из 4 блоков.
    int pieces[7][4] = {
        {3, 4, 5, 6},   ///< Z-образное тетромино
        {2, 4, 6, 7},   ///< L-образное тетромино
        {2, 3, 4, 5},   ///< O-образное тетромино (квадрат)
        {2, 4, 5, 7},   ///< S-образное тетромино
        {1, 3, 5, 7},   ///< I-образное тетромино (линия)
        {3, 5, 6, 7},   ///< J-образное тетромино
        {2, 4, 5, 6}    ///< T-образное тетромино
    };

    /// Представление заблокированного тетромино на игровом поле.
    class PieceLock {
    public:
        /// Координата X заблокированного блока.
        int x;

        /// Координата Y заблокированного блока.
        int y;

        /// Состояние анимации блокировки (используется для визуальных эффектов).
        double animation = 0;
    };

    /// Вектор заблокированных тетромино на игровом поле.
    std::vector<std::vector<PieceLock>> pieces_lock;

    /// Представление частицы для визуальных эффектов (например, взрывов).
    class Particle {
    public:
        /// Конструктор. Инициализирует частицу с позицией, скоростью и направлением.
        /// \param x Начальная координата X.
        /// \param y Начальная координата Y.
        /// \param speed Начальная скорость частицы.
        /// \param direction Начальное направление частицы в градусах.
        Particle(int x, int y, int speed, int direction) {
            this->x = x;
            this->y = y;
            this->direction = direction;
            this->speed = speed;
        }

        /// Координата X частицы.
        double x;

        /// Координата Y частицы.
        double y;

        /// Направление движения частицы в градусах.
        int direction;

        /// Скорость движения частицы.
        double speed;

        /// Значение альфа-канала для эффекта затухания (прозрачность).
        double alpha = 255;

        /// Форма частицы для отрисовки.
        sf::RectangleShape shape;

        /// Обновление позиции и прозрачности частицы на основе времени кадра.
        /// \param time_per_frame Время в секундах с момента последнего обновления кадра.
        void update(double time_per_frame) {
            double angle = this->direction * (cos(-1) / 180);
            this->x += this->speed * cos(angle) * time_per_frame;
            this->y += this->speed * sin(angle) * time_per_frame;
            this->alpha -= 400 * time_per_frame;
            this->speed += 100 * ((-this->speed) / 15) * time_per_frame;
        }

        /// Отрисовка частицы в игровом окне.
        /// \param window Указатель на окно SFML.
        void draw(sf::RenderWindow* window) {
            this->shape.setSize(sf::Vector2f(2, 2));
            this->shape.setFillColor(sf::Color(255, 255, 255, std::max((double)0, (double)this->alpha)));
            this->shape.setPosition(this->x, this->y);
            window->draw(this->shape);
        }
    };
    
    /// Вектор частиц для визуальных эффектов (например, взрыва блоков).
    std::vector<Particle> particles;

    /// Вспомогательная функция для получения знака числа.
    /// \param num Число для проверки.
    /// \return -1, если число отрицательное; 1, если положительное; 0, если равно нулю.
    int sign(int num) {
        if (num < 0) return -1;
        else if (num > 0) return 1;
        else return 0;
    }

    /// Создаёт частицы для визуальных эффектов при разрушении блоков.
    /// \param particles Ссылка на вектор частиц, в который будут добавлены новые частицы.
    void createParticle(std::vector<Particle>* particles) {
        for (int i = 0; i < 4; i++) {
            /// Генерация новой частицы с случайными координатами и направлением движения.
            Particle particle((piece[i].x * 30) + 150 + 15 + (rand() % 60 - 30),
                (piece[i].y * 30) - 60 - 30,
                rand() % 250 + 150,
                270 + (rand() % 60 - 30));
            particles->push_back(particle);
        }
    }

    /// Проверяет, не столкнулся ли "призрак" тетромино с игровым полем.
    /// "Призрак" — это тетромино, показывающее, где фигура приземлится.
    /// \return True, если нет столкновения, иначе False.
    bool isCollidedGhost() {
        for (int i = 0; i < 4; i++) {
            if (ghost[i].y >= HEIGHT) return false;
            else if (board[ghost[i].y][ghost[i].x]) return false;
        }
        return true;
    }

    /// Проверяет, не столкнулось ли текущее тетромино с игровым полем или другими блоками.
    /// \return True, если нет столкновения, иначе False.
    bool isCollided() {
        for (int i = 0; i < 4; i++) {
            /// Проверка выхода за границы игрового поля.
            if (piece[i].x < 0 || piece[i].x >= WIDTH || piece[i].y >= HEIGHT) return false;
            /// Проверка на наличие блока в занимаемой позиции.
            else if (board[piece[i].y][piece[i].x]) return false;
        }
        return true;
    }

    /// Проверяет, не завершилась ли игра (если текущее тетромино не может быть размещено).
    /// \return True, если игра закончена, иначе False.
    bool isDead() {
        for (int i = 0; i < 4; i++) {
            if (board[piece[i].y][piece[i].x]) return true;
        }
        return false;
    }

    /// Объект главного меню игры.
    MainMenuView mainMenuView;

    /// Обрабатывает события главного меню.
    /// \param event Событие, которое требуется обработать.
    void handleMainMenuEvent(const sf::Event& event);

    /// Запускает новую игру в Тетрис.
    void startTetrisGame();
};

#endif // MAINGAMECONTROLLER_HPP