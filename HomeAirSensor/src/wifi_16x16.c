/* GIMP RGBA C-Source image dump (wifi_16x16.c) */

#ifdef __AVR__
#include <avr/io.h>
#include <avr/pgmspace.h>
#elif defined(ESP8266)
#include <pgmspace.h>
#elif defined(__IMXRT1052__) || defined(__IMXRT1062__)
// PROGMEM is defefind for T4 to place data in specific memory section
#undef PROGMEM
#define PROGMEM
#else
#define PROGMEM
#endif
const unsigned char WIFI_16x16[] PROGMEM =
"\060\204$!iJ\256s\323\234\030\306<\347\377\377\377\377\377\377\377\377\377"
"\377\377\377\377\377\377\377\377\377\256s\000\000\000\000\000\000\000\000\000\000\000\000mkY\316"
"\337\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377"
"\276\367<\347\070\306\222\224$!\000\000\000\000\216s<\347\377\377\377\377\377\377"
"\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\236\367"
"\266\265\246\061\000\000\206\061\272\326\377\377\377\377\377\377\377\377\327\275"
"\222\224\024\245\266\265\272\326\276\367\377\377\377\377}\357\020\204\000\000\004"
"!\272\326\377\377\377\377\377\377(B\000\000\000\000\000\000\000\000E)\024\245}\357\377\377"
"\337\377\323\234\000\000\307\071]\357\377\377\377\377<\347\070\306\266\265\323"
"\234\212R\000\000\000\000\010B\333\336\377\377\337\377\357{\000\000\317{\377\377\377\377"
"\377\377\377\377\377\377\377\377\377\377\333\336\216s\000\000$!\333\336\377\377"
"}\357E)\000\000y\316\377\377\373\336\070\306\232\326]\357\377\377\377\377\337"
"\377\262\224\000\000(B\236\367\377\377u\255\000\000\256s\377\377\307\071\000\000\000\000\000"
"\000\216s\034\347\377\377\337\377mk\000\000\064\245\377\377}\357\242\020\000\000]\357"
"\070\306\262\224\317{\343\030\000\000\206\061<\347\377\377\272\326\000\000\206\061\276"
"\367\377\377Q\214\000\000\070\306\377\377\377\377\377\377}\357Mk\000\000\357{\377"
"\377\337\377IJ\000\000\272\326\377\377\030\306\000\000\363\234\377\377]\357\337\377"
"\377\377<\347a\010\000\000}\357\377\377\262\224\000\000\327\275\377\377\034\347\000\000"
"\317{\323\234\000\000mk\337\377\377\377\256s\000\000\333\336\377\377\266\265\000\000"
"\024\245\377\377\276\367\000\000\212R\206\061\000\000\000\000]\357\377\377\323\234\000\000"
"\232\326\377\377\070\306\000\000\222\224\377\377\337\377\000\000$!\367\275\206\061"
"\323\234\377\377\377\377\070\306\010B<\347\377\377<\347\010B\327\275\377\377"
"\377\377\256s\060\204";

