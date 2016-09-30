#include <iostream>


#include "xml.h"
#include "xsd.h"

using namespace std;

int main(int argc, char *argv[])
{
    izxml::Xml xml;
    xml.loadXml(argv[1]);
    izxml::Xsd xsd;

    xsd.validateXml(&xml);

    return 0;
}
