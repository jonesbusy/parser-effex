#include "Rendering/TangentRender.h"

TangentRender::TangentRender(IExpression* function, double x, double tangent, const ItemData& data, QGraphicsScene* scene) : FunctionItem(function, data, scene), x(x), tangent(tangent)
{
    this->setPen(QPen(Qt::DashDotDotLine));
}

void TangentRender::compute(QRectF* bounds, int accuracy)
{
    // Hors écran ?
    if (x < bounds->left() || x > bounds->right() || this->getStatus(bounds, this->eval(bounds, this->x)) != ONSCREEN)
    {
        this->line = QLineF();

        return;
    }

    // Distance entre la fonction de base et la dérivée
    double delta = this->eval(bounds, this->x) - (this->x * this->tangent);

    // Fonction réciproque de y1
    double x1 = (bounds->top() - delta) / this->tangent;
    double y1 = bounds->top();

    // Fonction réciproque de y2
    double x2 = (bounds->bottom() - delta) / this->tangent;
    double y2 = bounds->bottom();

    // Tangente == 0 ?
    if (MathTools::isNaN(x1) || MathTools::isInfinity(x1) || MathTools::isNaN(x2) || MathTools::isInfinity(x2))
    {
        x1 = bounds->left();
        y1 = x1 * this->tangent + delta;

        x2 = bounds->right();
        y2 = x2 * this->tangent + delta;
    }
    else
    {
        // Optimisation de x1...
        if (x1 < bounds->left() || x1 > bounds->right())
        {
            x1 = (x1 < bounds->left()) ? bounds->left() : bounds->right();
            y1 = x1 * this->tangent + delta;
        }

        // Optimisation de x2...
        if (x2 < bounds->left() || x2 > bounds->right())
        {
            x2 = (x2 < bounds->left()) ? bounds->left() : bounds->right();
            y2 = x2 * this->tangent + delta;
        }

        // Inversion nécessaire ?
        if (x1 > x2)
        {
            MathTools::reverse(x1, x2);
            MathTools::reverse(y1, y2);
        }
    }

    // Création de la tangente
    this->line = QLineF(x1, y1, x2, y2);

    // Invoque un rafraîchissement d'affichage
    this->update();
}

QRectF TangentRender::boundingRect() const
{
    if (this->line.isNull())

        return QRectF();

    if (this->line.y1() > this->line.y2())

        return QRectF(this->line.x1(), this->line.y2(), this->line.x2() - this->line.x1(), this->line.y1() - this->line.y2());

    return QRectF(this->line.x1(), this->line.y1(), this->line.x2() - this->line.x1(), this->line.y2() - this->line.y1());
}

void TangentRender::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
    // Tangente non visible ?
    if (this->line.isNull())

        return;

    // Pinceau
    painter->setPen(this->getPen());

    // Dessin de la tengante
    painter->drawLine(this->line);
}
