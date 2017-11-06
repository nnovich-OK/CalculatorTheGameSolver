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
		: CommandException("can't parse \"" + what_arg + "\"\n") {}
};

class CommandButtonDuplicateException : public CommandException {
public:
	explicit CommandButtonDuplicateException(const std::string& buttonStringId)
		: CommandException("button already exists\n") {}
};

class CommandMissingParameterException : public CommandException {
public:
	explicit CommandMissingParameterException()
		: CommandException("parameters are missing\n") {}
};

#endif