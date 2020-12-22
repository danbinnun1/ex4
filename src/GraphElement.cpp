#include "GraphElement.hpp"

server_side::GraphElement::GraphElement(uint32_t row, uint32_t col):m_row(row),m_col(col){}

uint32_t server_side::GraphElement::getRow() const{
    return m_row;
}
uint32_t server_side::GraphElement::getCol() const{
    return m_col;
}
