#ifndef COMPOUNDPAINTCOMMAND_H
#define COMPOUNDPAINTCOMMAND_H

#include "command.h"
#include <QGraphicsPixmapItem>
#include <QList>

class CompoundPaintCommand : public Command {
	QList<QGraphicsPixmapItem *> items;       // List of affected items
	QList<QPixmap>               prevPixmaps; // List of previous pixmaps
	QList<QPixmap>               newPixmaps;  // List of new pixmaps

  public:
	CompoundPaintCommand(const QList<QGraphicsPixmapItem *> &items, const QList<QPixmap> &prevPixmaps, const QList<QPixmap> &newPixmaps);

	void execute() override;
	void undo() override;
};

#endif // COMPOUNDPAINTCOMMAND_H
