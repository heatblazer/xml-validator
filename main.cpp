#include "xml.h"
#include "xsd.h"

/// 1 is suppres verbosity
/// 2 is load xml
/// 3 is load xsd
/// 0 is unknow
/// \brief parse_args
/// \param arg
/// \return
///
int parse_args(char* arg);

///TODO(ilian) add an option to support
/// XSD validation
/// \brief print_menu
/// \param opt
///
void print_menu(const char* opt);


int main(int argc, char *argv[])
{

    if (argc <=2 ) {
        print_menu(NULL);
        exit(10);
    } else {
       izxml::Xml xml;
       izxml::Xsd xsd;
       for(int i=1; argv[i] != NULL; ++i) {
           int res = parse_args(argv[i]);
           switch (res) {
           case 2:
               if (strstr(argv[i+1], ".xml") == NULL) {
                   print_menu("Please, provide .xml file to load after -x opt.");
                   exit(3);
               }
               xml.loadXml(argv[i+1]);
               break;
           case 3:
               if (strstr(argv[i+1], ".xsd") == NULL) {
                   print_menu("Please, provide .xsd file to load after -s opt.");
                   exit(3);
               }
               xsd.loadXsd(argv[i+1]);
               xsd.parseXsd(argv[i+1]);
               break;
           case 1:
               // omit verbosity - set the message level
               xsd.verbosity(false); // TODO
               break;
           case 0:
           default:
               break;
           }
       }
       // DELETEME
       fprintf(stdout, "Validation is: %s\n", (xsd.validateXml(&xml)? "OK" : "FAIL"));
    }
    return 0;
}



void print_menu(const char* opt)
{
    if (opt != NULL) {
        puts(opt);
    }
    printf("Usage:\n"
              "-a omit all messages\n"
              "-x <xml file>\n"
              "-s <xsd file>\n");
}


int parse_args(char* arg)
{
    int res = 0;
    if(strcmp(arg, "-a") == 0) {
        res = 1;
    } else if (strcmp(arg, "-x") == 0) {
        res = 2;
    } else if (strcmp(arg, "-s") == 0) {
        res = 3;
    } else {
        // unnown
        res = 0;
    }
    return res;
}
