#ifndef GRID_H_INCLUDED
#define GRID_H_INCLUDED

#include <vector>

#include "C3Vec.hpp"

class Grid
{
	public:
        Grid(unsigned int nx,unsigned int ny,unsigned int nz, double minx, double maxx, double miny, double maxy, double minz, double maxz);
        ~Grid(){}

		// Getters
        std::vector<double>	getCubeVerticesValues(unsigned int indexX,unsigned int indexY,unsigned int indexZ);
        std::vector<C3Vec>	getCubeVerticesPositions(unsigned int indexX,unsigned int indexY,unsigned int indexZ);
        unsigned int		getNCubeX(){return m_iNXPoints-1;}
        unsigned int		getNCubeY(){return m_iNYPoints-1;}
        unsigned int		getNCubeZ(){return m_iNZPoints-1;}

        C3Vec			getVerticePosition(unsigned int indexX,unsigned int indexY,unsigned int indexZ){return C3Vec(m_dMinX+indexX*m_dXStep, m_dMinY+indexY*m_dYStep, m_dMinZ+indexZ*m_dZStep);}

		// Setters
        void			setValue(unsigned int indexX,unsigned int indexY,unsigned int indexZ, double value){m_vValues[indexX][indexY][indexZ] = value;}

	private:
        unsigned int				m_iNXPoints;
        unsigned int				m_iNYPoints;
        unsigned int				m_iNZPoints;
		double						m_dMinX, m_dMaxX;
		double						m_dMinY, m_dMaxY;
		double						m_dMinZ, m_dMaxZ;
		double						m_dXStep;
		double						m_dYStep;
		double						m_dZStep;
		std::vector<std::vector<std::vector<double>>> 	m_vValues;
};


#endif
