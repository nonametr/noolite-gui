#include "formater.h"

#include <iomanip>
#include <string.h>

CFormatter::CFormatter():
    buf()
{
}

CFormatter::~CFormatter()
{
}

std::string CFormatter::get()
{
    flush();
    return buf.str();
}

std::string CFormatter::vformat (const char *fmt, va_list args)
{
    static const size_t size = 1024;
    char buf[size];

    va_list args_copy;
    va_copy (args_copy, args);
    int needed = vsnprintf(&buf[0], size, fmt, args);

    if (needed < 0) {
        return std::string();
    }

    size_t result_len = static_cast<size_t>(needed);

    if (result_len > size) {
        std::vector<char> buf;
        buf.resize(result_len+1);
        needed = vsnprintf(&buf[0], result_len+1, fmt, args_copy);
    }

    return std::string(&buf[0]);
}

std::string CFormatter::format (const char *fmt, ...)
{
    va_list ap;
    va_start (ap, fmt);
    std::string buf = vformat (fmt, ap);
    va_end (ap);
    return buf;
}


namespace
{
    static const int LIST_FIRST = 1;
    static const int LIST_OTHER = 2;
}

CJsonFormatter::CJsonFormatter(bool argExtended):
    CFormatter(),
    extended(argExtended),
    states(1, LIST_FIRST)
{
    buf << '{';
}

CJsonFormatter::~CJsonFormatter()
{
}

void CJsonFormatter::flush()
{
    buf << '}';
}

void CJsonFormatter::printComma()
{
    if (states.back() == LIST_OTHER)
        buf << ',';
    states.back() = LIST_OTHER;
}

void CJsonFormatter::printName(const std::string & name)
{
    printComma();

    if (!name.empty()) {
        printValue(name);
        buf << ':';
    }
}

void CJsonFormatter::printValue(size_t value)
{
    buf << value;
}

void CJsonFormatter::printValue(ssize_t value)
{
    buf << value;
}

void CJsonFormatter::printValue(long double value)
{
    std::string tmp = format("%Lf", value);
    if (tmp == "nan") tmp = "\"NAN\"";
    if (tmp == "inf") tmp = "\"INF\"";
    if (tmp == "+inf") tmp = "\"+INF\"";
    if (tmp == "-inf") tmp = "\"-INF\"";
    buf << format("%s", tmp.c_str());
}

void CJsonFormatter::printValue(ssize_t value, int digits)
{
    ssize_t base = 1;
    for (int i=0; i<digits; ++i) {
        base *= 10;
    }

    buf << value/base;

    if (digits > 0) {
        buf << "." << std::setw(digits) << std::setfill('0') << value%base;
    }
}

void CJsonFormatter::hexChar(uint64_t code)
{
    char tmp[8] = "\\u____\0";
    static char hexDigit[17] = "0123456789ABCDEF";

    for (int i=0; i<4; ++i) {
        tmp[5-i] = hexDigit[code & 0x000F];
        code >>= 4;
    }

    buf << tmp;
}

void CJsonFormatter::printValue(const std::string & value)
{
    buf << '\"';

    const char * str = value.c_str();
    for (;;) {

        if (!str || *str == '\0') break;

        else if (*str == '\"' || *str == '\\' || *str == '/') {
            buf << '\\' << *str;
            ++str;
            continue;
        }

        else if (*str >= ' ' && *str <= 127) {
            buf << *str;
            ++str;
            continue;
        }

        else if (*str == '\b') {
            buf << "\\b";
            ++str;
            continue;
        }

        else if (*str == '\t') {
            buf << "\\t";
            ++str;
            continue;
        }

        else if (*str == '\n') {
            buf << "\\n";
            ++str;
            continue;
        }

        else if (*str == '\f') {
            buf << "\\f";
            ++str;
            continue;
        }

        else if (*str == '\r') {
            buf << "\\r";
            ++str;
            continue;
        }



        uint64_t code = 0;
        int max_lex = strlen(str);
        int len = 0;

        if (false) ; /* For symmetry */

        else if ((*str & 0x60) == 0x40) {
            code = *str & 0x1F;
            len = 2;
        }

        else if ((*str & 0x70) == 0x60) {
            code = *str & 0x0F;
            len = 3;
        }

        else if ((*str & 0x78) == 0x70) {
            code = *str & 0x07;
            len = 4;
        }

        else if ((*str & 0x7C) == 0x78) {
            code = *str & 0x03;
            len = 5;
        }

        else if ((*str & 0x7E) == 0x7C) {
            code = *str & 0x01;
            len = 6;
        }

        len = len > max_lex ? max_lex : len;

        if (len == 0) {
            buf << "?";
            ++str;
            continue;
        }

        for (int i=1; i<len; ++i) {

            if (str[i] >= 0 || (str[i] & 0x40) != 0) {
                buf << "?";
                continue;
            }

            code <<= 6;
            code |= str[i] & 0x3F;
        }

        if (code <= 0xFFFF) {

            hexChar(code);
        }
        else {

            uint64_t ex_code = code - 0x10000;
            uint64_t lo = ex_code & 0x3FF;
            uint64_t hi = ex_code >> 10;
            if (hi <= 0x3FF) {
                hexChar(hi + 0xD800);
                hexChar(lo + 0xDC00);
            } else {
                buf << '?';
            }
        }

        str += len;
    }

    buf << '\"';
}

void CJsonFormatter::printValue(bool value)
{
    buf << (value ? "true" : "false");
}

void CJsonFormatter::nullValue(const std::string & name)
{
    printName(name);
    buf << "null";
}

void CJsonFormatter::uintValue(const std::string & name, size_t value)
{
    printName(name);
    printValue(value);
}

void CJsonFormatter::intValue(const std::string & name, ssize_t value)
{
    printName(name);
    printValue(value);
}

void CJsonFormatter::floatValue(const std::string & name, long double value)
{
    printName(name);
    printValue(value);
}

void CJsonFormatter::floatValue(const std::string & name, ssize_t value, int digits)
{
    printName(name);
    printValue(value, digits);
}

void CJsonFormatter::stringValue(const std::string & name, const std::string & value)
{
    printName(name);
    printValue(value);
}

void CJsonFormatter::boolValue(const std::string & name, bool value)
{
    printName(name);
    printValue(value);
}

void CJsonFormatter::rawValue(const std::string & name, const std::string & json)
{
    printName(name);
    buf << json;
}

void CJsonFormatter::beginObject(const std::string & name)
{
    printName(name);
    buf << '{';
    states.push_back(LIST_FIRST);
}

void CJsonFormatter::endObject()
{
    buf << '}';
    states.pop_back();
}

void CJsonFormatter::beginArray(const std::string & name)
{
    printName(name);
    buf << '[';
    states.push_back(LIST_FIRST);
}

void CJsonFormatter::endArray()
{
    buf << ']';
    states.pop_back();
}
