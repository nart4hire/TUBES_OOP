#ifndef EXCEPTION_HEADER
#define EXCEPTION_HEADER

#include <string>

namespace mobicraft
{
    class Exception
    {
    protected:
        const int id;
    public:
        Exception(int id) : id(id) {}
        ~Exception() {}

        int getId() const { return this->id; }
        virtual std::string what() const = 0;
    };

    class NothingSlotException : public Exception
    {
    public:
        NothingSlotException() : Exception(1) {}
        ~NothingSlotException() {}

        std::string what() const { return "Nothing was in source slot."; }
    };

    class CrashSlotException : public Exception
    {
    public:
        CrashSlotException() : Exception(2) {}
        ~CrashSlotException() {}

        std::string what() const { return "Something different already in destination slot."; }
    };

    class NumberTooBigException : public Exception
    {
    public:
        NumberTooBigException() : Exception(3) {}
        ~NumberTooBigException() {}

        std::string what() const { return "Number inputed was too big."; }
    };

    class NotExistsException : public Exception
    {
    public:
        NotExistsException() : Exception(4) {}
        ~NotExistsException() {}

        std::string what() const { return "Input does not exist."; }
    };

    class WrongTypeException : public Exception
    {
    public:
        WrongTypeException() : Exception(5) {}
        ~WrongTypeException() {}

        std::string what() const { return "Input of the wrong type."; }
    };

    class ContainerFullException : public Exception
    {
    public:
        ContainerFullException() : Exception(6) {}
        ~ContainerFullException() {}

        std::string what() const { return "Object Buffer is already full type."; }
    };

    class InvalidQuantityException : public Exception
    {
    public:
        InvalidQuantityException() : Exception(7) {}
        ~InvalidQuantityException() {}

        std::string what() const { return "Invalid quantity."; }
    };

    class ConfigFileException : public Exception
    {
    public:
        ConfigFileException() : Exception(8) {}
        ~ConfigFileException() {}

        std::string what() const { return "Error accessing config file."; }
    };

    class CraftedItemNotFound : public Exception
    {
    public:
        CraftedItemNotFound() : Exception(9) {}
        ~CraftedItemNotFound() {}
        
        std::string what() const { return "No item is crafted yet."; }
    };

    class InvalidCommandException : public Exception
    {
    public:
        InvalidCommandException() : Exception(10) {}
        ~InvalidCommandException() {}
        
        std::string what() const { return "Invalid command."; }
    };

    class IgnoredArgumentsException : public Exception
    {
    public:
        IgnoredArgumentsException() : Exception(10) {}
        ~IgnoredArgumentsException() {}
        
        std::string what() const { return "Excessive arguments are ignored."; }
    };
}

#endif