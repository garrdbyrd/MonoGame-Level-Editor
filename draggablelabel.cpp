#include "draggablelabel.h"

void draggableLabel::mousePressEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        QDrag *drag = new QDrag(this);
        QMimeData *mimeData = new QMimeData;

        // Set the data to be dragged
        mimeData->setText("YourDataHere"); // Modify as needed
        drag->setMimeData(mimeData);
        drag->setPixmap(this->pixmap(Qt::ReturnByValue).scaled(48, 48)); // Thumbnail

        // Execute the drag
        Qt::DropAction dropAction = drag->exec(Qt::CopyAction | Qt::MoveAction);
    }
}
