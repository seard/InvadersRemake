#ifndef HUD_H
#define HUD_H

class Screen
{
public:
	static void WinScreen();
	static void LoseScreen();
	static void Update();
private:
	static void Text();
	static void Outline();
};

#endif