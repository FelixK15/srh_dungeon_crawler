#ifndef __SRH_EXCEPTIONS__
#define __SRH_EXCEPTIONS__

#include "SRHIncludes.h"

class SRHWindowAlreadyDefinedException : public std::exception
{
	virtual const char *what() const throw();
};

class SRHNoWindowException : public std::exception
{
	virtual const char *what() const throw();
};

class SRHWindowsException : public std::exception
{
public:
	SRHWindowsException(int iErrorCode);

	virtual const char *what() const throw();

private:
	int m_iErrorCode;
};

#endif