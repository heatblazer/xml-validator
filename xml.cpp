#include "xml.h"

#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <string.h>

#include <libxml/parser.h>
#include <libxml/valid.h>

namespace izxml {

Xml::Xml()
    : m_data(nullptr)
{

}

Xml::~Xml()
{

}

/// test a simple xml reading to a buffer
/// \brief Xml::test
/// \param xml
///
void Xml::test(const char *xml)
{
    unsigned int fsize = _get_file_size(xml);
    char* xml_src = new char[sizeof(char)*fsize+1]; // don`t forget the +1 or artefacts
                                                    // for missing 0 appear
    FILE* fp = fopen(xml, "r");
    char c;
    unsigned int i = 0;
    while ( (c = fgetc(fp)) != -1) {
        xml_src[i++] = c;
    }
    printf("\n");
    printf("XML source:\n%s\n", xml_src);
    fclose(fp);

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

unsigned int Xml::_get_file_size(const char *file)
{
    struct stat buf;
    if ((stat(file, &buf)) != 0) {
        return 0;
    }

    return (unsigned int) buf.st_size;
}


} // namespace izxml
