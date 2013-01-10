#include "GameMath.h"

int Clamp( int iValue,int iMin,int iMax )
{
	if(iValue <= iMin)
	{
		return iMin;
	}else if(iValue >= iMax)
	{
		return iMax;
	}else{
		return iValue;
	}
}
