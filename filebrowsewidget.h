#ifndef FILEBROWSEWIDGET_H
#define FILEBROWSEWIDGET_H

#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QHBoxLayout>

class FileBrowseWidget : public QWidget {
    Q_OBJECT
public:
    FileBrowseWidget(QWidget *parent = nullptr);
    QString filePath() const;
    void setFilePath(const QString &path);
private slots:
    void onBrowseButtonClicked();
private:
    QLineEdit *lineEdit;
    QPushButton *browseButton;
};

#endif // FILEBROWSEWIDGET_H
