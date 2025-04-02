#pragma once
#pragma once

#include <string>
#include <cstdint>

namespace Engine {
    class Debug
    {
    public:
        enum class LogType : uint32_t {
            MESSAGE = static_cast<uint32_t>(0),
            WARNING,
            ERROR,
            SUCCESS,
            LOADING,
            PROCESSING,
        };

        static void Log(const std::string& message, LogType type = LogType::MESSAGE);
    private:
        enum class Color {
            WHITE,
            YELLOW,
            RED,
            GREEN,
            BLUE,
            MAGENTA
        };

        static void SetConsoleColor(Color color);

        static void ResetConsoleColor();

        static std::string GetDateTimeNow();
    };




}


