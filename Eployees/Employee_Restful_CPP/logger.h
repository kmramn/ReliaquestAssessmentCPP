#pragma once

#include <iostream>
#include <fstream>
#include <mutex>
#include <string>
#include <chrono>
#include <iomanip>

class AuditLogger {
    std::wofstream m_wofLogFile;
    std::mutex m_mtxLog;

    // Private constructor
    AuditLogger(const std::wstring& filename);

    // Delete copy and move operations
    AuditLogger(const AuditLogger&) = delete;
    AuditLogger& operator=(const AuditLogger&) = delete;
    AuditLogger(AuditLogger&&) = delete;
    AuditLogger& operator=(AuditLogger&&) = delete;

    std::wstring getTimestamp();

public:
    // Get the singleton instance
    static AuditLogger& GetInstance();

    void log(const wstring& message);
    void log(const string& szMessage);
    void log(const vector<wstring>& wszvecData);
    void log(const map<wstring, wstring>& wszmapData);
};
