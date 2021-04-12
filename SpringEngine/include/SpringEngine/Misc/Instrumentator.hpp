#pragma once

namespace SE
{
    struct ProfileResult
    {
        std::string Name;
        long long Start, End;
        uint32_t ThreadID;
    };

    struct InstrumentationSession
    {
        std::string Name;
    };

    class Instrumentor
    {
    public:
        Instrumentor();
        void beginSession(const std::string& name, const std::string& filepath = "results.json");
        void endSession();
        void writeProfile(const ProfileResult& result);

        void writeHeader();

        void writeFooter();

        static Instrumentor& get()
        {
            static Instrumentor instance;
            return instance;
        }
    private:
        InstrumentationSession* m_currentSession;
        std::ofstream m_outputStream;
        int m_profileCount;

    };


    class InstrumentationTimer
    {
    public:
        InstrumentationTimer(const char* name);
        ~InstrumentationTimer();

        void stop();

    private:
        const char* m_name;
        std::chrono::time_point<std::chrono::high_resolution_clock> m_startTimepoint;
        bool m_stopped;
    };
}

#ifdef SE_DEBUG
#define SE_PROFILE_SCOPE(name)  InstrumentationTimer timer##__LINE__(name)
#define SE_PROFILE_FUNCTION() SE_PROFILE_SCOPE(__FUNCSIG__)
#else
#define SE_PROFILE_SCOPE(name)
#define SE_PROFILE_FUNCTION()
#endif