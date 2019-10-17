#include "String.h"
#include <cstring>

String::String(char *str) {
    m_str = str;
}

bool String::operator> (const String& str) {
    return (strcmp(m_str, str.m_str)) > 0;
}
bool String::operator== (const String& str) {
    return (strcmp(m_str, str.m_str)) == 0;
}
bool String::operator< (const String& str) {
    return (strcmp(m_str, str.m_str)) < 0;
}

std::ostream& operator<< (std::ostream& os, const String& str) {
    os << str.m_str;
    return os;
}

