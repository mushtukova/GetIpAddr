#ifndef MYSNMP_H
#define MYSNMP_H

#include <QDebug>
#include <snmp.h>
#include <QByteArray>
#include "defines.h"

typedef BOOL (WINAPI *pSnmpExtensionInit)(
                                          IN  DWORD               dwTimeZeroReference,
                                          OUT HANDLE              *hPollForTrapEvent,
                                          OUT AsnObjectIdentifier *supportedView);

typedef BOOL (WINAPI *pSnmpExtensionQuery)(
                                           IN BYTE                   requestType,
                                           IN OUT RFC1157VarBindList *variableBindings,
                                           OUT AsnInteger            *errorStatus,
                                           OUT AsnInteger            *errorIndex);


class mySNMP
{
public:
    mySNMP();
    ~mySNMP();

    BOOL    Init(DWORD dwTimeZeroReference,HANDLE *hPollForTrapEvent,AsnObjectIdentifier *supportedView);
    BOOL    Query(BYTE requestType,OUT RFC1157VarBindList *variableBindings,
                AsnInteger *errorStatus,AsnInteger *errorIndex);

private:
    HINSTANCE             m_hInst = NULL;
    pSnmpExtensionInit    m_Init = NULL;
    pSnmpExtensionQuery   m_Query = NULL;
};

class myMib
{
public:
    BOOL Init();
    BOOL GetIP(UINT count, UINT OID_value[], UINT OID_lenght);

private:
    mySNMP snmp;
};

#endif // MYSNMP_H
