#include "csvFileController.h"
#include <fstream>

std::string CSVController::secondsToTime(long int& seconds) {
    int hours = seconds / 3600;
    int minutes = (seconds % 3600) / 60;

    std::string hoursStr = std::to_string(hours);
    if (hours < 10) hoursStr = "0" + hoursStr;

    std::string minutesStr = std::to_string(minutes);
    if (minutes < 10) minutesStr = "0" + minutesStr;

    return hoursStr + ":" + minutesStr;
}

void CSVController::editCSVFile(const std::string& appName, const QDateTime& sTime, const QDateTime& eTime,  const int& lTime, const int& time, long int total, const std::string& fileName) {
    try {
        std::vector<std::string> content = readCSVFile(fileName);
        std::ofstream logsFile(fileName, std::ios::trunc); // clear file before append

        if (!logsFile.is_open()) throw std::runtime_error("Unable to open Logs File");

        QTime start(0, 0, 0);
        QString newLine;
        newLine.append(appName + "; ");
        newLine.append(sTime.toString("yyyy-MM-dd HH:mm:ss") + "; ");
        newLine.append(eTime.toString("yyyy-MM-dd HH:mm:ss") + "; ");
        newLine.append(start.addSecs(lTime).toString("hh:mm:ss") + "; ");
        newLine.append(start.addSecs(time).toString("hh:mm:ss") + "; ");
        newLine.append(secondsToTime(total) + "\n");

        size_t foundName;
        for (auto& line : content) {
            foundName = line.find(appName);
            if (foundName != std::string::npos) {
                line = newLine.toStdString();
                break;
            }
        }

        if (foundName == std::string::npos) {
            content.push_back(newLine.toStdString());
        }

        for (auto& line : content) {
            logsFile << line;
        }

        logsFile.close();
        return;

    } catch (const std::exception& err) {
        throw std::runtime_error(err.what());
        return;
    }
}

void CSVController::createCSVFile(const std::string& fileName, const std::string& header) {
    try {
        std::ofstream logsFile(fileName, std::ios::trunc); // clear file before append

        if (!logsFile.is_open()) throw std::runtime_error("Unable to create Logs File");

        logsFile << header;

        logsFile.close();
        return;

    } catch (const std::exception& err) {
        throw std::runtime_error(err.what());
        return;
    }
}

std::vector<std::string> CSVController::readCSVFile(const std::string& fileName) {
    try {
        std::ifstream logsFile(fileName);

        std::vector<std::string> content;

        if (!logsFile.is_open()) createCSVFile();

        std::string line;
        while (std::getline(logsFile, line)) {
            content.push_back(line + "\n");
        }

        logsFile.close();
        return content;

    } catch (const std::exception& err) {
        throw std::runtime_error(err.what());
        return {};
    }
}

bool CSVController::isLogsFileEmpty(const std::string& fileName, const std::string& header) {
    try {
        std::vector<std::string> content = readCSVFile(fileName);

        return content.size() <= 1;

    } catch (const std::exception& err) {
        throw std::runtime_error(err.what());
        return 0;
    }
}
