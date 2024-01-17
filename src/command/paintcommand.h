#ifndef PAINTCOMMAND_H
#define PAINTCOMMAND_H

#include "command.h"
#include <QGraphicsPixmapItem>
#include <QPixmap>

class PaintCommand : public Command {
	QGraphicsPixmapItem *item;
	QPixmap prevPixmap;
	QPixmap newPixmap;

  public:
	PaintCommand(QGraphicsPixmapItem *item, const QPixmap &prevPixmap, const QPixmap &newPixmap);
	void execute() override;
	void undo() override;
};

#endif // PAINTCOMMAND_H
