#ifndef COMMANDHISTORY_H
#define COMMANDHISTORY_H

#include <stack>
#include "command.h"

class CommandHistory {
public:
    CommandHistory() = default;
    ~CommandHistory();

    void executeCommand(Command* command);
    void undo();
    void redo();

private:
    std::stack<Command*> undoStack;
    std::stack<Command*> redoStack;

    // Helper function to clear a stack
    void clearStack(std::stack<Command*>& stack);
};

#endif // COMMANDHISTORY_H
