#include "xsd.h"
#include "xml.h"
#include "utils.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

namespace izxml {

/// more complex tree walker for xsd inspectation
/// global access to a list
/// \brief Xsd::s_pairs
///
QList<pair_t> Xsd::s_pairs;

/// TODO: suggest values needed for the
/// produced error
/// \brief Xsd::handleValidationError
/// \param ctx
/// \param format
///
void Xsd::handleValidationError(void *ctx, const char *format, ...) {

    Xsd* xptr = (Xsd*) ctx;
    (void) xptr;
    char *errMsg;
    va_list args;
    va_start(args, format);
    vasprintf(&errMsg, format, args);
    va_end(args);
    fprintf(stderr, "Validation Error: %s", errMsg);
    free(errMsg);
}


Xsd::Xsd()
    : m_verbosity(true),
      m_xsd({NULL, NULL, NULL}),
      m_data({0, NULL})// no verbosity by default
{

}

Xsd::~Xsd()
{
    _cleanup();
}

bool Xsd::validateXml(Xml * const xml)
{
    bool res = false;
    char* buf = NULL;
    unsigned int size = xml->getXmlSize();
    buf = (char*) malloc(sizeof(char) * size);
    if (buf == NULL) {
        exit(4);
    }
    memcpy(buf, xml->getRawBytes(), size);

    xmlDocPtr xmlDocPtr = xmlParseMemory(buf, size);
    m_xsd.parserCtx = xmlSchemaNewMemParserCtxt(m_data.data, m_data.size);
    free(buf);
    buf = NULL;
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
        xmlFreeDoc(xmlDocPtr);
        exit(3);
    }

    m_xsd.validCtx = xmlSchemaNewValidCtxt(m_xsd.schema);
    if (m_xsd.validCtx == NULL) {
        if (m_verbosity) {
            fprintf(stderr, "Could not create XSD schema validator\n");
        }
        xmlFreeDoc(xmlDocPtr);
        exit(3);
    }

    if (m_verbosity) {
        xmlSetStructuredErrorFunc(NULL, NULL);
        xmlSetGenericErrorFunc(this, handleValidationError);
        xmlThrDefSetStructuredErrorFunc(NULL, NULL);
        xmlThrDefSetGenericErrorFunc(this, handleValidationError);
    }

    int result = xmlSchemaValidateDoc(m_xsd.validCtx, xmlDocPtr);
    xmlFreeDoc(xmlDocPtr);

    res = (result == 0) ? true : false;
    return res;
}

/// parse an XSD file - experimental
/// parse and fill the global list with key val pairs
/// each call to parseXsd will clear the list
/// so be careful
/// \brief Xsd::parseXsd
/// \param fname
/// \return
///
bool Xsd::parseXsd(const char* fname)
{
    // clean the list
    Xsd::s_pairs.clear();

    bool res = false;
    xmlDoc* doc = NULL;
    xmlNode* root_element = NULL;
    doc = xmlReadFile(fname, NULL, 0);
    if (doc == NULL) {
        return res;
    }
    root_element = xmlDocGetRootElement(doc);

    _walker(root_element, &_print_node);
    xmlFreeDoc(doc);
    xmlCleanupParser();

    return res;
}

/// TODO: load raw bytes
/// \brief Xsd::loadXsd
/// \param fname
/// \return
///
bool Xsd::loadXsd(const char *fname)
{
    if (m_data.data != NULL) {
        free(m_data.data);
        m_data.data = NULL;
        m_data.size = 0;
    }

    m_data.size = Utils::getFileSize(fname);
    m_data.data = Utils::loadFileData(fname);
    if (m_data.size <= 0 || m_data.data == NULL) {
        return false;
    }
    return true;
}

void Xsd::verbosity(bool on_off)
{
    m_verbosity = on_off;
}

void Xsd::_cleanup()
{

    Xsd::s_pairs.clear();
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

    if (m_data.data != NULL) {
        free(m_data.data);
        m_data.data = NULL;
        m_data.size = 0;
    }
}

void Xsd::_walker(xmlNode *root, xmlOperation op)
{
    xmlNode* cur = NULL;
    for(cur = root; cur != NULL; cur = cur->next) {
        if (op != NULL) {
            op(cur);
        }
        _walker(cur->children, op);
    }
}

void Xsd::_print_node(xmlNode *node)
{
    if (node != NULL) {
        // put somewhere node name ... map later
        xmlAttr* attr = node->properties;
        while (attr != NULL) {
            xmlChar* val = xmlNodeListGetString(node->doc, attr->children, 1);
            pair_t kv = {(char*)attr->name, (char*)val};
            Xsd::s_pairs.push_back(kv);
            xmlFree(val);
            attr = attr->next;
        }
    }
}


} // namespace izxml
