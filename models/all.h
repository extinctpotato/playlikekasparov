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
};

Guacamole figures[6] = {
	{rookVerts,sizeof(rookVerts),rookNormals,sizeof(rookNormals),rookTexCoords,sizeof(rookTexCoords),rookNumVerts}, 
	{knightVerts,sizeof(knightVerts),knightNormals,sizeof(knightNormals),knightTexCoords,sizeof(knightTexCoords),knightNumVerts}, 
	{bishopVerts,sizeof(bishopVerts),bishopNormals,sizeof(bishopNormals),bishopTexCoords,sizeof(bishopTexCoords),bishopNumVerts}, 
	{queenVerts,sizeof(queenVerts),queenNormals,sizeof(queenNormals),queenTexCoords,sizeof(queenTexCoords),queenNumVerts}, 
	{kingVerts,sizeof(kingVerts),kingNormals,sizeof(kingNormals),kingTexCoords,sizeof(kingTexCoords),kingNumVerts}, 
	{pawnVerts,sizeof(pawnVerts),pawnNormals,sizeof(pawnNormals),pawnTexCoords,sizeof(pawnTexCoords),pawnNumVerts}, 
};
