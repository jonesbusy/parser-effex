#include "Rendering/SurfaceRender.h"

SurfaceRender::SurfaceRender(IExpression* function, double x1, double x2, const ItemData& data, QGraphicsScene* scene) : FunctionItem(function, data, scene)
{
    // Inversion si besoin
    if (x2 >= x1)
    {
        this->x1 = x1;
        this->x2 = x2;
    }
    else
    {
        this->x1 = x2;
        this->x2 = x1;
    }

    // Effet de transparence
    QGraphicsOpacityEffect* effect = new QGraphicsOpacityEffect();

    // 60 % d'opacité | 40 % de transparence
    effect->setOpacity(0.6);

    this->setGraphicsEffect(effect);
}

void SurfaceRender::compute(QRectF* bounds, int accuracy)
{
    // Hors écran ?
    if (bounds->right() <= this->x1 || bounds->left() >= this->x2)
    {
        this->surface = QPolygonF();

        return;
    }

    // Calcul d'un nouveau delta
    this->setYDelta(bounds);

    // Optimisation des bords
    double x1 = (this->x1 > bounds->left()) ? this->x1 : bounds->left();
    double x2 = (this->x2 < bounds->right()) ? this->x2 : bounds->right();

    // Incrément
    double increment = (x2 - x1) / (((x2 - x1) / bounds->width()) * accuracy);

    // Recherche d'un côté gauche fiable
    while (true)
    {
        // Point y
        double y = this->eval(bounds, x1);

        // Côté gauche trouvé ?
        if (this->getStatus(bounds, y) != UNDEFINED)

            break;

        // Incrémentation
        x1 += increment;

        // Figure impossible à représenter ?
        if (x1 > x2)
        {
            this->surface = QPolygonF();

            return;
        }
    }

    // Valeur y de base (optimisation)
    double yBase = 0;

    if (bounds->top() > 0)

        yBase = bounds->top() - this->getYDelta();

    else if (bounds->bottom() < 0)

        yBase = bounds->bottom() + this->getYDelta();

    // Points du polygone
    QVector<QPointF> points;

    // Premier point
    points.push_back(QPointF(x1, yBase));

    // Limite en x
    double xLimit = x2 + increment / 2.0;

    // Calcul de tous les points
    for (double x = x1; x <= xLimit; x += increment)
    {
        double y = this->eval(bounds, x);

        if (this->getStatus(bounds, y) != UNDEFINED)

            points.push_back(QPointF(x, y));
    }

    // Dernier point
    points.push_back(QPointF(points.last().x(), yBase));

    // Création de la surface
    this->surface = QPolygonF(points);

    // Invoque un rafraîchissement d'affichage
    this->update();
}

void SurfaceRender::setColor(const QColor& color)
{
    // Couleurs intermédiaires
    QColor middleColor1 = color;
    QColor middleColor2 = color;

    middleColor1.setRed(middleColor1.red() / 1.1);
    middleColor1.setGreen(middleColor1.green() / 1.1);
    middleColor1.setBlue(middleColor1.blue() / 1.1);

    middleColor2.setRed(middleColor2.red() / 1.7);
    middleColor2.setGreen(middleColor2.green() / 1.7);
    middleColor2.setBlue(middleColor2.blue() / 1.7);

    // Nouveau dégradé
    this->gradient = QLinearGradient();

    gradient.setCoordinateMode(QGradient::ObjectBoundingMode);

    // Affectation des couleurs
    gradient.setColorAt(0.0, color);
    gradient.setColorAt(0.3, middleColor2);
    gradient.setColorAt(0.5, middleColor1);
    gradient.setColorAt(0.7, middleColor2);
    gradient.setColorAt(1.0, color);

    // Appel du parent
    FunctionItem::setColor(color);
}

QRectF SurfaceRender::boundingRect() const
{
    return this->surface.boundingRect();
}

void SurfaceRender::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
    // Surface non visible ?
    if (this->surface.isEmpty())

        return;

    // Pinceau
    painter->setPen(this->getPen());

    // Dégradé
    painter->setBrush(this->gradient);

    // Dessin de la surface
    painter->drawPolygon(this->surface);
}
