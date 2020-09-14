#include "GraphElement.hpp"
#include <stdint.h>

using namespace server_side;

GraphElement::GraphElement(uint32_t row, uint32_t col):m_row(row),m_col(col){}

uint32_t GraphElement::getRow() const{
    return m_row;
}
uint32_t GraphElement::getCol() const{
    return m_col;
}
