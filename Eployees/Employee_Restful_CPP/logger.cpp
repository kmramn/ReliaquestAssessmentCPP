
#include "stdafx.h"

// Get the singleton instance
/*static*/
AuditLogger& AuditLogger::GetInstance()
{
    static AuditLogger loggerInstance(L"server.log");
    return loggerInstance;
}

AuditLogger::AuditLogger(const std::wstring& filename)
    : m_wofLogFile(filename, std::ios::app)  // Append mode
{
    if (!m_wofLogFile.is_open()) {
        std::wcerr << L"Failed to open log file: " << filename << std::endl;
    }
}
void AuditLogger::log(const std::string& szMessage)
{
    wstring wszMessage = convertToWString(szMessage.c_str());
    log(wszMessage);
}

void AuditLogger::log(const std::wstring& message)
{
    std::lock_guard<std::mutex> lock(m_mtxLog);

    std::wstring timestamp = getTimestamp();
    std::wstring fullMessage = timestamp + L" " + message;

    // Console output
    std::wcout << fullMessage << std::endl;

    // File output
    if (m_wofLogFile.is_open()) {
        m_wofLogFile << fullMessage << std::endl;
    }
}

void AuditLogger::log(const vector<wstring>& wszvecData)
{
    wstring wszBuf = { L"vector: " };
    for (auto data : wszvecData)
    {
        wszBuf += data;
        wszBuf += L"\n";
    }

    log(wszBuf);
}

void AuditLogger::log(const map<wstring, wstring>& wszmapData)
{
    wstring wszBuf = { L"map: " };
    for (auto& [wszKey, wszValue] : wszmapData)
    {
        wszBuf += wszKey;
        wszBuf += L":";
        wszBuf += wszValue;
        wszBuf += L"\n";
    }

    log(wszBuf);
}

std::wstring AuditLogger::getTimestamp()
{
    auto now = std::chrono::system_clock::now();
    auto timeT = std::chrono::system_clock::to_time_t(now);
    std::tm tm;
#ifdef _WIN32
    localtime_s(&tm, &timeT);
#else
    localtime_r(&timeT, &tm);
#endif
    wchar_t buffer[32];
    std::wcsftime(buffer, sizeof(buffer), L"%Y-%m-%d %H:%M:%S", &tm);
    return std::wstring(buffer);
}
