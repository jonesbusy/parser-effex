#include "Rendering/FunctionGraphics.h"

FunctionGraphics::FunctionGraphics(IExpression* function, QGraphicsScene* scene) : QGraphicsItem(NULL, scene), function(function), yDelta(0.5)
{
}

const QColor& FunctionGraphics::getColor() const
{
    return this->color;
}

void FunctionGraphics::setColor(const QColor& color)
{
    this->color = color;

    this->pen.setColor(this->color);

    this->update();
}

void FunctionGraphics::optimizeBounds(QRectF* bounds)
{
    double middleYDelta = bounds->height() / (2 * Y_DELTA_ACCURACY);

    bounds->setTop(bounds->top() - middleYDelta);
    bounds->setBottom(bounds->bottom() + middleYDelta);
}

double FunctionGraphics::eval(QRectF* bounds, double x, Cases* cases) const
{
    if (cases != NULL)

        cases->clear();

    double y = this->function->eval(x, cases);

    if (MathTools::isNaN(y) || MathTools::isInfinity(y))

        return NaN;

    else if (y > bounds->bottom())

        return bounds->bottom() + this->yDelta;

    else if (y < bounds->top())

        return bounds->top() - this->yDelta;

    return y;
}

int FunctionGraphics::getStatus(QRectF* bounds, double y) const
{
    if (MathTools::isNaN(y))

        return UNDEFINED;

    else if (y > bounds->bottom())

        return ABOVE;

    else if (y < bounds->top())

        return BELOW;

    return ONSCREEN;
}

void FunctionGraphics::update()
{
    QGraphicsItem::update(this->boundingRect());
}

const QPen& FunctionGraphics::getPen() const
{
    return this->pen;
}

void FunctionGraphics::setPen(const QPen& pen)
{
    this->pen = pen;
}

double FunctionGraphics::getYDelta() const
{
    return this->yDelta;
}

void FunctionGraphics::setYDelta(QRectF* bounds)
{
    this->yDelta = bounds->height() / Y_DELTA_ACCURACY;
}
