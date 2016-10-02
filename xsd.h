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
    bool loadXsd(const char* fname);
    void verbosity(bool on_off);

private:
    const char* m_file;
    bool m_verbosity;

};

} // namespace izxml


#endif // XSD_H
