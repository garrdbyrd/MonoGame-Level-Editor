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
        layout->setLabelAlignment(Qt::AlignBaseline);
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
                // Left widget (label)
                QLabel* leftLabel = new QLabel(key);
                QWidget* leftContainer = new QWidget;
                QVBoxLayout* leftLayout = new QVBoxLayout(leftContainer);
                leftLayout->addWidget(leftLabel);
                leftLayout->setAlignment(Qt::AlignBottom);
                leftLayout->setContentsMargins(0, 0, 0, 0);
                // Right widget (custom widget)
                QWidget* rightContainer = new QWidget;
                QVBoxLayout* rightLayout = new QVBoxLayout(rightContainer);
                rightLayout->addWidget(settingWidget);
                rightLayout->setAlignment(Qt::AlignRight);
                rightLayout->setContentsMargins(0, 0, 0, 0);

                layout->addRow(leftContainer, rightContainer);
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
