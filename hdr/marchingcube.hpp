#ifndef MARCHING_CUBE_H_INCLUDED
#define MARCHING_CUBE_H_INCLUDED

#include "grid.hpp"
#include "C3Vec.hpp"

C3Vec interpolateVertices(C3Vec r1, C3Vec r2, double dValue1, double dValue2, double dIsovalue);
void MarchingCube(Grid grid, double dIsovalue, std::vector<C3Vec> &Vertices, std::vector<unsigned int> &Triangles, std::vector<C3Vec> &Normals);

#endif // MARCHING_CUBE_INCLUDED
