// Refactored 15.04.2021	// Looked Through 15.09.2021
#include "RootException.h" // need 
#include <sstream> // need 


RootException::RootException(int Line, const char* File) noexcept
	:
	Line(Line),
	File(File)
{}

const char* RootException::what() const noexcept
{
	std::ostringstream OStringStream;
	OStringStream << GetType() << std::endl
		<< GetOriginString();
	WhatBuffer = OStringStream.str();
	return WhatBuffer.c_str();
}

const char* RootException::GetType() const noexcept
{
	return "Exception";
}

int RootException::GetLine() const noexcept
{
	return Line;
}

const std::string& RootException::GetFile() const noexcept
{
	return File;
}

std::string RootException::GetOriginString() const noexcept
{
	std::ostringstream OStringStream;
	OStringStream << "[File] " << File << std::endl
		<< "[Line] " << Line;
	return OStringStream.str();
}