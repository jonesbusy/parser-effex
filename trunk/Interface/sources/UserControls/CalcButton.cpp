#include "UserControls/CalcButton.h"

CalcButton::CalcButton(const QString& text, const QString& tag) : QPushButton(text), tag(tag)
{
    QObject::connect(this, SIGNAL(clicked()),
                     this, SLOT(sendClickedTag()));
}

QString CalcButton::getTag() const
{
    return this->tag;
}

void CalcButton::setTag(const QString& tag)
{
    this->tag = tag;
}

void CalcButton::sendClickedTag()
{
    emit clicked(this->tag);
}
