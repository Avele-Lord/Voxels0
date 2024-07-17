#pragma once
// Refactored 14.04.2021	// Looked Through 15.09.2021
//#include <exception> // Delete later
#include <string> // need 


class RootException : public std::exception
{
public:
	RootException(int Line, const char* File) noexcept;
	const char* what() const noexcept override;
	virtual const char* GetType() const noexcept;
	int GetLine() const noexcept;
	const std::string& GetFile() const noexcept;
	std::string GetOriginString() const noexcept;
private:
	int Line;
	std::string File;
protected:
	mutable std::string WhatBuffer;
};