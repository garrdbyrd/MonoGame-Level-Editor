#ifndef SCROLLMENU_H
#define SCROLLMENU_H

#include "qevent.h"
#include "selectablelabel.h"

class Caspian
{
    public:
    void populateScrollMenu();
    void labelClicked(SelectableLabel);
    void resizeEvent(QResizeEvent);
};

#endif  // SCROLLMENU_H
