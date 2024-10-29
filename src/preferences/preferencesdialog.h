#ifndef PREFERENCESDIALOG_H
#define PREFERENCESDIALOG_H

#include <QDialog>
#include <QWidget>

namespace Ui
{
class preferencesDialog;
}

class preferencesDialog : public QDialog
{
    Q_OBJECT

    public:
    explicit preferencesDialog(QWidget *parent = nullptr);
    ~preferencesDialog();

    private:
    Ui::preferencesDialog *ui;
    void populatePreferences();
};

#endif  // PREFERENCESDIALOG_H
