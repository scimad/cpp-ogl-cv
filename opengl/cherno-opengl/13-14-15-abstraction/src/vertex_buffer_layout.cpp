#include "vertex_buffer_layout.hpp"

// Why is this specialization kept in c++ file and not on header
// https://stackoverflow.com/questions/4445654/multiple-definition-of-template-specialization-when-using-different-objects
template<>
void VertexBufferLayout::push<float>(unsigned int count){
    elements.push_back({GL_FLOAT, count, GL_FALSE});
    stride += count * VertexBufferElement::getSizeOfType(GL_FLOAT);
}

template<>
void VertexBufferLayout::push<unsigned int>(unsigned int count){
    elements.push_back({GL_UNSIGNED_INT, count, GL_FALSE});
    stride += count * VertexBufferElement::getSizeOfType(GL_UNSIGNED_INT);
}

template<>
void VertexBufferLayout::push<unsigned char>(unsigned int count){
    elements.push_back({GL_UNSIGNED_BYTE, count, GL_TRUE});
    stride += count * VertexBufferElement::getSizeOfType(GL_UNSIGNED_BYTE);
}
