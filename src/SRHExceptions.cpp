#include "SRHExceptions.h"

const char *SRHWindowAlreadyDefinedException::what() const throw()
{
	return "A window already been defined previously. No new window will be created.";
}
//////////////////////////////////////////////////////////////////////////
const char *SRHNoWindowException::what() const throw()
{
	return "No window has been defined previously. Can not close non existing window.";
}
//////////////////////////////////////////////////////////////////////////
SRHWindowsException::SRHWindowsException( int iErrorCode )
	: m_iErrorCode(iErrorCode)
{

}

const char * SRHWindowsException::what() const throw()
{
	//Get the error string from the window API and return it.
	LPTSTR pMessage = NULL;
	FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_ALLOCATE_BUFFER,NULL,m_iErrorCode,0,(LPTSTR)&pMessage,0,NULL);

	if(pMessage == NULL){
		pMessage = "Unknown exception";
	}

	return pMessage;
}
