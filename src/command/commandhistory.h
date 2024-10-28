#ifndef COMMANDHISTORY_H
#define COMMANDHISTORY_H

#include <stack>

class Command {
   public:
    virtual ~Command() = default;
    virtual void execute() = 0;
    virtual void undo() = 0;
};

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

#endif  // COMMANDHISTORY_H
