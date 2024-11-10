#include <QShortcut>
#include "caspian.h"
#include "ui_caspian.h"

// Actions/shortcuts
void Caspian::undo()
{
    commandHistory.undo();
    updateActionStates();
}

void Caspian::redo()
{
    commandHistory.redo();
    updateActionStates();
}

void Caspian::setupShortcuts()
{
    new QShortcut(Qt::CTRL + Qt::Key_Z, this, SLOT(undo()));
    new QShortcut(Qt::CTRL + Qt::Key_Y, this, SLOT(redo()));
    new QShortcut(Qt::CTRL + Qt::SHIFT + Qt::Key_Z, this, SLOT(redo()));
}

void Caspian::updateActionStates()
{
    ui->actionUndo->setEnabled(!commandHistory.isUndoStackEmpty());
    ui->actionRedo->setEnabled(!commandHistory.isRedoStackEmpty());
}

void Caspian::setupActions()
{
    connect(
        ui->actionPreferences,
        &QAction::triggered,
        this,
        &Caspian::onPreferencesTriggered
    );
    connect(ui->actionUndo, &QAction::triggered, this, &Caspian::undo);
    connect(ui->actionRedo, &QAction::triggered, this, &Caspian::redo);
    updateActionStates();
}