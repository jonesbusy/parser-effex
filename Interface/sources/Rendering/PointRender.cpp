#include "Rendering/PointRender.h"

PointRender::PointRender(IExpression* function, double x, const ItemData& data, QGraphicsScene* scene) : FunctionItem(function, data, scene), x(x), width(0), height(0)
{
}

void PointRender::compute(QRectF* bounds, int accuracy)
{
    // Nouveau point
    this->point = QPoint();

    // Pas représentable ?
    if (MathTools::isNaN(this->x))

        return;

    // Coordonnée y
    double y = this->eval(bounds, this->x);

    // Point visible ?
    if (this->getStatus(bounds, y) == ONSCREEN)
    {
        this->point.setX(this->x);
        this->point.setY(y);
    }

    // Taille relative à la scène
    this->width = bounds->width() / 150;
    this->height = this->width * (bounds->height() / bounds->width());

    // Invoque un rafraîchissement d'affichage
    this->update();
}

QRectF PointRender::boundingRect() const
{
    // Point nul ?
    if (this->point.isNull())

        return QRectF();

    return QRectF(this->point.x() - this->width, this->point.y() - this->height, 2 * this->width, 2 * this->height);
}

void PointRender::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
    // Point non visible ?
    if (this->point.isNull())

        return;

    // Pinceau
    painter->setPen(this->getPen());

    // Dessin du point
    painter->drawEllipse(this->point, this->width, this->height);
}
