#pragma once
#include "MiddleWare.hpp"
#include "PebbleLog.h"
#include <chrono>
#include <ctime>
#include <iomanip>
#include <mutex>
#include <sstream>
#include <type_traits>

namespace utils::Log::MiddleWare {

    // ʹ�� chrono ��ȡ����ʱ�䲢��ʽ��Ϊ�ַ���
    std::string getLocalTimeString(const std::string &format = "%Y-%m-%d %H:%M:%S") {
        // ��ȡ��ǰʱ���
        auto now = std::chrono::system_clock::now();
        // ת��Ϊ time_t
        std::time_t now_time_t = std::chrono::system_clock::to_time_t(now);
        // ת��Ϊ����ʱ��
        std::tm localTime;
#ifdef _WIN32
        localtime_s(&localTime, &now_time_t);// Windows ʹ�� localtime_s
#else
        localtime_r(&now_time_t, &localTime);// Linux ʹ�� localtime_r
#endif

        // ��ʽ��ʱ��
        char timeStr[20];
        std::strftime(timeStr, sizeof(timeStr), format.c_str(), &localTime);
        return std::string(timeStr);
    }

    class LocalTimeStampMiddleware : public LoggerMiddleware<LocalTimeStampMiddleware> {
    public:
        LocalTimeStampMiddleware() : formatStr("%Y-%m-%d %H:%M:%S") {}

        template<typename T>
            requires std::is_constructible_v<std::string, T>// ������Լ����ȷ��������ת��Ϊ std::string
        LocalTimeStampMiddleware(T &&format) : formatStr(std::forward<T>(format)) {
            static_assert(!std::is_same_v<std::decay_t<T>, std::string> || !formatStr.empty(),
                          "Time format string must not be empty.");
            static_assert(std::is_constructible_v<std::string, T>,
                          "Template parameter must be convertible to std::string.");
        }

        void process() {
            std::lock_guard<std::mutex> lock(PebbleLog::getMutex());
            std::string timeStr = getLocalTimeString(formatStr);
            PebbleLog::setLogName(PebbleLog::getLogName() + "[" + timeStr + "]");
            PebbleLog::setTimeFormat(formatStr);
        }

    private:
        std::string formatStr;
    };

    class DailyLogMiddleware : public LoggerMiddleware<DailyLogMiddleware> {
    public:
        DailyLogMiddleware() {}

        void process() {
            std::lock_guard<std::mutex> lock(PebbleLog::getMutex());
            std::string dateStr = getLocalTimeString("%Y-%m-%d");
            std::string logName = PebbleLog::getLogName();
            size_t dotPos = logName.find_last_of('.');
            if (dotPos != std::string::npos) {
                // ���ļ����в�������
                std::string newLogName = logName.substr(0, dotPos) + "_" + dateStr + logName.substr(dotPos);
                PebbleLog::setLogName(newLogName);
            } else {
                // ���û����չ����ֱ�����ļ������������
                PebbleLog::setLogName(logName + "_" + dateStr);
            }
        }
    };

    class TraceMiddleware : public LoggerMiddleware<TraceMiddleware> {
    public:
        TraceMiddleware(const std::string &file, int line, const std::string &func, const std::string &args)
            : file(file), line(line), func(func), args(args) {}

        void process() {
            std::lock_guard<std::mutex> lock(PebbleLog::getMutex());
            std::stringstream ss;
            ss << "[Trace] File: " << file << ", Line: " << line << ", Function: " << func << ", Args: " << args;
            PebbleLog::info(ss.str());// ʹ����־�����
        }

    private:
        std::string file;
        int line;
        std::string func;
        std::string args;
    };

    class ThreadIDMiddleware : public LoggerMiddleware<ThreadIDMiddleware> {
    public:
        ThreadIDMiddleware() {}

        void process() {
            std::lock_guard<std::mutex> lock(PebbleLog::getMutex());
            std::stringstream ss;
            ss << "[ThreadID:" << std::this_thread::get_id() << "] ";
            PebbleLog::setConsolePrefixFormat(ss.str() + PebbleLog::getConsolePrefixFormat());
        }
    };

    class CustomTagMiddleware : public LoggerMiddleware<CustomTagMiddleware> {
    public:
        CustomTagMiddleware(const std::string &tag) : tag(tag) {}

        void process() {
            std::lock_guard<std::mutex> lock(PebbleLog::getMutex());
            PebbleLog::setConsolePrefixFormat("[" + tag + "] " + PebbleLog::getConsolePrefixFormat());
        }

    private:
        std::string tag;
    };
}// namespace utils::Log::MiddleWare