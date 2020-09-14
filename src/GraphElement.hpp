#pragma once
#include <stdint.h>

namespace server_side {
class GraphElement{
private:
    uint32_t m_row;
    uint32_t m_col;

public:
    GraphElement(uint32_t row, uint32_t col);
    uint32_t getRow() const;
    uint32_t getCol() const;
};
} // namespace server_side