#pragma once

/*****************************************************************************
*  Changeling Game Engine Library                                            *
*  Copyright (C) 2024 Depec o Djemi  ywb3295326723@outlook.com.              *
*                                                                            *
*  This file is part of CGEL.                                                *
*                                                                            *
*  @file     logger.h	                                                     *
*  @brief    A logger Singleton                                              *
*  Details.                                                                  *
*                                                                            *
*  @author   Depec o Djemi                                                   *
*  @email    ywb3295326723@putlook.com                                       *
*  @version  a.0.0.1													     *
*  @date     2024/11/23                                                      *
*  @license  NONE							                                 *
*                                                                            *
*----------------------------------------------------------------------------*
*  Remark         : Description                                              *
*----------------------------------------------------------------------------*
*  Change History :                                                          *
*  <Date>     | <Version> | <Author>       | <Description>                   *
*----------------------------------------------------------------------------*
*  2024/11/23 | a.0.0.1   | Depec o Djemi  | Create file                     *
*----------------------------------------------------------------------------*
*                                                                            *
*****************************************************************************/

#include <iostream>
#include <memory>
#include <chrono>
#include <format>
#include <ctime>
#include <string>
#include <sstream>
#include <iomanip>

/**
 * @brief A logger singleton
 */
class Logger {
public:
	/** 
	* @brief Log function
	* @param s    information
	*/
	static void Log(std::string s);
	Logger();
	~Logger();
private:
	static std::shared_ptr<Logger> m_instance;
	Logger(const Logger& signal);
	const Logger& operator=(const Logger& signal);
	/** 
	* @brief Format date to "YYYY-MM-DD hh:mm:ss"
	* @param s    information
	* 
	* @return Formated date string
	*/
	std::string FormatDateTime();
};
