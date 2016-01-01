#pragma once
#include <exception>

class InvalidOp : public std::exception
{
	const char* what() const noexcept override { return "Invalid OP code or parameters."; }
};
