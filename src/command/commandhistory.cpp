#include "commandhistory.h"

CommandHistory::~CommandHistory()
{
    clearStack(undoStack);
    clearStack(redoStack);
}

void CommandHistory::executeCommand(Command *command)
{
    command->execute();
    undoStack.push(command);
    clearStack(redoStack);  // Clear redo stack as new command invalidates
                            // the redo history
}

void CommandHistory::undo()
{
    if (!undoStack.empty()) {
        Command *command = undoStack.top();
        undoStack.pop();
        command->undo();
        redoStack.push(command);
    }
}

void CommandHistory::redo()
{
    if (!redoStack.empty()) {
        Command *command = redoStack.top();
        redoStack.pop();
        command->execute();
        undoStack.push(command);
    }
}

void CommandHistory::clearStack(std::stack<Command *> &stack)
{
    while (!stack.empty()) {
        delete stack.top();  // Assumes CommandHistory owns the commands
                             // and should delete them
        stack.pop();
    }
}

bool CommandHistory::isUndoStackEmpty()
{
    return undoStack.empty();
}

bool CommandHistory::isRedoStackEmpty()
{
    return redoStack.empty();
}
