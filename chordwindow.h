#ifndef CHORDWINDOW_H
#define CHORDWINDOW_H

#include <QWidget>
#include <QPainter>
#include <QDebug>
#include <QColor>
#include <QtMath>


class ChordWindow : public QWidget
{
    Q_OBJECT

public:
    ChordWindow(QWidget *parent = nullptr);

    virtual void paintEvent(QPaintEvent *event);
    void DrawArc(int s, int e);
    int CalculateCircumference();
    void DrawCircle(int r, QPoint c);

    void PlaceNodes(int nodes, float spacing, float width, float circumference);
    void CalculateCentreOfArcs(int i, float cA, float startX, float startY);
    void PlaceLinks();
    void DrawLinks(QPoint i, QPoint o);
    void CalculateCentreOfArcs(int i, int startAngle, int endAngle);
};

#endif // CHORDWINDOW_H
