#ifndef LOGIC_INFO_H
#define LOGIC_INFO_H

#include <string>
#include <map>

class LogicInfo {
private:
    std::map<std::string, std::string> infos;

public:
    LogicInfo() = default;
    ~LogicInfo() = default;

    std::string& operator[](std::string key);

    bool operator=(const LogicInfo& other);
};

#endif // LOGIC_INFO_H