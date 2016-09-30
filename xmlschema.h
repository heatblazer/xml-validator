#ifndef XMLSCHEMA_H
#define XMLSCHEMA_H


static const char XSD[] =
        "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
        "<xs:schema xmlns:xs=\"http://www.w3.org/2001/XMLSchema\">\n"
        "<xs:element name=\"Config\">"
            "<xs:complexType>"
            "<xs:sequence>"
                "<xs:element name=\"Voip\" type=\"xs:string\"/>"
                "<xs:complexType>"
                "<xs:sequence>"
                "<xs:element name=\"SipRegistrar\"/>"
                "<xs:attribute name=\"url\" type=\"xs:string\"/>"
                "<xs:element name=\"SipTransport\"/>"
                    "<xs:attribute name=\"type\" type=\"xs:string\" use=\"required\"/>"
                    "<xs:attribute name=\"port\" type=\"xs:integer\" use=\"required\"/>"
                    "<xs:attribute name=\"portRange\" type=\"xs:integer\" use=\"required\"/>"
                    "<xs:attribute name=\"qos\" type=\"xs:boolean\" use=\"required\"/>"
                "</xs:sequence>"
                "</xs:complexType>"
        "</xs:sequence>"
        "</xs:complexType>"
        "</xs:element>"
        "</xs:schema>"
        ; // end test XSD


#endif // XMLSCHEMA_H
