#include "xstring.h"
#include <stdio.h>

int main() {
    String test1 = StringCreate("");
    printf("%d %s\n", StringLength(test1), test1);

    StringReadln(&test1);
    printf("%d %s\n", StringLength(test1), test1);

    String test2 = StringFromUint(0);
    String test3 = StringFromUint(1);
    String test4 = StringFromUint(100);
    String test5 = StringFromUint(-1);
    String test6 = StringFromUint(127252);

    printf("%d %s\n", StringLength(test2), test2);
    printf("%d %s\n", StringLength(test3), test3);
    printf("%d %s\n", StringLength(test4), test4);
    printf("%d %s\n", StringLength(test5), test5);
    printf("%d %s\n", StringLength(test6), test6);

    String test7 = StringCreate("oih0coij1 wu81j 19r 12 j1f0 _  _! 2_1@ #12 _");
    String test8 = StringCreate("oih0coij1 wu81j 19r 12 j1f0 _  _! 2_1@ #12 _");
    printf("%s\n", StringEquals(test7, test8) ? "Equal" : "Not Equal");

    test7 = StringCreate("oih0coij1 wu81j_19r 12 j1f0 _  _! 2_1@ #12 _");
    test8 = StringCreate("oih0coij1 wu81j 19r 12 j1f0 _  _! 2_1@ #12 _");
    printf("%s\n", StringEquals(test7, test8) ? "Equal" : "Not Equal");

    String test9 = StringCreate("ijafiou1");
    StringAppendString(&test9, StringCreate("asdy1 120312-3 1230-"));
    StringAppendChar(&test9, 'a');
    printf("%d %s\n", StringLength(test9), test9);

    StringResize(&test9, 5);
    printf("%d %s\n", StringLength(test9), test9);

    return 0;
}
