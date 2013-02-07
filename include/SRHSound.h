#ifndef __SRH_SOUND__
#define __SRH_SOUND__

void SRHInitSound();

/**
 * Loads a specific sound from a *.wav file and plays it once.
 *
 * @param pSoundFile - Path to the *.wav sound file.
 */
void SRHPlaySound(const char *pSoundFile);



#endif