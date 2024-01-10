#include "preferencesdialog.h"
#include "config.h"
#include "qlabel.h"
#include "ui_preferencesdialog.h"

#include <QVBoxLayout>
#include <QFormLayout>
#include <QCheckBox>
#include <QDebug>
#include <QSpacerItem>
#include <QScrollArea>
#include <QLabel>

preferencesDialog::preferencesDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::preferencesDialog)
{
    ui->setupUi(this);
    populatePreferences();
}

preferencesDialog::~preferencesDialog()
{
    delete ui;
}

void preferencesDialog::populatePreferences() {
    Config config;

    for (QString& sectionName : config.childGroups()){
        QScrollArea* preferenceTabScrollArea = new QScrollArea;
        QWidget* scrollWidget = new QWidget;
        QFormLayout* layout = new QFormLayout(scrollWidget);
        layout->setLabelAlignment(Qt::AlignBaseline | Qt::AlignBaseline);
        //layout->setSizeConstraint(QLayout::SetNoConstraint);

        preferenceTabScrollArea->setWidgetResizable(true);
        preferenceTabScrollArea->setFrameShadow(QFrame::Raised);
        preferenceTabScrollArea->setWidget(scrollWidget);

        // auto settingsMap = config.getSettings(sectionName);

        config.beginGroup(sectionName);
        foreach (const QString& key, config.allKeys()) {
            QWidget* settingWidget = config.getSettingWidget(key);
            // FileBrowseWidget* settingWidget = dynamic_cast<FileBrowseWidget*>(config.getSettingWidget(key));
            if (settingWidget != nullptr) {
                QLabel* bottomLabel = new QLabel(key);
                QWidget* bottomContainer = new QWidget;
                QVBoxLayout* bottomLayout = new QVBoxLayout(bottomContainer);

                bottomLayout->addWidget(bottomLabel);
                bottomLayout->setAlignment(Qt::AlignBottom);
                bottomLayout->setContentsMargins(0, 0, 0, 0);

                layout->addRow(bottomContainer, settingWidget);
            } else {
                QCheckBox* checkBox = new QCheckBox(key);
                layout->addWidget(checkBox);
            }
        }
        config.endGroup();

        // QSpacerItem* verticalSpacer = new QSpacerItem(0, 0, QSizePolicy::Maximum, QSizePolicy::Expanding);
        // layout->addSpacerItem(verticalSpacer);
        ui->preferencesTabs->addTab(preferenceTabScrollArea, sectionName);
    }
}

// QWidget* createBottomAlignedLabel(const QString& labelText) {
//     QLabel* bottomLabel = new QLabel(labelText);
//     QWidget* bottomContainer = new QWidget;
//     QVBoxLayout* bottomLayout = new QVBoxLayout(bottomContainer);

//     bottomLayout->addStretch();  // Add stretchable space at the top
//     bottomLayout->addWidget(bottomLabel);  // Add the label at the bottom
//     bottomLayout->setAlignment(bottomLabel, Qt::AlignBottom);  // Align the label to the bottom
//     bottomLayout->setContentsMargins(0, 0, 0, 0);  // Remove margins, adjust as needed

//     return bottomContainer;
// }
