#include "bishop.h"  
#include "field.h" 
#include "king.h"  
#include "knight.h"  
#include "pawn.h"
#include "queen.h"  
#include "rook.h"

struct Guacamole {
	float *verts;
	size_t vertsSize;
	float *normals;
	size_t normalsSize;
	float *texCoords;
	size_t texCoordsSize;
	unsigned int vertexCount;
	unsigned int vao;
};

Guacamole figures[] = {
	{rookVerts,sizeof(rookVerts),rookNormals,sizeof(rookNormals),rookTexCoords,sizeof(rookTexCoords),rookNumVerts,0}, 
	{knightVerts,sizeof(knightVerts),knightNormals,sizeof(knightNormals),knightTexCoords,sizeof(knightTexCoords),knightNumVerts,0}, 
	{bishopVerts,sizeof(bishopVerts),bishopNormals,sizeof(bishopNormals),bishopTexCoords,sizeof(bishopTexCoords),bishopNumVerts,0}, 
	{queenVerts,sizeof(queenVerts),queenNormals,sizeof(queenNormals),queenTexCoords,sizeof(queenTexCoords),queenNumVerts,0}, 
	{kingVerts,sizeof(kingVerts),kingNormals,sizeof(kingNormals),kingTexCoords,sizeof(kingTexCoords),kingNumVerts,0}, 
	{pawnVerts,sizeof(pawnVerts),pawnNormals,sizeof(pawnNormals),pawnTexCoords,sizeof(pawnTexCoords),pawnNumVerts,0}, 
	{fieldVerts,sizeof(fieldVerts),fieldNormals,sizeof(fieldNormals),fieldTexCoords,sizeof(fieldTexCoords),fieldNumVerts,0}, 
};
