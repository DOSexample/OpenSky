#pragma once

#include <string>

class CString : public std::basic_string<char, std::char_traits<char>, std::allocator<char>>
{
public:
    CString()
    {
    }
    CString( const char* lhs ) 
    {
        this->append( lhs );
    }

    CString& operator+( const char* lhs )
    {
        this->append( lhs );
        return *this;
    }
    CString& operator+=( const char* lhs )
    {
        this->append( lhs );
        return *this;
    }

    CString& operator+( int lhs )
    {
        char tmp[128];
        sprintf( tmp, "%d", lhs );
        this->append( tmp );
        return *this;
    }
    CString& operator+=( int lhs )
    {
        char tmp[128];
        sprintf( tmp, "%d", lhs );
        this->append( tmp );
        return *this;
    }

    CString& operator+( const CString& lhs )
    {
        this->append( lhs );
        return *this;
    }
    CString& operator+=( const CString& lhs )
    {
        this->append( lhs );
        return *this;
    }

    CString& operator=( const char* lhs )
    {
        this->clear();
        this->append( lhs );
        return *this;
    }

    CString& operator=( const std::string& lhs )
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

    CString& Sprintf( const char* fmt, ... )
    {
        char tmp[1024];

	    va_list args;
	    va_start( args, fmt );
	    vsprintf( tmp, fmt, args );
	    va_end( args );
        this->clear();
        this->append( tmp );

        return *this;
    }
};