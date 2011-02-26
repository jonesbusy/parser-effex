#include "Windows/AboutBox.h"

AboutBox::AboutBox(QWidget* parent) : QDialog(parent)
{
    this->setModal(true);
    this->setFixedSize(600, 300);
    this->setWindowTitle("À propos de Effex");

    /* Spécifie un flag pour enlever le bouton "help" de la boîte de dialogue.
       Le deuxième flag a la même utilité, il permet d'assurer cette fonctionnalité
       dans tous les OS.*/
    this->setWindowFlags(Qt::WindowTitleHint | Qt::WindowSystemMenuHint);

    // La bannière de la boîte de dialogue.
    this->banner = new QLabel(this);
    this->banner->setPixmap(QPixmap(":/images/about.png"));

    // Easter eggs.
    this->easterEggs = new QLabel(this);
    this->easterEggs->setGeometry(420, 20, 130, 120);
    this->easterEggs->setToolTip("Mmmhhh, je n'ai pas de fonction pour réfléchir...");

    this->kiki = new QLabel(this);
    this->kiki->setGeometry(350, 185, 100, 112);
    this->kiki->setPixmap(QPixmap(":/images/kiki.png"));
    this->kiki->setVisible(false);

    QFrame* line = new QFrame(this);

    line->setFrameStyle(QFrame::HLine | QFrame::Sunken);
    line->setGeometry(0, 159, 600, 2);

    // Label contenant le texte de la boîte de dialogue.
    this->text = new QLabel(this);
    this->text->setGeometry(20, 150, 500, 150);
    this->text->setText("<p>Effex est un projet créé dans le cadre du cours PRO de la HEIG-VD.<br />" \
                        "Il permet de représenter des fonctions dans le domaine réel.</p>" \
                        "<p>Chef programmeur : Pascal Berberat<br />" \
                        "Programmeurs : Valentin Delaye, David Miserez</p>" \
                        "<p>Version 1.0</p>" \
                        "<p>Basé sur Qt 4.6.2 (32 bits)</p>");

    // Bouton permettant de quitter la boîte de dialogue.
    this->closeButton = new QPushButton("Fermer", this);
    this->closeButton->setGeometry(499, 268, 95, 27);
    this->closeButton->setDefault(true);
    this->closeButton->setToolTip("Fermer la fenêtre \"À propos de Effex\"");

    QObject::connect(this->closeButton  , SIGNAL(clicked()),
                     this               , SLOT(accept()));
}

void AboutBox::keyPressEvent(QKeyEvent* event)
{
    static QString pass = "";

    pass += event->key();

    if (pass.indexOf("KIKI") != -1 || pass.indexOf("kiki") != -1)
    {
        this->kiki->setVisible(true);

        pass = "";
    }

    if (pass.length() > 1000)

        pass = "";
}
