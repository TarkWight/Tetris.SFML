#include "MainGameController.hpp"


MainGameController::MainGameController() : mainMenuView() {}
MainGameController::~MainGameController() {}

void MainGameController::runGame() {
    sf::RenderWindow window(sf::VideoMode(600, 720), "Tetris");

	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			} else {
				handleMainMenuEvent(event);
			}
		}
        window.clear();
        mainMenuView.draw(window);
        window.display();
	}	
}



void MainGameController::handleMainMenuEvent(const sf::Event& event) {
    if (event.type == sf::Event::MouseButtonPressed) {
        if (mainMenuView.isStartButtonClicked(event.mouseButton.x, event.mouseButton.y)) {
            startTetrisGame();   exit(0);
        } else if (mainMenuView.isChangeColorButtonClicked(event.mouseButton.x, event.mouseButton.y)) {
           std::cout << "Change color\n";
         } else if (mainMenuView.isLeaderboardButtonClicked(event.mouseButton.x, event.mouseButton.y)) {
           std::cout << "Show leaderboard\n";
        }
        else if (mainMenuView.isExitButtonClicked(event.mouseButton.x, event.mouseButton.y)) {
            std::cout << "exit\n";
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

void MainGameController::startTetrisGame() {
    
    sf::RenderWindow window(sf::VideoMode(600, 720), "Tetris");
        srand(time(0));

       

        //Sound
        sf::Sound sfx_clearline; sf::SoundBuffer buffer_clearline;
        buffer_clearline.loadFromFile("../resource/sound/clearline.ogg");
        sfx_clearline.setBuffer(buffer_clearline);

        sf::Sound sfx_clearquad; sf::SoundBuffer buffer_clearquad;
        buffer_clearquad.loadFromFile("../resource/sound/clearquad.ogg");
        sfx_clearquad.setBuffer(buffer_clearquad);

        sf::Sound sfx_clearspin; sf::SoundBuffer buffer_clearspin;
        buffer_clearspin.loadFromFile("../resource/sound/clearspin.ogg");
        sfx_clearspin.setBuffer(buffer_clearspin);

        sf::Sound sfx_clearbtb; sf::SoundBuffer buffer_clearbtb;
        buffer_clearbtb.loadFromFile("../resource/sound/clearbtb.ogg");
        sfx_clearbtb.setBuffer(buffer_clearbtb);

        sf::Sound sfx_btb_break; sf::SoundBuffer buffer_btb_break;
        buffer_btb_break.loadFromFile("../resource/sound/btb_break.ogg");
        sfx_btb_break.setBuffer(buffer_btb_break);

        sf::Sound sfx_combo_1; sf::SoundBuffer buffer_combo_1;
        buffer_combo_1.loadFromFile("../resource/sound/combo_1.ogg");
        sfx_combo_1.setBuffer(buffer_combo_1);

        sf::Sound sfx_combo_2; sf::SoundBuffer buffer_combo_2;
        buffer_combo_2.loadFromFile("../resource/sound/combo_2.ogg");
        sfx_combo_2.setBuffer(buffer_combo_2);

        sf::Sound sfx_combo_3; sf::SoundBuffer buffer_combo_3;
        buffer_combo_3.loadFromFile("../resource/sound/combo_3.ogg");
        sfx_combo_3.setBuffer(buffer_combo_3);

        sf::Sound sfx_combo_4; sf::SoundBuffer buffer_combo_4;
        buffer_combo_4.loadFromFile("../resource/sound/combo_4.ogg");
        sfx_combo_4.setBuffer(buffer_combo_4);

        sf::Sound sfx_combo_5; sf::SoundBuffer buffer_combo_5;
        buffer_combo_5.loadFromFile("../resource/sound/combo_5.ogg");
        sfx_combo_5.setBuffer(buffer_combo_5);

        sf::Sound sfx_combo_6; sf::SoundBuffer buffer_combo_6;
        buffer_combo_6.loadFromFile("../resource/sound/combo_6.ogg");
        sfx_combo_6.setBuffer(buffer_combo_6);

        sf::Sound sfx_combo_7; sf::SoundBuffer buffer_combo_7;
        buffer_combo_7.loadFromFile("../resource/sound/combo_7.ogg");
        sfx_combo_7.setBuffer(buffer_combo_7);

        sf::Sound sfx_combo_8; sf::SoundBuffer buffer_combo_8;
        buffer_combo_8.loadFromFile("../resource/sound/combo_8.ogg");
        sfx_combo_8.setBuffer(buffer_combo_8);

        sf::Sound sfx_combo_9; sf::SoundBuffer buffer_combo_9;
        buffer_combo_9.loadFromFile("../resource/sound/combo_9.ogg");
        sfx_combo_9.setBuffer(buffer_combo_9);

        sf::Sound sfx_combo_10; sf::SoundBuffer buffer_combo_10;
        buffer_combo_10.loadFromFile("../resource/sound/combo_10.ogg");
        sfx_combo_10.setBuffer(buffer_combo_10);

        sf::Sound sfx_combo_11; sf::SoundBuffer buffer_combo_11;
        buffer_combo_11.loadFromFile("../resource/sound/combo_11.ogg");
        sfx_combo_11.setBuffer(buffer_combo_11);

        sf::Sound sfx_combo_12; sf::SoundBuffer buffer_combo_12;
        buffer_combo_12.loadFromFile("../resource/sound/combo_12.ogg");
        sfx_combo_12.setBuffer(buffer_combo_12);

        sf::Sound sfx_combo_13; sf::SoundBuffer buffer_combo_13;
        buffer_combo_13.loadFromFile("../resource/sound/combo_13.ogg");
        sfx_combo_13.setBuffer(buffer_combo_13);

        sf::Sound sfx_combo_14; sf::SoundBuffer buffer_combo_14;
        buffer_combo_14.loadFromFile("../resource/sound/combo_14.ogg");
        sfx_combo_14.setBuffer(buffer_combo_14);

        sf::Sound sfx_combo_15; sf::SoundBuffer buffer_combo_15;
        buffer_combo_15.loadFromFile("../resource/sound/combo_15.ogg");
        sfx_combo_15.setBuffer(buffer_combo_15);

        sf::Sound sfx_combo_16; sf::SoundBuffer buffer_combo_16;
        buffer_combo_16.loadFromFile("../resource/sound/combo_16.ogg");
        sfx_combo_16.setBuffer(buffer_combo_16);

        sf::Sound sfx_combo_1_power; sf::SoundBuffer buffer_combo_1_power;
        buffer_combo_1_power.loadFromFile("../resource/sound/combo_1_power.ogg");
        sfx_combo_1_power.setBuffer(buffer_combo_1_power);

        sf::Sound sfx_combo_2_power; sf::SoundBuffer buffer_combo_2_power;
        buffer_combo_2_power.loadFromFile("../resource/sound/combo_2_power.ogg");
        sfx_combo_2_power.setBuffer(buffer_combo_2_power);

        sf::Sound sfx_combo_3_power; sf::SoundBuffer buffer_combo_3_power;
        buffer_combo_3_power.loadFromFile("../resource/sound/combo_3_power.ogg");
        sfx_combo_3_power.setBuffer(buffer_combo_3_power);

        sf::Sound sfx_combo_4_power; sf::SoundBuffer buffer_combo_4_power;
        buffer_combo_4_power.loadFromFile("../resource/sound/combo_4_power.ogg");
        sfx_combo_4_power.setBuffer(buffer_combo_4_power);

        sf::Sound sfx_combo_5_power; sf::SoundBuffer buffer_combo_5_power;
        buffer_combo_5_power.loadFromFile("../resource/sound/combo_5_power.ogg");
        sfx_combo_5_power.setBuffer(buffer_combo_5_power);

        sf::Sound sfx_combo_6_power; sf::SoundBuffer buffer_combo_6_power;
        buffer_combo_6_power.loadFromFile("../resource/sound/combo_6_power.ogg");
        sfx_combo_6_power.setBuffer(buffer_combo_6_power);

        sf::Sound sfx_combo_7_power; sf::SoundBuffer buffer_combo_7_power;
        buffer_combo_7_power.loadFromFile("../resource/sound/combo_7_power.ogg");
        sfx_combo_7_power.setBuffer(buffer_combo_7_power);

        sf::Sound sfx_combo_8_power; sf::SoundBuffer buffer_combo_8_power;
        buffer_combo_8_power.loadFromFile("../resource/sound/combo_8_power.ogg");
        sfx_combo_8_power.setBuffer(buffer_combo_8_power);

        sf::Sound sfx_combo_9_power; sf::SoundBuffer buffer_combo_9_power;
        buffer_combo_9_power.loadFromFile("../resource/sound/combo_9_power.ogg");
        sfx_combo_9_power.setBuffer(buffer_combo_9_power);

        sf::Sound sfx_combo_10_power; sf::SoundBuffer buffer_combo_10_power;
        buffer_combo_10_power.loadFromFile("../resource/sound/combo_10_power.ogg");
        sfx_combo_10_power.setBuffer(buffer_combo_10_power);

        sf::Sound sfx_combo_11_power; sf::SoundBuffer buffer_combo_11_power;
        buffer_combo_11_power.loadFromFile("../resource/sound/combo_11_power.ogg");
        sfx_combo_11_power.setBuffer(buffer_combo_11_power);

        sf::Sound sfx_combo_12_power; sf::SoundBuffer buffer_combo_12_power;
        buffer_combo_12_power.loadFromFile("../resource/sound/combo_12_power.ogg");
        sfx_combo_12_power.setBuffer(buffer_combo_12_power);

        sf::Sound sfx_combo_13_power; sf::SoundBuffer buffer_combo_13_power;
        buffer_combo_13_power.loadFromFile("../resource/sound/combo_13_power.ogg");
        sfx_combo_13_power.setBuffer(buffer_combo_13_power);

        sf::Sound sfx_combo_14_power; sf::SoundBuffer buffer_combo_14_power;
        buffer_combo_14_power.loadFromFile("../resource/sound/combo_14_power.ogg");
        sfx_combo_14_power.setBuffer(buffer_combo_14_power);

        sf::Sound sfx_combo_15_power; sf::SoundBuffer buffer_combo_15_power;
        buffer_combo_15_power.loadFromFile("../resource/sound/combo_15_power.ogg");
        sfx_combo_15_power.setBuffer(buffer_combo_15_power);

        sf::Sound sfx_combo_16_power; sf::SoundBuffer buffer_combo_16_power;
        buffer_combo_16_power.loadFromFile("../resource/sound/combo_16_power.ogg");
        sfx_combo_16_power.setBuffer(buffer_combo_16_power);

        sf::Sound sfx_combobreak; sf::SoundBuffer buffer_combobreak;
        buffer_combobreak.loadFromFile("../resource/sound/combobreak.ogg");
        sfx_combobreak.setBuffer(buffer_combobreak);

        sf::Sound sfx_move; sf::SoundBuffer buffer_move;
        buffer_move.loadFromFile("../resource/sound/move.ogg");
        sfx_move.setBuffer(buffer_move);

        sf::Sound sfx_rotate; sf::SoundBuffer buffer_rotate;
        buffer_rotate.loadFromFile("../resource/sound/rotate.ogg");
        sfx_rotate.setBuffer(buffer_rotate);

        sf::Sound sfx_spin; sf::SoundBuffer buffer_spin;
        buffer_spin.loadFromFile("../resource/sound/spin.ogg");
        sfx_spin.setBuffer(buffer_spin);

        sf::Sound sfx_hold; sf::SoundBuffer buffer_hold;
        buffer_hold.loadFromFile("../resource/sound/hold.ogg");
        sfx_hold.setBuffer(buffer_hold);

        sf::Sound sfx_harddrop; sf::SoundBuffer buffer_harddrop;
        buffer_harddrop.loadFromFile("../resource/sound/harddrop.ogg");
        sfx_harddrop.setBuffer(buffer_harddrop);

        sf::Sound sfx_hit; sf::SoundBuffer buffer_hit;
        buffer_hit.loadFromFile("../resource/sound/hit.ogg");
        sfx_hit.setBuffer(buffer_hit);

        sf::Sound sfx_floor; sf::SoundBuffer buffer_floor;
        buffer_floor.loadFromFile("../resource/sound/floor.ogg");
        sfx_floor.setBuffer(buffer_floor);

        sf::Sound sfx_sidehit; sf::SoundBuffer buffer_sidehit;
        buffer_sidehit.loadFromFile("../resource/sound/sidehit.ogg");
        sfx_sidehit.setBuffer(buffer_sidehit);

        sf::Sound sfx_allclear; sf::SoundBuffer buffer_allclear;
        buffer_allclear.loadFromFile("../resource/sound/allclear.ogg");
        sfx_allclear.setBuffer(buffer_allclear);

        //Pieces
        sf::Texture t;
        t.loadFromFile("../resource/sprite/jstris1.png");
        int texture_size = 30;
        sf::Sprite s(t);
        s.setTextureRect(sf::IntRect(0, 0, texture_size, texture_size));

        //Ghost
        sf::Texture t_ghost;
        t_ghost.loadFromFile("../resource/sprite/ghost.png");
        sf::Sprite s_ghost(t_ghost);
        s_ghost.setTextureRect(sf::IntRect(0, 0, texture_size, texture_size));

        //Lock Pieces Animation
        sf::Texture t_lock;
        t_lock.loadFromFile("../resource/sprite/piece_lock.png");
        sf::Sprite s_lock(t_lock);
        s_lock.setTextureRect(sf::IntRect(0, 0, texture_size, texture_size));

        //Board
        sf::Texture board_t;
        board_t.loadFromFile("../resource/sprite/board.png");
        sf::Sprite board_s(board_t);

        //Font
        sf::Font font;
        font.loadFromFile("../resource/font/Minecraft.ttf");

        int hold;
        int move_x;
        int rotate;
        int color;
        int harddrop;
        int holded;
        int move_left;
        int move_right;
        int start;

        sf::Clock clock;
        sf::Clock game_clock;
        sf::Clock game_elapsed_time;

        double timer;
        double delay;
        std::vector<int> seven_bag;
        std::vector<int> seven_bag_next;

    restart:

        //Handling control
        double das = 8;
        double lock_delay = 0.5;
        double fastdrop_delay = 0;
        int lock_count = 14;
        int is_touch_ground = 0;

        int all_line_count = 0;
        int all_piece_count = 0;

        int lock_count_value = lock_count;
        double das_value = das;
        double lock_delay_value = lock_delay;

        for (int i = 0; i < HEIGHT; i++)
            for (int j = 0; j < WIDTH; j++)
                board[i][j] = 0;

        start = 3;
        timer = 0;
        delay = 0.5;
        move_x = 0;
        color = 0;
        harddrop = 0;
        rotate = 0;
        hold = -1;
        move_left = 0;
        move_right = 0;
        holded = 0;
        seven_bag = generateNewBag();
        seven_bag_next = generateNewBag();

        double piece_indicator_shape_alpha = 0;
        double board_wobble = 0;

        int line_clear_combo = 0;
        int btb_combo = 0;

        //Choose First Piece
        int choose_piece = seven_bag.at(0);
        seven_bag.erase(seven_bag.begin());

        color = choose_piece;
        for (int i = 0; i < 4; i++) {

            piece[i].x = pieces[choose_piece][i] % 2 + 4;
            piece[i].y = pieces[choose_piece][i] / 2 + 3;
            piece[i].rotation = 0;

            if (color == J_TETROMINO) piece[i].x--;
        }
        for (int i = 0; i < 4; i++) {

            Piece center = piece[1];
            if (color == I_TETROMINO) piece[i].Rotate(center, 1);
            if (color == T_TETROMINO) piece[i].Rotate(center, -1);
            if (color == S_TETROMINO) piece[i].Rotate(center, -1);
            if (color == Z_TETROMINO) piece[i].Rotate(center, -1);
            if (color == L_TETROMINO) piece[i].Rotate(center, -1);
            if (color == J_TETROMINO) piece[i].Rotate(center, 1);
        }

        int is_rotate_cw = 0;
        int is_rotate_ccw = 0;
        int is_harddrop = 0;
        int is_right = 0;
        int is_left = 0;
        int is_hold = 0;
        int is_sidehit = 0;
        int is_tspin = 0;
        int is_restart = 0;

        int key_rotate_cw = 0;
        int key_rotate_ccw = 0;
        int key_harddrop = 0;
        int key_right = 0;
        int key_left = 0;
        int key_right_hold = 0;
        int key_left_hold = 0;
        bool is_on_focus = true;
        int last_key = 0;
        int key_restart = 0;

        while (window.isOpen()) {

            float time = clock.getElapsedTime().asSeconds();

            for (int i = 0; i < 4; i++) {

                cache[i] = piece[i];
                piece[i].y++;
            }
            if (!isCollided()) {
                lock_delay_value -= time;

                if (lock_delay_value <= 0) {

                    for (int i = 0; i < 4; i++) piece[i] = cache[i];
                    goto makeNewPiece;
                }
                if (is_touch_ground == 0) {

                    is_touch_ground = 1;
                    sfx_hit.play();
                }
            }
            else {

                is_touch_ground = 0;
            }
            for (int i = 0; i < 4; i++) piece[i] = cache[i];

            timer += time;
            clock.restart();

            sf::Event e;
            while (window.pollEvent(e)) {

                if (e.type == sf::Event::GainedFocus) is_on_focus = true;
                if (e.type == sf::Event::LostFocus) is_on_focus = false;

                if (is_on_focus && e.type == sf::Event::KeyReleased) {

                    if (e.key.code == sf::Keyboard::X || e.key.code == sf::Keyboard::Up) is_rotate_cw = 0;
                    if (e.key.code == sf::Keyboard::Z) is_rotate_ccw = 0;
                    if (e.key.code == sf::Keyboard::Space) is_harddrop = 0;
                    if (e.key.code == sf::Keyboard::C) is_hold = 0;
                    if (e.key.code == sf::Keyboard::Left) is_left = 0;
                    if (e.key.code == sf::Keyboard::Right) is_right = 0;
                    if (e.key.code == sf::Keyboard::R) is_restart = 0;
                }

                if (e.type == sf::Event::Closed) {

                    window.close();
                }
            }

            if (is_on_focus) {

                //Key Fixed
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::C) && is_hold == 0) {

                    is_hold = -1;
                    holded = 1;
                }
                if ((sf::Keyboard::isKeyPressed(sf::Keyboard::X) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) && is_rotate_cw == 0) {

                    is_rotate_cw = -1;
                    rotate = 1;
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z) && is_rotate_ccw == 0) {

                    is_rotate_ccw = -1;
                    rotate = -1;
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && is_harddrop == 0) {

                    is_harddrop = -1;
                    harddrop = 1;
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && is_left == 0) {

                    is_left = -1;
                    move_left = 1;
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && is_right == 0) {

                    is_right = -1;
                    move_right = 1;
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::R) && is_restart == 0) {

                    is_restart = -1;
                    goto restart;
                }

                //Dead
                if (isDead()) {

                    goto restart;
                }

                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) delay = fastdrop_delay;

                //========================= Move =========================
                key_left = sf::Keyboard::isKeyPressed(sf::Keyboard::Left);
                key_right = sf::Keyboard::isKeyPressed(sf::Keyboard::Right);
                if (!key_left && !key_right) das_value = das;

                if (move_right) {

                    for (int i = 0; i < 4; i++) {

                        cache[i] = piece[i];
                        piece[i].x += 1;
                    }

                    if (!isCollided()) for (int i = 0; i < 4; i++) piece[i] = cache[i];
                    else {

                        sfx_move.play();
                        if (lock_count_value > 0) {

                            lock_count_value--;
                            lock_delay_value = lock_delay;
                        }
                    }

                    das_value = das;
                }
                if (move_left) {

                    for (int i = 0; i < 4; i++) {

                        cache[i] = piece[i];
                        piece[i].x -= 1;
                    }

                    if (!isCollided()) for (int i = 0; i < 4; i++) piece[i] = cache[i];
                    else {

                        sfx_move.play();
                        if (lock_count_value > 0) {

                            lock_count_value--;
                            lock_delay_value = lock_delay;
                        }
                    }

                    das_value = das;
                }

                if (das_value <= 0) {

                    for (int i = 0; i < 4; i++) {

                        cache[i] = piece[i];
                        piece[i].x += sign(key_right - key_left);
                    }

                    if (!isCollided()) {

                        if (is_sidehit == 0) {

                            is_sidehit = 1;
                            sfx_sidehit.play();
                        }
                        for (int i = 0; i < 4; i++) piece[i] = cache[i];
                    }
                    else {

                        is_sidehit = 0;
                        if (lock_count_value > 0) {

                            lock_count_value--;
                            lock_delay_value = lock_delay;
                        }

                        sfx_move.play();
                    }
                }
                das_value -= clock.getElapsedTime().asSeconds() * 75;

                //Hold
                if (holded) {

                    sfx_hold.play();

                    if (hold == -1) {

                        hold = color;
                        color = -1;

                        while (isCollided()) {

                            for (int i = 0; i < 4; i++) piece[i].y++;
                        }

                        for (int i = 0; i < 4; i++) piece[i].y--;
                        lock_delay_value = -1;
                        timer = 0;
                        goto makeNewPiece;
                    }
                    else {

                        int temp;
                        temp = color;
                        color = hold;
                        hold = temp;
                        timer = 0;
                        lock_count_value = lock_count;
                        lock_delay_value = lock_delay;

                        choose_piece = color;
                        for (int i = 0; i < 4; i++) {

                            piece[i].x = pieces[choose_piece][i] % 2 + 4;
                            piece[i].y = pieces[choose_piece][i] / 2 + 2;
                            piece[i].rotation = 0;

                            if (color == J_TETROMINO) piece[i].x--;
                            if (color == I_TETROMINO) piece[i].y++;
                        }
                        for (int i = 0; i < 4; i++) {

                            Piece center = piece[1];
                            if (color == I_TETROMINO) piece[i].Rotate(center, 1);
                            if (color == T_TETROMINO) piece[i].Rotate(center, -1);
                            if (color == S_TETROMINO) piece[i].Rotate(center, -1);
                            if (color == Z_TETROMINO) piece[i].Rotate(center, -1);
                            if (color == L_TETROMINO) piece[i].Rotate(center, -1);
                            if (color == J_TETROMINO) piece[i].Rotate(center, 1);
                            piece[i].rotation = 1;
                        }
                    }
                }

                //HardDrop
                if (harddrop && start <= 0) {

                    while (isCollided()) {

                        for (int i = 0; i < 4; i++) piece[i].y++;
                        createParticle(&particles);
                    }

                    for (int i = 0; i < 4; i++) piece[i].y--;
                    lock_delay_value = -1;
                    sfx_harddrop.play();
                    goto makeNewPiece;
                }

                //========================= Rotate =========================
                if (rotate != 0) {

                    int before_rotation, after_rotation;
                    for (int i = 0; i < 4; i++) {

                        cache[i] = piece[i];
                        before_rotation = piece[i].rotation;
                        if (color == I_TETROMINO) {

                            if (piece[i].rotation == 1) {

                                if (rotate == 1) {
                                    if (i == 0) { piece[i].x -= 1, piece[i].y -= 1; };
                                    if (i == 2) { piece[i].x += 1, piece[i].y += 1; };
                                    if (i == 3) { piece[i].x += 2, piece[i].y += 2; };
                                }
                                else {
                                    if (i == 0) { piece[i].x -= 2, piece[i].y += 2; };
                                    if (i == 1) { piece[i].x -= 1, piece[i].y += 1; };
                                    if (i == 3) { piece[i].x += 1, piece[i].y -= 1; };
                                }
                            }
                            if (piece[i].rotation == 2) {

                                if (rotate == 1) {
                                    if (i == 0) { piece[i].x -= 2, piece[i].y += 2; };
                                    if (i == 1) { piece[i].x -= 1, piece[i].y += 1; };
                                    if (i == 3) { piece[i].x += 1, piece[i].y -= 1; };
                                }
                                else {
                                    if (i == 0) { piece[i].x += 1, piece[i].y += 1; };
                                    if (i == 2) { piece[i].x -= 1, piece[i].y -= 1; };
                                    if (i == 3) { piece[i].x -= 2, piece[i].y -= 2; };
                                }
                            }
                            if (piece[i].rotation == 3) {

                                if (rotate == 1) {
                                    if (i == 0) { piece[i].x += 1, piece[i].y += 1; };
                                    if (i == 2) { piece[i].x -= 1, piece[i].y -= 1; };
                                    if (i == 3) { piece[i].x -= 2, piece[i].y -= 2; };
                                }
                                else {
                                    if (i == 0) { piece[i].x += 2, piece[i].y -= 2; };
                                    if (i == 1) { piece[i].x += 1, piece[i].y -= 1; };
                                    if (i == 3) { piece[i].x -= 1, piece[i].y += 1; };
                                }
                            }
                            if (piece[i].rotation == 4) {

                                if (rotate == 1) {
                                    if (i == 0) { piece[i].x += 2, piece[i].y -= 2; };
                                    if (i == 1) { piece[i].x += 1, piece[i].y -= 1; };
                                    if (i == 3) { piece[i].x -= 1, piece[i].y += 1; };
                                }
                                else {
                                    if (i == 0) { piece[i].x -= 1, piece[i].y -= 1; };
                                    if (i == 2) { piece[i].x += 1, piece[i].y += 1; };
                                    if (i == 3) { piece[i].x += 2, piece[i].y += 2; };
                                }
                            }
                            piece[i].rotation += rotate;
                        }
                        else if (color != O_TETROMINO) piece[i].Rotate(piece[1], rotate);

                        if (piece[i].rotation > 4) piece[i].rotation = 1;
                        if (piece[i].rotation < 1) piece[i].rotation = 4;

                        after_rotation = piece[i].rotation;
                    }

                    Piece rotation_piece[4];
                    if (color != I_TETROMINO) {

                        if ((before_rotation == 1 && after_rotation == 2) || (before_rotation == 3 && after_rotation == 2)) { //1 >> 2 & 3 >> 2
                            //TEST 2
                            if (!isCollided()) {
                                for (int i = 0; i < 4; i++) {

                                    rotation_piece[i].x = piece[i].x;
                                    rotation_piece[i].y = piece[i].y;
                                    piece[i].x += -1;
                                    piece[i].y += 0;
                                }
                            }
                            //TEST 3
                            if (!isCollided()) {
                                for (int i = 0; i < 4; i++) {

                                    piece[i].x = rotation_piece[i].x;
                                    piece[i].y = rotation_piece[i].y;
                                    piece[i].x += -1;
                                    piece[i].y += -1;
                                }
                            }
                            //TEST 4
                            if (!isCollided()) {
                                for (int i = 0; i < 4; i++) {

                                    piece[i].x = rotation_piece[i].x;
                                    piece[i].y = rotation_piece[i].y;
                                    piece[i].x += 0;
                                    piece[i].y += 2;
                                }
                            }
                            //TEST 5
                            if (!isCollided()) {
                                for (int i = 0; i < 4; i++) {

                                    piece[i].x = rotation_piece[i].x;
                                    piece[i].y = rotation_piece[i].y;
                                    piece[i].x += -1;
                                    piece[i].y += 2;
                                }
                            }
                        }
                        if ((before_rotation == 2 && after_rotation == 1) || (before_rotation == 2 && after_rotation == 3)) { //2 >> 1 && 2 >> 3
                            //TEST 2
                            if (!isCollided()) {
                                for (int i = 0; i < 4; i++) {

                                    rotation_piece[i].x = piece[i].x;
                                    rotation_piece[i].y = piece[i].y;
                                    piece[i].x += 1;
                                    piece[i].y += 0;
                                }
                            }
                            //TEST 3
                            if (!isCollided()) {
                                for (int i = 0; i < 4; i++) {

                                    piece[i].x = rotation_piece[i].x;
                                    piece[i].y = rotation_piece[i].y;
                                    piece[i].x += 1;
                                    piece[i].y += 1;
                                }
                            }
                            //TEST 4
                            if (!isCollided()) {
                                for (int i = 0; i < 4; i++) {

                                    piece[i].x = rotation_piece[i].x;
                                    piece[i].y = rotation_piece[i].y;
                                    piece[i].x += 0;
                                    piece[i].y += -2;
                                }
                            }
                            //TEST 5
                            if (!isCollided()) {
                                for (int i = 0; i < 4; i++) {

                                    piece[i].x = rotation_piece[i].x;
                                    piece[i].y = rotation_piece[i].y;
                                    piece[i].x += 1;
                                    piece[i].y += -2;
                                }
                            }
                        }
                        if ((before_rotation == 3 && after_rotation == 4) || (before_rotation == 1 && after_rotation == 4)) { //3 >> 4 & 1 >> 4
                            //TEST 2
                            if (!isCollided()) {
                                for (int i = 0; i < 4; i++) {

                                    rotation_piece[i].x = piece[i].x;
                                    rotation_piece[i].y = piece[i].y;
                                    piece[i].x += 1;
                                    piece[i].y += 0;
                                }
                            }
                            //TEST 3
                            if (!isCollided()) {
                                for (int i = 0; i < 4; i++) {

                                    piece[i].x = rotation_piece[i].x;
                                    piece[i].y = rotation_piece[i].y;
                                    piece[i].x += 1;
                                    piece[i].y += -1;
                                }
                            }
                            //TEST 4
                            if (!isCollided()) {
                                for (int i = 0; i < 4; i++) {

                                    piece[i].x = rotation_piece[i].x;
                                    piece[i].y = rotation_piece[i].y;
                                    piece[i].x += 0;
                                    piece[i].y += 2;
                                }
                            }
                            //TEST 5
                            if (!isCollided()) {
                                for (int i = 0; i < 4; i++) {

                                    piece[i].x = rotation_piece[i].x;
                                    piece[i].y = rotation_piece[i].y;
                                    piece[i].x += 1;
                                    piece[i].y += 2;
                                }
                            }
                        }
                        if ((before_rotation == 4 && after_rotation == 3) || (before_rotation == 4 && after_rotation == 1)) { //4 >> 3 && 4 >> 1
                            //TEST 2
                            if (!isCollided()) {
                                for (int i = 0; i < 4; i++) {

                                    rotation_piece[i].x = piece[i].x;
                                    rotation_piece[i].y = piece[i].y;
                                    piece[i].x += -1;
                                    piece[i].y += 0;
                                }
                            }
                            //TEST 3
                            if (!isCollided()) {
                                for (int i = 0; i < 4; i++) {

                                    piece[i].x = rotation_piece[i].x;
                                    piece[i].y = rotation_piece[i].y;
                                    piece[i].x += -1;
                                    piece[i].y += 1;
                                }
                            }
                            //TEST 4
                            if (!isCollided()) {
                                for (int i = 0; i < 4; i++) {

                                    piece[i].x = rotation_piece[i].x;
                                    piece[i].y = rotation_piece[i].y;
                                    piece[i].x += 0;
                                    piece[i].y += -2;
                                }
                            }
                            //TEST 5
                            if (!isCollided()) {
                                for (int i = 0; i < 4; i++) {

                                    piece[i].x = rotation_piece[i].x;
                                    piece[i].y = rotation_piece[i].y;
                                    piece[i].x += -1;
                                    piece[i].y += -2;
                                }
                            }
                        }
                    }

                    if (!isCollided()) for (int i = 0; i < 4; i++) piece[i] = cache[i];
                    else {

                        if (lock_count_value > 0) {

                            lock_count_value--;
                            lock_delay_value = lock_delay;
                        }
                        sfx_rotate.play();

                        if (color == T_TETROMINO) {

                            int corner_count = 0;
                            if (board[piece[1].y + 1][piece[1].x + 1] != 0 || piece[1].x + 1 >= WIDTH || piece[1].y + 1 >= HEIGHT) corner_count++;
                            if (board[piece[1].y + 1][piece[1].x - 1] != 0 || piece[1].x - 1 < 0 || piece[1].y + 1 >= HEIGHT) corner_count++;
                            if (board[piece[1].y - 1][piece[1].x + 1] != 0 || piece[1].x + 1 >= WIDTH || piece[1].y - 1 < 0) corner_count++;
                            if (board[piece[1].y - 1][piece[1].x - 1] != 0 || piece[1].x - 1 < 0 || piece[1].y + 1 < 0) corner_count++;

                            if (corner_count >= 3) {

                                sfx_spin.play();
                                is_tspin = 1;
                            }
                        }
                    }
                }

                //Game Update
                if (timer > delay) {

                makeNewPiece:

                    for (int i = 0; i < 4; i++) {

                        cache[i] = piece[i];
                        piece[i].y++;
                    }

                    if (!isCollided() && lock_delay_value < 0) {

                        if (!holded) {

                            createParticle(&particles);
                            createParticle(&particles);
                            createParticle(&particles);

                            std::vector<PieceLock> piece_lock;
                            for (int i = 0; i < 4; i++) {

                                PieceLock piece_lock_one;
                                piece_lock_one.x = piece[i].x;
                                piece_lock_one.y = piece[i].y;

                                piece_lock.push_back(piece_lock_one);
                            }
                            pieces_lock.push_back(piece_lock);

                            board_wobble = 7;
                            all_piece_count++;
                        }

                        if (!harddrop && !holded) {

                            sfx_floor.play();
                        }

                        for (int i = 0; i < 4; i++) board[cache[i].y][cache[i].x] = color + 1;
                        int choose_piece = seven_bag.at(0);
                        seven_bag.erase(seven_bag.begin());
                        if (seven_bag.size() == 0) {
                            seven_bag = seven_bag_next;
                            seven_bag_next = generateNewBag();
                        }

                        color = choose_piece;
                        for (int i = 0; i < 4; i++) {

                            piece[i].x = pieces[choose_piece][i] % 2 + 4;
                            piece[i].y = pieces[choose_piece][i] / 2 + 2;
                            piece[i].rotation = 0;

                            if (color == J_TETROMINO) piece[i].x--;
                            if (color == I_TETROMINO) piece[i].y++;
                        }
                        for (int i = 0; i < 4; i++) {

                            Piece center = piece[1];
                            if (color == I_TETROMINO) piece[i].Rotate(center, 1);
                            if (color == T_TETROMINO) piece[i].Rotate(center, -1);
                            if (color == S_TETROMINO) piece[i].Rotate(center, -1);
                            if (color == Z_TETROMINO) piece[i].Rotate(center, -1);
                            if (color == L_TETROMINO) piece[i].Rotate(center, -1);
                            if (color == J_TETROMINO) piece[i].Rotate(center, 1);
                            piece[i].rotation = 1;
                        }

                        lock_delay_value = lock_delay;
                        lock_count_value = lock_count;
                        is_touch_ground = 0;

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

                            line_clear_combo++;
                            if (line_clear_count == 4 || is_tspin) {

                                btb_combo++;
                                if (btb_combo > 1) sfx_clearbtb.play();
                                else {
                                    if (is_tspin) sfx_clearspin.play();
                                    else sfx_clearquad.play();
                                }

                                int combo = line_clear_combo - 1;
                                if (combo == 1) sfx_combo_1.play();
                                else if (combo == 2) sfx_combo_2.play();
                                else if (combo == 3) sfx_combo_3.play();
                                else if (combo == 4) sfx_combo_4_power.play();
                                else if (combo == 5) sfx_combo_5_power.play();
                                else if (combo == 6) sfx_combo_6_power.play();
                                else if (combo == 7) sfx_combo_7_power.play();
                                else if (combo == 8) sfx_combo_8_power.play();
                                else if (combo == 9) sfx_combo_9_power.play();
                                else if (combo == 10) sfx_combo_10_power.play();
                                else if (combo == 11) sfx_combo_11_power.play();
                                else if (combo == 12) sfx_combo_12_power.play();
                                else if (combo == 13) sfx_combo_13_power.play();
                                else if (combo == 14) sfx_combo_14_power.play();
                                else if (combo == 15) sfx_combo_15_power.play();
                                else if (combo >= 16) sfx_combo_16_power.play();
                            }
                            else {

                                if (btb_combo != 0) {

                                    if (btb_combo > 1) sfx_btb_break.play();
                                    btb_combo = 0;
                                }

                                sfx_clearline.play();

                                int combo = line_clear_combo - 1;
                                if (combo == 1) sfx_combo_1.play();
                                else if (combo == 2) sfx_combo_2.play();
                                else if (combo == 3) sfx_combo_3.play();
                                else if (combo == 4) sfx_combo_4.play();
                                else if (combo == 5) sfx_combo_5.play();
                                else if (combo == 6) sfx_combo_6.play();
                                else if (combo == 7) sfx_combo_7.play();
                                else if (combo == 8) sfx_combo_8.play();
                                else if (combo == 9) sfx_combo_9.play();
                                else if (combo == 10) sfx_combo_10.play();
                                else if (combo == 11) sfx_combo_11.play();
                                else if (combo == 12) sfx_combo_12.play();
                                else if (combo == 13) sfx_combo_13.play();
                                else if (combo == 14) sfx_combo_14.play();
                                else if (combo == 15) sfx_combo_15.play();
                                else if (combo >= 16) sfx_combo_16.play();
                            }

                            all_line_count += line_clear_count;
                        }
                        else if (line_clear_combo != 0) {

                            if (line_clear_combo > 3) sfx_combobreak.play();
                            line_clear_combo = 0;
                        }

                        int perfect_clear = 1;
                        for (int i = 0; i < HEIGHT; i++) {
                            for (int j = 0; j < WIDTH; j++) {
                                if (board[i][j] != 0) perfect_clear = 0;
                            }
                        }
                        if (perfect_clear && !holded) sfx_allclear.play();

                        is_tspin = 0;
                    }
                    else if (!isCollided()) {

                        for (int i = 0; i < 4; i++) piece[i] = cache[i];
                    }
                    else {

                        lock_count_value = lock_count;

                        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {

                            createParticle(&particles);
                            createParticle(&particles);
                        }
                    }

                    timer = 0;
                }
                board_wobble += 100 * ((-board_wobble) / 15) * time;

                //Update Ghost
                for (int i = 0; i < 4; i++) {

                    ghost[i].x = piece[i].x;
                    ghost[i].y = piece[i].y;
                }
                for (int i = 0; i < 4; i++) {

                    while (isCollidedGhost()) {

                        for (int i = 0; i < 4; i++) ghost[i].y++;
                    }

                    for (int i = 0; i < 4; i++) ghost[i].y--;
                }

                move_x = 0;
                rotate = 0;
                delay = 0.5;
                harddrop = 0;
                holded = 0;
                move_left = 0;
                move_right = 0;

                window.clear(sf::Color::Black);

                //Draw Backboard
                sf::RectangleShape backboard_shape;
                backboard_shape.setSize(sf::Vector2f(320, 650));
                backboard_shape.setFillColor(sf::Color::White);
                backboard_shape.setPosition(140, 20 + board_wobble);
                window.draw(backboard_shape);

                //Draw Grid
                board_s.setPosition(150, -30 + board_wobble);
                window.draw(board_s);

                //Draw Das Bar
                float das_progress = std::max((double)0, (double)(lock_delay_value / lock_delay));

                sf::RectangleShape das_bar_shape;
                das_bar_shape.setSize(sf::Vector2f(das_progress * 320, 8));
                das_bar_shape.setFillColor(sf::Color::White);
                das_bar_shape.setPosition(140, 700 + board_wobble);
                window.draw(das_bar_shape);

                //Draw Lock Count
                sf::CircleShape lock_count_circle;
                lock_count_circle.setRadius(6);
                lock_count_circle.setFillColor(sf::Color::White);
                for (int i = 0; i < lock_count_value; i++) {

                    lock_count_circle.setPosition(141 + (i * 23.5), 680 + board_wobble);
                    window.draw(lock_count_circle);
                }

                //Draw Hold
                s.setColor(sf::Color(255, 255, 255, 255));
                if (hold != -1) {

                    Piece hold_piece[4];
                    int hold_piece_choose;
                    hold_piece_choose = hold;

                    for (int j = 0; j < 4; j++) {

                        hold_piece[j].x = pieces[hold_piece_choose][j] % 2 + 4;
                        hold_piece[j].y = pieces[hold_piece_choose][j] / 2 + 3;

                        if (hold == J_TETROMINO) hold_piece[j].x--;
                    }
                    for (int j = 0; j < 4; j++) {

                        Piece center = hold_piece[1];
                        if (hold == I_TETROMINO) hold_piece[j].Rotate(center, 1);
                        if (hold == T_TETROMINO) hold_piece[j].Rotate(center, -1);
                        if (hold == S_TETROMINO) hold_piece[j].Rotate(center, -1);
                        if (hold == Z_TETROMINO) hold_piece[j].Rotate(center, -1);
                        if (hold == L_TETROMINO) hold_piece[j].Rotate(center, -1);
                        if (hold == J_TETROMINO) hold_piece[j].Rotate(center, 1);
                    }

                    for (int j = 0; j < 4; j++) {

                        s.setTextureRect(sf::IntRect(hold * texture_size, 0, texture_size, texture_size));
                        int x_offset = 0;
                        if (hold == I_TETROMINO || hold == O_TETROMINO) x_offset = 15;
                        s.setPosition(hold_piece[j].x * texture_size - 65 - x_offset, hold_piece[j].y * texture_size - 10);
                        window.draw(s);
                    }
                }

                //Draw Next Pieces
                s.setColor(sf::Color(255, 255, 255, 255));
                for (int i = 0; i < seven_bag.size() + seven_bag_next.size(); i++) {

                    if (i < 5) {

                        Piece next_piece[4];
                        int next_piece_choose;
                        if (i < seven_bag.size()) next_piece_choose = seven_bag.at(i);
                        else next_piece_choose = seven_bag_next.at(i - seven_bag.size());

                        int next_color = next_piece_choose;
                        for (int j = 0; j < 4; j++) {

                            next_piece[j].x = pieces[next_piece_choose][j] % 2 + 4;
                            next_piece[j].y = pieces[next_piece_choose][j] / 2 + 3;

                            if (next_color == J_TETROMINO) next_piece[j].x--;
                        }
                        for (int j = 0; j < 4; j++) {

                            Piece center = next_piece[1];
                            if (next_color == I_TETROMINO) next_piece[j].Rotate(center, 1);
                            if (next_color == T_TETROMINO) next_piece[j].Rotate(center, -1);
                            if (next_color == S_TETROMINO) next_piece[j].Rotate(center, -1);
                            if (next_color == Z_TETROMINO) next_piece[j].Rotate(center, -1);
                            if (next_color == L_TETROMINO) next_piece[j].Rotate(center, -1);
                            if (next_color == J_TETROMINO) next_piece[j].Rotate(center, 1);
                        }

                        for (int j = 0; j < 4; j++) {

                            s.setTextureRect(sf::IntRect(next_color * texture_size, 0, texture_size, texture_size));
                            int x_offset = 0;
                            if (next_color == I_TETROMINO || next_color == O_TETROMINO) x_offset = 15;
                            s.setPosition(next_piece[j].x * texture_size + 395 - x_offset, next_piece[j].y * texture_size - 10 + (90 * i));
                            window.draw(s);
                        }
                    }
                }

                //Draw Placed Pieces
                for (int i = 0; i < HEIGHT; i++) {

                    for (int j = 0; j < WIDTH; j++) {

                        s.setColor(sf::Color(255, 255, 255, 255));
                        if (board[i][j] == 0) continue;
                        s.setTextureRect(sf::IntRect((board[i][j] - 1) * texture_size, 0, texture_size, texture_size));
                        s.setPosition(j * texture_size + 150, i * texture_size - 90 + board_wobble);
                        window.draw(s);
                    }
                }

                //Draw Piece Lock
                for (int i = 0; i < pieces_lock.size(); i++) {

                    for (int j = 0; j < 4; j++) {

                        s_lock.setTextureRect(sf::IntRect((int)pieces_lock.at(i).at(j).animation * texture_size, 0, texture_size, texture_size));
                        s_lock.setColor(sf::Color(255, 255, 255, 200));
                        s_lock.setPosition(pieces_lock.at(i).at(j).x * texture_size + 150, (pieces_lock.at(i).at(j).y - 1) * texture_size - 90 + board_wobble);
                        window.draw(s_lock);

                        pieces_lock.at(i).at(j).animation += time * FRAMERATE * 4;
                    }

                    for (int j = 0; j < 4; j++) {

                        if (pieces_lock.at(i).at(j).animation >= 67) {

                            pieces_lock.erase(pieces_lock.begin() + i);
                            break;
                        }
                    }
                }

                //Draw Ghost
                s_ghost.setTextureRect(sf::IntRect(color * texture_size, 0, texture_size, texture_size));
                for (int i = 0; i < 4; i++) {

                    s_ghost.setPosition(piece[i].x * texture_size + 150, ghost[i].y * texture_size - 90 + board_wobble);
                    window.draw(s_ghost);
                }

                //Draw Pieces
                piece_indicator_shape_alpha = (sin(game_elapsed_time.getElapsedTime().asSeconds() * 10) + 1) * 30;
                sf::RectangleShape piece_indicator_shape;
                piece_indicator_shape.setSize(sf::Vector2f(30, 30));
                piece_indicator_shape.setFillColor(sf::Color(255, 255, 255, piece_indicator_shape_alpha));

                float piece_alpha = std::max((double)0, (double)(lock_delay_value / lock_delay));
                for (int i = 0; i < 4; i++) {

                    s.setTextureRect(sf::IntRect(7 * texture_size, 0, texture_size, texture_size));
                    s.setColor(sf::Color(255, 255, 255, 255));
                    s.setPosition(piece[i].x * texture_size + 150, piece[i].y * texture_size - 90 + board_wobble);
                    window.draw(s);

                    s.setTextureRect(sf::IntRect(color * texture_size, 0, texture_size, texture_size));
                    s.setColor(sf::Color(255, 255, 255, piece_alpha * 255));
                    s.setPosition(piece[i].x * texture_size + 150, piece[i].y * texture_size - 90 + board_wobble);
                    window.draw(s);

                    piece_indicator_shape.setPosition(piece[i].x * texture_size + 150, piece[i].y * texture_size - 90 + board_wobble);
                    window.draw(piece_indicator_shape);
                }

                //Draw Particle
                for (int i = 0; i < particles.size(); i++) {

                    particles.at(i).update(time);
                    particles.at(i).draw(&window);
                    if (particles.at(i).alpha <= 0) particles.erase(particles.begin() + i);
                }

                //Draw Backboard
                backboard_shape.setSize(sf::Vector2f(320, 20));
                backboard_shape.setFillColor(sf::Color::Black);
                backboard_shape.setPosition(140, 0 + board_wobble);
                window.draw(backboard_shape);

                backboard_shape.setSize(sf::Vector2f(320, 10));
                backboard_shape.setFillColor(sf::Color::White);
                backboard_shape.setPosition(140, 10 + board_wobble);
                window.draw(backboard_shape);

                //Draw Text
                sf::Text text;
                text.setFont(font);
                text.setCharacterSize(35);
                text.setFillColor(sf::Color::White);

                text.setString("NEXT");
                text.setPosition(480, 30);
                window.draw(text);

                text.setString("HOLD");
                text.setPosition(25, 30);
                window.draw(text);

                text.setCharacterSize(22);
                text.setString(std::to_string(line_clear_combo - 1) + " COMBO");
                text.setPosition(475, 650);
                if (line_clear_combo - 1 > 0) window.draw(text);

                sf::RectangleShape text_box;
                sf::Rect text_rect = text.getLocalBounds();;
                text_box.setFillColor(sf::Color::White);

                text.setFillColor(sf::Color::Black);
                text.setCharacterSize(25);
                text.setString("LINES");
                text_rect = text.getLocalBounds();
                text.setPosition(120 - text_rect.width, 400 + board_wobble);
                text_box.setSize(sf::Vector2f(text_rect.width + 40, text_rect.height * 2 - 4));
                text_box.setOrigin(sf::Vector2f(20, 0));
                text_box.setPosition(text.getPosition());
                window.draw(text_box);
                window.draw(text);

                text.setFillColor(sf::Color::White);
                text.setCharacterSize(30);
                text.setString(std::to_string(all_line_count));
                text_rect = text.getLocalBounds();
                text.setPosition(120 - text_rect.width, 450 + board_wobble);
                window.draw(text);

                text.setFillColor(sf::Color::Black);
                text.setCharacterSize(25);
                text.setString("PIECES");
                text_rect = text.getLocalBounds();
                text.setPosition(120 - text_rect.width, 510 + board_wobble);
                text_box.setSize(sf::Vector2f(text_rect.width + 40, text_rect.height * 2 - 4));
                text_box.setOrigin(sf::Vector2f(20, 0));
                text_box.setPosition(text.getPosition());
                window.draw(text_box);
                window.draw(text);

                text.setFillColor(sf::Color::White);
                text.setCharacterSize(30);
                text.setString(std::to_string(all_piece_count));
                text_rect = text.getLocalBounds();
                text.setPosition(120 - text_rect.width, 560 + board_wobble);
                window.draw(text);

                window.display();

            }
            start--;
            game_clock.restart();
        }
    

}