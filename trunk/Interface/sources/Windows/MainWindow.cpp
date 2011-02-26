#include "Windows/MainWindow.h"

MainWindow::MainWindow() : currentFonction(NULL), parser(""), currentAction(NONE), sceneClicks(0), takeTowPoints(true), currentX1(0), currentX2(0), cursorPosition(0), selection("")
{
    // Titre de la fenêtre
    this->setWindowTitle("Effex");

    // Positionnement
    this->setMinimumSize(1100, 700);
    this->setGeometry(100, 100, 1100, 700);
    this->setWindowState(Qt::WindowMaximized);

    // Couleurs par défaut des fonctions
    this->functionsColors[0] = QColor(0, 40, 255);
    this->functionsColors[1] = QColor(255, 0, 0);
    this->functionsColors[2] = QColor(0, 170, 0);
    this->functionsColors[3] = QColor(230, 0, 210);
    this->functionsColors[4] = QColor(240, 150, 0);

    // Widget central
    this->setCentralWidget(new QWidget());

    // Création de la structure principale
    this->createMainStructure();

    // Création du panneau de contrôle
    this->createControlPanel();

    // Création du panneau de rendu
    this->createRenderPanel();

    // Création des actions
    this->createActions();

    // Création du menu
    this->createMenu();

    // Ajout de la structure principale au Widget central
    this->centralWidget()->setLayout(this->mainLayout);

    // Focus sur l'édition de fonction
    this->functionLineEdit->setFocus();
}

void MainWindow::functionSelected(int index)
{
    // Plus de fonction ?
    if (index == -1)

        return;

    // Récupèration de la fonction (managée)
    this->currentFonction = this->functionsView->getFunctionManager(index);

    // Affichage exclusif ?
    if (this->onlyOneCheckBox->isChecked())

        this->functionsView->showOnly(this->currentFonction);

    this->clearResultTable();

    this->refreshResultTable();
}

void MainWindow::insertFunction()
{
    static int count;

    if (this->functionLineEdit->text().trimmed().isEmpty())

        return;

    // Ajout de la fonction courante au parseur
    this->parser.setInput(this->functionLineEdit->text().toStdString());

    // Parsage et enregistrement de l'expression
    IExpression* expression = this->parser.parse();

    // Boîte de message d'erreur
    QMessageBox messageBox;

    messageBox.setIcon(QMessageBox::Warning);
    messageBox.setStandardButtons(QMessageBox::Ok);
    messageBox.setDefaultButton(QMessageBox::Ok);

    // Erreur de parsage ou maximum de fonctions atteint
    if (expression == NULL)
    {
        messageBox.setText("Fonction incorrecte !\nVeuillez vérifier la syntaxe de votre fonction.");

        messageBox.exec();

        this->functionLineEdit->setFocus();

        return;
    }
    else if (this->functionsComboBox->count() >= MAX_FUNCTIONS)
    {
        messageBox.setText("Vous avez atteint le nombre maximum de fonctions.");
        messageBox.setInformativeText("Si vous voulez ajouter une fonction, veuillez en supprimer une autre.");

        messageBox.exec();

        this->functionLineEdit->setFocus();

        return;
    }

    // Création de la fonction
    this->currentFonction = this->functionsView->addFunction(expression);

    // Couleur par défaut de la fonction
    this->currentFonction->setColor(this->functionsColors[count++ % MAX_FUNCTIONS]);

    // Ajout de la fonction à la liste déroulante
    this->functionsComboBox->addItem(this->functionLineEdit->text().trimmed());
    this->functionsComboBox->setCurrentIndex(this->functionsComboBox->count() - 1);

    // Effacement de la zone de texte
    this->functionLineEdit->clear();

    // Activation des menus des fonctions et des opérations
    this->functionsMenu->setEnabled(true);
    this->operationsMenu->setEnabled(true);

    // Activation du groupe de fonctions
    this->functionBox->setEnabled(true);
}

void MainWindow::changeFunctionColor()
{
    // Boîte de couleurs
    QColorDialog colorDialog;

    // Couleur de la fonction
    colorDialog.setCurrentColor(this->currentFonction->getColor());

    // Couleur refusée ?
    if (colorDialog.exec() != QColorDialog::Accepted)

        return;

    // Enregistrement de la couleur
    this->currentFonction->setColor(colorDialog.currentColor());
}

void MainWindow::deleteFonction()
{
    // Fonction(s) existante(s) ?
    if (this->functionsComboBox->currentIndex() != -1)
    {
        // Boîte de message
        QMessageBox messageBox;

        messageBox.setIcon(QMessageBox::Question);
        messageBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
        messageBox.setDefaultButton(QMessageBox::No);
        messageBox.setText("Voulez-vous vraiment supprimer la fonction : " + this->functionsComboBox->currentText() + " ?");

        // Refusé ?
        if (messageBox.exec() != QMessageBox::Yes)

            return;

        // Effacement de la fonction
        this->functionsView->removeFunction(this->currentFonction);

        // Effacement de la fonction à la liste déroulante
        this->functionsComboBox->removeItem(this->functionsComboBox->currentIndex());
    }

    this->checkFunctionState();
}

void MainWindow::clearFunctions()
{
    // Boîte de message
    QMessageBox messageBox;

    messageBox.setIcon(QMessageBox::Question);
    messageBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    messageBox.setDefaultButton(QMessageBox::No);
    messageBox.setText("Voulez-vous vraiment supprimer <u>toutes</u> les fonctions ?");

    // Accepté ?
    if (messageBox.exec() == QMessageBox::Yes)
    {
        this->functionsView->clearFunctions();

        this->functionsComboBox->clear();

        this->checkFunctionState();
    }
}

void MainWindow::doIntegral(bool enabled)
{
    this->currentAction = (enabled) ? INTEGRAL : NONE;
    this->takeTowPoints = true;

    this->setAllButtons(!enabled, this->integralButton);

    this->doAction(enabled);
}

void MainWindow::doTangent(bool enabled)
{
    this->currentAction = (enabled) ? TANGENT : NONE;
    this->takeTowPoints = false;

    this->setAllButtons(!enabled, this->tangentButton);

    this->doAction(enabled);
}

void MainWindow::doZero(bool enabled)
{
    this->currentAction = (enabled) ? ZERO : NONE;
    this->takeTowPoints = true;

    this->setAllButtons(!enabled, this->zeroButton);

    this->doAction(enabled);
}

void MainWindow::doMaximum(bool enabled)
{
    this->currentAction = (enabled) ? MAXIMUM : NONE;
    this->takeTowPoints = true;

    this->setAllButtons(!enabled, this->maximumButton);

    this->doAction(enabled);
}

void MainWindow::doMinimum(bool enabled)
{
    this->currentAction = (enabled) ? MINIMUM : NONE;
    this->takeTowPoints = true;

    this->setAllButtons(!enabled, this->minimumButton);

    this->doAction(enabled);
}

void MainWindow::deleteFunctionItem()
{
    if (this->currentFonction != NULL && this->resultsTable->currentIndex().row() != -1 && this->resultsTable->currentIndex().row() < this->currentFonction->countItems())
    {
        this->currentFonction->removeItem(this->resultsTable->currentIndex().row());

        this->refreshResultTable();

        int index = this->currentFonction->countItems();

        this->resultsTable->item(index, 0)->setText("");
        this->resultsTable->item(index, 1)->setText("");
        this->resultsTable->item(index, 2)->setText("");

        this->setOperationsButtons(true);
    }
}

void MainWindow::clearFunctionItems()
{
    if (this->currentFonction != NULL)
    {
        // Boîte de message
        QMessageBox messageBox;

        messageBox.setIcon(QMessageBox::Question);
        messageBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
        messageBox.setDefaultButton(QMessageBox::No);
        messageBox.setText("Voulez-vous vraiment supprimer <u>toutes</u> les opérations ?");

        if (messageBox.exec() == QMessageBox::Yes)
        {
            this->currentFonction->clearItems();

            this->clearResultTable();
        }
    }
}

void MainWindow::functionEdited(QString text)
{
    this->createFunctionButton->setEnabled(!text.trimmed().isEmpty());

    this->cursorPosition = this->functionLineEdit->cursorPosition();
}

void MainWindow::storeCursorPosition(int oldPosition, int newPosition)
{
    if (this->selection.isEmpty())

        this->cursorPosition = newPosition;
}

void MainWindow::storeSelection()
{
    if (this->functionLineEdit->hasFocus())
    {
        this->selection = this->functionLineEdit->selectedText().trimmed();

        if (this->functionLineEdit->selectionStart() != -1)

            this->cursorPosition = this->functionLineEdit->selectionStart();
    }
}

void MainWindow::insertOperator(QString tag)
{
    // Sauvegarde de l'expression de l'utilisateur
    QString expression = this->functionLineEdit->text();

    // Sauvegarde de la position du curseur
    int cursorPosition = this->cursorPosition;

    // Position du remplacement
    int replacePosition = tag.indexOf(OPERATOR_ARG_VAR);

    // Est-ce une fonction (exp, ln, sin, ...) ?
    bool isFunction = tag.contains(OPERATOR_ARG_VAR);

    // Fonction (exp, ln, sin, ...) ?
    if (isFunction)
    {
        // Placement de la sélection dans la fonction
        tag.replace(OPERATOR_ARG_VAR, this->selection);

        // Texte sélectionné ?
        if (this->selection.length())

            // Nettoyage du texte sélectionné
            expression.remove(cursorPosition, this->selection.length());
    }

    // Placement de la balise à la position du curseur
    expression.insert(cursorPosition, tag);

    // Fonction sans sélection ?
    if (isFunction && !this->selection.length())

        // Retrait
        cursorPosition -= tag.length() - replacePosition;

    // Modification de la zone de texte
    this->functionLineEdit->setFocus();
    this->functionLineEdit->setText(expression);
    this->functionLineEdit->setCursorPosition(cursorPosition + tag.length());

    // Suppression de la sélection courant
    this->selection = "";
}

void MainWindow::changeDisplayMode(bool onlyOne)
{
    if (onlyOne)

        this->functionsView->showOnly(this->currentFonction);

    else

        this->functionsView->showAll();
}

void MainWindow::setGridMarking(bool enabled)
{
    this->functionsView->setGridMarking(enabled);
}

void MainWindow::setAntialiasing(bool enabled)
{
    this->functionsView->setAntialiasing(enabled);
}

void MainWindow::sceneClicked(QMouseEvent* event, const QPointF& point)
{
    if (this->functionsView->getDisplayMode() != FunctionsView::Fixed || event->button() != Qt::LeftButton)

        return;

    this->functionsView->addMarker(point.x());

    if (!this->sceneClicks)
    {
        this->currentX1 = point.x();

        this->xPositionBar1->setValue(this->currentX1);
        this->xPositionBar1->setChecked(true);

        if (this->takeTowPoints)
        {
            this->sceneClicks++;

            this->xPositionBar = this->xPositionBar2;

            this->xPositionBar2->setEnabled(true);

            this->xPositionBar2->setFocus();
        }
        else
        {
            this->doAction(false);

            this->createFunctionItem();
        }
    }
    else
    {
        this->sceneClicks = 0;

        this->currentX2 = point.x();

        this->xPositionBar2->setValue(this->currentX2);
        this->xPositionBar2->setChecked(true);

        this->doAction(false);

        this->createFunctionItem();
    }
}

void MainWindow::boundsChanged()
{
    if (this->xMinSpinBox->value() + 1 >= this->xMaxSpinBox->value())

        this->xMaxSpinBox->setValue(this->xMinSpinBox->value() + 2);

    if (this->yMinSpinBox->value() + 1 >= this->yMaxSpinBox->value())

        this->yMaxSpinBox->setValue(this->yMinSpinBox->value() + 2);

    this->xPositionBar1->setRange(this->xMinSpinBox->value(), this->xMaxSpinBox->value());
    this->xPositionBar2->setRange(this->xMinSpinBox->value(), this->xMaxSpinBox->value());

    this->functionsView->setSceneRect(this->xMinSpinBox->value(),
                                      this->yMinSpinBox->value(),
                                      this->xMaxSpinBox->value() - this->xMinSpinBox->value(),
                                      this->yMaxSpinBox->value() - this->yMinSpinBox->value());
}

void MainWindow::boundsMoved(const QRectF& rect)
{
    this->xMinSpinBox->blockSignals(true);
    this->xMaxSpinBox->blockSignals(true);

    this->xMinSpinBox->setValue(rect.left());
    this->xMaxSpinBox->setValue(rect.right());

    this->xMinSpinBox->blockSignals(false);
    this->xMaxSpinBox->blockSignals(false);

    this->yMinSpinBox->blockSignals(true);
    this->yMaxSpinBox->blockSignals(true);

    this->yMinSpinBox->setValue(rect.top());
    this->yMaxSpinBox->setValue(rect.bottom());

    this->yMinSpinBox->blockSignals(false);
    this->yMaxSpinBox->blockSignals(false);

    this->xPositionBar1->setRange(rect.left(), rect.right());
    this->xPositionBar2->setRange(rect.left(), rect.right());
}

void MainWindow::reinitializeBounds()
{
    this->functionsView->setSceneRect(DEFAULT_X_MIN, DEFAULT_Y_MIN, DEFAULT_X_MAX - DEFAULT_X_MIN, DEFAULT_Y_MAX - DEFAULT_Y_MIN);
}

void MainWindow::xLineMoved(double value)
{
    this->xPositionBar->setValue(value);
}

void MainWindow::xPositionChanged(double value)
{
    this->functionsView->setXLine(value);
}

void MainWindow::xPositionAccepted(double value)
{
    if (this->functionsView->getDisplayMode() != FunctionsView::Fixed)

        return;

    this->functionsView->addMarker(value);

    if (!this->sceneClicks)
    {
        this->currentX1 = value;

        if (this->takeTowPoints)
        {
            this->sceneClicks++;

            this->xPositionBar = this->xPositionBar2;

            this->xPositionBar2->setEnabled(true);

            this->xPositionBar2->setFocus();
        }
        else
        {
            this->doAction(false);

            this->createFunctionItem();
        }
    }
    else
    {
        this->sceneClicks = 0;

        this->currentX2 = value;

        this->doAction(false);

        this->createFunctionItem();
    }
}

void MainWindow::xPositionAborted()
{
    this->sceneClicks = 0;

    this->xPositionBar = this->xPositionBar1;

    this->xPositionBar1->setFocus();

    this->xPositionBar2->setEnabled(false);

    this->functionsView->clearMarkers();
}

void MainWindow::showHelp()
{
    if (!QDesktopServices::openUrl(QUrl::fromLocalFile("Tutorial.pdf")))
    {
        // Boîte de message d'erreur
        QMessageBox messageBox;

        messageBox.setIcon(QMessageBox::Critical);
        messageBox.setStandardButtons(QMessageBox::Ok);
        messageBox.setDefaultButton(QMessageBox::Ok);
        messageBox.setText("Fichier d'aide introuvable !");

        messageBox.exec();
    }
}

void MainWindow::showAboutBox()
{
    AboutBox().exec();
}

void MainWindow::createMainStructure()
{
    // Disposition principale
    this->mainLayout = new QHBoxLayout();

    this->mainLayout->setContentsMargins(12, 12, 12, 22);

    // Cadre de contrôle
    this->controlFrame = new QFrame();

    this->controlFrame->setFixedWidth(305);
    this->controlFrame->setContentsMargins(0, 0, 0, 0);
    this->controlFrame->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::MinimumExpanding);

    // Ajout du cadre de contrôle à la disposition principale
    this->mainLayout->addWidget(this->controlFrame);

    // Espacement...
    this->mainLayout->addSpacing(3);

    // Groupement "Rendu"
    this->renderBox = new QGroupBox("Rendu");

    // Ajout du groupement "Rendu" à la disposition principale
    this->mainLayout->addWidget(this->renderBox);
}

void MainWindow::createControlPanel()
{
    // Disposition du cadre de contrôle
    this->controlLayout = new QVBoxLayout();

    this->controlLayout->setContentsMargins(0, 0, 0, 0);

    // Création de la boîte d'édition
    this->createEditionBox();

    // Ajout de la boîte d'édition à la disposition du cadre de contrôle
    this->controlLayout->addWidget(this->editionBox);

    // Espacement...
    this->controlLayout->addSpacing(3);

    // Création de la boîte de fonctions
    this->createFunctionsBox();

    // Ajout de la boîte de fonctions à la disposition du cadre de contrôle
    this->controlLayout->addWidget(this->functionBox);

    // Affectation à son parent
    this->controlFrame->setLayout(this->controlLayout);
}

void MainWindow::createEditionBox()
{
    // Groupement "Edition"
    this->editionBox = new QGroupBox("Edition");

    // Disposition de la boîte d'édition
    this->editionBoxLayout = new QVBoxLayout();

    // Disposition pour la zone d'édition et le bouton de fonction
    this->editionRowLayout = new QHBoxLayout();

    // Ligne d'édition de fonction
    this->functionLineEdit = new QLineEdit();

    QObject::connect(this->functionLineEdit , SIGNAL(returnPressed()),
                     this                   , SLOT(insertFunction()));

    QObject::connect(this->functionLineEdit , SIGNAL(textChanged(QString)),
                     this                   , SLOT(functionEdited(QString)));

    QObject::connect(this->functionLineEdit , SIGNAL(cursorPositionChanged(int, int)),
                     this                   , SLOT(storeCursorPosition(int, int)));

    QObject::connect(this->functionLineEdit , SIGNAL(selectionChanged()),
                     this                   , SLOT(storeSelection()));

    // Ajout de la ligne d'édition de fonction à sa disposition
    this->editionRowLayout->addWidget(this->functionLineEdit);

    // Bouton de création de fonction
    this->createFunctionButton = new QPushButton("Créer");

    this->createFunctionButton->setFixedWidth(70);
    this->createFunctionButton->setEnabled(false);
    this->createFunctionButton->setToolTip("Créer la fonction");

    QObject::connect(this->createFunctionButton , SIGNAL(clicked()),
                     this                       , SLOT(insertFunction()));

    // Ajout du bouton de création de fonction à sa disposition
    this->editionRowLayout->addWidget(this->createFunctionButton);

    // Ajout de la disposition pour la zone d'édition et le bouton de fonction à la disposition de la boîte d'édition
    this->editionBoxLayout->addLayout(this->editionRowLayout);

    // Espacement...
    this->editionBoxLayout->addSpacing(3);

    // Cadre des opérateurs
    this->operatorsFrame = new QFrame();

    this->operatorsFrame->setFrameStyle(QFrame::Panel | QFrame::Sunken);

    // Grillage des opérateurs
    this->operatorsGrid = new QGridLayout();

    this->operatorsGrid->setContentsMargins(10, 10, 10, 10);
    this->operatorsGrid->setSpacing(7);

    // Création des opérateurs
    this->createOperatorButton("x2"     , "x^2");
    this->createOperatorButton("x^y"    , "x^(#)");
    this->createOperatorButton("log"    , "log(#)");
    this->createOperatorButton("ln"     , "ln(#)");
    this->createOperatorButton("sin"    , "sin(#)");
    this->createOperatorButton("cos"    , "cos(#)");
    this->createOperatorButton("tan"    , "tan(#)");
    this->createOperatorButton("exp"    , "exp(#)");
    this->createOperatorButton("asin"   , "asin(#)");
    this->createOperatorButton("acos"   , "acos(#)");
    this->createOperatorButton("atan"   , "atan(#)");
    this->createOperatorButton("sqrt"   , "sqrt(#)");
    this->createOperatorButton("sinh"   , "sinh(#)");
    this->createOperatorButton("cosh"   , "cosh(#)");
    this->createOperatorButton("tanh"   , "tanh(#)");
    this->createOperatorButton("abs"    , "abs(#)");

    // Affectation du grillage des opérateurs à son parent
    this->operatorsFrame->setLayout(this->operatorsGrid);

    // Ajout du cadre des opérateurs à la disposition de la boîte d'édition
    this->editionBoxLayout->addWidget(this->operatorsFrame);

    // Affectation à son parent
    this->editionBox->setLayout(this->editionBoxLayout);
}

void MainWindow::createFunctionsBox()
{
    // Groupement "Fonctions"
    this->functionBox = new QGroupBox("Fonction");

    this->functionBox->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::MinimumExpanding);
    this->functionBox->setEnabled(false);

    // Disposition des contrôles de la fonction
    this->functionBoxLayout = new QVBoxLayout();

    // Cadre du choix des fonctions
    this->functionsRowFrame = new QFrame();

    this->functionsRowFrame->setContentsMargins(0, 0, 0, 0);

    // Ligne du choix des fonctions
    this->functionsRowLayout = new QHBoxLayout();

    this->functionsRowLayout->setContentsMargins(0, 0, 0, 0);

    // Label "f(x) = ..."
    QLabel* functionLabel = new QLabel("f(x) =");

    functionLabel->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Fixed);

    // Ajout du label "f(x) = ..." à la ligne du choix des fonctions
    this->functionsRowLayout->addWidget(functionLabel);

    // Liste des fonctions
    this->functionsComboBox = new QComboBox();

    QObject::connect(this->functionsComboBox    , SIGNAL(currentIndexChanged(int)),
                     this                       , SLOT(functionSelected(int)));

    // Ajout de la liste des fonctions à la ligne du choix des fonctions
    this->functionsRowLayout->addWidget(this->functionsComboBox);

    // Bouton de changement de couleur pour fonction
    this->functionColorButton = new QPushButton();

    this->functionColorButton->setFixedSize(25, 22);
    this->functionColorButton->setIcon(QPixmap(":/images/palette.png"));
    this->functionColorButton->setToolTip("Changer la couleur de la fonction");

    QObject::connect(this->functionColorButton  , SIGNAL(clicked()),
                     this                       , SLOT(changeFunctionColor()));

    // Ajout du bouton de changement de couleur pour fonction à la ligne du choix des fonctions
    this->functionsRowLayout->addWidget(this->functionColorButton);

    // Bouton de suppression de fonction
    this->deleteFunctionButton = new QPushButton();

    this->deleteFunctionButton->setFixedSize(25, 22);
    this->deleteFunctionButton->setIcon(QPixmap(":/images/delete.png"));
    this->deleteFunctionButton->setToolTip("Supprimer la fonction");

    QObject::connect(this->deleteFunctionButton , SIGNAL(clicked()),
                     this                       , SLOT(deleteFonction()));

    // Ajout du bouton de suppression de fonction à la ligne du choix des fonctions
    this->functionsRowLayout->addWidget(this->deleteFunctionButton);

    // Affectation à son parent
    this->functionsRowFrame->setLayout(this->functionsRowLayout);

    // Ajout du cadre du choix des fonctions à la disposition des contrôles de la fonction
    this->functionBoxLayout->addWidget(this->functionsRowFrame);

    // Espacement...
    this->functionBoxLayout->addSpacing(5);

    // Séparateur visuel
    QFrame* separator = new QFrame();

    separator->setFrameShape(QFrame::HLine);
    separator->setFrameShadow(QFrame::Sunken);

    // Ajout du séparateur visuel à la disposition des contrôles de la fonction
    this->functionBoxLayout->addWidget(separator);

    // Espacement...
    this->functionBoxLayout->addSpacing(3);

    // Ligne des opérations de fonction
    this->operationsRowLayout = new QHBoxLayout();

    // Bouton de création d'intégrale
    this->integralButton = new QPushButton("Int");

    this->integralButton->setCheckable(true);
    this->integralButton->setToolTip("Créer une intégrale");

    QObject::connect(this->integralButton   ,  SIGNAL(clicked(bool)),
                     this                   ,  SLOT(doIntegral(bool)));

    // Ajout du bouton de création d'intégrale à la ligne des opérations de fonction
    this->operationsRowLayout->addWidget(this->integralButton);

    // Bouton de création de tangente
    this->tangentButton = new QPushButton("Tan");

    this->tangentButton->setCheckable(true);
    this->tangentButton->setToolTip("Créer une tangente");

    QObject::connect(this->tangentButton    , SIGNAL(clicked(bool)),
                     this                   , SLOT(doTangent(bool)));

    // Ajout du bouton de création de tangente à la ligne des opérations de fonction
    this->operationsRowLayout->addWidget(this->tangentButton);

    // Bouton de recherche du zéro
    this->zeroButton = new QPushButton("Zéro");

    this->zeroButton->setCheckable(true);
    this->zeroButton->setToolTip("Chercher un zéro");

    QObject::connect(this->zeroButton       , SIGNAL(clicked(bool)),
                     this                   , SLOT(doZero(bool)));

    // Ajout du bouton de recherche du zéro à la ligne des opérations de fonction
    this->operationsRowLayout->addWidget(this->zeroButton);

    // Bouton de recherche du maximum
    this->maximumButton = new QPushButton("Max");

    this->maximumButton->setCheckable(true);
    this->maximumButton->setToolTip("Chercher un maximum");

    QObject::connect(this->maximumButton    , SIGNAL(clicked(bool)),
                     this                   , SLOT(doMaximum(bool)));

    // Ajout du bouton de recherche du maximum à la ligne des opérations de fonction
    this->operationsRowLayout->addWidget(this->maximumButton);

    // Bouton de recherche du minimum
    this->minimumButton = new QPushButton("Min");

    this->minimumButton->setCheckable(true);
    this->minimumButton->setToolTip("Chercher un minimum");

    QObject::connect(this->minimumButton    , SIGNAL(clicked(bool)),
                     this                   , SLOT(doMinimum(bool)));

    // Ajout du bouton de recherche du minimum à la ligne des opérations de fonction
    this->operationsRowLayout->addWidget(this->minimumButton);

    // Ajout de la ligne des opérations de fonction à la disposition des contrôles de la fonction
    this->functionBoxLayout->addLayout(operationsRowLayout);

    // Table de résultats
    this->resultsTable = new QTableWidget();

    this->resultsTable->setColumnCount(3);
    this->resultsTable->setRowCount(MAX_FUNCTION_ITEMS);

    this->resultsTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    this->resultsTable->setSelectionMode(QAbstractItemView::SingleSelection);
    this->resultsTable->setFont(QFont(this->resultsTable->font().toString(), 8, 1, false));

    this->resultsTable->setHorizontalHeaderItem(0, new QTableWidgetItem("Type"));
    this->resultsTable->setHorizontalHeaderItem(1, new QTableWidgetItem("Domaine"));
    this->resultsTable->setHorizontalHeaderItem(2, new QTableWidgetItem("Résultat"));

    this->resultsTable->horizontalHeader()->setResizeMode(0, QHeaderView::Custom);
    this->resultsTable->horizontalHeader()->setResizeMode(1, QHeaderView::Custom);
    this->resultsTable->horizontalHeader()->setResizeMode(2, QHeaderView::Custom);

    this->resultsTable->horizontalHeader()->resizeSection(0, 38);
    this->resultsTable->horizontalHeader()->resizeSection(1, 110);
    this->resultsTable->horizontalHeader()->resizeSection(2, 95);

    int tableWidgetItemFlags = 0;

    for (int i = 0; i < MAX_FUNCTION_ITEMS; i++)
    {
        this->resultsTable->verticalHeader()->setResizeMode(i, QHeaderView::Fixed);

        for (int j = 0; j < 3; j++)
        {
            // Cellule
            QTableWidgetItem* tableWidgetItem = new QTableWidgetItem(QTableWidgetItem::Type);

            if (!i)
            {
                tableWidgetItemFlags = tableWidgetItem->flags();
                tableWidgetItemFlags ^= Qt::ItemIsEditable;
            }

            tableWidgetItem->setFlags((Qt::ItemFlags)tableWidgetItemFlags);
            tableWidgetItem->setTextAlignment(Qt::AlignCenter);

            this->resultsTable->setItem(i, j, tableWidgetItem);
        }
    }

    // Ajout de la table de résultats à la disposition des contrôles de la fonction
    this->functionBoxLayout->addWidget(this->resultsTable);

    // Ligne de résultats
    this->resultsRowLayout = new QHBoxLayout();

    // Label
    this->resultsRowLayout->addWidget(new QLabel("Options des opérations"));

    // Bouton de suppression d'une opération
    this->deleteOperationButton = new QPushButton();

    this->deleteOperationButton->setFixedSize(25, 22);
    this->deleteOperationButton->setIcon(QPixmap(":/images/delete.png"));
    this->deleteOperationButton->setToolTip("Supprimer l'opération sélectionnée");

    QObject::connect(this->deleteOperationButton    , SIGNAL(clicked()),
                     this                           , SLOT(deleteFunctionItem()));

    // Ajout du bouton de suppression d'une opération à la ligne de résultats
    this->resultsRowLayout->addWidget(this->deleteOperationButton);

    // Bouton de suppression de toutes les opérations
    this->clearOperationsButton = new QPushButton();

    this->clearOperationsButton->setFixedSize(25, 22);
    this->clearOperationsButton->setIcon(QPixmap(":/images/trash.png"));
    this->clearOperationsButton->setToolTip("Supprimer toutes les opérations");

    QObject::connect(this->clearOperationsButton    , SIGNAL(clicked()),
                     this                           , SLOT(clearFunctionItems()));

    // Ajout du bouton de suppression de toutes les opérations à la ligne de résultats
    this->resultsRowLayout->addWidget(this->clearOperationsButton);

    // Ajout de la ligne de résultats à la disposition des contrôles de la fonction
    this->functionBoxLayout->addLayout(this->resultsRowLayout);

    // Affectation à son parent
    this->functionBox->setLayout(this->functionBoxLayout);
}

void MainWindow::createRenderPanel()
{
    // Disposition du rendu
    this->renderBoxLayout = new QVBoxLayout();

    // En-tête du rendu (bornes...)
    this->renderHeaderLayout = new QHBoxLayout();

    // Case à cocher pour l'affichage exclusif
    this->onlyOneCheckBox = new QCheckBox("Affichage exclusif");

    this->onlyOneCheckBox->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Fixed);

    QObject::connect(this->onlyOneCheckBox  , SIGNAL(clicked(bool)),
                     this                   , SLOT(changeDisplayMode(bool)));

    // Ajout de la case à cocher pour l'affichage exclusif à l'en-tête du rendu
    this->renderHeaderLayout->addWidget(this->onlyOneCheckBox);

    // Espacement central
    QFrame* spacingFrame = new QFrame();

    spacingFrame->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);

    // Ajout du bouton de réinitialisation à l'en-tête du rendu
    this->renderHeaderLayout->addWidget(spacingFrame);

    // Création des modificateurs de bornes : x
    this->createBoundSetter(this->xMinSpinBox, "x min :", DEFAULT_X_MIN, FunctionsView::X_MIN_LIMIT, FunctionsView::X_MAX_LIMIT);
    this->createBoundSetter(this->xMaxSpinBox, "x max :", DEFAULT_X_MAX, FunctionsView::X_MIN_LIMIT, FunctionsView::X_MAX_LIMIT);

    // Espacement...
    this->renderHeaderLayout->addSpacing(15);

    // Création des modificateurs de bornes : y
    this->createBoundSetter(this->yMinSpinBox, "y min :", DEFAULT_Y_MIN, FunctionsView::Y_MIN_LIMIT, FunctionsView::Y_MAX_LIMIT);
    this->createBoundSetter(this->yMaxSpinBox, "y max :", DEFAULT_Y_MAX, FunctionsView::Y_MIN_LIMIT, FunctionsView::Y_MAX_LIMIT);

    // Espacement...
    this->renderHeaderLayout->addSpacing(5);

    // Bouton de réinitialisation des bornes
    this->resetBoundsButton = new QPushButton();

    this->resetBoundsButton->setFixedSize(25, 22);
    this->resetBoundsButton->setIcon(QPixmap(":/images/center.png"));
    this->resetBoundsButton->setToolTip("Réinitialiser les bornes");

    QObject::connect(this->resetBoundsButton    , SIGNAL(clicked()),
                     this                       , SLOT(reinitializeBounds()));

    // Ajout du bouton de réinitialisation des bornes à l'en-tête du rendu
    this->renderHeaderLayout->addWidget(this->resetBoundsButton);

    // Ajout de l'en-tête du rendue à la disposition du rendu
    this->renderBoxLayout->addLayout(this->renderHeaderLayout);

    // Espacement...
    this->renderBoxLayout->addSpacing(3);

    // Gestionnaire de rendu de fonctions
    this->functionsView = new FunctionsView(DEFAULT_X_MIN, DEFAULT_X_MAX, DEFAULT_Y_MIN, DEFAULT_Y_MAX);

    // Anticrénelage activé
    // this->functionsView->setAntialiasing(true);

    QObject::connect(this->functionsView    , SIGNAL(clicked(QMouseEvent*, QPointF)),
                     this                   , SLOT(sceneClicked(QMouseEvent*, QPointF)));

    QObject::connect(this->functionsView    , SIGNAL(sceneMoved(QRectF)),
                     this                   , SLOT(boundsMoved(QRectF)));

    QObject::connect(this->functionsView    , SIGNAL(xLineMoved(double)),
                     this                   , SLOT(xLineMoved(double)));

    // Ajout du gestionnaires de rendu de fonctions à la disposition du rendu
    this->renderBoxLayout->addWidget(this->functionsView);

    // Espacement...
    this->renderBoxLayout->addSpacing(3);

    // Barre de positionnement 1
    this->xPositionBar1 = new XPositionBar("Position x1 :", DEFAULT_X_MIN, DEFAULT_X_MAX);

    this->xPositionBar1->setEnabled(false);

    QObject::connect(this->xPositionBar1    , SIGNAL(xPositionChanged(double)),
                     this                   , SLOT(xPositionChanged(double)));

    QObject::connect(this->xPositionBar1    , SIGNAL(xPositionAccepted(double)),
                     this                   , SLOT(xPositionAccepted(double)));

    QObject::connect(this->xPositionBar1    , SIGNAL(xPositionAborted()),
                     this                   , SLOT(xPositionAborted()));

    // Ajout de la barre de positionnement 1 à la disposition du rendu
    this->renderBoxLayout->addWidget(this->xPositionBar1);

    // Barre de positionnement 2
    this->xPositionBar2 = new XPositionBar("Position x2 :", DEFAULT_X_MIN, DEFAULT_X_MAX);

    this->xPositionBar2->setEnabled(false);

    QObject::connect(this->xPositionBar2    , SIGNAL(xPositionChanged(double)),
                     this                   , SLOT(xPositionChanged(double)));

    QObject::connect(this->xPositionBar2    , SIGNAL(xPositionAccepted(double)),
                     this                   , SLOT(xPositionAccepted(double)));

    // Ajout de la barre de positionnement 2 à la disposition du rendu
    this->renderBoxLayout->addWidget(this->xPositionBar2);

    // Barre de positionnement courante...
    this->xPositionBar = this->xPositionBar1;

    // Affectation à son parent
    this->renderBox->setLayout(this->renderBoxLayout);
}

void MainWindow::createActions()
{
    // Action : Fermer l'application
    this->closeAction = new QAction("&Quitter", this);

    this->closeAction->setShortcut(QKeySequence(Qt::ALT + Qt::Key_F4));

    QObject::connect(this->closeAction  , SIGNAL(triggered()),
                     this               , SLOT(close()));

    // Action : Réinitialiser les bornes
    this->resetBoundsAction = new QAction("&Réinitialiser les bornes", this);

    this->resetBoundsAction->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_R));

    QObject::connect(this->resetBoundsAction    , SIGNAL(triggered()),
                     this                       , SLOT(reinitializeBounds()));

    // Action : Changer la couleur de la fonction
    this->changeFunctionColorAction = new QAction("&Changer la couleur...", this);

    QObject::connect(this->changeFunctionColorAction    , SIGNAL(triggered()),
                     this                               , SLOT(changeFunctionColor()));

    // Action : Supprimer la fonction
    this->deleteFunctionAction = new QAction("&Supprimer", this);

    QObject::connect(this->deleteFunctionAction , SIGNAL(triggered()),
                     this                       , SLOT(deleteFonction()));

    // Action : Supprimer toutes les fonctions
    this->clearFunctionsAction = new QAction("&Tout supprimer", this);

    QObject::connect(this->clearFunctionsAction , SIGNAL(triggered()),
                     this                       , SLOT(clearFunctions()));

    // Action : Créer une intégrale
    this->integralAction = new QAction("&Intégrale", this);

    QObject::connect(this->integralAction   , SIGNAL(triggered()),
                     this->integralButton   , SLOT(click()));

    // Action : Créer une tangente
    this->tangentAction = new QAction("Tan&gente", this);

    QObject::connect(this->tangentAction    , SIGNAL(triggered()),
                     this->tangentButton    , SLOT(click()));

    // Action : Chercher un zéro
    this->zeroAction = new QAction("&Zéro", this);

    QObject::connect(this->zeroAction       , SIGNAL(triggered()),
                     this->zeroButton       , SLOT(click()));

    // Action : Chercher un maximum
    this->maximumAction = new QAction("Ma&ximum", this);

    QObject::connect(this->maximumAction    , SIGNAL(triggered()),
                     this->maximumButton    , SLOT(click()));

    // Action : Chercher un minimum
    this->minimumAction = new QAction("Mi&nimum", this);

    QObject::connect(this->minimumAction    , SIGNAL(triggered()),
                     this->minimumButton    , SLOT(click()));

    // Action : Supprimer l'opération sélectionné
    this->deleteOperationAction = new QAction("&Supprimer", this);

    QObject::connect(this->deleteOperationAction    , SIGNAL(triggered()),
                     this                           , SLOT(deleteFunctionItem()));

    // Action : Supprimer toutes les opérations
    this->clearOperationsAction = new QAction("&Tout supprimer", this);

    QObject::connect(this->clearOperationsAction    , SIGNAL(triggered()),
                     this                           , SLOT(clearFunctionItems()));

    // Action : Affichage exclusif
    this->onlyOneAction = new QAction("Affichage &exclusif", this);

    this->onlyOneAction->setCheckable(true);
    this->onlyOneAction->setChecked(false);
    this->onlyOneAction->setShortcut(QKeySequence(Qt::Key_F2));

    QObject::connect(this->onlyOneAction    , SIGNAL(triggered()),
                     this->onlyOneCheckBox  , SLOT(click()));

    QObject::connect(this->onlyOneCheckBox  , SIGNAL(toggled(bool)),
                     this->onlyOneAction    , SLOT(setChecked(bool)));

    // Action : Afficher la grille
    this->viewGridAction = new QAction("&Grille", this);

    this->viewGridAction->setCheckable(true);
    this->viewGridAction->setChecked(true);
    this->viewGridAction->setShortcut(QKeySequence(Qt::Key_F3));

    QObject::connect(this->viewGridAction   , SIGNAL(triggered(bool)),
                     this                   , SLOT(setGridMarking(bool)));

    // Action : Anticrénelage
    this->antialiasingAction = new QAction("&Anticrénelage", this);

    this->antialiasingAction->setCheckable(true);
    this->antialiasingAction->setChecked(false);
    this->antialiasingAction->setShortcut(QKeySequence(Qt::Key_F4));

    QObject::connect(this->antialiasingAction   , SIGNAL(triggered(bool)),
                     this                       , SLOT(setAntialiasing(bool)));

    // Action : Afficher l'aide
    this->helpAction = new QAction("&Manuel de démarrage", this);

    this->helpAction->setShortcut(QKeySequence(Qt::Key_F1));

    QObject::connect(this->helpAction   , SIGNAL(triggered()),
                     this               , SLOT(showHelp()));

    // Action : A propos de Effex
    this->aboutAction = new QAction("À propos de &Effex...", this);

    QObject::connect(this->aboutAction  , SIGNAL(triggered()),
                     this               , SLOT(showAboutBox()));
}

void MainWindow::createMenu()
{
    // Barre de menu
    this->menuBar = new QMenuBar();

    this->fileMenu = new QMenu("&Fichier");

    this->fileMenu->addAction(this->closeAction);

    this->editionMenu = new QMenu("&Edition");

    this->editionMenu->addAction(this->resetBoundsAction);

    this->functionsMenu = new QMenu("Fo&nctions");

    this->functionsMenu->addAction(this->changeFunctionColorAction);
    this->functionsMenu->addSeparator();
    this->functionsMenu->addAction(this->deleteFunctionAction);
    this->functionsMenu->addAction(this->clearFunctionsAction);

    this->functionsMenu->setEnabled(false);

    this->operationsMenu = new QMenu("&Opérations");

    this->operationsMenu->addAction(this->integralAction);
    this->operationsMenu->addAction(this->tangentAction);
    this->operationsMenu->addAction(this->zeroAction);
    this->operationsMenu->addAction(this->maximumAction);
    this->operationsMenu->addAction(this->minimumAction);
    this->operationsMenu->addSeparator();
    this->operationsMenu->addAction(this->deleteOperationAction);
    this->operationsMenu->addAction(this->clearOperationsAction);

    this->operationsMenu->setEnabled(false);

    this->displayMenu = new QMenu("&Affichage");

    this->displayMenu->addAction(this->onlyOneAction);
    this->displayMenu->addAction(this->viewGridAction);
    this->displayMenu->addAction(this->antialiasingAction);

    this->helpMenu = new QMenu("A&ide");

    this->helpMenu->addAction(this->helpAction);
    this->helpMenu->addSeparator();
    this->helpMenu->addAction(this->aboutAction);

    // Affectations à la barre de menu
    this->menuBar->addMenu(this->fileMenu);
    this->menuBar->addMenu(this->editionMenu);
    this->menuBar->addMenu(this->functionsMenu);
    this->menuBar->addMenu(this->operationsMenu);
    this->menuBar->addMenu(this->displayMenu);
    this->menuBar->addMenu(this->helpMenu);

    // Menu de la fenêtre
    this->setMenuBar(this->menuBar);
}

void MainWindow::createFunctionItem()
{
    int index = 0;

    switch (this->currentAction)
    {
        case INTEGRAL:

            index = this->currentFonction->addIntegral("Int", this->currentX1, this->currentX2);


            break;

        case TANGENT:

            index = this->currentFonction->addTangent("Tan", this->currentX1);

            break;

        case ZERO:

            index = this->currentFonction->addZero("Zéro", this->currentX1, this->currentX2);

            break;

        case MAXIMUM:


            index = this->currentFonction->addMaximum("Max", this->currentX1, this->currentX2);

            break;

        case MINIMUM:


            index = this->currentFonction->addMinimum("Min", this->currentX1, this->currentX2);

            break;

        default:

            return;
    }

    this->resultsTable->item(index, 0)->setText(this->currentFonction->getItemData(index).getName());
    this->resultsTable->item(index, 1)->setText(this->currentFonction->getItemData(index).getDomain());
    this->resultsTable->item(index, 2)->setText(QVariant(MathTools::setDecimal(this->currentFonction->getItemData(index).getValue(), 3)).toString());

    this->resultsTable->selectRow(index);

    if (this->currentFonction->countItems() >= MAX_FUNCTION_ITEMS)

        this->setOperationsButtons(false);
}

void MainWindow::createOperatorButton(const QString& text, const QString& tag)
{
    static int row = this->operatorsGrid->rowCount();
    static int column;

    CalcButton* button = new CalcButton(text, tag);

    QObject::connect(button , SIGNAL(clicked(QString)),
                     this   , SLOT(insertOperator(QString)));

    this->operatorsGrid->addWidget(button, row, column);

    if (!(++column % 4))
    {
        row++;
        column = 0;
    }
}

void MainWindow::createBoundSetter(QDoubleSpinBox*& spinBox, const QString& title, int value, int min, int max)
{
    // Titre
    QLabel* label = new QLabel(title);

    label->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Fixed);

    // Ajout du titre à la disposition du rendu
    this->renderHeaderLayout->addWidget(label);

    // Boîte de modification
    spinBox = new QDoubleSpinBox();

    spinBox->setFixedWidth(80);
    spinBox->setSingleStep(1);
    spinBox->setDecimals(4);
    spinBox->setRange(min, max);
    spinBox->setValue(value);

    QObject::connect(spinBox    , SIGNAL(valueChanged(double)),
                     this       , SLOT(boundsChanged()));

    // Ajout de la boîte de modification à la disposition du rendu
    this->renderHeaderLayout->addWidget(spinBox);
}

void MainWindow::doAction(bool enabled)
{
    if (enabled)

        this->functionsView->showOnly(this->currentFonction);

    else if (!this->onlyOneCheckBox->isChecked())

        this->functionsView->showAll();

    this->functionsView->switchOn((!enabled) ? FunctionsView::FreeLook : FunctionsView::Fixed);

    this->functionsView->setXLine(this->functionsView->sceneRect().left());
    this->functionsView->setXLineVisible(enabled);

    this->xPositionBar = this->xPositionBar1;

    this->xPositionBar1->setEnabled(enabled);
    this->xPositionBar2->setEnabled(false);

    this->xPositionBar1->reset();
    this->xPositionBar2->reset();

    if (enabled)

        this->xPositionBar1->setFocus();

    else
    {
        this->setAllButtons(true, NULL);

        this->functionsView->clearMarkers();
    }
}

void MainWindow::checkFunctionState()
{
    // Plus de fonction ?
    if (this->functionsComboBox->currentIndex() == -1)
    {
        // Aucune fonction...
        this->currentFonction = NULL;

        // Activation des menus des fonctions et des opérations
        this->functionsMenu->setEnabled(false);
        this->operationsMenu->setEnabled(false);

        // Effacement de la table de résultats
        this->clearResultTable();

        // Désactivation du groupe de fonctions
        this->functionBox->setEnabled(false);
    }
}

void MainWindow::clearResultTable()
{
    for (int i = 0; i < this->resultsTable->rowCount(); i++)
    {
        this->resultsTable->item(i, 0)->setText("");
        this->resultsTable->item(i, 1)->setText("");
        this->resultsTable->item(i, 2)->setText("");
    }

    this->setOperationsButtons(true);

    this->resultsTable->selectRow(0);
}

void MainWindow::refreshResultTable()
{
    if (this->currentFonction != NULL)
    {
        for (int i = 0; i < this->currentFonction->countItems(); i++)
        {
            this->resultsTable->item(i, 0)->setText(this->currentFonction->getItemData(i).getName());
            this->resultsTable->item(i, 1)->setText(this->currentFonction->getItemData(i).getDomain());
            this->resultsTable->item(i, 2)->setText(QVariant(MathTools::setDecimal(this->currentFonction->getItemData(i).getValue(), 3)).toString());
        }

        if (this->currentFonction->countItems())

            this->resultsTable->selectRow(this->currentFonction->countItems() - 1);

        this->setOperationsButtons(this->currentFonction->countItems() < MAX_FUNCTION_ITEMS);
    }
}

void MainWindow::setAllButtons(bool enabled, QPushButton* except)
{
    this->menuBar->setEnabled(enabled);

    this->editionBox->setEnabled(enabled);

    this->functionsRowFrame->setEnabled(enabled);

    for (int i = 0; i < this->operationsRowLayout->count(); i++)
    {
        if (this->operationsRowLayout->itemAt(i)->widget() != except)

            ((QPushButton*)this->operationsRowLayout->itemAt(i)->widget())->setEnabled(enabled);

        if (enabled)

            ((QPushButton*)this->operationsRowLayout->itemAt(i)->widget())->setChecked(false);
    }

    this->resultsTable->setEnabled(enabled);
    this->deleteOperationButton->setEnabled(enabled);
    this->clearOperationsButton->setEnabled(enabled);

    this->onlyOneCheckBox->setEnabled(enabled);

    this->xMinSpinBox->setEnabled(enabled);
    this->xMaxSpinBox->setEnabled(enabled);

    this->yMinSpinBox->setEnabled(enabled);
    this->yMaxSpinBox->setEnabled(enabled);

    this->resetBoundsButton->setEnabled(enabled);

    if (enabled)

        this->sceneClicks = 0;
}

void MainWindow::setOperationsButtons(bool enabled)
{
    // Actions
    this->integralAction->setEnabled(enabled);
    this->tangentAction->setEnabled(enabled);
    this->zeroAction->setEnabled(enabled);
    this->maximumAction->setEnabled(enabled);
    this->minimumAction->setEnabled(enabled);

    // Boutons
    this->integralButton->setEnabled(enabled);
    this->tangentButton->setEnabled(enabled);
    this->zeroButton->setEnabled(enabled);
    this->maximumButton->setEnabled(enabled);
    this->minimumButton->setEnabled(enabled);
}
