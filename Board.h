#pragma once
#include "Territory.h"

#include <array>
#include <optional>

template <std::size_t kWidth, std::size_t kHeight>
class Board
{

private:
    static const std::size_t kSize = kWidth * kHeight;

private:
    std::array<std::optional<Territory>, kSize> m_board;
};

