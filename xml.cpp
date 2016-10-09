#include "xml.h"
#include "utils.h"

#include <libxml/parser.h>
#include <libxml/valid.h>

namespace izxml {

Xml::Xml()
    : m_verbosity(true),
      m_data({0, NULL})
{

}

Xml::~Xml()
{
    if (m_data.data != NULL) {
        free(m_data.data);
        m_data.data = NULL;
        m_data.size = 0;
    }
}

bool Xml::loadXml(const char *xml)
{
    m_data.size = Utils::getFileSize(xml);
    m_data.data = Utils::loadFileData(xml);

    if (m_data.size <=0 || m_data.data == NULL) {
        return false;
    }

    return true;
}

char *Xml::getRawBytes()
{
    return m_data.data;
}

unsigned int Xml::getXmlSize()
{
    return m_data.size;
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


} // namespace izxml
