#include "xsd.h"

#include "xml.h"
#include "xmlschema.h"

#include <stdio.h>
#include <string.h>

namespace izxml {

/// TODO: suggest values needed for the
/// produced error
/// \brief Xsd::handleValidationError
/// \param ctx
/// \param format
///
void Xsd::handleValidationError(void *ctx, const char *format, ...) {

    Xsd* xptr = (Xsd*) ctx;

    char *errMsg;
    va_list args;
    va_start(args, format);
    vasprintf(&errMsg, format, args);
    va_end(args);

    // enumerations only
    char* start = strchr(errMsg, '{');
    if (start != NULL) {
        char* end = strchr(errMsg, '}');
        int len = end - start;
        char* str = new char[len-2];
        start++;
        end--;
        strncpy(str, start, len-2);
        // TODO!!!
        QString s(str);
        QStringList vals = s.split(",");
    }
    fprintf(stderr, "Validation Error: %s", errMsg);
    free(errMsg);
}


Xsd::Xsd()
    : m_file(nullptr),
      m_verbosity(true) // no verbosity by default
{

}

Xsd::~Xsd()
{
    _cleanup();
}

bool Xsd::validateXml(Xml * const xml)
{
    bool res = false;
    char* buf = xml->getRawBytes();
    unsigned int size = xml->getXmlSize();

    xmlDocPtr xmlDocPtr = xmlParseMemory(buf, size);
    unsigned int xsd_size = (sizeof(XSD) / sizeof(XSD[0]));
    // parse the raw memory, not a file
    // from memory defined in the .h file
    m_xsd.parserCtx = xmlSchemaNewParserCtxt(m_file);
//    parserCtx = xmlSchemaNewMemParserCtxt(XSD, xsd_size);
    if (m_xsd.parserCtx == NULL) {
        if (m_verbosity) {
            fprintf(stderr, "Failed to load memory to parser ctx\n");
        }
        exit(3);
    }

    m_xsd.schema = xmlSchemaParse(m_xsd.parserCtx);
    if (m_xsd.schema == NULL) {
        if (m_verbosity) {
            fprintf(stderr, "Could not parse XSD schema\n");
        }
        exit(3);
    }

    m_xsd.validCtx = xmlSchemaNewValidCtxt(m_xsd.schema);
    if (m_xsd.validCtx == NULL) {
        if (m_verbosity) {
            fprintf(stderr, "Could not create XSD schema validator\n");
        }
        exit(3);
    }

    if (m_verbosity) {
        xmlSetStructuredErrorFunc(NULL, NULL);
        xmlSetGenericErrorFunc(this, handleValidationError);
        xmlThrDefSetStructuredErrorFunc(NULL, NULL);
        xmlThrDefSetGenericErrorFunc(this, handleValidationError);
    }

    int result = xmlSchemaValidateDoc(m_xsd.validCtx, xmlDocPtr);

    res = result == 0 ? true : false;
    return res;
}

bool Xsd::loadXsd(const char *fname)
{
    m_file  = fname;
}

void Xsd::verbosity(bool on_off)
{
    m_verbosity = on_off;
}

void Xsd::_cleanup()
{
    // cleanup
    if (m_xsd.parserCtx != NULL) {
        xmlSchemaFreeParserCtxt(m_xsd.parserCtx);

    }

    if (m_xsd.schema != NULL) {
        xmlSchemaFree(m_xsd.schema);
    }

    if (m_xsd.validCtx != NULL) {
        xmlSchemaFreeValidCtxt(m_xsd.validCtx);
    }
}


} // namespace izxml
