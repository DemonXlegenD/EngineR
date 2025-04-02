#include "Debug.h"

#include <iostream>
#include <chrono>
#include <iomanip>
#include <ctime>
#include <sstream>

#ifdef _WIN32

#define NOMINMAX
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

#undef ERROR

#endif

namespace Engine {

    void Debug::Log(const std::string& message, LogType type) {
#ifdef _DEBUG
        std::string timeStamp = GetDateTimeNow();

        switch (type) {
        case LogType::MESSAGE:
            SetConsoleColor(Color::WHITE);
            std::cout << timeStamp << "/[MESSAGE]: " << message << std::endl;
            break;
        case LogType::WARNING:
            SetConsoleColor(Color::YELLOW);
            std::cout << timeStamp << "/[WARNING]: " << message << std::endl;
            break;
        case LogType::ERROR:
            SetConsoleColor(Color::RED);
            std::cout << timeStamp << "/[ERROR]: " << message << std::endl;
            break;
        case LogType::SUCCESS:
            SetConsoleColor(Color::GREEN);
            std::cout << timeStamp << "/[SUCCESS]: " << message << std::endl;
            break;
        case LogType::LOADING:
            SetConsoleColor(Color::BLUE);
            std::cout << timeStamp << "/[LOADING]: " << message << std::endl;
            break;
        case LogType::PROCESSING:
            SetConsoleColor(Color::MAGENTA);
            std::cout << timeStamp << "/[PROCESSING]: " << message << std::endl;
            break;
        default:
            SetConsoleColor(Color::WHITE);
            std::cout << timeStamp << "/[MESSAGE]: " << message << std::endl;
            break;
        }
        ResetConsoleColor();
#endif
    }

    void Debug::SetConsoleColor(Color color) {
#ifdef _WIN32
        // Windows-specific console coloring
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        switch (color) {
        case Color::WHITE: SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE); break;
        case Color::YELLOW: SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN); break;
        case Color::RED: SetConsoleTextAttribute(hConsole, FOREGROUND_RED); break;
        case Color::GREEN: SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN); break;
        case Color::BLUE: SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE); break;
        case Color::MAGENTA: SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_BLUE); break;
        default:
            SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE); break;
        }
#else
        // Unix-like systems (Linux/Mac)
        switch (color) {
        case Color::WHITE: std::cout << "\033[0m"; break;  // Reset to default
        case Color::YELLOW: std::cout << "\033[33m"; break; // Yellow
        case Color::RED: std::cout << "\033[31m"; break;    // Red
        case Color::GREEN: std::cout << "\033[32m"; break; // Green
        case Color::BLUE: std::cout << "\033[34m"; break;  // Bleu
        case Color::MAGENTA: std::cout << "\033[35m"; break; // Magenta
        default: std::cout << "\033[0m"; break;
        }
#endif
    }

    void Debug::ResetConsoleColor() {
#ifdef _WIN32
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
#else
        std::cout << "\033[0m"; // Reset to default
#endif
    }

    std::string Debug::GetDateTimeNow() {
        auto now = std::chrono::system_clock::now();
        auto in_time_t = std::chrono::system_clock::to_time_t(now);

        struct tm timeInfo;
        localtime_s(&timeInfo, &in_time_t);

        std::stringstream ss;
        ss << std::put_time(&timeInfo, "[%H:%M:%S]");
        return ss.str();
    }
}