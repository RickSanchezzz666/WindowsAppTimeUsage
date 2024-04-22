#ifndef CSVFILECONTROLLER_H
#define CSVFILECONTROLLER_H

#include <string>
#include <vector>
#include <QString>

#include <QDateTime>

class CSVController{
public:
    static void createCSVFile(const std::string& fileName = "timeUsageLogs.csv", const std::string& header = "AppName; LastStart; LastClose; LastSessionTime; SessionTime\n");
    static std::vector<std::string> readCSVFile(const std::string& fileName = "timeUsageLogs.csv");
    static void editCSVFile(const std::string& appName, const QDateTime& sTime, const QDateTime& eTime, const int& lTime, const int& time, const std::string& fileName = "timeUsageLogs.csv");
    static bool isLogsFileEmpty(const std::string& fileName = "timeUsageLogs.csv", const std::string& header = "AppName; LastStart; LastClose; LastSessionTime; SessionTime\n");
};

#endif // CSVFILECONTROLLER_H
