#include "hdr/sphericalharmonic.hpp"

#include <boost/math/constants/constants.hpp>
#include <boost/math/special_functions/legendre.hpp>
#include <boost/math/special_functions/factorials.hpp>

SphericalHarmonic::SphericalHarmonic(int l, int m)
{
	double  dNormalizationConstant(0e0);

	if(m < -l or m > l)
	{
		std::stringstream errMsg;
		errMsg << "Invalid value for the quantum number m (|m| > l = " << l << "') with " << m << std::endl;
		std::cerr << errMsg.str();
		exit(1);
	}

    dNormalizationConstant = (2e0*l+1e0)/(4e0 * boost::math::constants::pi<double>()) * (boost::math::factorial<double>(static_cast<unsigned int>(l-std::abs(m))))/(boost::math::factorial<double>(static_cast<unsigned int>(l+std::abs(m))));

	m_dNormalizationConstant = std::sqrt(dNormalizationConstant);
	m_iL = l;
	m_iM = m;
}

double SphericalHarmonic::operator()(double theta, double phi)
{
    double dLegendre = boost::math::legendre_p<double>(m_iL, std::abs(m_iM), std::cos(theta));
	double dSign = 1e0*!(m_iM & 1) - 1e0*(m_iM & 1);
	double dValue = dSign * dLegendre * m_dNormalizationConstant;

	if(m_iM < 0)
	{
		dValue *= 2e0/boost::math::constants::root_two<double>() * std::sin(m_iM*phi);
	}
	else if(m_iM > 0)
	{
		dValue *= 2e0/boost::math::constants::root_two<double>() * std::cos(m_iM*phi);
	}

	return dValue;
}
