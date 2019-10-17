#ifndef _STRING_H_
#define _STRING_H_

#include <ostream>

class String
{
private:
    char* m_str;
public:
    String(char* str);
    bool operator> (const String& str);
    bool operator< (const String& str);
    bool operator== (const String& str);
    friend std::ostream& operator<< (std::ostream& os, const String& str);
};

#endif /* String.h */
