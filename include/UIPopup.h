#ifndef __UIPopup_H__
#define __UIPopup_H__

/**
*@breif used to draw the text onto the screne

*/


/**
*@breif draws the players stats to the screen

*/
void drawstats(int health, float exp, int mana, int level, int skillpoints, int strength, int speed, int arcane, int gold);

/**
*@breif not done

*/
void deletestats();
/**
*@breif draws the health/mana/and exp bar

*/
void drawhud(int health, int mana, float exp);

/**
*@breif draws win screen

*/
void drawwin();

/**
*@breif draws lose screen

*/

void drawlose();












#endif // !__UIPopup_H__


