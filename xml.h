#ifndef XML_H
#define XML_H

namespace izxml {

class Xml
{
public:
    Xml();
    ~Xml();

    void loadXml(const char* xml);
    char* getRawBytes();
    unsigned int getXmlSize();
    void verbosity(bool on_off);

private:
    void _update();
    unsigned int  _get_file_size(const char* file);

private:
    char* m_data;
    unsigned int m_size;
    bool m_verbosity;
};

} // izxml
#endif // XML_H
