#ifndef DATAHANDLER_H
#define DATAHANDLER_H

#include <QFile>
#include <QDebug>

class DataHandler
{
public:
    DataHandler();
    std::vector<QString> readCsvNodes();
    QMultiHash<QString, QString> readCsvLinks();
    int calculateNodesNumber(std::vector<QString> nodes);
};

#endif // DATAHANDLER_H
