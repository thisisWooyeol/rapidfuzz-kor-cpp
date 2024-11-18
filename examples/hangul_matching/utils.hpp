#ifndef HANGUL_MATCHING_UTILS_HPP
#define HANGUL_MATCHING_UTILS_HPP

#include <codecvt>
#include <locale>
#include <string>

// Conversion functions
inline std::wstring utf8_to_wstring(const std::string& str)
{
    std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
    return converter.from_bytes(str);
}

inline std::string wstring_to_utf8(const std::wstring& wstr)
{
    std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
    return converter.to_bytes(wstr);
}

#endif // HANGUL_MATCHING_UTILS_HPP