#ifndef LOGGING__LOG_ENTRY__H__INCLUDED
#define LOGGING__LOG_ENTRY__H__INCLUDED


#include <algorithm>
#include <iostream>
#include <list>
#include <string>

#include "lexical_cast.h"


#define LOG(SEVERITY) Logging::Entry(SEVERITY)

#define INFO LOG(Logging::Severity::Information)
#define WARN LOG(Logging::Severity::Warning)
#define ERROR LOG(Logging::Severity::Error)


namespace Logging
{
    using std::string;


    enum class Severity {
        Information,
        Warning,
        Error
    };

    static string const InformationName = "Information";
    static string const WarningName = "Warning";
    static string const ErrorName = "Error";

    inline
    string const& GetSeverity(Severity severity)
    {
        struct InvalidSeverityError
        {
            enum Severity Severity;

            InvalidSeverityError(enum Severity severity):
                Severity(severity)
            {}
        };

        switch(severity)
        {
            case Severity::Information: return InformationName;
            case Severity::Warning: return WarningName;
            case Severity::Error: return ErrorName;

            default: throw InvalidSeverityError(severity);
        }
    }

    class Entry {
        private:
            Severity _severity;
            std::list<string> _message_components;
            std::ostream& _stream;

            template<typename T>
            void Wrap(T const& content)
            {
                _stream << "[" << content << "] ";
            }

        public:
            Entry(Severity severity):
                _severity(severity),
                _message_components(),
                _stream(std::cout)
            {}

            ~Entry()
            {
                string message;
                size_t message_length = 0;

                std::for_each(
                        _message_components.begin(),
                        _message_components.end(),
                        [&message_length](string const& component)
                        { message_length+= component.length(); });

                message.reserve(message_length);

                std::for_each(
                        _message_components.begin(),
                        _message_components.end(),
                        [&message](string const& component)
                        { message+= component; });

                Wrap(GetSeverity(_severity));

                _stream << message << std::endl;
            }

            Entry& operator<<(string const& string_to_add)
            {
                _message_components.push_back(string_to_add);
                return (*this);
            }

            Entry& operator<<(char* c_string_to_add)
            {
                _message_components.push_back(c_string_to_add);
                return (*this);
            }
    };  // class Entry
}  // namespace Logging


#endif  // LOGGING__LOG_ENTRY__H__INCLUDED

