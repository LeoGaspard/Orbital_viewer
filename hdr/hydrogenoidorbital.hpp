#ifndef HYDROGENOID_ORBITAL_H_INCLUDED
#define HYDROGENOID_ORBITAL_H_INCLUDED

#include <iostream>

#include "sphericalharmonic.hpp"

class HydrogenoidOrbital
{
	public:
			HydrogenoidOrbital(int n, int l, int m);
            ~HydrogenoidOrbital(){}

			// Getters
            int 	get_n(){return m_iN;}
            int 	get_l(){return m_iL;}
            int 	get_m(){return m_iM;}

			double 	operator ()(double x, double y, double z);

	private:
			int m_iN, m_iL, m_iM;
			SphericalHarmonic m_Ylm;
			double m_dRadialNormalizationConstant;

};

#endif // HYDROGENOID_ORBITAL_H_INCLUDED
