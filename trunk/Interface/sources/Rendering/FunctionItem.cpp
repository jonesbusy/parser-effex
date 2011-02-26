#include "Rendering/FunctionItem.h"

FunctionItem::FunctionItem(IExpression* function, const ItemData& data, QGraphicsScene* scene) : FunctionGraphics(function, scene), data(data)
{
}

const ItemData& FunctionItem::getData() const
{
    return this->data;
}
