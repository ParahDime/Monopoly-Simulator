#include "Logger.h"

Logger::Logger()
{
    std::string folder = "game_results";

    if (!std::filesystem::exists(folder)) {
        std::filesystem::create_directory(folder);
    }

    //Get the time
    auto now = std::chrono::system_clock::now();
    std::time_t currentTime = std::chrono::system_clock::to_time_t(now);
    std::tm timeInfo;

    //Convert to local time
    #if defined(_WIN32)
        localtime_s(&timeInfo, &currentTime);
    #else
        localtime_r(&currentTime, &timeInfo);
    #endif

    //Format
    std::stringstream timeString;
    timeString << std::put_time(&timeInfo, "%Y-%m-%d_%H-%M-%S");

    // 4. Construct the final unique path
    // Example: game_results/game_2026-06-24_16-38-37.txt
    std::string path = folder + "/game_" + timeString.str() + ".txt";

    logFile.open(path);
    if (logFile.is_open()) {
        fileIsOpen = true;
    }
}

Logger::~Logger()
{
}

string Logger::getName()
{
	return fileName;
}

void Logger::setName(string name)
{
	fileName = name;
}

//unused class
void Logger::openFile()
{
}

void Logger::writeToFile(string text)
{
    cout << text << "\n";
    if (fileIsOpen) {
        logFile << text << std::endl;
    }

}

void Logger::closeFile()
{
    if (fileIsOpen) {
        logFile.close();
        fileIsOpen = false;
    }
}
