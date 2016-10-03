#include <iostream>
#include <stdio.h>
#include <string.h>

#include "xml.h"
#include "xsd.h"

using namespace std;

static void print_menu(const char* opt)
{
    if (opt != NULL) {
        puts(opt);
    }
    printf("Usage:\n"
              "-a omit all messages\n"
              "-x load xml\n"
              "-s load xsd\n");
}

/// 1 is suppres verbosity
/// 2 is load xml
/// 3 is load xsd
/// 0 is unknow
/// \brief parse_args
/// \param arg
/// \return
///
static int parse_args(char* arg)
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
       std::cout << "Validation : " << (xsd.validateXml(&xml) ? "OK" : "FAIL")
                 << " \n";

    }

    exit(0);
}
