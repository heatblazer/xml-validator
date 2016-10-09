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

struct pair_t
{
    QString name;
    QString value;
};

class Xsd
{
public:
    static QList<pair_t> s_pairs;

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
    bool m_verbosity;
    struct {
        xmlSchemaParserCtxtPtr parserCtx;
        xmlSchemaPtr    schema;
        xmlSchemaValidCtxtPtr validCtx;
    } m_xsd;

    struct {
        size_t size;
        char* data;
    } m_data;

};

} // namespace izxml


#endif // XSD_H
