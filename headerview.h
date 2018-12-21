#ifndef HEADERVIEW_H
#define HEADERVIEW_H

#include <QObject>
#include <QHeaderView>
#include <QPainter>
#include <QMouseEvent>
#include <QDebug>

class HeaderView : public QHeaderView
{
public:
    HeaderView(Qt::Orientation orientation, QWidget* parent = 0);

    bool isPressedCheckBox(const QPoint &mousePos);
protected:
    void paintSection(QPainter* painter, const QRect& rect, int logicalIndex) const Q_DECL_OVERRIDE;

    void mouseMoveEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    void mousePressEvent(QMouseEvent* event) Q_DECL_OVERRIDE;
    void mouseDoubleClickEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
private:
    bool _isOn = false;
    mutable QRect _rectHeaderCheckBox;//复选框的位置
    mutable int _checkeBoxColumn = 0;
};

#endif // HEADERVIEW_H
