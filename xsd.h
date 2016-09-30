#ifndef XSD_H
#define XSD_H

namespace izxml {

class Xml;

class Xsd
{
public:
    Xsd();
    ~Xsd();

    bool validateXml(Xml* const xml);


};

} // namespace izxml


#endif // XSD_H
