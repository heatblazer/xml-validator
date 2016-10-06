#ifndef XSD_H
#define XSD_H

#include <QtCore>
// lib xml //
#include <libxml/parser.h>
#include <libxml/valid.h>
#include <libxml/xmlschemas.h>

namespace izxml {

class Xml;

typedef void (*xmlOperation)(xmlNode*);

class Xsd
{
public:
    Xsd();
    ~Xsd();
    static void handleValidationError(void *ctx, const char *format, ...);
    bool validateXml(Xml* const xml);
    bool parseXsd(const char* fname);
    bool loadXsd(const char* fname);
    void verbosity(bool on_off);

private:
    static void _print_node(xmlNode* node);

    void _cleanup();
    void _walker(xmlNode* root, xmlOperation op);
private:
    const char* m_file;
    bool m_verbosity;
    struct {
        xmlSchemaParserCtxtPtr parserCtx;
        xmlSchemaPtr    schema;
        xmlSchemaValidCtxtPtr validCtx;
    } m_xsd;

    QList<QString> m_values;
};

} // namespace izxml


#endif // XSD_H
