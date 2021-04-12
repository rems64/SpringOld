//
// Basic instrumentation profiler by Cherno

// Usage: include this header file somewhere in your code (eg. precompiled header), and then use like:
//
// Instrumentor::Get().BeginSession("Session Name");        // Begin session 
// {
//     InstrumentationTimer timer("Profiled Scope Name");   // Place code like this in scopes you'd like to include in profiling
//     // Code
// }
// Instrumentor::Get().EndSession();                        // End Session
//
// You will probably want to macro-fy this, to switch on/off easily and use things like __FUNCSIG__ for the profile name.
//
#include <SpringEngine/Misc/Instrumentator.hpp>

namespace SE
{
    Instrumentor::Instrumentor() : m_currentSession(nullptr), m_profileCount(0)
    {
    }

    void Instrumentor::beginSession(const std::string& name, const std::string& filepath)
    {
        m_outputStream.open(filepath);
        writeHeader();
        m_currentSession = new InstrumentationSession{ name };
    }

    void Instrumentor::endSession()
    {
        writeFooter();
        m_outputStream.close();
        delete m_currentSession;
        m_currentSession = nullptr;
        m_profileCount = 0;
    }

    void Instrumentor::writeProfile(const ProfileResult& result)
    {
        if (m_profileCount++ > 0)
            m_outputStream << ",";

        std::string name = result.Name;
        std::replace(name.begin(), name.end(), '"', '\'');

        m_outputStream << "{";
        m_outputStream << "\"cat\":\"function\",";
        m_outputStream << "\"dur\":" << (result.End - result.Start) << ',';
        m_outputStream << "\"name\":\"" << name << "\",";
        m_outputStream << "\"ph\":\"X\",";
        m_outputStream << "\"pid\":0,";
        m_outputStream << "\"tid\":" << result.ThreadID << ",";
        m_outputStream << "\"ts\":" << result.Start;
        m_outputStream << "}";

        m_outputStream.flush();
    }

    void Instrumentor::writeHeader()
    {
        m_outputStream << "{\"otherData\": {},\"traceEvents\":[";
        m_outputStream.flush();
    }

    void Instrumentor::writeFooter()
    {
        m_outputStream << "]}";
        m_outputStream.flush();
    }

    InstrumentationTimer::InstrumentationTimer(const char* name) : m_name(name), m_stopped(false)
    {
        m_startTimepoint = std::chrono::high_resolution_clock::now();
    }

    InstrumentationTimer::~InstrumentationTimer()
    {
        if (!m_stopped)
            stop();
    }

    void InstrumentationTimer::stop()
    {
        auto endTimepoint = std::chrono::high_resolution_clock::now();

        long long start = std::chrono::time_point_cast<std::chrono::microseconds>(m_startTimepoint).time_since_epoch().count();
        long long end = std::chrono::time_point_cast<std::chrono::microseconds>(endTimepoint).time_since_epoch().count();

        uint32_t threadID = std::hash<std::thread::id>{}(std::this_thread::get_id());
        Instrumentor::get().writeProfile({ m_name, start, end, threadID });

        m_stopped = true;
    }
}