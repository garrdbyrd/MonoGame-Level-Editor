#ifndef CASPIAN_H
#define CASPIAN_H

#include <commandhistory.h>
#include <maingraphicsview.h>
#include <selectablelabel.h>

#include <QMainWindow>
#include <QResizeEvent>

QT_BEGIN_NAMESPACE
namespace Ui {
class Caspian;
}
QT_END_NAMESPACE

class Caspian : public QMainWindow {
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

	// Methods
	void populateScrollMenu();
	void setPropertiesTable();
	void onPreferencesTriggered();
	void updateActionStates();

  public slots:
	void undo();
	void redo();
	void recordCommand(Command *command);

  private slots:
	void labelClicked(SelectableLabel *label);
};

#endif // CASPIAN_H
