#ifndef XSD_H
#define XSD_H

namespace izxml {

class Xml;

class Xsd
{
public:
    Xsd();
    ~Xsd();
    static void handleValidationError(void *ctx, const char *format, ...);
    bool validateXml(Xml* const xml);


};

} // namespace izxml


#endif // XSD_H
