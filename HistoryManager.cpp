//
// History manager
// Manager history of impressionist for undo and redo
// Life is full of regrets but you cannot undo them
// So we wrote this class and let you undo your mistake here
//

#include "HistoryManager.h";

HistoryManager::HistoryManager()
{
	this->pointerPosition = 0;
	this->historyPointerQueue = std::deque<unsigned char*>();
}

HistoryManager::~HistoryManager()
{
	for(unsigned char* history: this->historyPointerQueue)
	{
		delete[] history;
		history = nullptr;
	}
}

// Private methods
void HistoryManager::popUntilRedoCleared()
{
	this->historyPointerQueue.clear();
	this->pointerPosition = 0;
}

// Public methods
void HistoryManager::pushHistoryBitmap(const unsigned char* source, const int width, const int height)
{
	if (isRedoAvailable())
	{
		popUntilRedoCleared();
	}
	int dimension = width * height * 3;
	unsigned char* history = new unsigned char[dimension];
	std::copy(source, source + dimension, history);
	this->historyPointerQueue.push_front(history);
	if(this->historyPointerQueue.size() > HISTORY_MAX)
	{
		this->popHistoryBitmap();
	}
}

void HistoryManager::popHistoryBitmap()
{
	delete[] this->historyPointerQueue.back();
	this->historyPointerQueue.pop_back();
}

bool HistoryManager::isRedoAvailable()
{
	return this->pointerPosition > 0;
}

bool HistoryManager::isUndoAvailable()
{
	return this->pointerPosition < this->historyPointerQueue.size() - 1;
}

unsigned char* HistoryManager::undo()
{
	if (!isUndoAvailable()) return nullptr;
	this->pointerPosition += 1;
	return this->historyPointerQueue[this->pointerPosition];
}

unsigned char* HistoryManager::redo()
{
	if (!isRedoAvailable()) return nullptr;
	this->pointerPosition -= 1;
	return this->historyPointerQueue[this->pointerPosition];
}
