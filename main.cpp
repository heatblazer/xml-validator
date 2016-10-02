#include <iostream>
#include <stdio.h>
#include <string.h>

#include "xml.h"
#include "xsd.h"

using namespace std;

static void print_menu()
{
    printf("Usage:\n"
              "-a omit all messages\n"
              "-x load xml\n"
              "-s load xsd\n");
}

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
        print_menu();
        exit(10);
    } else {
       for(int i=1; argv[i] != NULL; ++i) {
           int res = parse_args(argv[i]);
           switch (res) {
           case 2:
           case 3:
           case 1:
           case 0:
           default:
               break;
           }
       }

    }
#if 0
    izxml::Xml xml;
    xml.loadXml(argv[1]);
    izxml::Xsd xsd;

    xsd.validateXml(&xml);
#endif
    return 0;
}
