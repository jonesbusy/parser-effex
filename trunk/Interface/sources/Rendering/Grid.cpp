#include "Rendering/Grid.h"

Grid::Grid() : axesPen(Qt::SolidLine), linesPen(Qt::DashLine), marking(true), markingIsChanging(false)
{
    this->setZValue(0);

    this->axesPen.setColor(QColor(50, 50, 50));
    this->linesPen.setColor(QColor(185, 185, 185));
}

bool Grid::getMarking() const
{
    return this->marking;
}

void Grid::setMarking(bool enabled)
{
    // Optimisation du rafraîchissement
    if (this->marking)
    {
        this->markingIsChanging = true;

        this->update(this->sceneBoundingRect());

        this->marking = enabled;
    }
    else
    {
        this->marking = enabled;

        this->update(this->sceneBoundingRect());
    }
}

QRectF Grid::boundingRect() const
{
    if (!this->marking && !this->markingIsChanging)
    {
        bool xVisible = this->scene()->sceneRect().y() <= 0 && this->scene()->sceneRect().y() + this->scene()->sceneRect().height() > 0;
        bool yVisible = this->scene()->sceneRect().x() <= 0 && this->scene()->sceneRect().x() + this->scene()->sceneRect().width() > 0;

        if (!xVisible && !yVisible)

            return QRectF();

        else if (xVisible)

            return QRectF(this->scene()->sceneRect().left(), -1, this->scene()->sceneRect().right(), 1);

        else if (yVisible)

            return QRectF(-1, this->scene()->sceneRect().top(), 1, this->scene()->sceneRect().bottom());
    }

    return this->scene()->sceneRect();
}

void Grid::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
    QPainter::RenderHints renderHints = painter->renderHints();

    painter->setRenderHint(QPainter::Antialiasing, false);

    if (this->marking && !this->markingIsChanging)
    {
        int scaleIncrementX = (int)(this->scene()->sceneRect().width() / 20);
        int scaleIncrementY = (int)(this->scene()->sceneRect().height() / 20);

        scaleIncrementX = (scaleIncrementX < 1) ? 1 : scaleIncrementX;
        scaleIncrementY = (scaleIncrementY < 1) ? 1 : scaleIncrementY;

        // Pinceau
        painter->setPen(this->linesPen);

        painter->scale(1, -1);

        for (int x = scaleIncrementX; x <= this->scene()->sceneRect().right(); x += scaleIncrementX)

            if (x >= this->scene()->sceneRect().left())

                painter->drawLine(QLineF(x, -this->scene()->sceneRect().top(), x, -this->scene()->sceneRect().bottom()));

        for (int x = -scaleIncrementX; x >= this->scene()->sceneRect().left(); x -= scaleIncrementX)

            if (x <= this->scene()->sceneRect().right())

                painter->drawLine(QLineF(x, -this->scene()->sceneRect().top(), x, -this->scene()->sceneRect().bottom()));

        for (int y = scaleIncrementY; y <= this->scene()->sceneRect().bottom(); y += scaleIncrementY)

            if (y >= this->scene()->sceneRect().top())

                painter->drawLine(QLineF(this->scene()->sceneRect().left(), -y, this->scene()->sceneRect().right(), -y));

        for (int y = -scaleIncrementY; y >= this->scene()->sceneRect().top(); y -= scaleIncrementY)

            if (y <= this->scene()->sceneRect().bottom())

                painter->drawLine(QLineF(this->scene()->sceneRect().left(), -y, this->scene()->sceneRect().right(), -y));

        painter->scale(1, -1);
    }

    if (this->markingIsChanging)

        this->markingIsChanging = false;

    // Pinceau
    painter->setPen(this->axesPen);

    // Axe x
    painter->drawLine(QLineF(this->scene()->sceneRect().left(), 0, this->scene()->sceneRect().right(), 0));

    // Axe y
    painter->drawLine(QLineF(0, this->scene()->sceneRect().top(), 0, this->scene()->sceneRect().bottom()));

    painter->setRenderHints(renderHints, true);
}
