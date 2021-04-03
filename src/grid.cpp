#include "hdr/grid.hpp"


#include <sstream>

Grid::Grid(unsigned int nx,unsigned int ny,unsigned int nz, double minx, double maxx, double miny, double maxy, double minz, double maxz)
{
	m_iNXPoints = nx;
	m_iNYPoints = ny;
	m_iNZPoints = nz;
	m_dMinX = minx;
	m_dMinY = miny;
	m_dMinZ = minz;
	m_dMaxX = maxx;
	m_dMaxY = maxy;
	m_dMaxZ = maxz;

	m_dXStep = (m_dMaxX-m_dMinX)/m_iNXPoints;
	m_dYStep = (m_dMaxY-m_dMinY)/m_iNYPoints;
	m_dZStep = (m_dMaxZ-m_dMinZ)/m_iNZPoints;

	m_vValues = std::vector<std::vector<std::vector<double>>>(nx, std::vector<std::vector<double>>(ny,std::vector<double>(nz)));
}//Grid


// Returns the values of the grid at the 8 vertices of the cube 
// 	Input variables :
// 		- indexX	= index of the cube along the x direction
// 		- indexY	= index of the cube along the y direction
// 		- indexZ	= index of the cube along the z direction
//
// 	Output :
// 		Returns a vector of size 8 corresponding to the values of the grid
// 		at the 8 Points of index defined as it follows
//
// 		
//                           4---------------------5
//                          /|                    /|
//                         / |                   / |
//                        /  |                  /  |
//                       /   |                 /   |
//                      /    |                /    |
//                     /     |               /     |
//                    /      |              /      |         
//                   7-----------6---------6       |         
//                   |       |             |       |        
//                   |       0-------------|-------1
//                   |      /              |      /
//                   |     /               |     /
//                   |    /                |    /
//                   |   /                 |   /
//                   |  /                  |  /
//                   | /                   | /
//                   |/                    |/
//                   3---------------------2
//
std::vector<double>	Grid::getCubeVerticesValues(unsigned int indexX,unsigned int indexY,unsigned int indexZ)
{
	// Checks if the cube exists
	if(indexX >= m_iNXPoints or indexY >= m_iNYPoints or indexZ >= m_iNZPoints)
	{
		std::stringstream errMsg;
		errMsg << "Wrong value for cube position, the grid is of dimensions " << m_iNXPoints-1 << "x" << m_iNYPoints << "x" << m_iNZPoints << ". Cube at position " << indexX+1 << "x" << indexY+1 << "x" << indexZ+1 << " requested." << std::endl;
		std::cerr << errMsg.str();
		exit(1);	
	}

	std::vector<double> values(8);

	values[0] = m_vValues[indexX][indexY][indexZ];
	values[1] = m_vValues[indexX][indexY+1][indexZ];
	values[2] = m_vValues[indexX+1][indexY+1][indexZ];
	values[3] = m_vValues[indexX+1][indexY][indexZ];
	values[4] = m_vValues[indexX][indexY][indexZ+1];
	values[5] = m_vValues[indexX][indexY+1][indexZ+1];
	values[6] = m_vValues[indexX+1][indexY+1][indexZ+1];
	values[7] = m_vValues[indexX+1][indexY][indexZ+1];

	return values;
} // getCubeVerticesValues


// Returns the positions of the 8 vertices of the cube 
// 	Input variables :
// 		- indexX	= index of the cube along the x direction
// 		- indexY	= index of the cube along the y direction
// 		- indexZ	= index of the cube along the z direction
//
// 	Output :
// 		Returns a vector of size 8x3 corresponding to cartesian coordinates
// 		of the 8 vertices defined as it follows
//
// 		
//                           4---------------------5
//                          /|                    /|
//                         / |                   / |
//                        /  |                  /  |
//                       /   |                 /   |
//                      /    |                /    |
//                     /     |               /     |
//                    /      |              /      |         
//                   7-----------6---------6       |         
//                   |       |             |       |        
//                   |       0-------------|-------1
//                   |      /              |      /
//                   |     /               |     /
//                   |    /                |    /
//                   |   /                 |   /
//                   |  /                  |  /
//                   | /                   | /
//                   |/                    |/
//                   3---------------------2
std::vector<C3Vec>	Grid::getCubeVerticesPositions(unsigned int indexX,unsigned int indexY,unsigned int indexZ)
{
	// Checks if the cube exists
	if(indexX >= m_iNXPoints or indexY >= m_iNYPoints or indexZ >= m_iNZPoints)
	{
		std::stringstream errMsg;
		errMsg << "Wrong value for cube position, the grid is of dimensions " << m_iNXPoints-1 << "x" << m_iNYPoints << "x" << m_iNZPoints << ". Cube at position " << indexX+1 << "x" << indexY+1 << "x" << indexZ+1 << " requested." << std::endl;
		std::cerr << errMsg.str();
		exit(1);	
	}

	std::vector<C3Vec> positions(8);

	positions[0] = C3Vec(m_dMinX + indexX*m_dXStep, m_dMinY + indexY*m_dYStep,m_dMinZ + indexZ*m_dZStep);
	positions[1] = C3Vec(m_dMinX + indexX*m_dXStep, m_dMinY + (indexY+1)*m_dYStep, m_dMinZ + indexZ*m_dZStep);
	positions[2] = C3Vec(m_dMinX + (indexX+1)*m_dXStep, m_dMinY + (indexY+1)*m_dYStep, m_dMinZ + indexZ*m_dZStep);
	positions[3] = C3Vec(m_dMinX + (indexX+1)*m_dXStep, m_dMinY + indexY*m_dYStep, m_dMinZ + indexZ*m_dZStep);
	positions[4] = C3Vec(m_dMinX + indexX*m_dXStep, m_dMinY + indexY*m_dYStep, m_dMinZ + (indexZ+1)*m_dZStep);
	positions[5] = C3Vec(m_dMinX + indexX*m_dXStep, m_dMinY + (indexY+1)*m_dYStep, m_dMinZ + (indexZ+1)*m_dZStep);
	positions[6] = C3Vec(m_dMinX + (indexX+1)*m_dXStep, m_dMinY + (indexY+1)*m_dYStep, m_dMinZ + (indexZ+1)*m_dZStep);
	positions[7] = C3Vec(m_dMinX + (indexX+1)*m_dXStep, m_dMinY + indexY*m_dYStep, m_dMinZ + (indexZ+1)*m_dZStep);

	return positions;
} // getCubeVerticesValues

