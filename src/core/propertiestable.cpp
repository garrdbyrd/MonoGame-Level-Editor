#include <cstdio>
#include "./ui_caspian.h"
#include "caspian.h"

void Caspian::setPropertiesTable()
{
    QStringList headers;
    headers << "Property"
            << "Value";
    ui->selectedProperties->setHorizontalHeaderLabels(headers);
    ui->selectedProperties->horizontalHeader()->setDefaultAlignment(
        Qt::AlignLeft
    );

    // Chunk to make column 1 read-only
    int rowCount = ui->selectedProperties->rowCount();
    for (int row = 0; row < rowCount; ++row) {
        QTableWidgetItem *item = ui->selectedProperties->item(row, 0);
        if (!item) {
            item = new QTableWidgetItem();
            ui->selectedProperties->setItem(row, 0, item);
        }
        item->setFlags(item->flags() & ~Qt::ItemIsEditable);
    }

    // Chunk for default values in column 2
    for (int row = 0; row < rowCount; ++row) {
        QString defaultValue = QString("Value%1").arg(row);

        QTableWidgetItem *item = ui->selectedProperties->item(row, 1);
        if (!item) {
            item = new QTableWidgetItem(defaultValue);
            ui->selectedProperties->setItem(row, 1, item);
        } else {
            item->setText(defaultValue);
        }
    }
}