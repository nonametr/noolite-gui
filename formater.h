#ifndef FORMATER_H
#define FORMATER_H

#include <ctime>

#include <sstream>
#include <string>
#include <vector>
#include <stdarg.h>

class CFormatter
{
    public:
        CFormatter();
        virtual ~CFormatter();

        std::string get();
        virtual void flush() {}

        virtual void beginObject(const std::string & name = "") = 0;
        virtual void endObject() = 0;
        virtual void beginArray(const std::string & name = "") = 0;
        virtual void endArray() = 0;
        virtual void uintValue(const std::string & name, size_t value) = 0;
        virtual void intValue(const std::string & name, ssize_t value) = 0;
        virtual void floatValue(const std::string & name, long double value) = 0;
        virtual void floatValue(const std::string & name, ssize_t value, int digits) = 0;
        virtual void stringValue(const std::string & name, const std::string & value) = 0;
        virtual void boolValue(const std::string & name, bool value) = 0;
        virtual void nullValue(const std::string & name) = 0;
        std::string format (const char *fmt, ...);
        std::string vformat (const char *fmt, va_list args);

        void timingValue(const std::string & name, double startPoint, double finishPoint)
        {
            floatValue(name, finishPoint - startPoint);
        }

        void uintElement(size_t value)
        {
            uintValue("", value);
        }

        void intElement(ssize_t value)
        {
            intValue("", value);
        }

        void floatElement(long double value)
        {
            floatValue("", value);
        }

        void stringElement(const std::string & value)
        {
            stringValue("", value);
        }

        void boolElement(bool value)
        {
            boolValue("", value);
        }

        template <typename Container>
            void uintArray(const char * name, const Container & container)
        {
            beginArray(name);
            for (size_t value : container) {
                uintElement(value);
            }
            endArray();
        }

    protected:
        std::stringstream buf;
};

class CJsonFormatter: public CFormatter
{
    public:
        explicit CJsonFormatter(bool argExtended = false);
        ~CJsonFormatter();
        virtual void flush();

        virtual void beginObject(const std::string & name = "");
        virtual void endObject();
        virtual void beginArray(const std::string & name = "");
        virtual void endArray();
        virtual void uintValue(const std::string & name, size_t value);
        virtual void intValue(const std::string & name, ssize_t value);
        virtual void floatValue(const std::string & name, long double value);
        virtual void floatValue(const std::string & name, ssize_t value, int digits);
        virtual void stringValue(const std::string & name, const std::string & value);
        virtual void boolValue(const std::string & name, bool value);
        virtual void nullValue(const std::string & name);
        void rawValue(const std::string & name, const std::string &json);

    private:
        bool extended;
        std::vector<int> states;

        void printComma();
        void printName(const std::string & name);
        void printValue(size_t value);
        void printValue(ssize_t value);
        void printValue(long double value);
        void printValue(ssize_t value, int digits);
        void printValue(const std::string & value);
        void printValue(bool value);
        void escapeString(const std::string & str);
        void hexChar(uint64_t code);
};

#endif // FORMATER_H
