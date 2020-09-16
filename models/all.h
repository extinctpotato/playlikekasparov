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
	char letter;
};

Guacamole figures[] = {
	{rookVerts,sizeof(rookVerts),rookNormals,sizeof(rookNormals),rookTexCoords,sizeof(rookTexCoords),rookNumVerts,0,'r'}, 
	{knightVerts,sizeof(knightVerts),knightNormals,sizeof(knightNormals),knightTexCoords,sizeof(knightTexCoords),knightNumVerts,0,'n'}, 
	{bishopVerts,sizeof(bishopVerts),bishopNormals,sizeof(bishopNormals),bishopTexCoords,sizeof(bishopTexCoords),bishopNumVerts,0,'b'}, 
	{queenVerts,sizeof(queenVerts),queenNormals,sizeof(queenNormals),queenTexCoords,sizeof(queenTexCoords),queenNumVerts,0,'q'}, 
	{kingVerts,sizeof(kingVerts),kingNormals,sizeof(kingNormals),kingTexCoords,sizeof(kingTexCoords),kingNumVerts,0,'k'}, 
	{pawnVerts,sizeof(pawnVerts),pawnNormals,sizeof(pawnNormals),pawnTexCoords,sizeof(pawnTexCoords),pawnNumVerts,0,'p'}, 
	{fieldVerts,sizeof(fieldVerts),fieldNormals,sizeof(fieldNormals),fieldTexCoords,sizeof(fieldTexCoords),fieldNumVerts,0,'f'}, 
};
