#include "clklabel.h"

void Clickable::mousePressEvent(QMouseEvent* event)
{
    emit clicked();
}
