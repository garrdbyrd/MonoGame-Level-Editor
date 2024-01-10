#include "filebrowsewidget.h"
#include <QFileDialog>

FileBrowseWidget::FileBrowseWidget(QWidget *parent)
    : QWidget(parent), lineEdit(new QLineEdit(this)), browseButton(new QPushButton("Browse", this)) {

    // Set up the layout
    QHBoxLayout *layout = new QHBoxLayout(this);
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
