#ifndef __VERTEX_BUFFER__
#define __VERTEX_BUFFER__

class VertexBuffer
{
private:
    unsigned int rendererID;
public:
    VertexBuffer(const void* data, unsigned int size);
    ~VertexBuffer();
    void bind();
    void unbind();
};




#endif //__VERTEX_BUFFER__
