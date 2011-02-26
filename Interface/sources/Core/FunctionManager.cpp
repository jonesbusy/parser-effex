#include "Core/FunctionManager.h"

int FunctionManager::currentZValue = 0;

FunctionManager::FunctionManager(IExpression* function, QGraphicsScene* scene) : function(function), scene(scene), functionRender(function), zValue(++FunctionManager::currentZValue)
{
    // Rendu de la fonction juste devant les éléments graphique associés
    this->functionRender.setZValue(this->zValue + 0.5);

    // Ajout du rendu de la fonction à la scène
    this->scene->addItem(&this->functionRender);
}

FunctionManager::~FunctionManager()
{
    // Suppression de tous les éléments graphique
    this->clearItems();

    // Suppression du rendu de la fonction
    this->scene->removeItem(&this->functionRender);

    // Suppression de la fonction
    delete this->function;
}

void FunctionManager::update(int accuracy)
{
    // Bornes
    QRectF bounds = this->scene->sceneRect();

    // Optimisation des bornes
    FunctionGraphics::optimizeBounds(&bounds);

    // Calcul du nouveau rendu de la fonction
    this->functionRender.compute(&bounds, accuracy);

    // Mise à jour des éléments graphique
    for (int i = 0; i < this->items.count(); i++)

        this->items[i]->compute(&bounds, accuracy);
}

int FunctionManager::addIntegral(const QString& name, double x1, double x2)
{
    double integral = MathTools::integral(this->function, x1, x2);

    return this->addItem(new SurfaceRender(this->function, x1, x2, ItemData(name, this->generateDomain(x1, x2), integral)));
}

int FunctionManager::addTangent(const QString& name, double x)
{
    double tangent = MathTools::tangent(this->function, x);

    // Bug en compilation -O2
    // double xDomain = MathTools::setDecimal(x, 2);

    double xDomain = x;

    // Déplacement à gauche, troncation, puis déplacement à droite
    xDomain *= 100;
    xDomain = floor(xDomain);
    xDomain /= 100;

    return this->addItem(new TangentRender(this->function, x, tangent, ItemData(name, QString::number(xDomain, 'g', 6), tangent)));
}

int FunctionManager::addZero(const QString& name, double x1, double x2)
{
    double zero = MathTools::zero(this->function, x1, x2);

    return this->addItem(new PointRender(this->function, zero, ItemData(name, this->generateDomain(x1, x2), zero)));
}

int FunctionManager::addMaximum(const QString& name, double x1, double x2)
{
    double maximum = MathTools::maximum(this->function, x1, x2);

    return this->addItem(new PointRender(this->function, maximum, ItemData(name, this->generateDomain(x1, x2), maximum)));
}

int FunctionManager::addMinimum(const QString& name, double x1, double x2)
{
    double minimum = MathTools::minimum(this->function, x1, x2);

    return this->addItem(new PointRender(this->function, minimum, ItemData(name, this->generateDomain(x1, x2), minimum)));
}

bool FunctionManager::removeItem(int index)
{
    // Dépassement ?
    if (index < 0 || index >= this->items.count())

        return false;

    // Suppression de la scène
    this->scene->removeItem(this->items[index]);

    // Suppression de l'objet
    delete this->items[index];

    this->items.remove(index);

    emit this->itemRemoved(this);

    return true;
}

void FunctionManager::clearItems()
{
    // Suppression de tous les éléments graphique
    for (int i = 0; i < this->items.count(); i++)
    {
        this->scene->removeItem(this->items[i]);

        delete this->items[i];
    }

    this->items.clear();
}

bool FunctionManager::equals(IExpression* function) const
{
    return this->function == function;
}

int FunctionManager::countItems() const
{
    return this->items.count();
}

ItemData FunctionManager::getItemData(int index) const
{
    // Dépassement ?
    if (index < 0 || index >= this->items.count())

        return ItemData("", "", 0);

    return this->items[index]->getData();
}

const QColor& FunctionManager::getColor() const
{
    return this->functionRender.getColor();
}

void FunctionManager::setColor(const QColor& color)
{
    this->functionRender.setColor(color);

    for (int i = 0; i < this->items.count(); i++)

        this->items[i]->setColor(color);
}

bool FunctionManager::isVisible() const
{
    return this->functionRender.isVisible();
}

void FunctionManager::setVisible(bool visible)
{
    this->functionRender.setVisible(visible);

    for (int i = 0; i < this->items.count(); i++)

        this->items[i]->setVisible(visible);
}

int FunctionManager::getCurrentZValue()
{
    return FunctionManager::currentZValue;
}

int FunctionManager::addItem(FunctionItem* item)
{
    // Même couleur de la fonction
    item->setColor(this->getColor());

    // Juste derrière la fonction
    item->setZValue(this->zValue);

    // Ajout aux tableau d'éléments
    this->items.push_back(item);

    // Ajout à la scène
    this->scene->addItem(item);

    emit this->itemAdded(this);

    return this->items.count() - 1;
}

QString FunctionManager::generateDomain(double x1, double x2) const
{
    if (x1 > x2)

        MathTools::reverse(x1, x2);

    // Bug en compilation -O2
    // double x1 = MathTools::setDecimal(x1, 2);
    // double x2 = MathTools::setDecimal(x2, 2);

    // Déplacement à gauche, troncation, puis déplacement à droite
    x1 *= 100;
    x1 = floor(x1);
    x1 /= 100;

    // Déplacement à gauche, troncation, puis déplacement à droite
    x2 *= 100;
    x2 = floor(x2);
    x2 /= 100;

    return "[ " + QString::number(x1, 'g', 6) + " , " + QString::number(x2, 'g', 6) + " ]";
}
