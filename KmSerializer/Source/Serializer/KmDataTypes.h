#pragma once


/// Primitive Data Types
typedef void               kmVoid;
typedef bool               kmBool;
typedef char               kmInt8;
typedef unsigned char      kmUInt8;
typedef short              kmInt16;
typedef unsigned short     kmUInt16;
typedef int                kmInt32;
typedef unsigned int       kmUInt32;
typedef long long          kmInt64;
typedef unsigned long long kmUInt64;
typedef float              kmFloat;
typedef double             kmDouble;

/// 1Byte Character Type (ASCII, UTF-8)
typedef char kmChar;
typedef std::basic_string< kmChar, std::char_traits< kmChar >, std::allocator< kmChar > > kmString;
typedef std::basic_stringstream< kmChar, std::char_traits< kmChar >, std::allocator< kmChar > > kmStringStream;
