#include <QtGui>
#include "chordwindow.h"
#include "datahandler.h"

ChordWindow::ChordWindow(QWidget *parent): QWidget(parent)
{

}

const int MAX_WINDOW_SIZE = 100;
const int RADIUS = 30;
const int MAX_DEGREE = 5760;
const QPoint CENTRE(50,50);
const QRect RECT(QPoint(20,20), QPoint(79,79));

DataHandler *data = new DataHandler();

std::vector<QString> nodes = data->readCsvNodes();
QMultiHash<QString, QString> links = data->readCsvLinks();

int m_nodesNumber = data->calculateNodesNumber(nodes);
QHash<QString, QPoint> linksCentre;

void ChordWindow::paintEvent(QPaintEvent *event)
{

    float circumference = (float)CalculateCircumference();
    float spacing = circumference / m_nodesNumber;
    float gap = spacing/2;
    float width = spacing - gap;
    float centreAngle = width/RADIUS;

    DrawCircle(RADIUS, CENTRE);
    PlaceNodes(m_nodesNumber, spacing, width, circumference);
    //CalculateCentreOfArcs(0, centreAngle, 79, 50);
    qDebug() << links;
    PlaceLinks();

}

void ChordWindow::PlaceNodes(int nodes, float spacing, float width, float circumference)
{
    for(int i=0; i<nodes; ++i)
    {
        float degSpacing = (spacing/circumference)*MAX_DEGREE;
        float degWidth = (width/circumference)*MAX_DEGREE;

        int start = i*(degSpacing);
        int end = degWidth;
        DrawArc(start, end);
        CalculateCentreOfArcs(i, start);

    }
}

//void ChordWindow::CalculateCentreOfArcs(int i, float cA, float startX, float startY)
//{
//    if(i<nodes.size())
//    {
//        float angle = cA;
//        //polar equations
//        //Px2 = Px -RADIUS + RADIUS*cos(centralAngle)
//        //Py2 = Py + RADIUS*sin(centralAngle)
//        float endX = startX - RADIUS + RADIUS*qCos(angle);
//        float endY = startY + RADIUS*qSin(angle);
//        qDebug() << endY;
//        QString node = nodes[i];
//        linksCentre.insert(node, QPoint((int)endX,(int)endY));

//        CalculateCentreOfArcs(++i, cA, endX, endY);

//    }

//}

void ChordWindow::CalculateCentreOfArcs(int i, int angle)
{
    float x = 50 + RADIUS*qCos(angle);
    float y = 50 + RADIUS*qSin(angle);
    QString node = nodes[i];
    linksCentre.insert(node, QPoint((int)x,(int)y));
}

//loop through links
    //for each key
        //find key in linksCentre and get the value
        //for each value
            //find key in linksCentre and get the value
//draw link

void ChordWindow::PlaceLinks()
{
    for(auto it = links.begin(); it != links.end(); ++it)
    {
        QPoint inputCentre = linksCentre.find(it.key()).value();
        QPoint outputCentre = linksCentre.find(it.value()).value();
        DrawLinks(inputCentre, outputCentre);
    }
}

void ChordWindow::DrawLinks(QPoint i, QPoint o)
{
    int width = 0;

    QPainter m(this);
    m.setWindow(0,0,MAX_WINDOW_SIZE,MAX_WINDOW_SIZE);
    QPen p;
    p.setColor(Qt::blue);
    p.setCapStyle(Qt::RoundCap);
    p.setWidth(width);
    m.setPen(p);
    m.drawLine(i, o);

}

void ChordWindow::DrawArc(int s, int e)
{
    //will have to set colour based on group
    //need to get group from csv (probs will convert nodes
    //to a hash or map and add it there)
    int width = 1;

    QPainter m(this);
    m.setWindow(0,0,MAX_WINDOW_SIZE,MAX_WINDOW_SIZE);
    QPen p;
    p.setColor(Qt::red);
    p.setCapStyle(Qt::RoundCap);
    p.setWidth(width);
    m.setPen(p);
    m.drawArc(RECT,s,e);

}

void ChordWindow::DrawCircle(int r, QPoint centre)
{
    QPainter m(this);
    m.setViewport(0,0, width(),height());
    m.setWindow(0,0,MAX_WINDOW_SIZE,MAX_WINDOW_SIZE);

    QPen p;
    int width = 0;
    p.setColor(Qt::black);
    p.setCapStyle(Qt::RoundCap);
    p.setWidth(width);

    m.setPen(p);
    m.drawEllipse(centre, r, r);
}

int ChordWindow::CalculateCircumference()
{
    return M_PI*2*RADIUS;
}

