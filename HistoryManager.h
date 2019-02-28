//
// History manager
// Manager history of impressionist for undo and redo
// Life is full of regrets but you cannot undo them
// So we wrote this class and let you undo your mistake here
//

#ifndef HISTORYMANAGER_H
#define HISTORYMANAGER_H

#include <deque>

class HistoryManager
{
public:
	HistoryManager();
	~HistoryManager();
	void pushHistoryBitmap(const unsigned char* source, const int width, const int height);
	void popHistoryBitmap();
	bool isRedoAvailable();
	bool isUndoAvailable();
	unsigned char* redo();
	unsigned char* undo();

private:
	void popUntilRedoCleared();

	int pointerPosition;
	std::deque<unsigned char*> historyPointerQueue;
	const int HISTORY_MAX = 10;
};

#endif
