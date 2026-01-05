#ifndef GRAPHICS_VOXELRENDERER_H
#define GRAPHICS_VOXELRENDERER_H

#include <stdlib.h>

class Mesh;
class Chunk;

class VoxelRenderer {
	float* buffer;
	size_t capacity;
public:
	VoxelRenderer(size_t capacity);
	~VoxelRenderer();

	Mesh* render(Chunk* chunk);
};

#endif /* GRAPHICS_VOXELRENDERER_H */