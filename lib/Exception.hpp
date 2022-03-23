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

        int getId() { return this->id; }
        virtual std::string what() = 0;
    };

    class NothingSlotException : public Exception
    {
    public:
        NothingSlotException() : Exception(1) {}
        ~NothingSlotException() {}

        std::string what() { return "Nothing was in source slot."; }
    };

    class CrashSlotException : public Exception
    {
    public:
        CrashSlotException() : Exception(2) {}
        ~CrashSlotException() {}

        std::string what() { return "Something different already in destination slot."; }
    };

    class NumberTooBigException : public Exception
    {
    public:
        NumberTooBigException() : Exception(3) {}
        ~NumberTooBigException() {}

        std::string what() { return "Number inputed was too big."; }
    };

    class NotExistsException : public Exception
    {
    public:
        NotExistsException() : Exception(4) {}
        ~NotExistsException() {}

        std::string what() { return "Input does not exist."; }
    };

    class WrongTypeException : public Exception
    {
    public:
        WrongTypeException() : Exception(5) {}
        ~WrongTypeException() {}

        std::string what() { return "Input of the wrong type."; }
    };

    class ContainerFullException : public Exception
    {
    public:
        ContainerFullException() : Exception(6) {}
        ~ContainerFullException() {}

        std::string what() { return "Object Buffer is already full type."; }
    };
}

#endif