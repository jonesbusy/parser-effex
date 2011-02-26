#include "Core/FunctionsView.h"

FunctionsView::FunctionsView(double xMin, double xMax, double yMin, double yMax, QWidget* parent) : QGraphicsView(parent), displayMode(FunctionsView::FreeLook), markerPen(Qt::DashLine), mouseButtonPressed(Qt::NoButton), antialiasing(false), isMoving(false)
{
    // Style de bordures
    this->setFrameStyle(QFrame::Box | QFrame::Sunken);
    this->setContentsMargins(0, 0, 0, 0);

    // Rendu OpenGL
    // this->setViewport(new QGLWidget(QGLFormat(QGL::SampleBuffers)));

    // Limites...
    if (xMin < X_MIN_LIMIT)

        xMin = X_MIN_LIMIT;

    if (xMax > X_MAX_LIMIT)

        xMax = X_MAX_LIMIT;

    if (yMin < Y_MIN_LIMIT)

        yMin = Y_MIN_LIMIT;

    if (yMax > Y_MAX_LIMIT)

        yMax = Y_MAX_LIMIT;

    // Création de scène graphique interne
    this->setScene(new QGraphicsScene(QRectF(xMin, yMin, xMax - xMin, yMax - yMin)));

    // Optimisaion pour la scène graphique dynamique
    this->scene()->setItemIndexMethod(QGraphicsScene::NoIndex);

    // Inversion de l'axe Y
    this->scale(1, -1);

    // Centrer et adapter la scène
    this->fitInView(this->sceneRect(), Qt::IgnoreAspectRatio);

    // Paramètres de rendu
    this->setAntialiasing(this->antialiasing);
    this->setViewportUpdateMode(QGraphicsView::MinimalViewportUpdate);

    // Couleur des marqueurs
    this->markerPen.setColor(QColor(10, 50, 255));

    // Grillage
    this->grid = new Grid();

    // Ajout du grillage à la scène
    this->scene()->addItem(this->grid);

    // Ligne de marquage en x
    this->xLine = new QGraphicsLineItem();

    // Paramètres de la ligne de marquage en x
    this->xLine->setVisible(false);
    this->xLine->setPen(this->markerPen);

    // Ajout de la ligne de marquage en x à la scène
    this->scene()->addItem(this->xLine);

    // Rectangle de zoom
    this->zoomRect = new QGraphicsRectItem();

    // Paramètres du rectangle de zoom
    this->zoomRect->setVisible(false);
    this->zoomRect->setPen(QPen(QColor(10, 50, 255)));
    this->zoomRect->setBrush(QBrush(QColor(150, 180, 240)));

    // Transparence du rectangle de zoom
    QGraphicsOpacityEffect* zoomRectOpacityEffect = new QGraphicsOpacityEffect();

    zoomRectOpacityEffect->setOpacity(0.5);

    this->zoomRect->setGraphicsEffect(zoomRectOpacityEffect);

    // Ajout du rectangle de zoom à la scène
    this->scene()->addItem(this->zoomRect);

    // Minuteur du redimensionnement
    this->resizeTimer = new QTimer(this);

    // Paramètres du minuteur du redimensionnement
    this->resizeTimer->setInterval(1000);
    this->resizeTimer->setSingleShot(true);

    QObject::connect(this->resizeTimer  , SIGNAL(timeout()),
                     this               , SLOT(resizeFinished()));
}

FunctionsView::~FunctionsView()
{
    for (int i = 0; i < this->functions.count(); i++)

        delete this->functions[i];
}

void FunctionsView::showAll()
{
    for (int i = 0; i < this->functions.count(); i++)

        this->functions[i]->setVisible(true);
}

void FunctionsView::showOnly(FunctionManager* functionManager)
{
    for (int i = 0; i < this->functions.count(); i++)

        this->functions[i]->setVisible(this->functions[i] == functionManager);
}

void FunctionsView::refresh()
{
    // Invocation de mise à jour à tous les gestionnaires de fonction
    for (int i = 0; i < this->functions.count(); i++)

        this->functions[i]->update(this->contentsRect().width());

    // Invocation de rafraîchissement à Windows
    // this->viewport()->update();
}

FunctionManager* FunctionsView::getFunctionManager(IExpression* function) const
{
    for (int i = 0; i < this->functions.count(); i++)

        if (this->functions[i]->equals(function))

            return this->functions[i];

    return NULL;
}

FunctionManager* FunctionsView::getFunctionManager(int index) const
{
    if (index >= 0 && index < this->functions.count())

        return this->functions[index];

    return NULL;
}

FunctionManager* FunctionsView::addFunction(IExpression* function)
{
    // Création d'un gestionnaire de fonction
    FunctionManager* functionManager = new FunctionManager(function, this->scene());

    // Mise à jour des données
    functionManager->update(this->contentsRect().width());

    QObject::connect(functionManager    , SIGNAL(itemAdded(FunctionManager*)),
                     this               , SLOT(functionItemModified(FunctionManager*)));

    QObject::connect(functionManager    , SIGNAL(itemRemoved(FunctionManager*)),
                     this               , SLOT(functionItemModified(FunctionManager*)));

    // Stockage du gestionnaire
    this->functions.push_back(functionManager);

    // Invocation de rafraîchissement à Windows
    this->viewport()->update();

    return functionManager;
}

bool FunctionsView::removeFunction(FunctionManager* functionManager)
{
    for (int i = 0; i < this->functions.count(); i++)

        if (this->functions[i] == functionManager)
        {
            this->removeFunction(i);

            return true;
        }

    return false;
}

bool FunctionsView::removeFunction(IExpression* function)
{
    for (int i = 0; i < this->functions.count(); i++)

        if (this->functions[i]->equals(function))
        {
            this->removeFunction(i);

            return true;
        }

    return false;
}

void FunctionsView::clearFunctions()
{
    for (int i = 0; i < this->functions.count(); i++)

        delete this->functions[i];

    this->functions.clear();
}

int FunctionsView::addMarker(double x)
{
    // Création d'un nouveau marqueur
    QGraphicsLineItem* lineItem = new QGraphicsLineItem(x, this->sceneRect().top(), x, this->sceneRect().bottom());

    // Paramètres du marqueur
    lineItem->setPen(this->markerPen);
    lineItem->setZValue(FunctionManager::getCurrentZValue() + 1);

    // Ajout du marqueur à la scène
    this->scene()->addItem(lineItem);

    // Stockage du marqueur
    this->markers.push_back(lineItem);

    return this->markers.count() - 1;
}

bool FunctionsView::removeMarker(int index)
{
    // Dépassement ?
    if (index < 0 || index >= this->markers.count())

        return false;

    this->scene()->removeItem(this->markers[index]);

    delete this->markers[index];

    this->markers.remove(index);

    return true;
}

void FunctionsView::clearMarkers()
{
    for (int i = 0; i < this->markers.count(); i++)
    {
        this->scene()->removeItem(this->markers[i]);

        delete this->markers[i];
    }

    this->markers.clear();
}

int FunctionsView::getDisplayMode() const
{
    return this->displayMode;
}

void FunctionsView::switchOn(DisplayMode displayMode)
{
    this->displayMode = displayMode;
}

bool FunctionsView::gridWithMarking() const
{
    return this->grid->getMarking();
}

void FunctionsView::setGridMarking(bool enabled)
{
    this->grid->setMarking(enabled);
}

bool FunctionsView::isAntialiasied() const
{
    return this->antialiasing;
}

void FunctionsView::setAntialiasing(bool enabled)
{
    this->antialiasing = enabled;

    this->setRenderHint(QPainter::Antialiasing, this->antialiasing);

    this->refresh();
}

void FunctionsView::setXLine(double x)
{
    this->xLine->setLine(QLineF(x, this->sceneRect().top(), x, this->sceneRect().bottom()));

    this->viewport()->update();
}

bool FunctionsView::xLineIsVisible() const
{
    return this->xLine->isVisible();
}

void FunctionsView::setXLineVisible(bool visible)
{
    if (this->antialiasing)

        this->setRenderHint(QPainter::Antialiasing, !visible);

    this->xLine->setVisible(visible);

    this->xLine->setZValue(FunctionManager::getCurrentZValue() + 1);

    this->setMouseTracking(visible);
}

void FunctionsView::setSceneRect(const QRectF& rect)
{
    // Dépassement horizontal ?
    if (rect.width() < 2 || rect.width() > X_MAX_LIMIT - X_MIN_LIMIT)

        return;

    // Dépassement vertical ?
    if (rect.height() < 2 || rect.height() > Y_MAX_LIMIT - Y_MIN_LIMIT)

        return;

    // Appel du parent
    QGraphicsView::setSceneRect(rect);

    // Modification de la scène
    this->scene()->setSceneRect(rect);

    // Mise à jour de tous les gestionnaires de fonction
    this->refresh();

    // Centrer et adapter la scène
    this->fitInView(this->sceneRect(), Qt::IgnoreAspectRatio);

    // Signal
    emit this->sceneMoved(this->sceneRect());
}

void FunctionsView::setSceneRect(qreal x, qreal y, qreal w, qreal h)
{
    this->setSceneRect(QRectF(x, y, w, h));
}

void FunctionsView::resizeFinished()
{
    // Réactivation de l'anticrénelage si besoin
    if (this->antialiasing && !this->isMoving)

        this->setRenderHint(QPainter::Antialiasing, true);
}

void FunctionsView::functionItemModified(FunctionManager* functionManager)
{
    functionManager->update(this->contentsRect().width());
}

void FunctionsView::zoom(const QPointF& centerPoint, double xFactor, double yFactor)
{
    // Nouvelle largeur et hauteur
    double width = this->sceneRect().width() * xFactor;
    double height = this->sceneRect().height() * yFactor;

    // Nouveau bord
    double x = centerPoint.x() - width / 2;
    double y = centerPoint.y() - height / 2;

    // Gestion des dépassements
    if (x + width > X_MAX_LIMIT)
    {
        width = X_MAX_LIMIT - X_MIN_LIMIT;

        x = X_MIN_LIMIT;
    }
    else if (x < X_MIN_LIMIT)

        x = X_MIN_LIMIT;

    if (y + height > Y_MAX_LIMIT)
    {
        height = Y_MAX_LIMIT - Y_MIN_LIMIT;

        y = Y_MIN_LIMIT;
    }
    else if (y < Y_MIN_LIMIT)

        y = Y_MIN_LIMIT;

    this->setSceneRect(x, y, width, height);
}

void FunctionsView::removeFunction(int index)
{
    delete this->functions[index];

    this->functions.remove(index);
}

QGraphicsScene* FunctionsView::scene() const
{
    return QGraphicsView::scene();
}

void FunctionsView::setScene(QGraphicsScene* scene)
{
    QGraphicsView::setScene(scene);
}

void FunctionsView::resizeEvent(QResizeEvent* event)
{
    QGraphicsView::resizeEvent(event);

    // Désactiver l'anticrénelage s'il est activé
    if (this->antialiasing)
    {
        this->resizeTimer->stop();

        this->setRenderHint(QPainter::Antialiasing, false);
    }

    // Si la largeur a été modifiée, mettre à jour toutes les fonctions
    if (event->oldSize().width() != event->size().width())

        this->refresh();

    // Centrer et adapter la scène
    this->fitInView(this->sceneRect(), Qt::IgnoreAspectRatio);

    // Enclencher le processus de réactivation de l'anticrénelage
    if (this->antialiasing)

        this->resizeTimer->start();
}

void FunctionsView::mousePressEvent(QMouseEvent* event)
{
    QGraphicsView::mousePressEvent(event);

    // Pas de traitement si le mode d'affichage n'est pas libre
    if (this->displayMode != FunctionsView::FreeLook)

        return;

    // Sauvegarde du bouton de souris
    this->mouseButtonPressed = event->button();

    // Désactiver le rectangle de zoom (bug)
    this->zoomRect->setVisible(false);
    this->zoomRect->setRect(0, 0, 0, 0);

    // Clic gauche (déplacement)
    if (this->mouseButtonPressed == Qt::LeftButton)
    {
        this->setCursor(Qt::ClosedHandCursor);

        if (this->antialiasing)

            this->setRenderHint(QPainter::Antialiasing, false);

        this->isMoving = true;

        this->mouseGrab = event->pos();
    }
    // Clic droit (zoom cadré)
    else if (this->mouseButtonPressed == Qt::RightButton)
    {
        this->setCursor(Qt::CrossCursor);

        QPointF currentPosition = this->mapToScene(event->pos());

        this->zoomRect->setRect(currentPosition.x(), currentPosition.y(), 0, 0);

        this->zoomRect->setVisible(true);
    }
}

void FunctionsView::mouseDoubleClickEvent(QMouseEvent* event)
{
    QGraphicsView::mouseDoubleClickEvent(event);

    // Pas de traitement si le mode d'affichage n'est pas libre
    if (this->displayMode != FunctionsView::FreeLook)

        return;

    // Clics gauche (zoom avant)
    if (event->button() == Qt::LeftButton)

        this->zoom(this->mapToScene(event->pos()), 0.75, 0.75);

    // Clics droit (zoom arrière)
    else if (event->button() == Qt::RightButton)

        this->zoom(this->mapToScene(event->pos()), 1.5, 1.5);
}

void FunctionsView::mouseReleaseEvent(QMouseEvent* event)
{
    QGraphicsView::mouseReleaseEvent(event);

    // Pas de traitement si le mode d'affichage n'est pas libre (juste un signal)
    if (this->displayMode != FunctionsView::FreeLook)
    {
        emit this->clicked(event, this->mapToScene(event->x(), event->y()));

        return;
    }

    this->setCursor(Qt::ArrowCursor);

    if (this->antialiasing)

        this->setRenderHint(QPainter::Antialiasing, true);

    // Clic gauche (fin du déplacement)
    if (this->mouseButtonPressed == Qt::LeftButton)

        this->isMoving = false;

    // Clic droit (fin du zoom cadré)
    else if (this->mouseButtonPressed == Qt::RightButton)
    {
        double width = fabs(this->zoomRect->rect().width());
        double height = fabs(this->zoomRect->rect().height());

        if (width >= 1 && height >= 1)

            this->zoom(this->zoomRect->rect().center(), width / this->sceneRect().width(), height / this->sceneRect().height());

        this->zoomRect->setVisible(false);
        this->zoomRect->setRect(0, 0, 0, 0);
    }

    this->mouseButtonPressed = Qt::NoButton;
}

void FunctionsView::mouseMoveEvent(QMouseEvent* event)
{
    QGraphicsView::mouseMoveEvent(event);

    // Déplacement avec la souris de la ligne de marquage en x si elle est visible
    if (this->xLine->isVisible())
    {
        double x = this->mapToScene(event->pos()).x();

        this->xLine->setLine(QLineF(x, this->sceneRect().top(), x, this->sceneRect().bottom()));

        this->viewport()->update();

        emit this->xLineMoved(x);
    }

    // Pas d'autres traitements si le mode d'affichage n'est pas libre
    if (this->displayMode != FunctionsView::FreeLook)

        return;

    if (this->mouseButtonPressed == Qt::LeftButton)
    {
        // Calcul du déplacement de la souris
        QPointF moving = this->mapToScene(this->mouseGrab) - this->mapToScene(event->pos());

        double x = this->sceneRect().x() + moving.x();
        double y = this->sceneRect().y() + moving.y();

        // Dépassement horizontal ?
        if (x + this->sceneRect().width() > X_MAX_LIMIT || x < X_MIN_LIMIT)

            x = this->sceneRect().x();

        // Dépassement vertical ?
        if (y + this->sceneRect().height() > Y_MAX_LIMIT || y < Y_MIN_LIMIT)

            y = this->sceneRect().y();

        this->setSceneRect(x, y, this->sceneRect().width(), this->sceneRect().height());

        this->mouseGrab = event->pos();
    }
    else if (this->mouseButtonPressed == Qt::RightButton)
    {
        QPointF currentPosition = this->mapToScene(event->pos());

        this->zoomRect->setRect(this->zoomRect->rect().x(),
                                this->zoomRect->rect().y(),
                                currentPosition.x() - this->zoomRect->rect().x(),
                                currentPosition.y() - this->zoomRect->rect().y());
    }
}

void FunctionsView::wheelEvent(QWheelEvent* event)
{
    QGraphicsView::wheelEvent(event);

    // Pas de traitement si le mode d'affichage n'est pas libre
    if (this->displayMode != FunctionsView::FreeLook || event->orientation() != Qt::Vertical)

        return;

    // Zoom avant
    if (event->delta() > 0)

        this->zoom(this->sceneRect().center(), 0.75, 0.75);

    // Zoom arrière
    else if (event->delta() < 0)

        this->zoom(this->sceneRect().center(), 1.5, 1.5);
}
