#include "command.h"

#include <stack>

Command::~Command() {}

class CommandHistory {
	std::stack<Command *> undoStack;
	std::stack<Command *> redoStack;

  public:
	void executeCommand(Command *command) {
		command->execute();
		undoStack.push(command);
		// Clear the redoStack as new command invalidates the redo history
		while (!redoStack.empty()) {
			delete redoStack.top();
			redoStack.pop();
		}
		clearStack(redoStack);
	}

	void undo() {
		if (!undoStack.empty()) {
			Command *command = undoStack.top();
			undoStack.pop();
			command->undo();
			redoStack.push(command);
		}
	}

	void redo() {
		if (!redoStack.empty()) {
			Command *command = redoStack.top();
			redoStack.pop();
			command->execute();
			undoStack.push(command);
		}
	}

	// Destructor to clean up command objects
	~CommandHistory() {
		clearStack(undoStack);
		clearStack(redoStack);
	}

  private:
	void clearStack(std::stack<Command *> &stack) {
		while (!stack.empty()) {
			delete stack.top();
			stack.pop();
		}
	}
};
