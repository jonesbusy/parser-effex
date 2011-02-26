#include "Rendering/FunctionRender.h"

FunctionRender::FunctionRender(IExpression* function, QGraphicsScene* scene) : FunctionGraphics(function, scene)
{
}

void FunctionRender::compute(QRectF* bounds, int accuracy)
{
    // Effacement de tous les points
    this->points.clear();

    // Calcul d'un nouveau delta
    this->setYDelta(bounds);

    // Incrément
    double increment = bounds->width() / accuracy;

    // Point courant
    double x = bounds->left();
    double y = this->eval(bounds, x, &this->cases1);

    // Statut courant
    int status = this->getStatus(bounds, y);

    // Point précédent
    double previousX = 0;
    double previousY = 0;

    // Statut précédent
    int previousStatus = UNDEFINED;

    // Point hors écran
    double xHoldOffScreen = POINT_OFF_SCREEN;
    double yHoldOffScreen = 0;

    // Statut hors écran
    int statusHoldOffScreen = UNDEFINED;

    // Ajouter le premier point ?
    if (status == ONSCREEN)

        this->points.push_back(QPointF(x, y));

    else if (status != UNDEFINED)
    {
        xHoldOffScreen = x;
        yHoldOffScreen = y;

        statusHoldOffScreen = status;
    }

    // Limite en x
    double xLimit = bounds->right();

    // Parcours de toute la largeur de la scène
    while (x < xLimit)
    {
        // Sauvegarde de l'ancien point
        previousX = x;
        previousY = y;

        // Sauvegarde de l'ancien statut
        previousStatus = status;

        // Incrémentation
        x += 3 * increment;

        // Dépassement ?
        if (x > xLimit)

            x = xLimit;

        // Résultat
        y = this->eval(bounds, x, &this->cases2);

        // Statut actuel
        status = this->getStatus(bounds, y);

        // Traitement des différents cas
        if (status == UNDEFINED)
        {
            if (previousStatus != UNDEFINED)
            {
                if (previousStatus == ONSCREEN)

                    this->domainEndpoint(bounds, previousX, x, previousY, y, previousStatus, status, 1);

                else if (this->isDrawable(xHoldOffScreen))

                    this->points.push_back(QPointF(xHoldOffScreen, yHoldOffScreen));

                this->points.push_back(QPointF(POINT_OFF_SCREEN, 0));

                xHoldOffScreen = POINT_OFF_SCREEN;
            }
        }
        else if (previousStatus == UNDEFINED)
        {
            if (status == ONSCREEN)
            {
                this->domainEndpoint(bounds, previousX, x, previousY, y, previousStatus, status, 1);

                this->points.push_back(QPointF(x, y));

                xHoldOffScreen = POINT_OFF_SCREEN;
            }
            else
            {
                xHoldOffScreen = x;
                yHoldOffScreen = y;

                statusHoldOffScreen = status;
            }
        }
        else if (this->cases1.equals(this->cases2))
        {
            if (status == ONSCREEN)
            {
                if (this->isDrawable(xHoldOffScreen))
                {
                    this->points.push_back(QPointF(xHoldOffScreen, yHoldOffScreen));

                    xHoldOffScreen = POINT_OFF_SCREEN;
                }

                this->points.push_back(QPointF(x, y));
            }
            else
            {
                if (this->isDrawable(xHoldOffScreen))
                {
                    if (status != statusHoldOffScreen)
                    {
                        // Un au-dessus, un en-dessous
                        this->points.push_back(QPointF(xHoldOffScreen, yHoldOffScreen));
                        this->points.push_back(QPointF(x, y));
                        this->points.push_back(QPointF(POINT_OFF_SCREEN, 0));
                    }
                }
                else

                    this->points.push_back(QPointF(x, y));

                xHoldOffScreen = x;
                yHoldOffScreen = y;

                statusHoldOffScreen = status;
            }
        }
        else // Discontinuité
        {
            if (previousStatus == ABOVE || previousStatus == BELOW)
            {
                if (status == previousStatus)
                {
                    if (this->isDrawable(xHoldOffScreen))
                    {
                        this->points.push_back(QPointF(xHoldOffScreen, yHoldOffScreen));
                        this->points.push_back(QPointF(POINT_OFF_SCREEN, 0));
                    }

                    xHoldOffScreen = x;
                    yHoldOffScreen = y;

                    statusHoldOffScreen = status;

                }
                else if (status == ONSCREEN)
                {
                    // Discontinuité peut-être visible
                    if (this->isDrawable(xHoldOffScreen))
                    {
                        this->points.push_back(QPointF(xHoldOffScreen, yHoldOffScreen));

                        xHoldOffScreen = POINT_OFF_SCREEN;
                    }

                    this->discontinuity(bounds, previousX, x, previousY, y, previousStatus, status, 1);

                    y = this->eval(bounds, x, &this->cases2);

                    this->points.push_back(QPointF(x, y));
                }
                else
                {
                    // Statut actuel est ABOVE ou BELOW, opposé au statut précédent; juste faire un saut...
                    if (this->isDrawable(xHoldOffScreen))

                        this->points.push_back(QPointF(xHoldOffScreen, yHoldOffScreen));

                    this->points.push_back(QPointF(POINT_OFF_SCREEN, 0));

                    xHoldOffScreen = x;
                    yHoldOffScreen = y;

                    statusHoldOffScreen = status;
                }
            }
            else
            {
                // Le statut précédent est ONSCREEN; discontinuité peut-être visible
                this->discontinuity(bounds, previousX, x, previousY, y, previousStatus, status, 1);

                y = this->eval(bounds, x, &this->cases2);

                if (status == ONSCREEN)
                {
                    this->points.push_back(QPointF(x, y));

                    xHoldOffScreen = POINT_OFF_SCREEN;
                }
                else
                {
                    xHoldOffScreen = x;
                    yHoldOffScreen = y;

                    statusHoldOffScreen = status;
                }
            }
        }

        // Echange des deux "cases"
        Cases casesTemp = this->cases2;
        this->cases2    = this->cases1;
        this->cases1    = casesTemp;
    }

    /*
    for (int i = 0; i < this->points.size(); i++)

        printf("Point : %lf %lf\n", this->points.at(i).x(), this->points.at(i).y());
    */

    // Création d'une nouvelle trajectoire
    this->createPath();
}

QRectF FunctionRender::boundingRect() const
{
    return this->path.boundingRect();
}

void FunctionRender::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
    // Pinceau
    painter->setPen(this->getPen());

    // Dessin de la trajectoire
    painter->drawPath(this->path);
}

void FunctionRender::createPath()
{
    // Nouvelle trajectoire
    this->path = QPainterPath();

    // Ne pas continuer s'il n'y a pas au moins deux points
    if (this->points.count() < 2)

        return;

    // Commencement au premier point
    this->path.moveTo(this->points[0]);

    // Parcours de tous les points
    for (register int i = 1; i < this->points.count(); i++)
    {
        // Point à l'écran ?
        if (this->isOnScreen(i))

            // Tirer un trait
            this->path.lineTo(this->points[i]);

        else
        {
            // Recherche du prochain point affichable
            do
            {
                i++;
            }
            while (i < this->points.count() && !this->isOnScreen(i));

            // Saut au prochain point
            if (i < this->points.count())

                this->path.moveTo(this->points[i]);
        }
    }

    // Invoque un rafraîchissement d'affichage
    this->update();
}

bool FunctionRender::isOnScreen(int index) const
{
    return this->isDrawable(this->points[index].x());
}

bool FunctionRender::isDrawable(double value) const
{
    return value > (POINT_OFF_SCREEN + POINT_OFF_SCREEN_DELTA);
}

void FunctionRender::discontinuity(QRectF* bounds, double x1, double x2, double y1, double y2, int status1, int status2, int depth)
{
    // Profondeur maximale de la récursivité atteinte ?
    if (depth == MAX_DEPTH)
    {
        this->points.push_back(QPointF(x1, y1));
        this->points.push_back(QPointF(POINT_OFF_SCREEN, 0));
        this->points.push_back(QPointF(x2, y2));
    }
    else
    {
        double xMiddle = (x1 + x2) / 2;

        y1 = this->eval(bounds, x1, &this->cases1);

        double yMiddle = this->eval(bounds, xMiddle, &this->cases2);

        bool casesEquals1 = this->cases1.equals(this->cases2);

        y2 = this->eval(bounds, x2, &this->cases1);

        bool casesEquals2 = this->cases1.equals(this->cases2);

        int statusMiddle = this->getStatus(bounds, yMiddle);

        if (statusMiddle == UNDEFINED)
        {
            if (status1 == ONSCREEN)

                this->domainEndpoint(bounds, x1, xMiddle, y1, yMiddle, status1, statusMiddle, 1);

            this->points.push_back(QPointF(POINT_OFF_SCREEN, 0));

            if (status2 == ONSCREEN)

                this->domainEndpoint(bounds, xMiddle, x2, yMiddle, y2, statusMiddle, status2, 1);
        }
        else if (!casesEquals1)
        {
            this->discontinuity(bounds, x1, xMiddle, y1, yMiddle, status1, statusMiddle, depth + 1);

            // Double discontinuité
            if (!casesEquals2)

                this->discontinuity(bounds, xMiddle, x2, yMiddle, y2, statusMiddle, status2, depth + 1);
        }
        else if (!casesEquals2)

            this->discontinuity(bounds, xMiddle, x2, yMiddle, y2, statusMiddle, status2, depth + 1);
        /*
        else

            printf(" [ FunctionRender - Error ] - Discontinuity @ ( %f , %f )\n", x1, x2);
        */
    }
}

void FunctionRender::domainEndpoint(QRectF* bounds, double x1, double x2, double y1, double y2, int status1, int status2, int depth)
{
    // Profondeur maximale de la récursivité atteinte ?
    if (depth == 2 * MAX_DEPTH)
    {
        if (status1 == ONSCREEN)

            this->points.push_back(QPointF(x1, y1));

        else // status2 == ONSCREEN

            this->points.push_back(QPointF(x2, y2));
    }
    else
    {
        double xMiddle = (x1 + x2) / 2;
        double yMiddle = this->eval(bounds, xMiddle);

        int statusMiddle = this->getStatus(bounds, yMiddle);

        if (statusMiddle == ABOVE || statusMiddle == BELOW)

            this->points.push_back(QPointF(xMiddle, yMiddle));

        else if (statusMiddle == status1) // statusMiddle == ONSCREEN || UNDEFINED

            this->domainEndpoint(bounds, xMiddle, x2, yMiddle, y2, statusMiddle, status2, depth + 1);

        else

            this->domainEndpoint(bounds, x1, xMiddle, y1, yMiddle, status1, statusMiddle, depth + 1);
    }
}
