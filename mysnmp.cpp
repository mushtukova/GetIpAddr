#include "mysnmp.h"

mySNMP::mySNMP()
{
    m_hInst = LoadLibraryA( (LPSTR)LibraryName );
    if(m_hInst < (HINSTANCE) HINSTANCE_ERROR){
        return ;
    }
    m_Init	=	(pSnmpExtensionInit)GetProcAddress(m_hInst ,"SnmpExtensionInit");
    m_Query	=	(pSnmpExtensionQuery)GetProcAddress(m_hInst ,"SnmpExtensionQuery");   
}

mySNMP::~mySNMP()
{
    if (m_hInst)
    {
        FreeLibrary( m_hInst );
        m_hInst = NULL;
    }
}

BOOL mySNMP::Init(DWORD dwTimeZeroReference, HANDLE *hPollForTrapEvent, AsnObjectIdentifier *supportedView)
{
    if(m_hInst && m_Init)
        return m_Init(dwTimeZeroReference,hPollForTrapEvent,supportedView);

    return FALSE;
}

BOOL mySNMP::Query(BYTE requestType,OUT RFC1157VarBindList *variableBindings,
                       AsnInteger *errorStatus,AsnInteger *errorIndex)
{
    if(m_hInst && m_Query)
        return m_Query(requestType,variableBindings,errorStatus,errorIndex);

    return FALSE;
}

BOOL myMib::Init()
{
    HANDLE              PollForTrapEvent;
    AsnObjectIdentifier SupportedView;

    return snmp.Init(GetTickCount(),&PollForTrapEvent,&SupportedView);
}

BOOL myMib::GetIP(UINT count, UINT OID_value[], UINT OID_lenght)
{
    AsnObjectIdentifier MIB_oid = { OID_lenght, OID_value };

    RFC1157VarBindList  varBindList;
    RFC1157VarBind      varBind[1];

    AsnInteger          errorStatus;
    AsnInteger          errorIndex;

    AsnObjectIdentifier MIB_NULL = {0,0};

    BOOL                Exit = FALSE;
    UINT                realCount=0;

    varBindList.list = varBind;
    varBindList.len  = 1;
    varBind[0].name  = MIB_NULL;
    SNMP_oidcpy(&varBind[0].name,&MIB_oid);

    while(!Exit)
    {
        if(!snmp.Query(ASN_RFC1157_GETNEXTREQUEST,&varBindList,&errorStatus,&errorIndex))
            Exit=TRUE;
        else
        {
            if(SNMP_oidncmp(&varBind[0].name,&MIB_oid,MIB_oid.idLength))
                Exit=TRUE;
            else
            {
                if(varBind[0].value.asnType != ASN_OCTETSTRING)
                    SnmpUtilPrintAsnAny(&varBind[0].value);
                else
                {
                    QByteArray ByteToStr((const char*) varBind[0].value.asnValue.string.stream,
                            varBind[0].value.asnValue.string.length);
                    qDebug() << QString(ByteToStr);
                }
                realCount++;

                if(realCount >= count)
                    Exit = TRUE;
            }
        }
    }

    SNMP_FreeVarBind(&varBind[0]);

    return Exit;

}
