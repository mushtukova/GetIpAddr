#include <QCoreApplication>

#include "mysnmp.h"

UINT mib2IpAddr[] =                 { 1,3,6,1,2,1,4,20,1,1 };
UINT mib2IpRoute [] =               { 1,3,6,1,2,1,4,21,1,1 };
UINT mib2IpNetToMediaNetAddres[] =  { 1,3,6,1,2,1,4,22,1,3 };
UINT mib2ifDescr [] =               { 1,3,6,1,2,1,2,2,1,2 };

bool getIP();

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    getIP();
    return a.exec();
}

bool getIP()
{
    myMib       mib;
    UINT        Count = 100;

    if(!mib.Init())
        return false;

    if(!mib.GetIP(Count, mib2IpAddr, sizeof(mib2IpAddr)/sizeof(UINT)))
        return false;

    qDebug() << "";

    if(!mib.GetIP(Count, mib2IpNetToMediaNetAddres, sizeof(mib2IpNetToMediaNetAddres)/sizeof(UINT)))
        return false;

    qDebug() << "";

    //if(!mib.GetIP(Count, mib2ifDescr, sizeof(mib2ifDescr)/sizeof(UINT)))
    //    return false;

    return true;
}
