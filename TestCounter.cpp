#define DOCTEST_CONFIG_IMPLEMENT
#include "doctest.h"
//orel55551234@gmail.com
//orel nissan
//322861527
int main(int argc, char** argv) {
    const int numstop=5;
    doctest::Context context;

    // Set default values
    context.setOption("abort-after", numstop);  // Stop test execution after 5 failed assertions
    context.setOption("order-by", "name");  // Sort test cases by name

    context.applyCommandLine(argc, argv);

    // Run tests
    int res = context.run();

    if(context.shouldExit()) {
        return res;
    }
    return res;
}