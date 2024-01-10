#ifndef FILEBROWSEWIDGET_H
#define FILEBROWSEWIDGET_H

#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QHBoxLayout>
#include <QLabel>

class FileBrowseWidget : public QWidget {
    Q_OBJECT
public:
    FileBrowseWidget(const QString& labelText = QString(), QWidget *parent = nullptr);
    QString filePath() const;
    void setFilePath(const QString &path);
    void setLabelText(const QString &text);
    QLineEdit* getLineEdit() const;
private slots:
    void onBrowseButtonClicked();
private:
    QLineEdit *lineEdit;
    QPushButton *browseButton;
    QLabel *label;
};

#endif // FILEBROWSEWIDGET_H
