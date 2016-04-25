/**
 * @author Fang Qiao
 * @file Utilities.h
 * @date date created: Thu Dec 11 16:50:55 PST 2014
 * @brief
 *
 * Various misc utilities.
 * 
 * @date last modified: Thu Dec 11 16:50:55 PST 2014
 * 
 * @bug No known bugs.
 */
#ifndef UTILITIES_H
#define UTILITIES_H

#include <algorithm> 
#include <cctype>
#include <functional>
#include <iterator>
#include <map>
#include <locale>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>


template <typename T>
class EnumParser
{
    std::map <std::string, T> enumMap;
    public:
    EnumParser(){};
    T ParseEnum( const std::string &value )
    { 
        typename std::map<std::string, T>::const_iterator iValue
                = enumMap.find( value );
        if ( iValue  == enumMap.end() )
            throw std::runtime_error("");
        return iValue->second;
    }
};

// trim from start
static inline std::string &ltrim( std::string &s ) {
        s.erase(s.begin(), std::find_if( s.begin(), s.end(), std::not1(std::ptr_fun<int, int>(std::isspace))));
        return s;
}

// trim from end
static inline std::string &rtrim( std::string &s ) {
        s.erase(std::find_if(s.rbegin(), s.rend(), std::not1(std::ptr_fun<int, int>(std::isspace))).base(), s.end());
        return s;
}

// trim from both ends
static inline std::string &trim( std::string &s ) {
        return ltrim( rtrim( s ) );
}

static inline std::vector<std::string> &split(
    const std::string &s, char delim, std::vector<std::string> &tokens ) {
    std::stringstream ss(s);
    std::string item;
    while ( std::getline( ss, item, delim ) ) {
        tokens.push_back(item);
    }
    return tokens;
}

#endif
