#include "xsd.h"

#include "xml.h"
#include "xmlschema.h"

#include <stdio.h>


#include <libxml/parser.h>
#include <libxml/valid.h>
#include <libxml/xmlschemas.h>

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
    fprintf(stderr, "Validation Error: %s", errMsg);
    free(errMsg);
}


Xsd::Xsd()
    : m_file(nullptr),
      m_verbosity(false) // no verbosity by default
{

}

Xsd::~Xsd()
{

}

bool Xsd::validateXml(Xml * const xml)
{
    bool res = false;
    char* buf = xml->getRawBytes();
    unsigned int size = xml->getXmlSize();
    printf("%s\n", buf);

    xmlSchemaParserCtxtPtr parserCtx = NULL;
    xmlSchemaPtr    schema = NULL;
    xmlSchemaValidCtxtPtr validCtx = NULL;

    xmlDocPtr xmlDocPtr = xmlParseMemory(buf, size);
    unsigned int xsd_size = (sizeof(XSD) / sizeof(XSD[0]));
    // parse the raw memory, not a file
    parserCtx = xmlSchemaNewParserCtxt(m_file);
    // from memory defined in the .h file
//    parserCtx = xmlSchemaNewMemParserCtxt(XSD, xsd_size);
    if (parserCtx == NULL) {
        fprintf(stderr, "Failed to load memory to parser ctx\n");
        return res;
    }

    schema = xmlSchemaParse(parserCtx);
    if (schema == NULL) {
        fprintf(stderr, "Could not parse XSD schema\n");
        return res;
    }

    validCtx = xmlSchemaNewValidCtxt(schema);
    if (validCtx == NULL) {
        fprintf(stderr, "Could not create XSD schema validator\n");
        return res;
    }

    xmlSetStructuredErrorFunc(NULL, NULL);
    xmlSetGenericErrorFunc(this, handleValidationError);
    xmlThrDefSetStructuredErrorFunc(NULL, NULL);
    xmlThrDefSetGenericErrorFunc(this, handleValidationError);

    int result = xmlSchemaValidateDoc(validCtx, xmlDocPtr);


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



} // namespace izxml
