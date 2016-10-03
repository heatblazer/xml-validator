#include "xml.h"

#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <string.h>

#include <libxml/parser.h>
#include <libxml/valid.h>

namespace izxml {

Xml::Xml()
    : m_data(nullptr),
      m_verbosity(false)
{

}

Xml::~Xml()
{

}

void Xml::loadXml(const char *xml)
{
    m_size = _get_file_size(xml);
    m_data = new char[sizeof(char)*m_size+1];
    FILE* fp = fopen(xml, "r");
    char c;
    unsigned int i = 0;
    while ( (c = fgetc(fp)) != -1) {
        m_data[i++] = c;
    }
    fclose(fp);
}

char *Xml::getRawBytes()
{
    return m_data;
}

unsigned int Xml::getXmlSize()
{
    return m_size;
}

void Xml::verbosity(bool on_off)
{
    m_verbosity = on_off;
    _update();
}

void Xml::_update()
{
    if (m_verbosity) {
        inithtmlDefaultSAXHandler(NULL);
        initdocbDefaultSAXHandler(NULL);
        initGenericErrorDefaultFunc(NULL);
    }
}

unsigned int Xml::_get_file_size(const char *file)
{
    struct stat buf;
    if ((stat(file, &buf)) != 0) {
        return 0;
    }

    return (unsigned int) buf.st_size;
}


} // namespace izxml
