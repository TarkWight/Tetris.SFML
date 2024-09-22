#ifndef MAINMENUVIEW_HPP
#define MAINMENUVIEW_HPP

#include <SFML/Graphics.hpp>
#include "../Utils/ColorPalette.hpp"

/// ����� MainMenuView �������� �� ����������� �������� ���� ���� � ��������� �������,
/// ����� ��� ����� ����� � ������� ������.
class MainMenuView {
public:
    /// �����������. �������������� ������ ���� � ����������� ������� ���.
    MainMenuView();

    /// ������������ ������� ���� � ��������� ����.
    /// \param window ����, � ������� ����� �������������� ����.
    void draw(sf::RenderWindow& window);

    /// ���������, ���� �� ������ ������ "�����".
    /// \param mouseX ������� X ������� ����.
    /// \param mouseY ������� Y ������� ����.
    /// \return True, ���� ������ "�����" ���� ������, ����� False.
    bool isStartButtonClicked(int mouseX, int mouseY);

    /// ���������, ���� �� ������ ������ "�������� ����".
    /// \param mouseX ������� X ������� ����.
    /// \param mouseY ������� Y ������� ����.
    /// \return True, ���� ������ "�������� ����" ���� ������, ����� False.
    bool isChangeColorButtonClicked(int mouseX, int mouseY);

    /// ���������, ���� �� ������ ������ "���������".
    /// \param mouseX ������� X ������� ����.
    /// \param mouseY ������� Y ������� ����.
    /// \return True, ���� ������ "���������" ���� ������, ����� False.
    bool isLeaderboardButtonClicked(int mouseX, int mouseY);

    /// ���������, ���� �� ������ ������ "�����".
    /// \param mouseX ������� X ������� ����.
    /// \param mouseY ������� Y ������� ����.
    /// \return True, ���� ������ "�����" ���� ������, ����� False.
    bool isExitButtonClicked(int mouseX, int mouseY);

    /// ������������ �������� ���� ��� ��������� �������� ���� ������ ��� ���������.
    /// \param mouseX ������� X ������� ����.
    /// \param mouseY ������� Y ������� ����.
    void handleMouseMove(int mouseX, int mouseY);

    /// ������������ ���� � ����������, �������� ������������� ����� ��������.
    /// \param event ������� SFML, ���������� ���������� � ������� �������.
    void handleKeyboardInput(const sf::Event& event);

private:
    /// ������ �������� ����
    sf::RectangleShape startButton;            //< ������ "������"
    sf::RectangleShape changeColorButton;      //< ������ "������� ����"
    sf::RectangleShape leaderboardButton;       //< ������ "�������"
    sf::RectangleShape exitButton;              //< ������ "�����"

    /// ��������� �������� ������
    sf::Font font;                              //< ����� ��� ������
    sf::Text startText;                         //< ����� �� ������ "������"
    sf::Text changeColorText;                   //< ����� �� ������ "������� ����"
    sf::Text leaderboardText;                   //< ����� �� ������ "�������"
    sf::Text exitText;                          //< ����� �� ������ "�����"

    ColorPalette palette;                       //< ������� ������ ��� ������
    sf::RectangleShape* hoveredButton;          //< ��������� ��Hovered ������
    int selectedButtonIndex;                    //< ������ ��������� ������

    /// ���� � �������� ����.
    std::string resourcePath = RESOURCE_DIR;

    /// �������������� ������ ����, ������� �� ������, ��������� � �����.
    void initializeButtons();

    /// ��������� ������� ��� ������ � ����������� �� ����, ����� �� ��� �������.
    void updateButtonAppearance();

    /// ������������� ��������� ������, ��������� ������.
    /// \param index ������ ������, ������� ����� ��������.
    void selectButton(int index);
};

#endif // MAINMENUVIEW_HPP
