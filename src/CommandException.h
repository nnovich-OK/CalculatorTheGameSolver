#ifndef COMMAND_EXCEPTION_H
#define COMMAND_EXCEPTION_H

#include <stdexcept>
#include <string>

class CommandException: public std::runtime_error {
public:
	explicit CommandException(const std::string& what_arg)
		: runtime_error(what_arg) {}
};

class CommandParameterParseException : public CommandException {
public:
	explicit CommandParameterParseException(const std::string& what_arg)
		: CommandException("can't parse \"" + what_arg + "\"") {}
};

class CommandButtonDuplicateException : public CommandException {
public:
	explicit CommandButtonDuplicateException(const std::string& buttonStringId)
		: CommandException("button \"" + buttonStringId + "\" is already added") {}
};

#endif