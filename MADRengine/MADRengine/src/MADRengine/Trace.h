#pragma once
#include "MADRpch.h"
#include "magic_enum.hpp"
#include "Windows.h"
#include "glfw3.h"
#include "spdlog.h"


//
//namespace Logging 
//{
//    auto max_size = 1048576 * 5;
//    auto max_files = 3;
//    auto logger = spdlog::rotating_logger_mt("some_logger_name", "logs/rotating.txt", max_size, max_files);
//	
//    bool Startup()
//	{
//
//        try
//        {
//
//
//            
//            logger->enable_backtrace(32);
//
//        }
//        catch (const spdlog::spdlog_ex& ex)
//        {
//            std::cout << "Log init failed: " << ex.what() << std::endl;
//            return 1;
//        }
//
//        //Stores last 32 messages
//
//
//
//
//
//
//		return 0;
//	}
//}
