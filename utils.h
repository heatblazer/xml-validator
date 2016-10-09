#ifndef UTILS_H
#define UTILS_H

namespace izxml {

class Utils
{
public:
    static unsigned int  getFileSize(const char* file);
    static char *loadFileData(const char* file);
};

} // izxml
#endif // UTILS_H
