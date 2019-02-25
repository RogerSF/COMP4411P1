//
// History manager
// Manager history of impressionist for undo and redo
// Life is full of regrets but you cannot undo them
// So we wrote this class and let you undo your mistake here
//

#ifndef HISTORYMANAGER_H
#define HISTORYMANAGER_H

#include <list>

class HistoryManager
{
public:
	HistoryManager();
	~HistoryManager();
	void pushHistoryBitmap(const unsigned char* source);
	void popHistoryBitmap();
	unsigned char* redo();
	unsigned char* undo();

private:
	void popUntilRedoCleared();
	bool isRedoAvailable();

	int redoCounter = 0;
	std::list<unsigned char*> historyPointerList;
};

#endif
