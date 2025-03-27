
#include "PebbleLog.h"
#include <cstdio>
#include <cstring>
#include <ctime>
#include <fcntl.h>// ���� open
#include <filesystem>
#include <fstream>
#ifdef _WIN32
#include <io.h>// for _open, _close
#include <windows.h>
#undef ERROR// ȡ���궨��
#else
#include <iostream>
#include <unistd.h>
#endif

namespace utils::Log {
    namespace defalut {
        // ����̨��Ĭ��ʱ���ʽ
        static std::string timeFormat = "%Y-%m-%d %H:%M:%S";
        static std::string filePrefixFormat = "";
    };// namespace defalut

    // ��ʼ����̬��Ա
    PebbleLog::LogProperty PebbleLog::logProperty;
    std::mutex PebbleLog::logMutex;
    std::queue<std::pair<LogLevel, std::string>> PebbleLog::logQueue;// ���徲̬��Ա���� logQueue
    std::mutex PebbleLog::queueMutex;                                // ���徲̬��Ա����
    std::condition_variable PebbleLog::queueCond;                    // ���徲̬��Ա����
    static bool skipDebug = false;

// �� PebbleLog ���캯���г�ʼ������̨ģʽ
    PebbleLog::PebbleLog() : stopFlag(false) {
#ifdef _WIN32
        // ���������ն�֧��
        HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
        DWORD dwMode = 0;
        if (GetConsoleMode(hOut, &dwMode)) {
            dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
            SetConsoleMode(hOut, dwMode);
        }
#endif
        logThread = std::thread(&PebbleLog::processLogs, this);
    }

    PebbleLog::~PebbleLog() {
        stopFlag = true;
        queueCond.notify_all();
        if (logThread.joinable()) {
            logThread.join();
        }
    }

    void PebbleLog::processLogs() {
        while (!stopFlag) {
            std::unique_lock<std::mutex> lock(queueMutex);
            queueCond.wait(lock, [this] { return !logQueue.empty() || stopFlag; });

            while (!logQueue.empty()) {
                auto entry = logQueue.front();
                logQueue.pop();
                lock.unlock();

                if (logProperty.type == LogType::CONSOLE) {
                    writeLogToConsole(entry.first, entry.second);
                } else if (logProperty.type == LogType::FILE) {
                    writeLogToFile(entry.second);
                } else {
                    writeLogToConsole(entry.first, entry.second);
                    writeLogToFile(entry.second);
                }

                lock.lock();
            }
        }
    }

    // ���÷���
    void PebbleLog::setLogLevel(LogLevel level) { logProperty.level = level; }
    void PebbleLog::setLogType(LogType type) { logProperty.type = type; }
    void PebbleLog::setMaxFileSize(size_t size) { logProperty.maxFileSize = size; }
    void PebbleLog::setMaxFileCount(size_t count) { logProperty.maxFileCount = count; }
    void PebbleLog::setLogPath(const std::string &path) { logProperty.logPath = path; }
    void PebbleLog::setLogName(const std::string &name) { logProperty.logName = name; }

    void PebbleLog::setTimeFormat(const std::string &format) { defalut::timeFormat = format; }

    void PebbleLog::setConsolePrefixFormat(const std::string &format) { defalut::filePrefixFormat = format; }

    void PebbleLog::setFilePrefixFormat(const std::string &format) {
        defalut::filePrefixFormat = format;
    }

    const std::string &PebbleLog::getLogName() { return logProperty.logName; }

    const std::string &PebbleLog::getConsolePrefixFormat() {
        return defalut::filePrefixFormat;
    }

    // ������־����
    void PebbleLog::log(LogLevel level, std::string_view message) {
        if (level < logProperty.level) return;

        std::string formattedMessage;
        formatLogMessage(level, std::string(message), formattedMessage);

        std::lock_guard<std::mutex> lock(getInstance().queueMutex);
        getInstance().logQueue.push({level, formattedMessage});
        getInstance().queueCond.notify_one();
    }

    void PebbleLog::formatLogMessage(LogLevel level, const std::string &message, std::string &formattedMessage) {
        auto now = std::time(nullptr);
        auto tm = *std::localtime(&now);

        // ʹ�� std::strftime ��� std::format ����ʱ���ʽ��
        char timeBuffer[20];
        std::strftime(timeBuffer, sizeof(timeBuffer), defalut::timeFormat.c_str(), &tm);
        std::string timeStr(timeBuffer);

        formattedMessage = std::format("[{}] {}[{}] {}", timeStr, defalut::filePrefixFormat.empty() ? "" : defalut::filePrefixFormat + " ", [&]() -> std::string {
                                   switch (level) {
                                       case LogLevel::INFO: return "INFO";
                                       case LogLevel::DEBUG: return "DEBUG";
                                       case LogLevel::WARN: return "WARN";
                                       case LogLevel::ERROR: return "ERROR";
                                       case LogLevel::FATAL: return "FATAL";
                                       case LogLevel::TRACE: return "TRACE";
                                       default: return "UNKNOWN";
                                   } }(), message);
    }

#ifdef _WIN32
    void PebbleLog::writeLogToConsole(LogLevel level, const std::string &message) {
        static HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        if (hConsole == INVALID_HANDLE_VALUE) return;

        // ������ɫ
        WORD colorCode = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE;// Ĭ�ϰ�ɫ
        switch (level) {
            case LogLevel::INFO:
                colorCode = FOREGROUND_GREEN;
                break;
            case LogLevel::DEBUG:
                colorCode = FOREGROUND_BLUE | FOREGROUND_INTENSITY;
                break;
            case LogLevel::WARN:
                colorCode = FOREGROUND_RED | FOREGROUND_GREEN;
                break;// ��ɫ
            case LogLevel::ERROR:
                colorCode = FOREGROUND_RED;
                break;
            case LogLevel::FATAL:
                colorCode = FOREGROUND_RED | FOREGROUND_BLUE;
                break;// ���
            case LogLevel::TRACE:
                colorCode = FOREGROUND_BLUE | FOREGROUND_INTENSITY;
                break;
            default:
                break;
        }
        SetConsoleTextAttribute(hConsole, colorCode);

        // д����Ϣ
        DWORD written;
        WriteConsoleA(hConsole, message.c_str(), static_cast<DWORD>(message.size()), &written, nullptr);
        WriteConsoleA(hConsole, "\n", 1, &written, nullptr);// ���з�

        // �ָ�Ĭ����ɫ
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
    }
#endif

    #ifndef _WIN32
    void PebbleLog::writeLogToConsole(LogLevel level, const std::string &message) {
        // ʹ�� ANSI ת������
        const char *colorCode = "";
        switch (level) {
            case LogLevel::INFO:
                colorCode = "\033[32m";
                break;
            case LogLevel::DEBUG:
                colorCode = "\033[36m";
                break;
            case LogLevel::WARN:
                colorCode = "\033[33m";
                break;
            case LogLevel::ERROR:
                colorCode = "\033[31m";
                break;
            case LogLevel::FATAL:
                colorCode = "\033[35m";
                break;
            case LogLevel::TRACE:
                colorCode = "\033[34m";
                break;
            default:
                colorCode = "\033[0m";
                break;
        }

        // ϵͳ����
        std::string output = colorCode + message + "\033[0m\n";
        ssize_t result = write(STDOUT_FILENO, output.c_str(), output.size());
        if (result == -1) {
            // ���÷�����ʹ�� cerr������ݹ���ã�
            std::cerr << "Console write failed: " << strerror(errno) << std::endl;
        }
    }
#endif

    // ������ļ���֧����ת��
    void PebbleLog::writeLogToFile(const std::string &message) {
        std::filesystem::create_directories(logProperty.logPath);
        std::string fullPath = logProperty.logPath + "/" + logProperty.logName;

        // ����ļ���С
        std::ifstream inFile(fullPath, std::ios::ate);
        if (inFile.is_open() && inFile.tellg() >= static_cast<std::streampos>(logProperty.maxFileSize)) {
            inFile.close();
            // �� maxFileCount - 1 �� 1 �������ļ�
            for (int i = logProperty.maxFileCount - 1; i > 0; --i) {
                std::string oldName = fullPath + "." + std::to_string(i - 1);
                std::string newName = fullPath + "." + std::to_string(i);
                if (std::filesystem::exists(oldName)) {
                    try {
                        std::filesystem::rename(oldName, newName);
                    } catch (const std::filesystem::filesystem_error &e) {
                        error("Filesystem error: " + std::string(e.what()));
                    } catch (const std::exception &e) {
                        error("General error: " + std::string(e.what()));
                    }
                }
            }
            // ����ǰ�ļ�������Ϊ fullPath.1
            std::string newName = fullPath + ".1";
            if (std::filesystem::exists(fullPath)) {
                try {
                    std::filesystem::rename(fullPath, newName);
                } catch (const std::filesystem::filesystem_error &e) {
                    error("Filesystem error: " + std::string(e.what()));
                } catch (const std::exception &e) {
                    error("General error: " + std::string(e.what()));
                }
            }
        }

        std::ofstream outFile(fullPath, std::ios::app);
        if (outFile.is_open()) {
            outFile << message << std::endl;
            outFile.close();
        } else {
            error("Failed to open log file: " + fullPath);
        }
    }
}// namespace utils::Log
