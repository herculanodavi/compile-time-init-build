#pragma once

#include <cstddef>
#include <string_view>

namespace sc::detail {
template <typename Tag>
constexpr static auto type_as_string() -> std::string_view {
#if defined(__clang__)
    constexpr std::string_view function_name = __PRETTY_FUNCTION__;
    constexpr auto rhs = function_name.size() - 2;

#elif defined(__GNUC__) || defined(__GNUG__)
    constexpr std::string_view function_name = __PRETTY_FUNCTION__;
    constexpr auto rhs = function_name.size() - 51;

#else
    static_assert(false, "Unknown compiler, can't build type name.");
#endif

    constexpr auto lhs = [&]() -> std::string_view::size_type {
        for (auto i = std::size_t{}; i < function_name.size(); i++) {
            if (function_name[i] == '=') {
                return i + 2;
            }
        }
        return 0;
    }();

    return function_name.substr(lhs, rhs - lhs + 1);
}

template <auto Value>
constexpr static auto enum_as_string() -> std::basic_string_view<char> {
#if defined(__clang__)
    constexpr std::string_view value_string = __PRETTY_FUNCTION__;
    constexpr auto rhs = value_string.size() - 2;

#elif defined(__GNUC__) || defined(__GNUG__)
    constexpr std::string_view value_string = __PRETTY_FUNCTION__;
    constexpr auto rhs = value_string.size() - 2;

#else
    static_assert(false, "Unknown compiler, can't build type name.");
#endif

    constexpr auto lhs = [&]() -> std::string_view::size_type {
        if (const auto colon_pos = value_string.find_last_of(':');
            colon_pos != std::string_view::npos) {
            return colon_pos + 1;
        }
        return 0;
    }();

    return value_string.substr(lhs, rhs - lhs + 1);
}
} // namespace sc::detail
