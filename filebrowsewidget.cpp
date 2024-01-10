#include "filebrowsewidget.h"
#include <QFileDialog>

FileBrowseWidget::FileBrowseWidget(const QString& labelText, QWidget *parent)
    : QWidget(parent), lineEdit(new QLineEdit(this)), browseButton(new QPushButton("Browse", this)), label(new QLabel(labelText, this)) {

    // Set up the layout
    QHBoxLayout *layout = new QHBoxLayout(this);
    layout->addWidget(label);
    layout->addWidget(lineEdit);
    layout->addWidget(browseButton);

    // Connect the browse button signal to the slot
    connect(browseButton, &QPushButton::clicked, this, &FileBrowseWidget::onBrowseButtonClicked);
}

QString FileBrowseWidget::filePath() const {
    return lineEdit->text();
}

void FileBrowseWidget::setFilePath(const QString &path) {
    lineEdit->setText(path);
}

void FileBrowseWidget::onBrowseButtonClicked() {
    QString selectedFile = QFileDialog::getOpenFileName(this, tr("Select File"));
    if (!selectedFile.isEmpty()) {
        lineEdit->setText(selectedFile);
    }
}

void FileBrowseWidget::setLabelText(const QString &text) {
    label->setText(text);
}

QLineEdit* FileBrowseWidget::getLineEdit() const {
    return lineEdit;
}
