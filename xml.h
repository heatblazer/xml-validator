#ifndef XML_H
#define XML_H

namespace izxml {

class Xml
{
public:
    Xml();
    ~Xml();
    /// DELETEME
    /// \brief test
    /// \param xml
    ///
    void test(const char* xml);

    void loadXml(const char* xml);
    char* getRawBytes();
    unsigned int getXmlSize();

private:
    unsigned int  _get_file_size(const char* file);

private:
    char* m_data;
    unsigned int m_size;
};

} // izxml
#endif // XML_H
