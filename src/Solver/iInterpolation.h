#pragma once

#ifndef I_INTERPOLATION
#define I_INTERPOLATION


template<typename T>
class iInterpolation
{
public:
	virtual ~iInterpolation() { }

	virtual void BuildInterpolation() = 0;
	virtual void FindAllInterpolationValues() = 0;
	virtual T FindInterpolationValue( T const x ) = 0;

};

#endif // !I_INTERPOLATION
