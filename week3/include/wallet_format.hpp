#pragma once

#include "wallet.hpp"
#include <fmt/format.h>

template <>
struct fmt::formatter<Wallet> : fmt::formatter<std::string_view>
{
    template <typename FormatContext>
    auto format(const Wallet& wallet, FormatContext& ctx) const
    {
        return fmt::format_to(
            ctx.out(),
            "Wallet #{}: balance = {}, limit = {}",
            wallet.get_id(),
            wallet.get_balance(),
            wallet.get_limit()
        );
    }
};