#ifndef CASPIAN_H
#define CASPIAN_H

#include <commandhistory.h>
#include <maingraphicsview.h>
#include <selectablelabel.h>
#include "config.h"

#include <QMainWindow>
#include <QResizeEvent>

QT_BEGIN_NAMESPACE
namespace Ui
{
class Caspian;
}
QT_END_NAMESPACE

class Caspian : public QMainWindow
{
    Q_OBJECT

    public:
    Caspian(QWidget *parent = nullptr);
    ~Caspian();

    protected:
    void resizeEvent(QResizeEvent *event) override;

    private:
    Ui::Caspian *ui;
    SelectableLabel *currentSelectedLabel = nullptr;
    CommandHistory commandHistory;
    MainGraphicsView *mainGraphicsView;
    // MainGraphicsView *mainGraphicsView;

    // Methods
    void populateScrollMenu();
    void setPropertiesTable();
    void onPreferencesTriggered();
    void updateActionStates();
    void updateStatusBar(const int x, const int y);
    void setupMainGraphicsView(Config &settings);
    // void recordCommand(Command *command);
    void setupShortcuts();
    void setupToolbar();
    void setupStatusBar();
    void setupActions();

    public slots:
    void undo();
    void redo();
    void recordCommand(Command *command);

    private slots:
    void labelClicked(SelectableLabel *label);
};

#endif  // CASPIAN_H
