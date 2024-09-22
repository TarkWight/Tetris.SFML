#include "MainGameController.hpp"

MainGameController::MainGameController() : mainMenuView() {}

MainGameController::~MainGameController() {}

/// Запуск основного игрового цикла.
void MainGameController::runGame() {
    sf::RenderWindow window(sf::VideoMode(600, 720), "Tetris");

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            else {
                handleMainMenuEvent(event);
            }
        }

        window.clear();
        mainMenuView.draw(window);
        window.display();
    }
}

/// Обрабатывает события главного меню.
/// \param event Событие, которое требуется обработать.
void MainGameController::handleMainMenuEvent(const sf::Event& event) {
    if (event.type == sf::Event::MouseButtonPressed) {
        if (mainMenuView.isStartButtonClicked(event.mouseButton.x, event.mouseButton.y)) {
            startTetrisGame();
            exit(0);
        }
        else if (mainMenuView.isChangeColorButtonClicked(event.mouseButton.x, event.mouseButton.y)) {
            std::cout << "Change color\n";
        }
        else if (mainMenuView.isLeaderboardButtonClicked(event.mouseButton.x, event.mouseButton.y)) {
            std::cout << "Show leaderboard\n";
        }
        else if (mainMenuView.isExitButtonClicked(event.mouseButton.x, event.mouseButton.y)) {
            std::cout << "Exit\n";
            exit(0);
        }
    }
    else if (event.type == sf::Event::MouseMoved) {
        mainMenuView.handleMouseMove(event.mouseMove.x, event.mouseMove.y);
    }
    else if (event.type == sf::Event::KeyPressed) {
        mainMenuView.handleKeyboardInput(event);
    }
}

/// Запускает новую игру в Тетрис.
void MainGameController::startTetrisGame() {
    sf::RenderWindow gameWindow(sf::VideoMode(600, 720), "Tetris");
    srand(static_cast<unsigned int>(time(0)));  // Инициализация генератора случайных чисел

    // Загрузка текстур для блоков
    sf::Texture texturePiece;
    texturePiece.loadFromFile(resourcePath + "/Resources/Sprites/jstris1.png");
    int textureSize = 30;  // Размер текстуры блока
    sf::Sprite spritePiece(texturePiece);
    spritePiece.setTextureRect(sf::IntRect(0, 0, textureSize, textureSize));

    // Загрузка текстуры для "призрака"
    sf::Texture textureGhost;
    textureGhost.loadFromFile(resourcePath + "/Resources/Sprites/ghost.png");
    sf::Sprite spriteGhost(textureGhost);
    spriteGhost.setTextureRect(sf::IntRect(0, 0, textureSize, textureSize));

    // Загрузка текстуры для анимации заблокированных блоков
    sf::Texture textureLockedPiece;
    textureLockedPiece.loadFromFile(resourcePath + "/Resources/Sprites/piece_lock.png");
    sf::Sprite spriteLockedPiece(textureLockedPiece);
    spriteLockedPiece.setTextureRect(sf::IntRect(0, 0, textureSize, textureSize));

    // Загрузка текстуры для игрового поля
    sf::Texture textureBoard;
    textureBoard.loadFromFile(resourcePath + "/Resources/Sprites/board.png");
    sf::Sprite spriteBoard(textureBoard);

    // Загрузка шрифта
    sf::Font fontGame;
    fontGame.loadFromFile(resourcePath + "/Resources/Fonts/Minecraft.ttf");

    int holdPiece;            // Переменная для хранения состояния удерживания тетромино
    int moveX;          // Переменная для перемещения по оси X
    int rotatePiece;         // Переменная для хранения направления поворота
    int colorPiece;          // Переменная для хранения цвета тетромино
    int hardDrop;       // Переменная для жесткого падения тетромино
    int holded;         // Переменная для отслеживания удерживаемого тетромино
    int moveLeft;       // Переменная для перемещения влево
    int moveRight;      // Переменная для перемещения вправо
    int start;          // Переменная для отслеживания начала игры

    sf::Clock trackingFrameTime;               // Часы для отслеживания времени кадра
    sf::Clock trackingGameTime;           // Часы для отслеживания времени игры
    sf::Clock elapsedGameTime;     // Часы для отслеживания прошедшего времени игры

    double gameTimer;                  // Таймер для управления временными интервалами
    double gameDelay;                  // Задержка между кадрами
    std::vector<int> bagOfSevenPieces;     // Вектор для хранения текущей последовательности тетромино
    std::vector<int> nextBagOfSevenPieces; // Вектор для хранения следующей последовательности тетромино

restart:
    // Обработка управления
        double airSoftDrop = 8;
        double lockDelay = 0.5;
        double fastDropDelay = 0;
        int lockCount = 14;
        bool isTouchGround = false;

        int totalLineCount = 0;
        int totalPieceCount = 0;

        int lockCountValue = lockCount;
        double airSoftDropValue = airSoftDrop;
        double lockDelayValue = lockDelay;

        // Инициализация игрового поля
        for (int i = 0; i < HEIGHT; i++) {
            for (int j = 0; j < WIDTH; j++) {
                board[i][j] = 0;
            }
        }

        start = 3;
        gameTimer = 0;
        gameDelay = 0.5;
        moveX = 0;
        colorPiece = 0;
        hardDrop = 0;
        rotatePiece = 0;
        holdPiece = -1;
        moveLeft = 0;
        moveRight = 0;
        holded = 0;
        bagOfSevenPieces = generateNewBag();
        nextBagOfSevenPieces = generateNewBag();

        double pieceIndicatorShapeAlpha = 0;
        double boardWobble = 0;

        int lineClearCombo = 0;
        int btbCombo = 0;

        // Выбор первого тетромино
        int chosenPieceIndex = bagOfSevenPieces.at(0);
        bagOfSevenPieces.erase(bagOfSevenPieces.begin());

        colorPiece = chosenPieceIndex;
        for (int i = 0; i < 4; i++) {
            currentPiece[i].x = pieces[chosenPieceIndex][i] % 2 + 4;
            currentPiece[i].y = pieces[chosenPieceIndex][i] / 2 + 3;
            currentPiece[i].rotation = 0;

            if (colorPiece == J_TETROMINO) {
                currentPiece[i].x--;
            }
        }

        for (int i = 0; i < 4; i++) {
            Piece center = currentPiece[1];
            if (colorPiece == I_TETROMINO) {
                currentPiece[i].rotate(center, 1);
            }
            if (colorPiece == T_TETROMINO) {
                currentPiece[i].rotate(center, -1);
            }
            if (colorPiece == S_TETROMINO) {
                currentPiece[i].rotate(center, -1);
            }
            if (colorPiece == Z_TETROMINO) {
                currentPiece[i].rotate(center, -1);
            }
            if (colorPiece == L_TETROMINO) {
                currentPiece[i].rotate(center, -1);
            }
            if (colorPiece == J_TETROMINO) {
                currentPiece[i].rotate(center, 1);
            }
        }

        // Флаги управления
        int isRotateClockWise = 0;
        int isRotateCounterClockwise = 0;
        int isHardDrop = 0;
        int isMoveRight = 0;
        int isMoveLeft = 0;
        int isHoldPiece = 0;
        int isSidehit = 0;
        int isTSpin = 0;
        int isRestart = 0;

        int keyRotateClockwise = 0;
        int keyRotateCounterClockwise = 0;
        int keyHardDrop = 0;
        int keyMoveRight = 0;
        int keyMoveLeft = 0;
        int keyRightHold = 0;
        int keyLeftHold = 0;
        bool isOnFocus = true;
        int lastKeyPressed = 0;
        int keyRestart = 0;

        // Основной цикл обработки событий в игре Тетрис.
        // Цикл будет работать, пока окно открыто. Он обновляет таймер игры, проверяет столкновения,
        // управляет логикой блокировки тетромино и обрабатывает события управления.
        while (gameWindow.isOpen()) {
            float elapsedTime = trackingFrameTime.getElapsedTime().asSeconds();

            for (int i = 0; i < 4; i++) {
                previousPiecePosition[i] = currentPiece[i];
                currentPiece[i].y++;
            }

            if (!isCollided()) {
                lockDelayValue -= elapsedTime;

                if (lockDelayValue <= 0) {
                    for (int i = 0; i < 4; i++) {
                        currentPiece[i] = previousPiecePosition[i];
                    }

                    goto makeNewPiece;
                }

                if (!isTouchGround) {
                    isTouchGround = true;
                }
            } else {
                isTouchGround = false;
            }

            for (int i = 0; i < 4; i++) {
                currentPiece[i] = previousPiecePosition[i];
            }

            gameTimer += elapsedTime;
            trackingFrameTime.restart();

            sf::Event e;
            while (gameWindow.pollEvent(e)) {
                if (e.type == sf::Event::GainedFocus) {
                    isOnFocus = true;
                }
                if (e.type == sf::Event::LostFocus) {
                    isOnFocus = false;
                }

                if (isOnFocus && e.type == sf::Event::KeyReleased) {
                    if (e.key.code == sf::Keyboard::X || e.key.code == sf::Keyboard::Up) {
                        isRotateClockWise = 0;
                    }
                    if (e.key.code == sf::Keyboard::Z) {
                        isRotateCounterClockwise = 0;
                    }
                    if (e.key.code == sf::Keyboard::Space) {
                        isHardDrop = 0;
                    }
                    if (e.key.code == sf::Keyboard::C) {
                        isHoldPiece = 0;
                    }
                    if (e.key.code == sf::Keyboard::Left) {
                        isMoveLeft = 0;
                    }
                    if (e.key.code == sf::Keyboard::Right) {
                        isMoveRight = 0;
                    }
                    if (e.key.code == sf::Keyboard::R) {
                        isRestart = 0;
                    }
                }

                if (e.type == sf::Event::Closed) {
                    gameWindow.close();
                }
            }

            if (isOnFocus) {

                //Key Fixed
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::C) && isHoldPiece == 0) {
                    isHoldPiece = -1;
                    holded = 1;
                }

                if ((sf::Keyboard::isKeyPressed(sf::Keyboard::X) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) && isRotateClockWise == 0) {
                    isRotateClockWise = -1;
                    rotatePiece = 1;
                }

                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z) && isRotateCounterClockwise == 0) {
                    isRotateCounterClockwise = -1;
                    rotatePiece = -1;
                }

                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && isHardDrop == 0) {
                    isHardDrop = -1;
                    hardDrop = 1;
                }

                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && isMoveLeft == 0) {
                    isMoveLeft = -1;
                    moveLeft = 1;
                }

                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && isMoveRight == 0) {
                    isMoveRight = -1;
                    moveRight = 1;
                }

                if (sf::Keyboard::isKeyPressed(sf::Keyboard::R) && isRestart == 0) {
                    isRestart = -1;
                    goto restart;
                }

                /// \brief Проверяет, проиграл ли игрок, и обрабатывает ускоренное падение.
                ///
                /// Эта часть кода проверяет, находится ли игрок в "мертвом" состоянии 
                /// (когда больше нет доступных ходов или фигуры заполнили игровое поле),
                /// и в случае смерти перезапускает игру. Также обрабатывается ввод с клавиши
                /// "стрелка вниз", которая активирует ускоренное падение фигуры.
                /// 
                /// \details Если игрок считается мертвым (функция isDead() возвращает true), 
                /// то игра перезапускается (идет переход к метке restart). Если нажата клавиша 
                /// "стрелка вниз", то устанавливается ускоренное время падения фигуры.
                /// 
                /// \note Использование метки restart позволяет быстро перезапустить игру без
                /// повторного создания объектов.
                /// 
                /// Управление клавишами:
                /// - Стрелка вниз: Ускоренное падение фигуры.
                if (isDead()) {
                    goto restart;  // Если игрок мертв, игра перезапускается
                }

                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
                    gameDelay = fastDropDelay;
                }


                /// \brief Обработка движений фигуры влево, вправо и мягкого падения.
                ///
                /// Этот блок кода обрабатывает перемещения текущей фигуры по горизонтали
                /// (влево и вправо) и вычисляет мягкое падение в воздухе. Он проверяет, нажаты
                /// ли клавиши движения и выполняет сдвиг фигуры на одну клетку в соответствующем
                /// направлении. Также осуществляется проверка на столкновения и обработка
                /// блокировки фигуры, если движение невозможно.
                ///
                /// \details
                /// - Если нажаты клавиши влево или вправо, фигура сдвигается на одну клетку
                ///   по оси X. Если после этого она сталкивается с другими блоками или стенками,
                ///   фигура возвращается на исходное место.
                /// - В случае столкновения, если не завершился отсчет времени до блокировки (lock),
                ///   уменьшается счетчик lockCountValue и сбрасывается таймер задержки блокировки.
                /// - Когда время мягкого падения (airSoftDrop) заканчивается, фигура падает
                ///   по направлению к низу, если нет препятствий.
                ///
                /// \note Переменная `airSoftDropValue` контролирует скорость мягкого падения,
                ///       в то время как переменные `lockCountValue` и `lockDelayValue` 
                ///       управляют процессом блокировки фигуры на месте.
                keyMoveLeft = sf::Keyboard::isKeyPressed(sf::Keyboard::Left);
                keyMoveRight = sf::Keyboard::isKeyPressed(sf::Keyboard::Right);
                if (!keyMoveLeft && !keyMoveRight) {
                    airSoftDropValue = airSoftDrop;
                }

                if (moveRight) {
                    for (int i = 0; i < 4; i++) {
                        previousPiecePosition[i] = currentPiece[i];
                        currentPiece[i].x += 1;
                    }

                    if (!isCollided()) for (int i = 0; i < 4; i++) {
                        currentPiece[i] = previousPiecePosition[i];
                    } else {
                        if (lockCountValue > 0) {
                            lockCountValue--;
                            lockDelayValue = lockDelay;
                        }
                    }

                    airSoftDropValue = airSoftDrop;
                }

                if (moveLeft) {
                    for (int i = 0; i < 4; i++) {
                        previousPiecePosition[i] = currentPiece[i];
                        currentPiece[i].x -= 1;
                    }

                    if (!isCollided()) {
                        for (int i = 0; i < 4; i++) {
                            currentPiece[i] = previousPiecePosition[i];
                        }
                    } else {
                        if (lockCountValue > 0) {
                            lockCountValue--;
                            lockDelayValue = lockDelay;
                        }
                    }

                    airSoftDropValue = airSoftDrop;
                }

                if (airSoftDropValue <= 0) {
                    for (int i = 0; i < 4; i++) {
                        previousPiecePosition[i] = currentPiece[i];
                        currentPiece[i].x += sign(keyMoveRight - keyMoveLeft);
                    }

                    if (!isCollided()) {
                        if (isSidehit == 0) {
                            isSidehit = 1;
                        }

                        for (int i = 0; i < 4; i++) {
                            currentPiece[i] = previousPiecePosition[i];
                        }
                    } else {
                        isSidehit = 0;
                        if (lockCountValue > 0) {
                            lockCountValue--;
                            lockDelayValue = lockDelay;
                        }
                    }
                }

                airSoftDropValue -= trackingFrameTime.getElapsedTime().asSeconds() * 75;

                /// \brief Обработка механики удержания фигуры.
                ///
                /// Этот блок кода реализует механику удержания текущей фигуры и замены её на
                /// фигуру из запаса. Если фигура ещё не была удержана, она помещается в запас,
                /// а текущая фигура заменяется на новую. Если фигура уже была удержана, она
                /// заменяется на фигуру, находящуюся в запасе.
                ///
                /// \details
                /// - Если фигура впервые удерживается (переменная holdPiece равна -1), она
                ///   заменяется на новую фигуру, а текущая помещается в запас.
                /// - Если фигура уже была удержана, происходит их обмен.
                /// - После удержания фигуры проверяются столкновения, и, если это необходимо,
                ///   фигура поднимается, чтобы избежать пересечений с другими блоками или стенами.
                /// - После выполнения удержания, обновляются параметры блокировки (lock),
                ///   перезапускается игровой таймер и происходит перерисовка новой фигуры.
                ///
                /// \note Этот блок также управляет вращением фигуры после удержания в зависимости
                ///       от типа фигуры (например, для T, Z или I тетромино применяются разные
                ///       вращения).
                if (holded) {
                    if (holdPiece == -1) {
                        holdPiece = colorPiece;
                        colorPiece = -1;

                        while (isCollided()) {
                            for (int i = 0; i < 4; i++) {
                                currentPiece[i].y++;
                            }
                        }

                        for (int i = 0; i < 4; i++) {
                            currentPiece[i].y--;
                        }

                        lockDelayValue = -1;
                        gameTimer = 0;
                        goto makeNewPiece;
                    } else {
                        int temp;
                        temp = colorPiece;
                        colorPiece = holdPiece;
                        holdPiece = temp;

                        gameTimer = 0;
                        lockCountValue = lockCount;
                        lockDelayValue = lockDelay;

                        chosenPieceIndex = colorPiece;
                        for (int i = 0; i < 4; i++) {
                            currentPiece[i].x = pieces[chosenPieceIndex][i] % 2 + 4;
                            currentPiece[i].y = pieces[chosenPieceIndex][i] / 2 + 2;
                            currentPiece[i].rotation = 0;

                            if (colorPiece == J_TETROMINO) {
                                currentPiece[i].x--;
                            }
                            if (colorPiece == I_TETROMINO) {
                                currentPiece[i].y++;
                            }
                        }

                        for (int i = 0; i < 4; i++) {
                            Piece center = currentPiece[1];
                            if (colorPiece == I_TETROMINO) {
                                currentPiece[i].rotate(center, 1);
                            }
                            if (colorPiece == T_TETROMINO) {
                                currentPiece[i].rotate(center, -1);
                            }
                            if (colorPiece == S_TETROMINO) {
                                currentPiece[i].rotate(center, -1);
                            }
                            if (colorPiece == Z_TETROMINO) {
                                currentPiece[i].rotate(center, -1);
                            }
                            if (colorPiece == L_TETROMINO) {
                                currentPiece[i].rotate(center, -1);
                            }
                            if (colorPiece == J_TETROMINO) {
                                currentPiece[i].rotate(center, 1);
                            }
                            currentPiece[i].rotation = 1;
                        }
                    }
                }

                //HardDrop
                if (hardDrop && start <= 0) {

                    while (isCollided()) {

                        for (int i = 0; i < 4; i++) currentPiece[i].y++;
                        createParticle(&particles);
                    }

                    for (int i = 0; i < 4; i++) currentPiece[i].y--;
                    lockDelayValue = -1;
                    goto makeNewPiece;
                }

                //========================= Rotate =========================
                if (rotatePiece != 0) {

                    int before_rotation, after_rotation;
                    for (int i = 0; i < 4; i++) {

                        previousPiecePosition[i] = currentPiece[i];
                        before_rotation = currentPiece[i].rotation;
                        if (colorPiece == I_TETROMINO) {

                            if (currentPiece[i].rotation == 1) {

                                if (rotatePiece == 1) {
                                    if (i == 0) { currentPiece[i].x -= 1, currentPiece[i].y -= 1; };
                                    if (i == 2) { currentPiece[i].x += 1, currentPiece[i].y += 1; };
                                    if (i == 3) { currentPiece[i].x += 2, currentPiece[i].y += 2; };
                                }
                                else {
                                    if (i == 0) { currentPiece[i].x -= 2, currentPiece[i].y += 2; };
                                    if (i == 1) { currentPiece[i].x -= 1, currentPiece[i].y += 1; };
                                    if (i == 3) { currentPiece[i].x += 1, currentPiece[i].y -= 1; };
                                }
                            }
                            if (currentPiece[i].rotation == 2) {

                                if (rotatePiece == 1) {
                                    if (i == 0) { currentPiece[i].x -= 2, currentPiece[i].y += 2; };
                                    if (i == 1) { currentPiece[i].x -= 1, currentPiece[i].y += 1; };
                                    if (i == 3) { currentPiece[i].x += 1, currentPiece[i].y -= 1; };
                                }
                                else {
                                    if (i == 0) { currentPiece[i].x += 1, currentPiece[i].y += 1; };
                                    if (i == 2) { currentPiece[i].x -= 1, currentPiece[i].y -= 1; };
                                    if (i == 3) { currentPiece[i].x -= 2, currentPiece[i].y -= 2; };
                                }
                            }
                            if (currentPiece[i].rotation == 3) {

                                if (rotatePiece == 1) {
                                    if (i == 0) { currentPiece[i].x += 1, currentPiece[i].y += 1; };
                                    if (i == 2) { currentPiece[i].x -= 1, currentPiece[i].y -= 1; };
                                    if (i == 3) { currentPiece[i].x -= 2, currentPiece[i].y -= 2; };
                                }
                                else {
                                    if (i == 0) { currentPiece[i].x += 2, currentPiece[i].y -= 2; };
                                    if (i == 1) { currentPiece[i].x += 1, currentPiece[i].y -= 1; };
                                    if (i == 3) { currentPiece[i].x -= 1, currentPiece[i].y += 1; };
                                }
                            }
                            if (currentPiece[i].rotation == 4) {

                                if (rotatePiece == 1) {
                                    if (i == 0) { currentPiece[i].x += 2, currentPiece[i].y -= 2; };
                                    if (i == 1) { currentPiece[i].x += 1, currentPiece[i].y -= 1; };
                                    if (i == 3) { currentPiece[i].x -= 1, currentPiece[i].y += 1; };
                                }
                                else {
                                    if (i == 0) { currentPiece[i].x -= 1, currentPiece[i].y -= 1; };
                                    if (i == 2) { currentPiece[i].x += 1, currentPiece[i].y += 1; };
                                    if (i == 3) { currentPiece[i].x += 2, currentPiece[i].y += 2; };
                                }
                            }
                            currentPiece[i].rotation += rotatePiece;
                        }
                        else if (colorPiece != O_TETROMINO) currentPiece[i].rotate(currentPiece[1], rotatePiece);

                        if (currentPiece[i].rotation > 4) currentPiece[i].rotation = 1;
                        if (currentPiece[i].rotation < 1) currentPiece[i].rotation = 4;

                        after_rotation = currentPiece[i].rotation;
                    }

                    Piece rotation_piece[4];
                    if (colorPiece != I_TETROMINO) {

                        if ((before_rotation == 1 && after_rotation == 2) || (before_rotation == 3 && after_rotation == 2)) { //1 >> 2 & 3 >> 2
                            //TEST 2
                            if (!isCollided()) {
                                for (int i = 0; i < 4; i++) {

                                    rotation_piece[i].x = currentPiece[i].x;
                                    rotation_piece[i].y = currentPiece[i].y;
                                    currentPiece[i].x += -1;
                                    currentPiece[i].y += 0;
                                }
                            }
                            //TEST 3
                            if (!isCollided()) {
                                for (int i = 0; i < 4; i++) {

                                    currentPiece[i].x = rotation_piece[i].x;
                                    currentPiece[i].y = rotation_piece[i].y;
                                    currentPiece[i].x += -1;
                                    currentPiece[i].y += -1;
                                }
                            }
                            //TEST 4
                            if (!isCollided()) {
                                for (int i = 0; i < 4; i++) {

                                    currentPiece[i].x = rotation_piece[i].x;
                                    currentPiece[i].y = rotation_piece[i].y;
                                    currentPiece[i].x += 0;
                                    currentPiece[i].y += 2;
                                }
                            }
                            //TEST 5
                            if (!isCollided()) {
                                for (int i = 0; i < 4; i++) {

                                    currentPiece[i].x = rotation_piece[i].x;
                                    currentPiece[i].y = rotation_piece[i].y;
                                    currentPiece[i].x += -1;
                                    currentPiece[i].y += 2;
                                }
                            }
                        }
                        if ((before_rotation == 2 && after_rotation == 1) || (before_rotation == 2 && after_rotation == 3)) { //2 >> 1 && 2 >> 3
                            //TEST 2
                            if (!isCollided()) {
                                for (int i = 0; i < 4; i++) {

                                    rotation_piece[i].x = currentPiece[i].x;
                                    rotation_piece[i].y = currentPiece[i].y;
                                    currentPiece[i].x += 1;
                                    currentPiece[i].y += 0;
                                }
                            }
                            //TEST 3
                            if (!isCollided()) {
                                for (int i = 0; i < 4; i++) {

                                    currentPiece[i].x = rotation_piece[i].x;
                                    currentPiece[i].y = rotation_piece[i].y;
                                    currentPiece[i].x += 1;
                                    currentPiece[i].y += 1;
                                }
                            }
                            //TEST 4
                            if (!isCollided()) {
                                for (int i = 0; i < 4; i++) {

                                    currentPiece[i].x = rotation_piece[i].x;
                                    currentPiece[i].y = rotation_piece[i].y;
                                    currentPiece[i].x += 0;
                                    currentPiece[i].y += -2;
                                }
                            }
                            //TEST 5
                            if (!isCollided()) {
                                for (int i = 0; i < 4; i++) {

                                    currentPiece[i].x = rotation_piece[i].x;
                                    currentPiece[i].y = rotation_piece[i].y;
                                    currentPiece[i].x += 1;
                                    currentPiece[i].y += -2;
                                }
                            }
                        }
                        if ((before_rotation == 3 && after_rotation == 4) || (before_rotation == 1 && after_rotation == 4)) { //3 >> 4 & 1 >> 4
                            //TEST 2
                            if (!isCollided()) {
                                for (int i = 0; i < 4; i++) {

                                    rotation_piece[i].x = currentPiece[i].x;
                                    rotation_piece[i].y = currentPiece[i].y;
                                    currentPiece[i].x += 1;
                                    currentPiece[i].y += 0;
                                }
                            }
                            //TEST 3
                            if (!isCollided()) {
                                for (int i = 0; i < 4; i++) {

                                    currentPiece[i].x = rotation_piece[i].x;
                                    currentPiece[i].y = rotation_piece[i].y;
                                    currentPiece[i].x += 1;
                                    currentPiece[i].y += -1;
                                }
                            }
                            //TEST 4
                            if (!isCollided()) {
                                for (int i = 0; i < 4; i++) {

                                    currentPiece[i].x = rotation_piece[i].x;
                                    currentPiece[i].y = rotation_piece[i].y;
                                    currentPiece[i].x += 0;
                                    currentPiece[i].y += 2;
                                }
                            }
                            //TEST 5
                            if (!isCollided()) {
                                for (int i = 0; i < 4; i++) {

                                    currentPiece[i].x = rotation_piece[i].x;
                                    currentPiece[i].y = rotation_piece[i].y;
                                    currentPiece[i].x += 1;
                                    currentPiece[i].y += 2;
                                }
                            }
                        }
                        if ((before_rotation == 4 && after_rotation == 3) || (before_rotation == 4 && after_rotation == 1)) { //4 >> 3 && 4 >> 1
                            //TEST 2
                            if (!isCollided()) {
                                for (int i = 0; i < 4; i++) {

                                    rotation_piece[i].x = currentPiece[i].x;
                                    rotation_piece[i].y = currentPiece[i].y;
                                    currentPiece[i].x += -1;
                                    currentPiece[i].y += 0;
                                }
                            }
                            //TEST 3
                            if (!isCollided()) {
                                for (int i = 0; i < 4; i++) {

                                    currentPiece[i].x = rotation_piece[i].x;
                                    currentPiece[i].y = rotation_piece[i].y;
                                    currentPiece[i].x += -1;
                                    currentPiece[i].y += 1;
                                }
                            }
                            //TEST 4
                            if (!isCollided()) {
                                for (int i = 0; i < 4; i++) {

                                    currentPiece[i].x = rotation_piece[i].x;
                                    currentPiece[i].y = rotation_piece[i].y;
                                    currentPiece[i].x += 0;
                                    currentPiece[i].y += -2;
                                }
                            }
                            //TEST 5
                            if (!isCollided()) {
                                for (int i = 0; i < 4; i++) {

                                    currentPiece[i].x = rotation_piece[i].x;
                                    currentPiece[i].y = rotation_piece[i].y;
                                    currentPiece[i].x += -1;
                                    currentPiece[i].y += -2;
                                }
                            }
                        }
                    }

                    if (!isCollided()) for (int i = 0; i < 4; i++) currentPiece[i] = previousPiecePosition[i];
                    else {

                        if (lockCountValue > 0) {

                            lockCountValue--;
                            lockDelayValue = lockDelay;
                        }

                        if (colorPiece == T_TETROMINO) {

                            int corner_count = 0;
                            if (board[currentPiece[1].y + 1][currentPiece[1].x + 1] != 0 || currentPiece[1].x + 1 >= WIDTH || currentPiece[1].y + 1 >= HEIGHT) corner_count++;
                            if (board[currentPiece[1].y + 1][currentPiece[1].x - 1] != 0 || currentPiece[1].x - 1 < 0 || currentPiece[1].y + 1 >= HEIGHT) corner_count++;
                            if (board[currentPiece[1].y - 1][currentPiece[1].x + 1] != 0 || currentPiece[1].x + 1 >= WIDTH || currentPiece[1].y - 1 < 0) corner_count++;
                            if (board[currentPiece[1].y - 1][currentPiece[1].x - 1] != 0 || currentPiece[1].x - 1 < 0 || currentPiece[1].y + 1 < 0) corner_count++;

                            if (corner_count >= 3) {

                                isTSpin = 1;
                            }
                        }
                    }
                }

                //Game Update
                if (gameTimer > gameDelay) {

                makeNewPiece:

                    for (int i = 0; i < 4; i++) {

                        previousPiecePosition[i] = currentPiece[i];
                        currentPiece[i].y++;
                    }

                    if (!isCollided() && lockDelayValue < 0) {

                        if (!holded) {

                            createParticle(&particles);
                            createParticle(&particles);
                            createParticle(&particles);

                            std::vector<PieceLock> piece_lock;
                            for (int i = 0; i < 4; i++) {

                                PieceLock piece_lock_one;
                                piece_lock_one.x = currentPiece[i].x;
                                piece_lock_one.y = currentPiece[i].y;

                                piece_lock.push_back(piece_lock_one);
                            }
                            piecesLock.push_back(piece_lock);

                            boardWobble = 7;
                            totalPieceCount++;
                        }

                        for (int i = 0; i < 4; i++) board[previousPiecePosition[i].y][previousPiecePosition[i].x] = colorPiece + 1;
                        int choose_piece = bagOfSevenPieces.at(0);
                        bagOfSevenPieces.erase(bagOfSevenPieces.begin());
                        if (bagOfSevenPieces.size() == 0) {
                            bagOfSevenPieces = nextBagOfSevenPieces;
                            nextBagOfSevenPieces = generateNewBag();
                        }

                        colorPiece = choose_piece;
                        for (int i = 0; i < 4; i++) {

                            currentPiece[i].x = pieces[choose_piece][i] % 2 + 4;
                            currentPiece[i].y = pieces[choose_piece][i] / 2 + 2;
                            currentPiece[i].rotation = 0;

                            if (colorPiece == J_TETROMINO) currentPiece[i].x--;
                            if (colorPiece == I_TETROMINO) currentPiece[i].y++;
                        }
                        for (int i = 0; i < 4; i++) {

                            Piece center = currentPiece[1];
                            if (colorPiece == I_TETROMINO) currentPiece[i].rotate(center, 1);
                            if (colorPiece == T_TETROMINO) currentPiece[i].rotate(center, -1);
                            if (colorPiece == S_TETROMINO) currentPiece[i].rotate(center, -1);
                            if (colorPiece == Z_TETROMINO) currentPiece[i].rotate(center, -1);
                            if (colorPiece == L_TETROMINO) currentPiece[i].rotate(center, -1);
                            if (colorPiece == J_TETROMINO) currentPiece[i].rotate(center, 1);
                            currentPiece[i].rotation = 1;
                        }

                        lockDelayValue = lockDelay;
                        lockCountValue = lockCount;
                        isTouchGround = false;

                        //=====================Clear Lines========================
                        int line_clear_count = 0;
                        int checkLine = HEIGHT - 1;
                        for (int i = HEIGHT - 1; i > 0; i--) {

                            int count = 0;
                            for (int j = 0; j < WIDTH; j++) {

                                if (board[i][j]) count++;
                                board[checkLine][j] = board[i][j];
                            }
                            if (count < WIDTH) checkLine--;
                            else line_clear_count++;
                        }
                        if (line_clear_count != 0) {

                            lineClearCombo++;
                            if (line_clear_count == 4 || isTSpin) {
                                btbCombo++;
                            }
                            else {

                                if (btbCombo != 0) {
                                    btbCombo = 0;
                                }
                            }

                            totalLineCount += line_clear_count;
                        }
                        else if (lineClearCombo != 0) {
                            lineClearCombo = 0;
                        }

                        int perfect_clear = 1;
                        for (int i = 0; i < HEIGHT; i++) {
                            for (int j = 0; j < WIDTH; j++) {
                                if (board[i][j] != 0) perfect_clear = 0;
                            }
                        }
                        isTSpin = 0;
                    }
                    else if (!isCollided()) {

                        for (int i = 0; i < 4; i++) currentPiece[i] = previousPiecePosition[i];
                    }
                    else {

                        lockCountValue = lockCount;

                        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {

                            createParticle(&particles);
                            createParticle(&particles);
                        }
                    }

                    gameTimer = 0;
                }
                boardWobble += 100 * ((-boardWobble) / 15) * elapsedTime;

                //Update Ghost
                for (int i = 0; i < 4; i++) {

                    ghost[i].x = currentPiece[i].x;
                    ghost[i].y = currentPiece[i].y;
                }
                for (int i = 0; i < 4; i++) {

                    while (isCollidedGhost()) {

                        for (int i = 0; i < 4; i++) ghost[i].y++;
                    }

                    for (int i = 0; i < 4; i++) ghost[i].y--;
                }

                moveX = 0;
                rotatePiece = 0;
                gameDelay = 0.5;
                hardDrop = 0;
                holded = 0;
                moveLeft = 0;
                moveRight = 0;

                gameWindow.clear(sf::Color::Black);

                //Draw Backboard
                sf::RectangleShape backboard_shape;
                backboard_shape.setSize(sf::Vector2f(320, 650));
                backboard_shape.setFillColor(sf::Color::White);
                backboard_shape.setPosition(140, 20 + boardWobble);
                gameWindow.draw(backboard_shape);

                //Draw Grid
                spriteBoard.setPosition(150, -30 + boardWobble);
                gameWindow.draw(spriteBoard);

                //Draw Das Bar
                float das_progress = std::max((double)0, (double)(lockDelayValue / lockDelay));

                sf::RectangleShape das_bar_shape;
                das_bar_shape.setSize(sf::Vector2f(das_progress * 320, 8));
                das_bar_shape.setFillColor(sf::Color::White);
                das_bar_shape.setPosition(140, 700 + boardWobble);
                gameWindow.draw(das_bar_shape);

                //Draw Lock Count
                sf::CircleShape lock_count_circle;
                lock_count_circle.setRadius(6);
                lock_count_circle.setFillColor(sf::Color::White);
                for (int i = 0; i < lockCountValue; i++) {

                    lock_count_circle.setPosition(141 + (i * 23.5), 680 + boardWobble);
                    gameWindow.draw(lock_count_circle);
                }

                //Draw Hold
                spritePiece.setColor(sf::Color(255, 255, 255, 255));
                if (holdPiece != -1) {

                    Piece hold_piece[4];
                    int hold_piece_choose;
                    hold_piece_choose = holdPiece;

                    for (int j = 0; j < 4; j++) {

                        hold_piece[j].x = pieces[hold_piece_choose][j] % 2 + 4;
                        hold_piece[j].y = pieces[hold_piece_choose][j] / 2 + 3;

                        if (holdPiece == J_TETROMINO) hold_piece[j].x--;
                    }
                    for (int j = 0; j < 4; j++) {

                        Piece center = hold_piece[1];
                        if (holdPiece == I_TETROMINO) hold_piece[j].rotate(center, 1);
                        if (holdPiece == T_TETROMINO) hold_piece[j].rotate(center, -1);
                        if (holdPiece == S_TETROMINO) hold_piece[j].rotate(center, -1);
                        if (holdPiece == Z_TETROMINO) hold_piece[j].rotate(center, -1);
                        if (holdPiece == L_TETROMINO) hold_piece[j].rotate(center, -1);
                        if (holdPiece == J_TETROMINO) hold_piece[j].rotate(center, 1);
                    }

                    for (int j = 0; j < 4; j++) {

                        spritePiece.setTextureRect(sf::IntRect(holdPiece * textureSize, 0, textureSize, textureSize));
                        int x_offset = 0;
                        if (holdPiece == I_TETROMINO || holdPiece == O_TETROMINO) x_offset = 15;
                        spritePiece.setPosition(hold_piece[j].x * textureSize - 65 - x_offset, hold_piece[j].y * textureSize - 10);
                        gameWindow.draw(spritePiece);
                    }
                }

                //Draw Next Pieces
                spritePiece.setColor(sf::Color(255, 255, 255, 255));
                for (int i = 0; i < bagOfSevenPieces.size() + nextBagOfSevenPieces.size(); i++) {

                    if (i < 5) {

                        Piece next_piece[4];
                        int next_piece_choose;
                        if (i < bagOfSevenPieces.size()) next_piece_choose = bagOfSevenPieces.at(i);
                        else next_piece_choose = nextBagOfSevenPieces.at(i - bagOfSevenPieces.size());

                        int next_color = next_piece_choose;
                        for (int j = 0; j < 4; j++) {

                            next_piece[j].x = pieces[next_piece_choose][j] % 2 + 4;
                            next_piece[j].y = pieces[next_piece_choose][j] / 2 + 3;

                            if (next_color == J_TETROMINO) next_piece[j].x--;
                        }
                        for (int j = 0; j < 4; j++) {

                            Piece center = next_piece[1];
                            if (next_color == I_TETROMINO) next_piece[j].rotate(center, 1);
                            if (next_color == T_TETROMINO) next_piece[j].rotate(center, -1);
                            if (next_color == S_TETROMINO) next_piece[j].rotate(center, -1);
                            if (next_color == Z_TETROMINO) next_piece[j].rotate(center, -1);
                            if (next_color == L_TETROMINO) next_piece[j].rotate(center, -1);
                            if (next_color == J_TETROMINO) next_piece[j].rotate(center, 1);
                        }

                        for (int j = 0; j < 4; j++) {

                            spritePiece.setTextureRect(sf::IntRect(next_color * textureSize, 0, textureSize, textureSize));
                            int x_offset = 0;
                            if (next_color == I_TETROMINO || next_color == O_TETROMINO) x_offset = 15;
                            spritePiece.setPosition(next_piece[j].x * textureSize + 395 - x_offset, next_piece[j].y * textureSize - 10 + (90 * i));
                            gameWindow.draw(spritePiece);
                        }
                    }
                }

                //Draw Placed Pieces
                for (int i = 0; i < HEIGHT; i++) {

                    for (int j = 0; j < WIDTH; j++) {

                        spritePiece.setColor(sf::Color(255, 255, 255, 255));
                        if (board[i][j] == 0) continue;
                        spritePiece.setTextureRect(sf::IntRect((board[i][j] - 1) * textureSize, 0, textureSize, textureSize));
                        spritePiece.setPosition(j * textureSize + 150, i * textureSize - 90 + boardWobble);
                        gameWindow.draw(spritePiece);
                    }
                }

                //Draw Piece Lock
                for (int i = 0; i < piecesLock.size(); i++) {

                    for (int j = 0; j < 4; j++) {

                        spriteLockedPiece.setTextureRect(sf::IntRect((int)piecesLock.at(i).at(j).animation * textureSize, 0, textureSize, textureSize));
                        spriteLockedPiece.setColor(sf::Color(255, 255, 255, 200));
                        spriteLockedPiece.setPosition(piecesLock.at(i).at(j).x * textureSize + 150, (piecesLock.at(i).at(j).y - 1) * textureSize - 90 + boardWobble);
                        gameWindow.draw(spriteLockedPiece);

                        piecesLock.at(i).at(j).animation += elapsedTime * FRAMERATE * 4;
                    }

                    for (int j = 0; j < 4; j++) {

                        if (piecesLock.at(i).at(j).animation >= 67) {

                            piecesLock.erase(piecesLock.begin() + i);
                            break;
                        }
                    }
                }

                //Draw Ghost
                spriteGhost.setTextureRect(sf::IntRect(colorPiece * textureSize, 0, textureSize, textureSize));
                for (int i = 0; i < 4; i++) {

                    spriteGhost.setPosition(currentPiece[i].x * textureSize + 150, ghost[i].y * textureSize - 90 + boardWobble);
                    gameWindow.draw(spriteGhost);
                }

                //Draw Pieces
                pieceIndicatorShapeAlpha = (sin(elapsedGameTime.getElapsedTime().asSeconds() * 10) + 1) * 30;
                sf::RectangleShape piece_indicator_shape;
                piece_indicator_shape.setSize(sf::Vector2f(30, 30));
                piece_indicator_shape.setFillColor(sf::Color(255, 255, 255, pieceIndicatorShapeAlpha));

                float piece_alpha = std::max((double)0, (double)(lockDelayValue / lockDelay));
                for (int i = 0; i < 4; i++) {

                    spritePiece.setTextureRect(sf::IntRect(7 * textureSize, 0, textureSize, textureSize));
                    spritePiece.setColor(sf::Color(255, 255, 255, 255));
                    spritePiece.setPosition(currentPiece[i].x * textureSize + 150, currentPiece[i].y * textureSize - 90 + boardWobble);
                    gameWindow.draw(spritePiece);

                    spritePiece.setTextureRect(sf::IntRect(colorPiece * textureSize, 0, textureSize, textureSize));
                    spritePiece.setColor(sf::Color(255, 255, 255, piece_alpha * 255));
                    spritePiece.setPosition(currentPiece[i].x * textureSize + 150, currentPiece[i].y * textureSize - 90 + boardWobble);
                    gameWindow.draw(spritePiece);

                    piece_indicator_shape.setPosition(currentPiece[i].x * textureSize + 150, currentPiece[i].y * textureSize - 90 + boardWobble);
                    gameWindow.draw(piece_indicator_shape);
                }

                //Draw Particle
                for (int i = 0; i < particles.size(); i++) {

                    particles.at(i).update(elapsedTime);
                    particles.at(i).draw(&gameWindow);
                    if (particles.at(i).alpha <= 0) particles.erase(particles.begin() + i);
                }

                //Draw Backboard
                backboard_shape.setSize(sf::Vector2f(320, 20));
                backboard_shape.setFillColor(sf::Color::Black);
                backboard_shape.setPosition(140, 0 + boardWobble);
                gameWindow.draw(backboard_shape);

                backboard_shape.setSize(sf::Vector2f(320, 10));
                backboard_shape.setFillColor(sf::Color::White);
                backboard_shape.setPosition(140, 10 + boardWobble);
                gameWindow.draw(backboard_shape);

                //Draw Text
                sf::Text text;
                text.setFont(fontGame);
                text.setCharacterSize(35);
                text.setFillColor(sf::Color::White);

                text.setString("NEXT");
                text.setPosition(480, 30);
                gameWindow.draw(text);

                text.setString("HOLD");
                text.setPosition(25, 30);
                gameWindow.draw(text);

                text.setCharacterSize(22);
                text.setString(std::to_string(lineClearCombo - 1) + " COMBO");
                text.setPosition(475, 650);
                if (lineClearCombo - 1 > 0) gameWindow.draw(text);

                sf::RectangleShape text_box;
                sf::Rect text_rect = text.getLocalBounds();;
                text_box.setFillColor(sf::Color::White);

                text.setFillColor(sf::Color::Black);
                text.setCharacterSize(25);
                text.setString("LINES");
                text_rect = text.getLocalBounds();
                text.setPosition(120 - text_rect.width, 400 + boardWobble);
                text_box.setSize(sf::Vector2f(text_rect.width + 40, text_rect.height * 2 - 4));
                text_box.setOrigin(sf::Vector2f(20, 0));
                text_box.setPosition(text.getPosition());
                gameWindow.draw(text_box);
                gameWindow.draw(text);

                text.setFillColor(sf::Color::White);
                text.setCharacterSize(30);
                text.setString(std::to_string(totalLineCount));
                text_rect = text.getLocalBounds();
                text.setPosition(120 - text_rect.width, 450 + boardWobble);
                gameWindow.draw(text);

                text.setFillColor(sf::Color::Black);
                text.setCharacterSize(25);
                text.setString("PIECES");
                text_rect = text.getLocalBounds();
                text.setPosition(120 - text_rect.width, 510 + boardWobble);
                text_box.setSize(sf::Vector2f(text_rect.width + 40, text_rect.height * 2 - 4));
                text_box.setOrigin(sf::Vector2f(20, 0));
                text_box.setPosition(text.getPosition());
                gameWindow.draw(text_box);
                gameWindow.draw(text);

                text.setFillColor(sf::Color::White);
                text.setCharacterSize(30);
                text.setString(std::to_string(totalPieceCount));
                text_rect = text.getLocalBounds();
                text.setPosition(120 - text_rect.width, 560 + boardWobble);
                gameWindow.draw(text);

                gameWindow.display();

            }
            start--;
            trackingGameTime.restart();
        }
}