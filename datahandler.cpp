#include "datahandler.h"

DataHandler::DataHandler()
{

}

std::vector<QString> DataHandler::readCsvNodes()
{
    std::vector<QString> nodes;
    //needs refactoring
    QFile file("/home/carlo/Development/C++/CSV/InternetOfEnergy.csv");

    if(!file.open(QFile::ReadOnly | QFile::Text))
    {
        qDebug() << "File does not exists";
    }else
    {
        QTextStream in(&file);
        in.readLine();
        while(!in.atEnd())
        {
            QString line = in.readLine();
            QString firstColumn = line.split(",").first();                nodes.push_back(firstColumn);

        }
        file.close();
    }
    return nodes;
}


QMultiHash<QString, QString> DataHandler::readCsvLinks()
{
    QMultiHash<QString, QString> links;
    int inputsPos = 1;
    int outputsPos = 2;

    //needs refactoring
    QFile file("/home/carlo/Development/C++/CSV/InternetOfEnergy.csv");

    if(!file.open(QFile::ReadOnly | QFile::Text))
    {
        qDebug() << "File does not exists";
    }else
    {
        QTextStream in(&file);
        in.readLine();
        int incounter = 0;
        int outcounter = 0;
        int notCounter = 0;
        while(!in.atEnd())
        {
            QString line = in.readLine();
            QString node = line.split(",").first();
            QString inputs = line.split(",").at(1);
            QString outputs = line.split(",").at(2);

            //needs refactoring
            if(inputs.isEmpty())
            {

            }else
            {
                for(int i=0; i<inputs.split(";").size(); ++i)
                {
                    QString input = inputs.split(";").at(i);
                    links.insert(input, node);
//                    if(links.contains(input,node))
//                    {
//                        //do nothing
//                        ++notCounter;
//                    }else
//                    {
//                        links.insert(input, node);
//                        ++incounter;
//                    }
                }
            }
            if(outputs.isEmpty())
            {

            }else
            {
                for(int j=0; j<outputs.split(";").size(); ++j)
                {
                    QString output = outputs.split(";").at(j);
                    links.insert(node, output);

//                    if(links.contains(node,output))
//                    {
//                        //do nothing
//                        ++notCounter;
//                    }else
//                    {
//                        links.insert(node, output);
//                        ++outcounter;
//                    }

                }
            }
        }
        qDebug() << incounter;
        qDebug() << outcounter;
        qDebug() << notCounter;
        file.close();
    }

    return links;

}

int DataHandler::calculateNodesNumber(std::vector<QString> nodes)
{
    return nodes.size();
}


