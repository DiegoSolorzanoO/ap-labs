#include "logger.h"

int main() {

    infof("%s\n", "This is an information log");
    warnf("%s\n", "This is a warning log");
    errorf("%s\n", "This is an error log");
    panicf("%s\n", "This is a panic log");

    return 0;
}