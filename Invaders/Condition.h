#ifndef CONDITION_H
#define CONDITION_H

class Condition
{
public:
	static bool WinControl();
	static bool LoseControl();
	static bool IsAlive();
private:
	static bool mWin;
	static bool mLose;
};



#endif



