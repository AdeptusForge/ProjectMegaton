#pragma once
#include "MADRpch.h"
#include "magic_enum.hpp"
#include "Windows.h"
#include "glfw3.h"
#include "spdlog.h"
#include "spdlog/sinks/rotating_file_sink.h"
#include "spdlog/fmt/fmt.h"

namespace Logging 
{
    enum class Pattern
    {
        Standard,
        Error,
        Extended,
        RawMemory,
    };
    std::map<Pattern, std::string> LoggingPatterns;

    //Load this from Engine Settings File
    void PatternSetup()
    {
        LoggingPatterns.insert({ Pattern::Standard, "" });
        LoggingPatterns.insert({ Pattern::Error, "" });
        LoggingPatterns.insert({ Pattern::Extended, "" });
        LoggingPatterns.insert({ Pattern::RawMemory, "" });


    }




    auto max_size = MEGABYTE * 5;
    auto max_files = 3;
	
    void Log(std::string data)
    {
#ifdef CONSOLE_LOG
        spdlog::info(data);
#endif // CONSOLE_LOG
        spdlog::get("MainLogger")->info(data);
    }

    bool Startup()
	{
        auto logger = spdlog::rotating_logger_mt("MainLogger", "logs/rotating.txt", max_size, max_files);

        PatternSetup();





        try
        {
            //Stores last 32 messages
            logger->enable_backtrace(32);

        }
        catch (const spdlog::spdlog_ex& ex)
        {
            std::cout << "Log init failed: " << ex.what() << std::endl;
            return 1;
        }


        Log("Logging Startup Successful");

		return 0;
	}
    void ChangeLogPattern(Pattern pattern) 
    {
        spdlog::set_pattern(LoggingPatterns.at(pattern));
    }



}
