#ifndef MAINMENUVIEW_HPP
#define MAINMENUVIEW_HPP

#include <SFML/Graphics.hpp>
#include "../Utils/ColorPalette.hpp"

/// Класс MainMenuView отвечает за отображение главного меню игры и обработку событий,
/// таких как клики мышью и нажатия клавиш.
class MainMenuView {
public:
    /// Конструктор. Инициализирует кнопки меню и настраивает внешний вид.
    MainMenuView();

    /// Отрисовывает главное меню в указанном окне.
    /// \param window Окно, в котором будет отрисовываться меню.
    void draw(sf::RenderWindow& window);

    /// Проверяет, была ли нажата кнопка "Старт".
    /// \param mouseX Позиция X курсора мыши.
    /// \param mouseY Позиция Y курсора мыши.
    /// \return True, если кнопка "Старт" была нажата, иначе False.
    bool isStartButtonClicked(int mouseX, int mouseY);

    /// Проверяет, была ли нажата кнопка "Изменить цвет".
    /// \param mouseX Позиция X курсора мыши.
    /// \param mouseY Позиция Y курсора мыши.
    /// \return True, если кнопка "Изменить цвет" была нажата, иначе False.
    bool isChangeColorButtonClicked(int mouseX, int mouseY);

    /// Проверяет, была ли нажата кнопка "Лидерборд".
    /// \param mouseX Позиция X курсора мыши.
    /// \param mouseY Позиция Y курсора мыши.
    /// \return True, если кнопка "Лидерборд" была нажата, иначе False.
    bool isLeaderboardButtonClicked(int mouseX, int mouseY);

    /// Проверяет, была ли нажата кнопка "Выход".
    /// \param mouseX Позиция X курсора мыши.
    /// \param mouseY Позиция Y курсора мыши.
    /// \return True, если кнопка "Выход" была нажата, иначе False.
    bool isExitButtonClicked(int mouseX, int mouseY);

    /// Обрабатывает движение мыши для изменения внешнего вида кнопок при наведении.
    /// \param mouseX Позиция X курсора мыши.
    /// \param mouseY Позиция Y курсора мыши.
    void handleMouseMove(int mouseX, int mouseY);

    /// Обрабатывает ввод с клавиатуры, позволяя переключаться между кнопками.
    /// \param event Событие SFML, содержащее информацию о нажатии клавиши.
    void handleKeyboardInput(const sf::Event& event);

private:
    /// Кнопки главного меню
    sf::RectangleShape startButton;            //< Кнопка "Начать"
    sf::RectangleShape changeColorButton;      //< Кнопка "Сменить цвет"
    sf::RectangleShape leaderboardButton;       //< Кнопка "Рейтинг"
    sf::RectangleShape exitButton;              //< Кнопка "Выход"

    /// Текстовые элементы кнопок
    sf::Font font;                              //< Шрифт для текста
    sf::Text startText;                         //< Текст на кнопке "Начать"
    sf::Text changeColorText;                   //< Текст на кнопке "Сменить цвет"
    sf::Text leaderboardText;                   //< Текст на кнопке "Рейтинг"
    sf::Text exitText;                          //< Текст на кнопке "Выход"

    ColorPalette palette;                       //< Палитра цветов для кнопок
    sf::RectangleShape* hoveredButton;          //< Указатель наHovered кнопка
    int selectedButtonIndex;                    //< Индекс выбранной кнопки

    /// Путь к ресурсам игры.
    std::string resourcePath = RESOURCE_DIR;

    /// Инициализирует кнопки меню, задавая их размер, положение и текст.
    void initializeButtons();

    /// Обновляет внешний вид кнопок в зависимости от того, какая из них выбрана.
    void updateButtonAppearance();

    /// Устанавливает выбранную кнопку, используя индекс.
    /// \param index Индекс кнопки, которая будет выделена.
    void selectButton(int index);
};

#endif // MAINMENUVIEW_HPP
