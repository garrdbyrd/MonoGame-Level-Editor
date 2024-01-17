#ifndef COMMANDHISTORY_H
#define COMMANDHISTORY_H

#include "command.h"
#include <stack>

class CommandHistory {
  public:
	CommandHistory() = default;
	~CommandHistory();

	void executeCommand(Command *command);
	void undo();
	void redo();
	bool isUndoStackEmpty();
	bool isRedoStackEmpty();

  private:
	std::stack<Command *> undoStack;
	std::stack<Command *> redoStack;

	// Helper function to clear a stack
	void clearStack(std::stack<Command *> &stack);
};

#endif // COMMANDHISTORY_H
