#include "headerview.h"

HeaderView::HeaderView(Qt::Orientation orientation, QWidget*  parent)
    : QHeaderView(orientation, parent)
{

}
/*绘制表头logicalIndex表示表头第几列，0表示第0列，也就是我们要画复选框的列，rect是表头第一列的大小*/
void HeaderView::paintSection(QPainter *painter, const QRect &rect, int logicalIndex) const
{
    painter->save();
    QHeaderView::paintSection(painter, rect, logicalIndex);
    painter->restore();

    if(logicalIndex == _checkeBoxColumn){

        //复选框位置
        _rectHeaderCheckBox.setX(rect.x() + 3);
        _rectHeaderCheckBox.setY(rect.y() + 10);
        _rectHeaderCheckBox.setWidth(14);
        _rectHeaderCheckBox.setHeight(14);
        //--
        QStyleOptionButton option;
        //        option.iconSize = QSize(10,10);
        option.text = "fdsafdsafds";
        option.rect = _rectHeaderCheckBox;

        if(_isOn)
            option.state = QStyle::State_On;
        else
            option.state = QStyle::State_Off;

        this->style()->drawPrimitive(QStyle::PE_IndicatorCheckBox, &option, painter);
    }
}
bool HeaderView::isPressedCheckBox(const QPoint & mousePos)
{
    if ( isEnabled()
         && logicalIndexAt(mousePos) == _checkeBoxColumn
         && _rectHeaderCheckBox.contains(mousePos)
         ){
        _isOn = !_isOn;
        updateSection(_checkeBoxColumn);//刷新表头第一列
        qDebug()<<"updateSection:"<<_isOn;
        //        emit headCheckBoxToggled(_isOn);
        return true;
    }
    return false;
}
void HeaderView::mouseDoubleClickEvent(QMouseEvent *event)
{
    qDebug()<<__FUNCTION__<<__LINE__;
    QPoint mousePos = event->pos();
    if (isPressedCheckBox(mousePos)){
        event->ignore();
    }else
        QHeaderView::mouseDoubleClickEvent(event);
}
void HeaderView::mousePressEvent(QMouseEvent *event)
{
    qDebug()<<__FUNCTION__<<__LINE__;
    //表头可控制，鼠标第一个列，鼠标在矩形范围内
    QPoint mousePos = event->pos();
    //    qDebug()<<isEnabled()<<logicalIndexAt(mousePos)<<_rectHeaderCheckBox.contains(mousePos)<<_checkeBoxColumn;
    if (isPressedCheckBox(mousePos)){
        event->ignore();
    }else
        QHeaderView::mousePressEvent(event);
}

void HeaderView::mouseMoveEvent(QMouseEvent *event)
{
    QHeaderView::mouseMoveEvent(event);
}
