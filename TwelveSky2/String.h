#pragma once

#include <string>

class String : public std::basic_string<char, std::char_traits<char>, std::allocator<char>>
{
public:
    String()
    {
    }
    String( const char* lhs ) 
    {
        this->append( lhs );
    }

    String& operator+( const char* lhs )
    {
        this->append( lhs );
        return *this;
    }
    String& operator+=( const char* lhs )
    {
        this->append( lhs );
        return *this;
    }

    String& operator+( int lhs )
    {
        char tmp[128];
        sprintf( tmp, "%d", lhs );
        this->append( tmp );
        return *this;
    }
    String& operator+=( int lhs )
    {
        char tmp[128];
        sprintf( tmp, "%d", lhs );
        this->append( tmp );
        return *this;
    }

    String& operator+( const String& lhs )
    {
        this->append( lhs );
        return *this;
    }
    String& operator+=( const String& lhs )
    {
        this->append( lhs );
        return *this;
    }

    String& operator=( const char* lhs )
    {
        this->clear();
        this->append( lhs );
        return *this;
    }

    String& operator=( const std::string& lhs )
    {
        this->clear();
        this->append( lhs );
        return *this;
    }

    operator const char*()
    {
        return this->c_str();
    }

    operator char*()
    {
        return (char*)this->c_str();
    }
};