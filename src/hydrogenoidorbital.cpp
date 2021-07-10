#include "hdr/hydrogenoidorbital.hpp"

#include <sstream>
#include <boost/math/special_functions/laguerre.hpp>
#include <boost/math/special_functions/factorials.hpp>

HydrogenoidOrbital::HydrogenoidOrbital(int n, int l, int m)
{
	if(n < 1)
	{
		std::stringstream errMsg;
		errMsg << "Invalid value for the quantum number n ( < 0) with " << n << std::endl; 
		std::cerr << errMsg.str();
		exit(1);			
	}
	if(l < 0 )
	{
		std::stringstream errMsg;
		errMsg << "Invalid value for the quantum number l ( < 0) with " << l << std::endl; 
		std::cerr << errMsg.str();
		exit(1);
	}
	if(l >= n )
	{
		std::stringstream errMsg;
		errMsg << "Invalid value for the quantum number l ( >= n = " << n << ") with " << l << std::endl; 
		std::cerr << errMsg.str();
		exit(1);
	}
	if(m < -l or m > l)
	{
		std::stringstream errMsg;
		errMsg << "Invalid value for the quantum number m (|m| > l = " << l << ") with " << m << std::endl; 
		std::cerr << errMsg.str();
		exit(1);
	}
	m_iN = n;
	m_iL = l;
	m_iM = m;
	m_Ylm = SphericalHarmonic(m_iL,m_iM);

    m_dRadialNormalizationConstant = std::sqrt(boost::math::factorial<double>(static_cast<unsigned int>(m_iN-m_iL-1))/(2e0*m_iN*boost::math::factorial<double>(static_cast<unsigned int>(m_iN+m_iL)))) * std::pow(2e0/static_cast<double>(m_iN), static_cast<double>(m_iL) + 1.5e0);


}// HydrogenoidOrbital

double HydrogenoidOrbital::operator()(double x, double y, double z)
{
	double dR = std::sqrt(x*x + y*y + z*z);
	double dTheta = 0e0;
	double dPhi = 0e0;
    	if(dR < std::numeric_limits<double>::epsilon())
	{
		dTheta = 0e0;
	}
	else
	{
		dTheta = std::acos(z/dR);
	}
    	dPhi = std::atan2(y,x);
    	double dRadialPart = std::pow(dR,m_iL)*std::exp(-dR/m_iN)*boost::math::laguerre(static_cast<unsigned int>(m_iN-m_iL-1), static_cast<unsigned int>(2*m_iL+1),2e0*dR/m_iN);

	return m_dRadialNormalizationConstant * dRadialPart * m_Ylm(dTheta,dPhi);
}//operator()
