#ifndef DANZUN_MESH_H_INCLUDED
#define DANZUN_MESH_H_INCLUDED

namespace dan {
    class Mesh {
        // The vertex array object
        unsigned int array;
        // The array buffer
        unsigned int vertices;
        // The element array buffer
        unsigned int indices;

        int countIndices;

        void steal(Mesh &other);
        // Generate buffers & vertex array
        void init();
        // Delete buffers & vertex array
        void deInit();
    public:
        Mesh();
        ~Mesh();
        Mesh(Mesh &&other);
        Mesh &operator=(Mesh &&other);

        void bind() const;
        static void unbind();

        // Set verticies for array buffer
        void setVertices(int count, const float *data);
        // Set indices for element array buffer
        void setIndices(int count, const unsigned int *data);
        // Set parameter for vertex array object
        void setParam(unsigned int index, int size, int stride, int offset);

        // Render the indices
        void render() const;

        // Render instaced
        void renderInstanced(unsigned int count) const;
    };
}

#endif
