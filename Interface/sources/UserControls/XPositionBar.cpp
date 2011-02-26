#include "UserControls/XPositionBar.h"

XPositionBar::XPositionBar(const QString& title, double min, double max)
{
    this->setContentsMargins(0, 5, 0, 5);

    this->layout = new QHBoxLayout();

    this->layout->setContentsMargins(0, 3, 0, 3);

    this->label = new QLabel(title);

    this->label->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Fixed);

    this->layout->addWidget(this->label);

    this->spinBox = new QDoubleSpinBox();

    this->spinBox->setFixedWidth(80);
    this->spinBox->setSingleStep(1);
    this->spinBox->setDecimals(4);
    this->spinBox->setRange(min, max);
    this->spinBox->setValue(min);
    this->spinBox->setKeyboardTracking(true);

    QObject::connect(this->spinBox  , SIGNAL(valueChanged(double)),
                     this           , SLOT(valueChanged(double)));

    this->layout->addWidget(this->spinBox);

    this->scrollBar = new QScrollBar(Qt::Horizontal);

    this->scrollBar->setSingleStep(5);
    this->scrollBar->setRange(0, PARTS);
    this->scrollBar->setValue(0);

    QObject::connect(this->scrollBar    , SIGNAL(valueChanged(int)),
                     this               , SLOT(valueChanged(int)));

    this->layout->addWidget(this->scrollBar);

    this->acceptButton = new QPushButton("Valider");

    this->acceptButton->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Fixed);
    this->acceptButton->setCheckable(true);

    QObject::connect(this->acceptButton , SIGNAL(clicked(bool)),
                     this               , SLOT(acceptChanged(bool)));

    this->layout->addWidget(this->acceptButton);

    this->setLayout(this->layout);
}

double XPositionBar::getValue() const
{
    return this->spinBox->value();
}

void XPositionBar::setValue(double value)
{
    this->spinBox->setValue(value);
}

void XPositionBar::setRange(double min, double max)
{
    this->blockSignals(true);

    this->spinBox->setRange(min, max);
    this->spinBox->setValue(min);

    this->scrollBar->setValue(0);

    this->blockSignals(false);
}

bool XPositionBar::isChecked() const
{
    return this->acceptButton->isChecked();
}

void XPositionBar::setChecked(bool checked)
{
    this->acceptButton->setChecked(checked);

    this->spinBox->setEnabled(!checked);
    this->scrollBar->setEnabled(!checked);
}

void XPositionBar::reset()
{
    this->spinBox->setEnabled(true);
    this->scrollBar->setEnabled(true);

    this->spinBox->setValue(this->spinBox->minimum());
    this->scrollBar->setValue(0);

    this->acceptButton->setChecked(false);
}

void XPositionBar::acceptChanged(bool accepted)
{
    this->spinBox->setEnabled(!accepted);
    this->scrollBar->setEnabled(!accepted);

    if (accepted)

        emit this->xPositionAccepted(this->spinBox->value());

    else

        emit this->xPositionAborted();
}

void XPositionBar::valueChanged(int value)
{
    this->spinBox->setValue(this->spinBox->minimum() + (((double)value / (double)PARTS) * (this->spinBox->maximum() - this->spinBox->minimum())));
}

void XPositionBar::valueChanged(double value)
{
    this->scrollBar->blockSignals(true);

    this->scrollBar->setValue((int)(((value - this->spinBox->minimum()) / (this->spinBox->maximum() - this->spinBox->minimum())) * PARTS));

    this->scrollBar->blockSignals(false);

    emit this->xPositionChanged(value);
}

void XPositionBar::keyPressEvent(QKeyEvent* event)
{
    QFrame::keyReleaseEvent(event);

    if (event->key() == Qt::Key_Return)

        this->acceptButton->click();
}
