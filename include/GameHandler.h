#ifndef __GAMEHANDLER__
#define __GAMEHANDLER__

void MoveLeft();
void MoveRight();
void MoveDown();
void MoveUp();

void Update(unsigned int iMS);
void Drawer();
void ReleaseResources();
void KeyboardHandler(char cKey);

void StartGame();
void QuitGame();
void ShowInstructions();

void TryOpenTreasure();
void TryAttackEnemy();

#endif