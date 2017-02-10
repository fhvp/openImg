#ifndef __MOBCONSOLE_H__
#define __MOBCONSOLE_H__

class CMOBConsole
{
private:
	static CMOBConsole*				instance;
	int								numColumns;
	int								numLines;
	int								numVisibleLines;

    enum ConsoleParam { 
		NUM_LINES,
		NUM_COLUMNS,
		NUM_VISIBLE_LINES
	};

protected:
	CMOBConsole();
public:
	virtual ~CMOBConsole();

	int SetNumberOfLines (int lines);
	int SetNumberOfColumns (int columns);
	int SetNumVisibleLines (int lines);

	void RedirectToConsole ();
	bool SetConsoleParam (ConsoleParam param);
	int  GetConsoleParam (ConsoleParam param);

	bool AllocateConsole ();
	void RemoveConsole ();

	static CMOBConsole* Instance();
};

#endif __MOBCONSOLE_H__
