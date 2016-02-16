#ifndef MENU_H
#define MENU_H

enum Sequence
{
	Menu,
	Play,             //1
	Options,          //4
	Exit,             //5
	MAX_SEQUENCE      //Last (6)
};

enum MENUKEYS
{
	MK_UP,
	MK_DOWN,
	MK_RIGHT,
	MK_LEFT,
	MK_ENT,
	MK_SPACE,
	K_MAX
};

enum SequenceOPT {
	OptionsMenu,
	Sound,			//1
	Back,			//3
	MAX_SEQUENCEOPT,
};


void displayMenu();
void displayOptions();
void displayExit();


//inside options
void options();
void displayOptions();
void displaySound();

//exit game
extern bool exitGame;

#endif