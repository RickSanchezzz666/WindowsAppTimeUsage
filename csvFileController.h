#ifndef CSVFILECONTROLLER_H
#define CSVFILECONTROLLER_H

#include <string>
#include <vector>
#include <QString>

#include <QDateTime>

class CSVController{
public:
    static void createCSVFile(const std::string& fileName = "timeUsageLogs.csv", const std::string& header = "AppName; LastStart; LastClose; LastSessionTime; SessionTime; TotalTimeSpent\n");
    static std::vector<std::string> readCSVFile(const std::string& fileName = "timeUsageLogs.csv", const std::string& header = "AppName; LastStart; LastClose; LastSessionTime; SessionTime; TotalTimeSpent\n");
    static void editCSVFile(const std::string& appName, const QDateTime& sTime, const QDateTime& eTime, const int& lTime, const int& time, long int total, const std::string& fileName = "timeUsageLogs.csv");
    static bool isLogsFileEmpty(const std::string& fileName = "timeUsageLogs.csv", const std::string& header = "AppName; LastStart; LastClose; LastSessionTime; SessionTime; TotalTimeSpent\n");
    static void deleteFromlogs(const std::string& appName, const std::string& fileName = "timeUsageLogs.csv", const std::string& header = "AppName\n");
    static void deleteFromlogsNoBlacklist(const std::string& appName, const std::string& fileName = "timeUsageLogs.csv", const std::string& header = "AppName\n");
    static bool changeNameInLogs(const std::string& appName, const std::string& appNameChange, const std::string& fileName = "timeUsageLogs.csv", const std::string& header = "AppName; NewAppName\n");

    static std::string secondsToTime(long int& seconds);
};


#endif // CSVFILECONTROLLER_H
