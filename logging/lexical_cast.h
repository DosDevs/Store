#ifndef LOGGING__LEXICAL_CAST__H__INCLUDED
#define LOGGING__LEXICAL_CAST__H__INCLUDED

#include <algorithm>
#include <string>

#include <iostream>


template<typename T>
T lexical_cast(uint64_t t);

template<>
inline
std::string lexical_cast<std::string>(uint64_t uint)
{
    std::string result;

    // Special case.
    if (uint == 0)
    {
        result.push_back('0');
        return result;
    }

    while (uint != 0)
    {
        result.push_back((uint % 10) + '0');
        uint/= 10;
    }

    std::reverse(result.begin(), result.end());

    return result;
}


template<typename T>
T lexical_cast(int64_t t);

template<>
inline
std::string lexical_cast<std::string>(int64_t sint)
{
    std::string result;

    if (sint < 0)
    {
        result.push_back('-');
        sint = -sint;
    }

    result+= lexical_cast<std::string>(uint64_t(sint));

    return result;
}


template<typename A>
A lexical_cast(std::string const& t);

template<>
inline
uint64_t lexical_cast<uint64_t>(std::string const& uint)
{
    uint64_t result = 0;

    auto iter = uint.begin();

    while (isspace(*iter))
        ++iter;

    if (*iter == '-')
        return 0;

    if (*iter == '+')
        ++iter;

    while((iter != uint.end()) && isdigit(*iter))
    {
        result*= 10;
        result+= uint64_t(*(iter++) - '0');
    }

    return result;
}

template<>
inline
int64_t lexical_cast<int64_t>(std::string const& sint)
{
    int64_t result = 0;
    bool is_positive = true;

    auto iter = sint.begin();

    while (isspace(*iter))
        ++iter;

    if (*iter == '-')
        is_positive = false;

    if (*iter == '+')
        ++iter;

    while((iter < sint.end()) && isdigit(*iter))
    {
        result*= 10;
        result+= uint64_t(*(iter++) - '0');
    }

    return is_positive? result: -result;
}


#endif  // LOGGING__LEXICAL_CAST__H__INCLUDED

