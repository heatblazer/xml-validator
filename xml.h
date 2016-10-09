#ifndef XML_H
#define XML_H

namespace izxml {

class Xml
{
public:
    Xml();
    ~Xml();

    bool loadXml(const char* xml);
    char* getRawBytes();
    unsigned int getXmlSize();
    void verbosity(bool on_off);

private:
    void _update();

private:
    bool m_verbosity;
    struct {
        unsigned int size;
        char* data;
    } m_data;
};

} // izxml
#endif // XML_H
