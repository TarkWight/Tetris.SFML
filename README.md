# Tetris.SFML

## Description

`Tetris.SFML` is an implementation of the classic Tetris game using the SFML library and MVC architecture. The project is designed with a focus on adhering to LLVM coding standards and includes various features such as a leaderboard, the ability to save results, pause the game, and a customisable menu.

## Main Features:
- **Graphical interface using SFML.**
- **Keyboard controls.**
- **Game menu:**
  - Game Start.
  - Exit.
  - Colour change.
- **Pause the game with the option to continue or exit to the menu.**
- **Leaderboard:**
  - Display top 5 results.
  - Saves and downloads top scores.
  - Showing the leaderboard after the end of the game.
- **Smoothly increase the speed of the game as you score points.**

## Build and run

Use Visual Stidio 2022, CLion to build the project on macOS and Windows. The project is configured to run using the Chocolatey management pack on Windows and Homebrew on macOS.


### Dependency installation
### Windows:
```
choco install cmake
choco install sfml
choco install googletest
choco install nlohmann-json
choco install spdlog
choco install cxxopts
```

## macOS:
```
brew install cmake
brew install sfml
brew install googletest
brew install nlohmann-json
brew install spdlog
brew install cxxopts
```

## For Windows:
Open PowerShell and run the command:

```powershell
.\build.ps1
```
The script will automatically create a build directory, generate the project using the Visual Studio 17 2022 generator, and run the build in Release mode.


## For macOS:
Make the ``build.sh` script executable:

```bash
chmod +x build.sh
```
Execute the script:

```bash
./build.sh
```
The script will create a build directory, generate a project using Makefiles, and run the build.
