#ifndef SPHERICAL_HARMONIC_H_INCLUDED
#define SPHERICAL_HARMONIC_H_INCLUDED

#include <iostream>
#include <cmath>

class SphericalHarmonic
{
	public:
        SphericalHarmonic(){m_iL = 1; m_iM = 0;}
		SphericalHarmonic(int l, int m);
        ~SphericalHarmonic(){}

		//Getters
        double 	operator()(double theta, double phi);
	
	private:
		int 	m_iL, m_iM;
		double 	m_dNormalizationConstant;

};

#endif // SPHERICAL_HARMONIC_H_INCLUDED
