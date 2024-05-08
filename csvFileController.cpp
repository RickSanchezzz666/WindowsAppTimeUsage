#include "csvFileController.h"

#include <fstream>
#include <sstream>

const std::vector<std::string> __initiallyBlockedApps = {
    "EditYourList",
    "ChangeName",
    "Delete",
    "Blacklist"
};

std::string CSVController::secondsToTime(long int& seconds) {
    int hours = seconds / 3600;
    int minutes = (seconds % 3600) / 60;

    std::string hoursStr = std::to_string(hours);
    if (hours < 10) hoursStr = "0" + hoursStr;

    std::string minutesStr = std::to_string(minutes);
    if (minutes < 10) minutesStr = "0" + minutesStr;

    return hoursStr + ":" + minutesStr;
}

bool CSVController::deleteFromBlackList(const std::string& appName, const std::string& fileName, const std::string& header) {
    try {
        std::vector<std::string> content = readCSVFile(fileName, header);

        auto it = content.begin();

        size_t foundName;
        for (auto& line : content) {
            foundName = line.find(appName);
            if (foundName != std::string::npos) {
                content.erase(it);
                break;
            } else ++it;
        }

        std::ofstream blacklist("blacklist.csv", std::ios::trunc);

        for (auto& line : content) {
            blacklist << line;
        }

        blacklist.close();
        return true;
    } catch (const std::exception& err) {
        throw std::runtime_error(err.what());
        return false;
    }
}

void CSVController::deleteFromlogs(const std::string& appName, const std::string& fileName, const std::string& header) {
    try {
        std::vector<std::string> content = readCSVFile(fileName, header);

        std::ofstream logsFile(fileName, std::ios::trunc); // clear file before append

        if (!logsFile.is_open()) throw std::runtime_error("Unable to open Logs File");

        auto it = content.begin();

        size_t foundName;
        for (auto& line : content) {
            foundName = line.find(appName);
            if (foundName != std::string::npos) {
                content.erase(it);
                break;
            } else ++it;
        }

        std::ofstream blacklist("blacklist.csv", std::ios::app);

        blacklist << appName + "; " + "\n";

        blacklist.close();

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


void CSVController::deleteFromlogsNoBlacklist(const std::string& appName, const std::string& fileName, const std::string& header) {
    try {
        std::vector<std::string> content = readCSVFile(fileName, header);

        std::ofstream logsFile(fileName, std::ios::trunc); // clear file before append

        if (!logsFile.is_open()) throw std::runtime_error("Unable to open Logs File");

        auto it = content.begin();

        size_t foundName;
        for (auto& line : content) {
            foundName = line.find(appName);
            if (foundName != std::string::npos) {
                content.erase(it);
                break;
            } else ++it;
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



bool CSVController::changeNameInLogs(const std::string& appName, const std::string& appNameChange, const std::string& fileName, const std::string& header) {
    try {
        std::vector<std::string> content = readCSVFile(fileName, header);

        std::ofstream logsFile(fileName, std::ios::trunc); // clear file before append

        if (!logsFile.is_open()) throw std::runtime_error("Unable to open Logs File");

        auto it = content.begin();

        size_t foundName;
        for (auto& line : content) {
            foundName = line.find(appName);
            if (foundName != std::string::npos) {
                std::istringstream ss(line);
                std::vector<QString> parts;
                std::string part;

                while (std::getline(ss, part, ';')) {
                    parts.push_back(QString::fromStdString(part).trimmed());
                }
                parts[0] = QString::fromStdString(appNameChange);

                line = parts[0].toStdString() + "; "
                       + parts[1].toStdString() + "; "
                       + parts[2].toStdString() + "; "
                       + parts[3].toStdString() + "; "
                       + parts[4].toStdString() + "; "
                       + parts[5].toStdString() + "\n";
                break;
            } else ++it;
        }

        for (auto& line : content) {
            logsFile << line;
        }

        logsFile.close();

        std::vector<std::string> blacklistContent = readCSVFile("blacklist.csv", header);

        bool foundExistence = false;

        for (auto& line : blacklistContent) {
            std::istringstream ss(line);
            std::vector<QString> parts;
            std::string part;

            while (std::getline(ss, part, ';')) {
                parts.push_back(QString::fromStdString(part).trimmed());
            }
            if (appName == parts[1].toStdString()) {
                parts[1] = QString::fromStdString(appNameChange);
                line = parts[0].toStdString() + "; "
                       + parts[1].toStdString() + "\n";
                foundExistence = true;
                break;
            } else ++it;
        }

        if (foundExistence) {
            std::ofstream changeList("blacklist.csv", std::ios::trunc);
            for (auto& line : blacklistContent) {
                changeList << line;
            }
            changeList.close();
            return true;
        } else {
            std::ofstream changeList("blacklist.csv", std::ios::app);
            changeList << appName + "; " + appNameChange + "\n";
            changeList.close();
            return false;
        }
    } catch (const std::exception& err) {
        throw std::runtime_error(err.what());
        return false;
    }
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
        for (const auto& app : __initiallyBlockedApps) {
            logsFile << app + "; \n";
        }

        logsFile.close();
        return;

    } catch (const std::exception& err) {
        throw std::runtime_error(err.what());
        return;
    }
}

std::vector<std::string> CSVController::readCSVFile(const std::string& fileName, const std::string& header) {
    try {
        std::ifstream logsFile(fileName);

        std::vector<std::string> content;

        if (!logsFile.is_open()) createCSVFile(fileName, header);

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
        std::vector<std::string> content = readCSVFile(fileName, header);

        return content.size() <= 1;

    } catch (const std::exception& err) {
        throw std::runtime_error(err.what());
        return 0;
    }
}
