#include "SRHSound.h"

#include "SRHGlobals.h"
#include "windows.h"

void SRHPlaySound( const char *pSoundFile )
{
	PlaySound(pSoundFile,NULL,SND_FILENAME | SND_ASYNC | SND_NOSTOP);
}
