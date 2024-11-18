#ifndef GET_CHOSEONG_CONSTANTS_HPP
#define GET_CHOSEONG_CONSTANTS_HPP

#include <string>

namespace RapidFuzz {
namespace Utils {
namespace Hangul {
namespace GetChoseong {

// Define the JasoHangulNFD struct with constants
struct JASO_HANGUL_NFD {
    static constexpr wchar_t START_CHOSEONG = L'\u1100';  // 'ᄀ' U+1100
    static constexpr wchar_t START_JUNGSEONG = L'\u1161'; // 'ᅡ' U+1161
    static constexpr wchar_t START_JONGSEONG = L'\u11A8'; // 'ᆨ' U+11A8
    static constexpr wchar_t END_CHOSEONG = L'\u1112';    // 'ᄒ' U+1112
    static constexpr wchar_t END_JUNGSEONG = L'\u1175';   // 'ᅵ' U+1175
    static constexpr wchar_t END_JONGSEONG = L'\u11C2';   // 'ᇂ' U+11C2
};

} // namespace GetChoseong
} // namespace Hangul
} // namespace Utils
} // namespace RapidFuzz

#endif // GET_CHOSEONG_CONSTANTS_HPP
