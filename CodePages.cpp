 /*
  * Unitex
  *
  * Copyright (C) 2001-2009 Universit� Paris-Est Marne-la-Vall�e <unitex@univ-mlv.fr>
  *
  * This library is free software; you can redistribute it and/or
  * modify it under the terms of the GNU Lesser General Public
  * License as published by the Free Software Foundation; either
  * version 2.1 of the License, or (at your option) any later version.
  *
  * This library is distributed in the hope that it will be useful,
  * but WITHOUT ANY WARRANTY; without even the implied warranty of
  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  * Lesser General Public License for more details.
  *
  * You should have received a copy of the GNU Lesser General Public
  * License along with this library; if not, write to the Free Software
  * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA.
  *
  */

#include "Unicode.h"
#include "CodePages.h"
#include "HTMLCharacters.h"
#include "Error.h"
#ifndef HGH_INSERT
#include "codePageKr.h"
#endif // HGH_INSERT


/**
 * This library provides facilities for converting text files from
 * an encoding to another. The process is as follows:
 *
 * input => internal representation in UTF-16 Little-Endian => output
 *
 * When the input encoding is on 1 byte, we use the 'unicode_src' array
 * so that 'unicode_src[c]' will give the unicode equivalent of the
 * 1 byte char 'c'.
 *
 * When the output encoding is on 1 byte, we use the 'unicode_dest' array
 * in the same way than 'unicode_src'. Then, we use the 'init_uni2asc_code_page_array'
 * function in order to fill the 'ascii_dest' so that 'ascii_dest[u]' will
 * give the 1 byte equivalent of the unicode character 'u'. We use this trick
 * in order to use only one initialization function per 1 byte encoding.
 *
 * All the 'init_....' functions take an array of 256 unichar and fill it
 * so that 'array[c]' is the unicode equivalent of the 1 byte character 'c'.
 * Each code page must be documented with an 'usage_....' function.
 *
 * Most code pages have been added by Claude Devis.
 *
 * More encodings can be found at:
 * - http://www.i18nguy.com/unicode/codepages.html#msftwindows
 * - http://www.kostis.net/charsets/
 */

//unichar unicode_src[256];
//unichar unicode_dest[256];
//unsigned char ascii_dest[MAX_NUMBER_OF_UNICODE_CHARS];


/**
 * Microsoft Thai code page (Windows 874).
 */
void init_windows_874(unichar* unicode) {
unichar i;
for (i=0;i<256;i++) unicode[i]=i;
unicode[0x80]=0x20ac;
unicode[0x85]=0x2026;
unicode[0x91]=0x2018;
unicode[0x92]=0x2019;
unicode[0x93]=0x201c;
unicode[0x94]=0x201d;
unicode[0x95]=0x2022;
unicode[0x96]=0x2013;
unicode[0x97]=0x2014;
for (i=0xa1;i<0xdb;i++) unicode[i]=(unichar)(i+(0x0e00-0xa0));
for (i=0xdf;i<0xfc;i++) unicode[i]=(unichar)(i+(0x0e00-0xa0));
}


/**
 * NeXTSTEP code page. This is useful for importing
 * old data from NeXTSTEP computers.
 */
void init_NeXTSTEP(unichar* unicode) {
unichar i;
for (i=0;i<256;i++) unicode[i]=i;
unicode[0xD5]=0xE0;
unicode[0xD7]=0xE2;
unicode[0xDB]=0xE7;
unicode[0xDC]=0xE8;
unicode[0xDD]=0xE9;
unicode[0xDE]=0xEA;
unicode[0xDF]=0xEB;
unicode[0xF4]=0xFB;
unicode[0xEE]=0xF4;
unicode[0xE4]=0xEE;
unicode[0xD9]=0xE4;
unicode[0xE5]=0xEF;
unicode[0xF6]=0xFC;
unicode[0xF0]=0xF6;
unicode[0xF2]=0xF9;
}


/**
 * Microsoft Latin code page (Windows 1252).
 */
void init_windows_1252(unichar* unicode) {
unichar i;
for (i=0;i<256;i++) unicode[i]=i;
unicode[0x80]=0x20ac;
unicode[0x82]=0x201a;
unicode[0x83]=0x0192;
unicode[0x84]=0x201e;
unicode[0x85]=0x2026;
unicode[0x86]=0x2020;
unicode[0x87]=0x2021;
unicode[0x88]=0x02c6;
unicode[0x89]=0x2030;
unicode[0x8a]=0x0160;
unicode[0x8b]=0x2039;
unicode[0x8c]=0x0152;
unicode[0x8e]=0x017d;
unicode[0x91]=0x2018;
unicode[0x92]=0x2019;
unicode[0x93]=0x201c;
unicode[0x94]=0x201d;
unicode[0x95]=0x2022;
unicode[0x96]=0x2013;
unicode[0x97]=0x2014;
unicode[0x98]=0x02dc;
unicode[0x99]=0x2122;
unicode[0x9a]=0x0161;
unicode[0x9b]=0x203a;
unicode[0x9c]=0x0153;
unicode[0x9e]=0x017e;
unicode[0x9f]=0x0178;
}


/**
 * Microsoft Greek code page (Windows 1253).
 */
void init_windows_1253(unichar* unicode) {
unichar i;
for (i=0;i<256;i++) unicode[i]=i;
unicode[0x80]=0x20ac;
unicode[0x82]=0x201a;
unicode[0x83]=0x0192;
unicode[0x84]=0x201e;
unicode[0x85]=0x2026;
unicode[0x86]=0x2020;
unicode[0x87]=0x2021;
unicode[0x89]=0x2030;
unicode[0x8b]=0x2039;
unicode[0x91]=0x2018;
unicode[0x92]=0x2019;
unicode[0x93]=0x201c;
unicode[0x94]=0x201d;
unicode[0x95]=0x2022;
unicode[0x96]=0x2013;
unicode[0x97]=0x2014;
unicode[0x99]=0x2122;
unicode[0x9b]=0x203a;
unicode[0xa1]=0x0385;
unicode[0xa2]=0x0386;
unicode[0xaf]=0x2015;
unicode[0xb4]=0x0384;
unicode[0xb8]=0x0388;
unicode[0xb9]=0x0389;
unicode[0xba]=0x038a;
unicode[0xbc]=0x038c;
unicode[0xbe]=0x038e;
unicode[0xbf]=0x038f;
for (i=0xc0;i<=0xd1;i++) unicode[i]=(unichar)(i+(0x0390-0xc0));
for (i=0xd3;i<=0xfe;i++) unicode[i]=(unichar)(i+(0x0390-0xc0));
}


/**
 * Microsoft Eastern Europe code page (Windows 1250).
 */
void init_windows_1250(unichar* unicode) {
unichar i;
for (i=0;i<256;i++) unicode[i]=i;
unicode[0x80]=0x20ac;
unicode[0x82]=0x201a;
unicode[0x84]=0x201e;
unicode[0x85]=0x2026;
unicode[0x86]=0x2020;
unicode[0x87]=0x2021;
unicode[0x89]=0x2030;
unicode[0x8a]=0x0160;
unicode[0x8b]=0x2039;
unicode[0x8c]=0x015a;
unicode[0x8d]=0x0164;
unicode[0x8e]=0x017d;
unicode[0x8f]=0x0179;
unicode[0x91]=0x2018;
unicode[0x92]=0x2019;
unicode[0x93]=0x201c;
unicode[0x94]=0x201d;
unicode[0x95]=0x2022;
unicode[0x96]=0x2013;
unicode[0x97]=0x2014;
unicode[0x99]=0x2122;
unicode[0x9a]=0x0161;
unicode[0x9b]=0x203a;
unicode[0x9c]=0x015b;
unicode[0x9d]=0x0165;
unicode[0x9e]=0x017e;
unicode[0x9f]=0x017a;
unicode[0xa1]=0x02c7;
unicode[0xa2]=0x02d8;
unicode[0xa3]=0x0141;
unicode[0xa5]=0x0104;
unicode[0xaa]=0x015e;
unicode[0xaf]=0x017b;
unicode[0xb2]=0x02db;
unicode[0xb3]=0x0142;
unicode[0xb9]=0x0105;
unicode[0xba]=0x015f;
unicode[0xbc]=0x013d;
unicode[0xbd]=0x02dd;
unicode[0xbe]=0x013e;
unicode[0xbf]=0x017c;
unicode[0xc0]=0x0154;
unicode[0xc3]=0x0102;
unicode[0xc5]=0x0139;
unicode[0xc6]=0x0106;
unicode[0xc8]=0x010c;
unicode[0xca]=0x0118;
unicode[0xcc]=0x011a;
unicode[0xcf]=0x010e;
unicode[0xd0]=0x0110;
unicode[0xd1]=0x0143;
unicode[0xd2]=0x0147;
unicode[0xd5]=0x0150;
unicode[0xd8]=0x0158;
unicode[0xd9]=0x016e;
unicode[0xdb]=0x0170;
unicode[0xde]=0x0162;
unicode[0xe0]=0x0155;
unicode[0xe3]=0x0103;
unicode[0xe5]=0x013a;
unicode[0xe6]=0x0107;
unicode[0xe8]=0x010d;
unicode[0xea]=0x0119;
unicode[0xec]=0x011b;
unicode[0xef]=0x010f;
unicode[0xf0]=0x0111;
unicode[0xf1]=0x0144;
unicode[0xf2]=0x0148;
unicode[0xf5]=0x0151;
unicode[0xf8]=0x0159;
unicode[0xf9]=0x016f;
unicode[0xfb]=0x0171;
unicode[0xfe]=0x0163;
unicode[0xff]=0x02d9;
}


/**
 * Microsoft Baltic code page (Windows 1257).
 */
void init_windows_1257(unichar* unicode) {
unichar i;
for (i=0;i<256;i++) unicode[i]=i;
unicode[0x80]=0x20ac;
unicode[0x82]=0x201a;
unicode[0x84]=0x201e;
unicode[0x85]=0x2026;
unicode[0x86]=0x2020;
unicode[0x87]=0x2021;
unicode[0x89]=0x2030;
unicode[0x8b]=0x2039;
unicode[0x8d]=0x00a8;
unicode[0x8e]=0x02c7;
unicode[0x8f]=0x00b8;
unicode[0x91]=0x2018;
unicode[0x92]=0x2019;
unicode[0x93]=0x201c;
unicode[0x94]=0x201d;
unicode[0x95]=0x2022;
unicode[0x96]=0x2013;
unicode[0x97]=0x2014;
unicode[0x99]=0x2122;
unicode[0x9b]=0x203a;
unicode[0x9d]=0x00af;
unicode[0x9e]=0x02db;
unicode[0xa8]=0x00d8;
unicode[0xaa]=0x0156;
unicode[0xaf]=0x00c6;
unicode[0xb8]=0x00f8;
unicode[0xba]=0x0157;
unicode[0xbf]=0x00e6;
unicode[0xc0]=0x0104;
unicode[0xc1]=0x012e;
unicode[0xc2]=0x0100;
unicode[0xc3]=0x0106;
unicode[0xc6]=0x0118;
unicode[0xc7]=0x0112;
unicode[0xc8]=0x010c;
unicode[0xca]=0x0179;
unicode[0xcb]=0x0116;
unicode[0xcc]=0x0122;
unicode[0xcd]=0x0136;
unicode[0xce]=0x012a;
unicode[0xcf]=0x013b;
unicode[0xd0]=0x0160;
unicode[0xd1]=0x0143;
unicode[0xd2]=0x0145;
unicode[0xd4]=0x014c;
unicode[0xd8]=0x0172;
unicode[0xd9]=0x0141;
unicode[0xda]=0x015a;
unicode[0xdb]=0x016a;
unicode[0xdd]=0x017b;
unicode[0xde]=0x017d;
unicode[0xe0]=0x0105;
unicode[0xe1]=0x012f;
unicode[0xe2]=0x0101;
unicode[0xe3]=0x0107;
unicode[0xe6]=0x0119;
unicode[0xe7]=0x0113;
unicode[0xe8]=0x010d;
unicode[0xea]=0x017a;
unicode[0xeb]=0x0117;
unicode[0xec]=0x0123;
unicode[0xed]=0x0137;
unicode[0xee]=0x012b;
unicode[0xef]=0x013c;
unicode[0xf0]=0x0161;
unicode[0xf1]=0x0144;
unicode[0xf2]=0x0146;
unicode[0xf4]=0x014d;
unicode[0xf8]=0x0173;
unicode[0xf9]=0x0142;
unicode[0xfa]=0x015b;
unicode[0xfb]=0x016b;
unicode[0xfd]=0x017c;
unicode[0xfe]=0x017e;
unicode[0xff]=0x02d9;
}

/**
 * Microsoft Cyrillic code page (Windows 1251).
 */
void init_windows_1251(unichar* unicode) {
unichar i;
for (i=0;i<256;i++) unicode[i]=i;
unicode[0x80]=0x0402;
unicode[0x81]=0x0403;
unicode[0x82]=0x201a;
unicode[0x83]=0x0453;
unicode[0x84]=0x201e;
unicode[0x85]=0x2026;
unicode[0x86]=0x2020;
unicode[0x87]=0x2021;
unicode[0x88]=0x20ac;
unicode[0x89]=0x2030;
unicode[0x8a]=0x0409;
unicode[0x8b]=0x2039;
unicode[0x8c]=0x040a;
unicode[0x8d]=0x040c;
unicode[0x8e]=0x040b;
unicode[0x8f]=0x040f;
unicode[0x90]=0x0452;
unicode[0x91]=0x2018;
unicode[0x92]=0x2019;
unicode[0x93]=0x201c;
unicode[0x94]=0x201d;
unicode[0x95]=0x2022;
unicode[0x96]=0x2013;
unicode[0x97]=0x2014;
unicode[0x99]=0x2122;
unicode[0x9a]=0x0459;
unicode[0x9b]=0x203a;
unicode[0x9c]=0x045a;
unicode[0x9d]=0x045c;
unicode[0x9e]=0x045b;
unicode[0x9f]=0x045f;
unicode[0xa1]=0x040e;
unicode[0xa2]=0x045e;
unicode[0xa3]=0x0408;
unicode[0xa5]=0x0490;
unicode[0xa8]=0x0401;
unicode[0xaa]=0x0404;
unicode[0xaf]=0x0407;
unicode[0xb2]=0x0406;
unicode[0xb3]=0x0456;
unicode[0xb4]=0x0491;
unicode[0xb8]=0x0451;
unicode[0xb9]=0x2116;
unicode[0xba]=0x0454;
unicode[0xbc]=0x0458;
unicode[0xbd]=0x0405;
unicode[0xbe]=0x0455;
unicode[0xbf]=0x0457;
for (i=0xc0;i<=0xff;i++) unicode[i]=(unichar)(i+(0x0410-0xc0));
}


/**
 * Microsoft Turkish code page (Windows 1254).
 */
void init_windows_1254(unichar* unicode) {
unichar i;
for (i=0;i<256;i++) unicode[i]=i;
unicode[0x80]=0x20ac;
unicode[0x82]=0x201a;
unicode[0x83]=0x0192;
unicode[0x84]=0x201e;
unicode[0x85]=0x2026;
unicode[0x86]=0x2020;
unicode[0x87]=0x2021;
unicode[0x88]=0x02c6;
unicode[0x89]=0x2030;
unicode[0x8a]=0x0160;
unicode[0x8b]=0x2039;
unicode[0x8c]=0x0152;
unicode[0x91]=0x2018;
unicode[0x92]=0x2019;
unicode[0x93]=0x201c;
unicode[0x94]=0x201d;
unicode[0x95]=0x2022;
unicode[0x96]=0x2013;
unicode[0x97]=0x2014;
unicode[0x98]=0x02dc;
unicode[0x99]=0x2122;
unicode[0x9a]=0x0161;
unicode[0x9b]=0x203a;
unicode[0x9c]=0x0153;
unicode[0x9f]=0x0178;
unicode[0xd0]=0x011e;
unicode[0xdd]=0x0130;
unicode[0xde]=0x015e;
unicode[0xf0]=0x011f;
unicode[0xfd]=0x0131;
unicode[0xfe]=0x015f;
}


/**
 * Microsoft Viet code page (Windows 1258).
 */
void init_windows_1258(unichar* unicode) {
unichar i;
for (i=0;i<256;i++) unicode[i]=i;
unicode[0x80]=0x20ac;
unicode[0x82]=0x201a;
unicode[0x83]=0x0192;
unicode[0x84]=0x201e;
unicode[0x85]=0x2026;
unicode[0x86]=0x2020;
unicode[0x87]=0x2021;
unicode[0x88]=0x02c6;
unicode[0x89]=0x2030;
unicode[0x8b]=0x2039;
unicode[0x8c]=0x0152;
unicode[0x91]=0x2018;
unicode[0x92]=0x2019;
unicode[0x93]=0x201c;
unicode[0x94]=0x201d;
unicode[0x95]=0x2022;
unicode[0x96]=0x2013;
unicode[0x97]=0x2014;
unicode[0x98]=0x02dc;
unicode[0x99]=0x2122;
unicode[0x9b]=0x203a;
unicode[0x9c]=0x0153;
unicode[0x9f]=0x0178;
unicode[0xc3]=0x0102;
unicode[0xcc]=0x0300;
unicode[0xd0]=0x0110;
unicode[0xd2]=0x0309;
unicode[0xd5]=0x01a0;
unicode[0xdd]=0x01af;
unicode[0xde]=0x0303;
unicode[0xe3]=0x0103;
unicode[0xec]=0x0301;
unicode[0xf0]=0x0111;
unicode[0xf2]=0x0323;
unicode[0xf5]=0x01a1;
unicode[0xfd]=0x01b0;
unicode[0xfe]=0x20ab;
}


/**
 * ISO Character Set 8859-1 (Latin 1) for Western Europe & USA.
 */
void init_iso_8859_1(unichar* unicode) {
unichar i;
for (i=0;i<256;i++) unicode[i]=i;
}


/**
 * ISO Character Set 8859-15 (Latin 9) for Western Europe & USA.
 */
void init_iso_8859_15(unichar* unicode) {
unsigned short int i;
for (i=0;i<256;i++) unicode[i]=i;
unicode[0xa4]=0x20ac;
unicode[0xa6]=0x0160;
unicode[0xa8]=0x0161;
unicode[0xb4]=0x017d;
unicode[0xb8]=0x017e;
unicode[0xbc]=0x0152;
unicode[0xbd]=0x0153;
unicode[0xbe]=0x0178;
}


/**
 * ISO Character Set 8859-2 (Latin 2) for Central & Eastern Europe.
 */
void init_iso_8859_2(unichar* unicode) {
unichar i;
for (i=0;i<256;i++) unicode[i]=i;
unicode[0xa1]=0x0104;
unicode[0xa2]=0x02d8;
unicode[0xa3]=0x0141;
unicode[0xa5]=0x013d;
unicode[0xa6]=0x015a;
unicode[0xa9]=0x0160;
unicode[0xaa]=0x015e;
unicode[0xab]=0x0164;
unicode[0xac]=0x0179;
unicode[0xae]=0x017d;
unicode[0xaf]=0x017b;
unicode[0xb1]=0x0105;
unicode[0xb2]=0x02db;
unicode[0xb3]=0x0142;
unicode[0xb5]=0x013e;
unicode[0xb6]=0x015b;
unicode[0xb7]=0x02c7;
unicode[0xb9]=0x0161;
unicode[0xba]=0x015f;
unicode[0xbb]=0x0165;
unicode[0xbc]=0x017a;
unicode[0xbd]=0x02dd;
unicode[0xbe]=0x017e;
unicode[0xbf]=0x017c;
unicode[0xc0]=0x0154;
unicode[0xc3]=0x0102;
unicode[0xc5]=0x0139;
unicode[0xc6]=0x0106;
unicode[0xc8]=0x010c;
unicode[0xca]=0x0118;
unicode[0xcc]=0x011a;
unicode[0xcf]=0x010e;
unicode[0xd0]=0x0110;
unicode[0xd1]=0x0143;
unicode[0xd2]=0x0147;
unicode[0xd5]=0x0150;
unicode[0xd8]=0x0158;
unicode[0xd9]=0x016e;
unicode[0xdb]=0x0170;
unicode[0xde]=0x0162;
unicode[0xe0]=0x0155;
unicode[0xe3]=0x0103;
unicode[0xe5]=0x013a;
unicode[0xe6]=0x0107;
unicode[0xe8]=0x010d;
unicode[0xea]=0x0119;
unicode[0xec]=0x011b;
unicode[0xef]=0x010f;
unicode[0xf0]=0x0111;
unicode[0xf1]=0x0144;
unicode[0xf2]=0x0148;
unicode[0xf5]=0x0151;
unicode[0xf8]=0x0159;
unicode[0xf9]=0x016f;
unicode[0xfb]=0x0171;
unicode[0xfe]=0x0163;
unicode[0xff]=0x02d9;
}


/**
 * ISO Character Set 8859-3 (Latin 3).
 */
void init_iso_8859_3(unichar* unicode) {
unichar i;
for (i=0;i<256;i++) unicode[i]=i;
unicode[0xa1]=0x0126;
unicode[0xa2]=0x02d8;
unicode[0xa6]=0x0124;
unicode[0xa9]=0x0130;
unicode[0xaa]=0x015e;
unicode[0xab]=0x011e;
unicode[0xac]=0x0134;
unicode[0xaf]=0x017b;
unicode[0xb1]=0x0127;
unicode[0xb6]=0x0125;
unicode[0xb9]=0x0131;
unicode[0xba]=0x015f;
unicode[0xbb]=0x011f;
unicode[0xbc]=0x0135;
unicode[0xbf]=0x017c;
unicode[0xc5]=0x010a;
unicode[0xc6]=0x0108;
unicode[0xd5]=0x0120;
unicode[0xd8]=0x011c;
unicode[0xdd]=0x016c;
unicode[0xde]=0x015c;
unicode[0xe5]=0x010b;
unicode[0xe6]=0x0109;
unicode[0xf5]=0x0121;
unicode[0xf8]=0x011d;
unicode[0xfd]=0x016d;
unicode[0xfe]=0x015d;
unicode[0xff]=0x02d9;
}


/**
 * ISO Character Set 8859-4 (Latin 4) for Northern Europe.
 */
void init_iso_8859_4(unichar* unicode) {
unichar i;
for (i=0;i<256;i++) unicode[i]=i;
unicode[0xa1]=0x0104;
unicode[0xa2]=0x0138;
unicode[0xa3]=0x0156;
unicode[0xa5]=0x0128;
unicode[0xa6]=0x013b;
unicode[0xa9]=0x0160;
unicode[0xaa]=0x0112;
unicode[0xab]=0x0122;
unicode[0xac]=0x0166;
unicode[0xae]=0x017d;
unicode[0xb1]=0x0105;
unicode[0xb2]=0x02db;
unicode[0xb3]=0x0157;
unicode[0xb5]=0x0129;
unicode[0xb6]=0x013c;
unicode[0xb7]=0x02c7;
unicode[0xb9]=0x0161;
unicode[0xba]=0x0113;
unicode[0xbb]=0x0123;
unicode[0xbc]=0x0167;
unicode[0xbd]=0x014a;
unicode[0xbe]=0x017e;
unicode[0xbf]=0x014b;
unicode[0xc0]=0x0100;
unicode[0xc7]=0x012e;
unicode[0xc8]=0x010c;
unicode[0xca]=0x0118;
unicode[0xcc]=0x0116;
unicode[0xcf]=0x012a;
unicode[0xd0]=0x0110;
unicode[0xd1]=0x0145;
unicode[0xd2]=0x014c;
unicode[0xd3]=0x0136;
unicode[0xd9]=0x0172;
unicode[0xdd]=0x0168;
unicode[0xde]=0x016a;
unicode[0xe0]=0x0101;
unicode[0xe7]=0x012f;
unicode[0xe8]=0x010d;
unicode[0xea]=0x0119;
unicode[0xec]=0x0117;
unicode[0xef]=0x012b;
unicode[0xf0]=0x0111;
unicode[0xf1]=0x0146;
unicode[0xf2]=0x014d;
unicode[0xf3]=0x0137;
unicode[0xf9]=0x0173;
unicode[0xfd]=0x0169;
unicode[0xfe]=0x016b;
unicode[0xff]=0x02d9;
}


/**
 * ISO Character Set 8859-5 for Cyrillic languages.
 */
void init_iso_8859_5(unichar* unicode) {
unichar i;
for (i=0;i<256;i++) unicode[i]=i;
unicode[0xf0]=0x2116;
unicode[0xfd]=0x00a7;
unicode[0xfe]=0x045e;
unicode[0xff]=0x045f;
for (i=0xa1;i<=0xac;i++) unicode[i]=(unsigned short int)(i+(0x0401-0xa1));
for (i=0xae;i<=0xef;i++) unicode[i]=(unsigned short int)(i+(0x040e -0xae));
for (i=0xf1;i<=0xfc;i++) unicode[i]=(unsigned short int)(i+(0x0451-0xf1));
}


/**
 * ISO Character Set 8859-7 for Greek.
 */
void init_iso_8859_7(unichar* unicode) {
unichar i;
for (i=0;i<256;i++) unicode[i]=i;
unicode[0xa1]=0x02bd;
unicode[0xa2]=0x02bc;
unicode[0xaf]=0x2015;
unicode[0xb4]=0x0384;
unicode[0xb5]=0x0385;
unicode[0xb6]=0x0386;
unicode[0xb8]=0x0388;
unicode[0xb9]=0x0389;
unicode[0xba]=0x038a;
unicode[0xbc]=0x038c;
for (i=0xbe;i<=0xd1;i++) unicode[i]=(unsigned short int)(i+(0x038e -0xbe));
for (i=0xd3;i<=0xfe;i++) unicode[i]=(unsigned short int)(i+(0x03a3-0xd3));
}


/**
 * ISO Character Set 8859-9 (Latin 5) for Turkish.
 */
void init_iso_8859_9(unichar* unicode) {
unichar i;
for (i=0;i<256;i++) unicode[i]=i;
unicode[0xd0]=0x011e;
unicode[0xdd]=0x0130;
unicode[0xde]=0x015e;
unicode[0xf0]=0x011f;
unicode[0xfd]=0x0131;
unicode[0xfe]=0x015f;
}


/**
 * ISO Character Set 8859-10 (Latin 6) for Nordic languages.
 */
void init_iso_8859_10(unichar* unicode) {
unichar i;
for (i=0;i<256;i++) unicode[i]=i;
unicode[0xa1]=0x0104;
unicode[0xa2]=0x0112;
unicode[0xa3]=0x0122;
unicode[0xa4]=0x012a;
unicode[0xa5]=0x0128;
unicode[0xa6]=0x0136;
unicode[0xa8]=0x013b;
unicode[0xa9]=0x0110;
unicode[0xaa]=0x0160;
unicode[0xab]=0x0166;
unicode[0xac]=0x017d;
unicode[0xae]=0x016a;
unicode[0xaf]=0x014a;
unicode[0xb1]=0x0105;
unicode[0xb2]=0x0113;
unicode[0xb3]=0x0123;
unicode[0xb4]=0x012b;
unicode[0xb5]=0x0129;
unicode[0xb6]=0x0137;
unicode[0xb8]=0x013c;
unicode[0xb9]=0x0111;
unicode[0xba]=0x0161;
unicode[0xbb]=0x0167;
unicode[0xbc]=0x017e;
unicode[0xbd]=0x2015;
unicode[0xbe]=0x016b;
unicode[0xbf]=0x014b;
unicode[0xc0]=0x0100;
unicode[0xc7]=0x012e;
unicode[0xc8]=0x010c;
unicode[0xca]=0x0118;
unicode[0xcc]=0x0116;
unicode[0xd1]=0x0145;
unicode[0xd2]=0x014c;
unicode[0xd7]=0x0168;
unicode[0xd9]=0x0172;
unicode[0xe0]=0x0101;
unicode[0xe7]=0x012f;
unicode[0xe8]=0x010d;
unicode[0xea]=0x0119;
unicode[0xec]=0x0117;
unicode[0xf1]=0x0146;
unicode[0xf2]=0x014d;
unicode[0xf7]=0x0169;
unicode[0xf9]=0x0173;
unicode[0xff]=0x0138;
}


/**
 * This function uses the 'unicode_dest' array to fill properly
 * the 'ascii_dest' one, so that 'ascii_dest[u]' will be
 * the 1 byte equivalent character of the unicode character 'u',
 * or the character '?' if 'u' has no equivalent in the given 1
 * byte encoding.
 */
void init_uni2asc_code_page_array(unsigned char* ascii_dest,unichar* unicode_dest) {
int i;
for (i=0;i<MAX_NUMBER_OF_UNICODE_CHARS;i++) {
	ascii_dest[i]='?';
}
for (i=0;i<256;i++) {
	ascii_dest[unicode_dest[i]]=(unsigned char)i;
}
}


void usage_windows_1252() {
u_printf("Microsoft Windows Codepage 1252 - Latin I (Western Europe & USA)\n");
u_printf("  Supported Languages :\n");
u_printf("    Afrikaans\n");
u_printf("    Basque\n");
u_printf("    Catalan\n");
u_printf("    Danish\n");
u_printf("    Dutch\n");
u_printf("    English\n");
u_printf("    Faroese\n");
u_printf("    Finnish\n");
u_printf("    French\n");
u_printf("    Galician\n");
u_printf("    German\n");
u_printf("    Icelandic\n");
u_printf("    Indonesian\n");
u_printf("    Italian\n");
u_printf("    Malay\n");
u_printf("    Norwegian\n");
u_printf("    Portuguese\n");
u_printf("    Spanish\n");
u_printf("    Swahili\n");
u_printf("    Swedish\n");
}


void usage_NeXTSTEP() {
u_printf("NeXTSTEP code page\n");
}


void usage_windows_874() {
u_printf("Microsoft Windows Codepage 874 - Thai\n");
}


void usage_windows_1253() {
u_printf("Microsoft Windows Codepage 1253 - Greek\n");
}


void usage_windows_1250() {
u_printf("Microsoft Windows Codepage 1250 - Central Europe\n");
u_printf("  Supported Languages :\n");
u_printf("    Albanian\n");
u_printf("    Croatian\n");
u_printf("    Czech\n");
u_printf("    Hungarian\n");
u_printf("    Polish\n");
u_printf("    Romanian\n");
u_printf("    Serbian (Latin)\n");
u_printf("    Slovak\n");
u_printf("    Slovenian\n");
}


void usage_windows_1257() {
u_printf("Microsoft Windows Codepage 1257 - Baltic\n");
u_printf("  Supported Languages :\n");
u_printf("    Estonian\n");
u_printf("    Latvian\n");
u_printf("    Lithuanian\n");
}


void usage_windows_1251() {
u_printf("Microsoft Windows Codepage 1251 - Cyrillic\n");
u_printf("  Supported Languages :\n");
u_printf("    Azeri (Cyrillic)\n");
u_printf("    Belarusian\n");
u_printf("    Bulgarian\n");
u_printf("    FYRO Macedonian\n");
u_printf("    Kazakh\n");
u_printf("    Kyrgyz\n");
u_printf("    Mongolian\n");
u_printf("    Russian\n");
u_printf("    Serbian (Cyrillic)\n");
u_printf("    Tatar\n");
u_printf("    Ukrainian\n");
u_printf("    Uzbek (Cyrillic)\n");
}


void usage_windows_1254() {
u_printf("Microsoft Windows Codepage 1254 - Turkish\n");
u_printf("  Supported Languages :\n");
u_printf("    Azeri (Latin)\n");
u_printf("    Turkish\n");
u_printf("    Uzbek (Latin)\n");
}


void usage_windows_1258() {
u_printf("Microsoft Windows Codepage 1258 - Viet\n");
u_printf("  Supported Languages :\n");
u_printf("    Vietnamese\n");
}


void usage_iso_8859_1() {
u_printf("ISO Character Set 8859-1  - Latin 1 (Western Europe & USA)\n");
u_printf("  Supported Languages :\n");
u_printf("    Afrikaans\n");
u_printf("    Albanian\n");
u_printf("    Basque\n");
u_printf("    Catalan\n");
u_printf("    Danish\n");
u_printf("    Dutch\n");
u_printf("    English\n");
u_printf("    Faroese\n");
u_printf("    Finnish\n");
u_printf("    French\n");
u_printf("    German\n");
u_printf("    Icelandic\n");
u_printf("    Irish\n");
u_printf("    Italian\n");
u_printf("    Norwegian\n");
u_printf("    Portuguese\n");
u_printf("    Rhaeto-Romanic\n");
u_printf("    Scottish\n");
u_printf("    Spanish\n");
u_printf("    Swahili\n");
u_printf("    Swedish\n");
}


void usage_iso_8859_15() {
u_printf("ISO Character Set 8859-15 - Latin 9 (Western Europe & USA)\n");
u_printf("  Supported Languages :\n");
u_printf("    idem iso-8859-1 with the Euro sign and forgotten French and Finnish letters\n");
}


void usage_iso_8859_2() {
u_printf("ISO Character Set 8859-2  - Latin 2 (Central & Eastern Europe)\n");
u_printf("  Supported Languages :\n");
u_printf("    Albanian\n");
u_printf("    Croatian\n");
u_printf("    Czech\n");
u_printf("    English\n");
u_printf("    German\n");
u_printf("    Hungarian\n");
u_printf("    Polish\n");
u_printf("    Romanian\n");
u_printf("    Serbian (Latin)\n");
u_printf("    Slovak\n");
u_printf("    Slovenian\n");
}


void usage_iso_8859_3() {
u_printf("ISO Character Set 8859-3  - Latin 3 (South Europe)\n");
u_printf("  Supported Languages :\n");
u_printf("    Afrikaans\n");
u_printf("    Catalan\n");
u_printf("    Dutch\n");
u_printf("    English\n");
u_printf("    Esperanto\n");
u_printf("    Galician\n");
u_printf("    German\n");
u_printf("    Italian\n");
u_printf("    Maltese\n");
}


void usage_iso_8859_4() {
u_printf("ISO Character Set 8859-4  - Latin 4 (Northern Europe)\n");
u_printf("  Supported Languages :\n");
u_printf("    Danish\n");
u_printf("    English\n");
u_printf("    Estonian\n");
u_printf("    Finnish\n");
u_printf("    German\n");
u_printf("    Greenlandic\n");
u_printf("    Lappish\n");
u_printf("    Latvian\n");
u_printf("    Lithuanian\n");
u_printf("    Norwegian\n");
u_printf("    Swedish\n");
}


void usage_iso_8859_5() {
u_printf("ISO Character Set 8859-5  - Cyrillic\n");
u_printf("  Supported Languages :\n");
u_printf("    Bulgarian\n");
u_printf("    Byelorussian\n");
u_printf("    English\n");
u_printf("    Macedonian\n");
u_printf("    Russian\n");
u_printf("    Serbian\n");
u_printf("    Ukrainian\n");
}


void usage_iso_8859_7() {
u_printf("ISO Character Set 8859-7  - Greek\n");
u_printf("  Supported Languages :\n");
u_printf("    Greek modern monotonic\n");
}


void usage_iso_8859_9() {
u_printf("ISO Character Set 8859-9  - Latin 5 (Turkish)\n");
u_printf("  Supported Languages :\n");
u_printf("    Danish\n");
u_printf("    Dutch\n");
u_printf("    English\n");
u_printf("    Finnish\n");
u_printf("    French\n");
u_printf("    German\n");
u_printf("    Irish\n");
u_printf("    Italian\n");
u_printf("    Norwegian\n");
u_printf("    Portuguese\n");
u_printf("    Spanish\n");
u_printf("    Swedish\n");
u_printf("    Turkish\n");
}


void usage_iso_8859_10() {
u_printf("ISO Character Set 8859-10 - Latin 6 (Nordic)\n");
u_printf("  Supported Languages :\n");
u_printf("    Danish\n");
u_printf("    English\n");
u_printf("    Estonian\n");
u_printf("    Finnish\n");
u_printf("    German\n");
u_printf("    German\n");
u_printf("    Inuit (Greenlandic Eskimo)\n");
u_printf("    Lappish (non-Skolt Sami)\n");
u_printf("    Latvian\n");
u_printf("    Lithuanian\n");
u_printf("    Norwegian\n");
u_printf("    Swedish\n");
}

#ifndef HGH_INSERT
convert_windows949kr_uni_CodePageOnly uniKoran949;
void usage_windows_949() {
u_printf("Microsoft Windows Codepage 949 - Korean\n");
}


/**
 * Reads a Korean character encoded in Windows 949.
 */
int read_mbcs_char(ABSTRACTFILE* f) {
int page;
int off;
unsigned char c;
if (af_fread((void*)&c,1,1,f)==1)
  page=(int)c;
else
  return EOF;

if(page&0x80){
	if (af_fread(&c,1,1,f)==1)
	  off=(int)c;
	else
	  return EOF;

	page=page&0x7F;
} else {
	off = page;
	page = 0;
}
return uniKoran949.mbcsUni949Table[page*256+off];
}


/**
 * Writes a Korean character encoded in Windows 949.
 */
int write_mbcs_char(unichar c,ABSTRACTFILE* f) {
int ret;
unsigned char cw;
cw=(unsigned char)(uniKoran949.uniMbcs949Table[c*2]&0xFF);
if (af_fwrite(&cw,1,1,f)!=1)
  return EOF;
else
  ret=(int)c;
if(c<128) return ret;

cw=(unsigned char)(uniKoran949.uniMbcs949Table[c*2+1]&0xFF);
if (af_fwrite(&cw,1,1,f)!=1)
  return EOF;
else
  ret=(int)c;
return ret;
}
#endif


void usage_utf8() {
u_printf("UTF8: universal multi-bytes encoding with a variable code length\n");
}


void usage_utf16_le() {
u_printf("UTF16 Little-Endian: universal 2-bytes encoding\n");
u_printf("This encoding requires that the 2 first bytes of a file are FF FE\n");
u_printf("Bytes are encoded in the little endian order, that is to say lower\n");
u_printf("byte first.\n");
}


void usage_utf16_be() {
u_printf("UTF16 Big-Endian: universal 2-bytes encoding\n");
u_printf("This encoding requires that the 2 first bytes of a file are FE FF\n");
u_printf("Bytes are encoded in the big endian order, that is to say higher\n");
u_printf("byte first.\n");
}


/**
 * This function reads a 1 byte character from the given file
 * returns its unicode equivalent, or EOF if the end of file has
 * been reached.
 */
int read_1_byte_character(ABSTRACTFILE* f,unichar* unicode_src) {
unsigned char c;
if (!af_fread(&c,1,1,f)) return EOF;
return unicode_src[(unsigned char)c];
}


/**
 * This function encodes the character 'c' into a 1 byte one, and
 * writes it to the given file. Returns 1 if OK or 0 if an error occurs.
 */
int write_1_byte_character(unsigned char c,ABSTRACTFILE* f) {
return af_fwrite(&c,1,1,f);
}


int write_one_char(unichar c,ABSTRACTFILE* f,struct encoding* encoding,unsigned char* ascii_dest) {
if (encoding->type==E_ONE_BYTE_ENCODING) {
	return write_1_byte_character(ascii_dest[c],f);
} else {
	return encoding->output_function(c,f);
}
}


/**
 * This function writes the number of the given unicode character to the
 * file 'f' as a decimal integer. We give an output function, because
 * one can want to encode the 'e' cute with '&#233;' but with
 * '&' '#' '2' '3' '3' and ';' encoded as 2-bytes characters, for instance
 * with an UTF16 output encoding.
 */
void write_integer(int n,ABSTRACTFILE* f,struct encoding* encoding,unsigned char* ascii_dest) {
if (n<10) {
	write_one_char('0'+n,f,encoding,ascii_dest);
	return;
}
write_integer(n/10,f,encoding,ascii_dest);
write_one_char('0'+n%10,f,encoding,ascii_dest);
}


/**
 * This function prints the unicode character 'c' to the file 'f' according
 * to the output function of the given encoding. If the character is not supported
 * by the encoding, the function can encode it in the HTML
 * form '&#XXX;' if specified by the parameters 'encode_all_characters'
 * and 'encode_HTML_control_characters'.
 *
 */
void html_characters_encoding(unichar c,struct encoding* encoding,ABSTRACTFILE* f,
			int encode_all_characters,int encode_HTML_control_characters,
			unsigned char* ascii_dest) {
/* First, we check if we have an HTML control character */
if (is_HTML_control_character(c)) {
	/* If necessary, we encode it in HTML */
	if (encode_HTML_control_characters) {
		write_one_char('&',f,encoding,ascii_dest);
		switch (c) {
			case '<': write_one_char('l',f,encoding,ascii_dest);
			          write_one_char('t',f,encoding,ascii_dest);
			          break;
			case '>': write_one_char('g',f,encoding,ascii_dest);
			          write_one_char('t',f,encoding,ascii_dest);
			          break;
			case '&': write_one_char('a',f,encoding,ascii_dest);
			          write_one_char('m',f,encoding,ascii_dest);
			          write_one_char('p',f,encoding,ascii_dest);
			          break;
			case '\'': write_one_char('q',f,encoding,ascii_dest);
			           write_one_char('u',f,encoding,ascii_dest);
			           write_one_char('o',f,encoding,ascii_dest);
			           write_one_char('t',f,encoding,ascii_dest);
			           break;
			default: error("Internal error in html_characters_encoding:\n");
					fatal_error("inconsistency about HTML characters\n");
		}
		write_one_char(';',f,encoding,ascii_dest);
		return;
	}
	/* Otherwise, we just print it, but only if it is supported by the encoding */
	if (encoding->can_be_encoded_function(c,ascii_dest)) {

	} else {
		/* If the control character can not be encoded as it, we
		 * print the default character '?' */
		write_one_char('?',f,encoding,ascii_dest);
	}
	return;
}
/* Here, we have to deal with a normal character */
if (!encoding->can_be_encoded_function(c,ascii_dest) && encode_all_characters) {
	/* If the character can not be encoded as it, we encode it like &#1200; */
	write_one_char('&',f,encoding,ascii_dest);
	write_one_char('#',f,encoding,ascii_dest);
	write_integer(c,f,encoding,ascii_dest);
	write_one_char(';',f,encoding,ascii_dest);
	return;
}
/* Otherwise, we just print the character */
write_one_char(c,f,encoding,ascii_dest);
}


/**
 * These 4 functions are shorcuts for invoking the 'html_characters_encoding'
 * function.
 */
void f00(unichar c,struct encoding* encoding,ABSTRACTFILE* f,unsigned char* ascii_dest) {
html_characters_encoding(c,encoding,f,0,0,ascii_dest);
}
void f01(unichar c,struct encoding* encoding,ABSTRACTFILE* f,unsigned char* ascii_dest) {
html_characters_encoding(c,encoding,f,0,1,ascii_dest);
}
void f10(unichar c,struct encoding* encoding,ABSTRACTFILE* f,unsigned char* ascii_dest) {
html_characters_encoding(c,encoding,f,1,0,ascii_dest);
}
void f11(unichar c,struct encoding* encoding,ABSTRACTFILE* f,unsigned char* ascii_dest) {
html_characters_encoding(c,encoding,f,1,1,ascii_dest);
}


/**
 * Reads one char from 'input', according to the given encoding, using
 * 'unicode_src' if the encoding is a 1-byte one.
 *
 */
int read_one_char(ABSTRACTFILE* input,struct encoding* encoding,unichar* unicode_src) {
if (encoding->type==E_ONE_BYTE_ENCODING) {
	return read_1_byte_character(input,unicode_src);
} else {
	return encoding->input_function(input);
}
}


/**
 * Takes an input file with a given input encoding and copies
 * it to an output file according to a given output encoding.
 * It returns CONVERSION_OK if the conversion succeeded, an error code
 * otherwise. The other parameters have the following meanings:
 *
 * - 'decode_HTML_normal_characters': if non null, indicates that HTML
 *      character declarations like '&#220', '&#xF12' or '&alpha;' must be
 *      decoded instead of being printed as it
 * - 'decode_control_normal_characters': if non null, indicates that HTML control
 *      character declarations like '&gt; must be decoded instead of being
 *      printed as it
 * - 'encode_non_ASCII_characters': if non null, indicates that non ASCII characters
 *      must be encoded as HTML strings like '&#228;' instead of being encoded
 *      as any other character
 * - 'encode_HTML_control_characters': if non null, indicates that HTML control
 *      characters like '<' must be encoded as HTML strings like '&#228;' instead
 *      of being encoded as any other character
 */
int convert(U_FILE* input,U_FILE* output,struct encoding* input_encoding,
			struct encoding* output_encoding,
            int decode_HTML_normal_characters,int decode_HTML_control_characters,
            int encode_all_characters,int encode_HTML_control_characters) {
/*
 * Initialization for the source encoding.
 */
int tmp;
void (*z)(unichar,struct encoding*,ABSTRACTFILE*,unsigned char*);
unichar unicode_src[256];
unichar unicode_dest[256];
unsigned char ascii_dest[MAX_NUMBER_OF_UNICODE_CHARS];
switch(input_encoding->type) {
	/* For UTF-16 encodings, we need to read the 2-byte header */
	case E_UTF16_LE:
		tmp=u_fgetc_UTF16LE(input->f);
		if (tmp!=U_BYTE_ORDER_MARK) {
			return INPUT_FILE_NOT_IN_UTF16_LE;
		}
		break;
	case E_UTF16_BE:
		tmp=u_fgetc_UTF16BE(input->f);
		if (tmp!=U_BYTE_ORDER_MARK) {
			return INPUT_FILE_NOT_IN_UTF16_BE;
		}
		break;
	case E_ONE_BYTE_ENCODING: input_encoding->init_function(unicode_src);
		break;
}
/*
 * If necessary, we write the UTF16 2-byte header to the destination file.
 * If the destination encoding is a 1 byte one, we call its initialiaztion
 * function.
 */
switch(output_encoding->type) {
	case E_UTF16_LE: u_fputc_UTF16LE(U_BYTE_ORDER_MARK,output->f); break;
	case E_UTF16_BE: u_fputc_UTF16BE(U_BYTE_ORDER_MARK,output->f); break;
	case E_ONE_BYTE_ENCODING: output_encoding->init_function(unicode_dest);
							init_uni2asc_code_page_array(ascii_dest,unicode_dest);
							break;
}
/* We choose the function that will be used to encode HTML characters
 * if necessary */
if (encode_all_characters)
	if (encode_HTML_control_characters)
		z=f11;
	else z=f10;
else if (encode_HTML_control_characters)
		z=f01;
	else z=f00;
/* Then we read all the characters from the input file and we encode them */
while ((tmp=read_one_char(input->f,input_encoding,unicode_src))!=EOF) {
	if (!decode_HTML_normal_characters || tmp!='&') {
		/* If we do not need to decode HTML normal characters like &#eacute;
		 * or if we do not have '&', we can print the character to the output */
		z((unichar)tmp,output_encoding,output->f,ascii_dest);
	} else {
		/* We read everything until we find the ';' character */
		char temp[257];
		int i=0;
		do {
			tmp=read_one_char(input->f,input_encoding,unicode_src);
			if (tmp==EOF) {
				/* If we find an unexpected end of file, we raise an error */
				return ERROR_IN_HTML_CHARACTER_NAME;
			}
			if (tmp>0x7F) {
				/* If the character is not an ascii one, it is an error */
				i=-1;
				break;
			}
			temp[i++]=(char)tmp;
		} while (tmp!=';' && i<256);
		if (i==-1) {
			/* If the character declaration contains a non ascii character,
			 * we print an error message and we write '?' to the output. */
			error("Non ASCII character in a HTML character declaration of the form &......;\n");
			z('?',output_encoding,output->f,ascii_dest);
		} else if (i==1) {
			/* If we have an empty code '&;' we print an error message and
			 * we print nothing to the output. */
			 error("Empty HTML code &;\n");
		}
		else if (tmp!=';' && i==256) {
			/* If the HTML character if too long, we print an error message
			 * and print '?' in the output. */
			 error("Too long HTML character of the form &........;\n");
			 z('?',output_encoding,output->f,ascii_dest);
		} else {
			temp[i-1]='\0';
			/* Now, temp contains "#228" or "eacute". We look for the associated
			 * code and we print it to the output if any; otherwise, we print
			 * the '?' character. */
			i=get_HTML_character(temp,decode_HTML_control_characters);
			switch (i) {
				case UNKNOWN_CHARACTER: z('?',output_encoding,output->f,ascii_dest); break;
				case MALFORMED_HTML_CODE: error("Malformed HTML character declaration &%s;\n",temp);
									z('?',output_encoding,output->f,ascii_dest); break;
				case DO_NOT_DECODE_CHARACTER:
					/* If we have a control character that we must not decode like '&gt;',
					 * we print it as it to the output */
					 z('&',output_encoding,output->f,ascii_dest);
					 for (int j=0;temp[j]!='\0';j++) {
					 	z(temp[j],output_encoding,output->f,ascii_dest);
					 }
					 z(';',output_encoding,output->f,ascii_dest);
					 break;
				default: if (!is_HTML_control_character(i) || decode_HTML_control_characters) {
							/* If we have a normal character or if we can
							 * encode control characters, then we print it */
							z(i,output_encoding,output->f,ascii_dest);
						} else {
							/* If we have a control character and if we can not decode it,
							 * then we copy the string representation that was in
							 * the input */
							z('&',output_encoding,output->f,ascii_dest);
							for (int j=0;temp[j]!='\0';j++) {
								z(temp[j],output_encoding,output->f,ascii_dest);
							}
							z(';',output_encoding,output->f,ascii_dest);
					 		break;
						}
			}
		}
	}
}
return CONVERSION_OK;
}



/* Array of all encodings */
struct encoding** encodings=NULL;
/* Size of in 'encodings' */
int number_of_encodings=0;
/* Root of the encoding name tree */
struct search_tree_node* encoding_names=NULL;


/**
 * Allocates, initializes and returns a new encoding description.
 */
struct encoding* new_encoding() {
struct encoding* encoding=(struct encoding*)malloc(sizeof(struct encoding));
if (encoding==NULL) {
   fatal_alloc_error("new_encoding");
}
encoding->name=NULL;
encoding->aliases=NULL;
encoding->number_of_aliases=0;
encoding->init_function=NULL;
encoding->input_function=NULL;
encoding->output_function=NULL;
encoding->usage_function=NULL;
encoding->can_be_encoded_function=NULL;
return encoding;
}


/**
 * This function is used for unrestricted encodings like UTF8 and UTF16.
 */
int can_always_encode(unichar c,unsigned char* a) {
/* Stupid expression, but its real purpose is to avoid the 'unused parameter warning' */
return 1 || c || a;
}


/**
 * This function is used for 1 byte encodings. It returns 1 if 'c'
 * can be encoded in the current encoding, 0 otherwise. The function assumes
 * that the 'ascii_dest' array has been initialized with
 * 'init_uni2asc_code_page_array'.
 */
int can_encode(unichar c,unsigned char* ascii_dest) {
if (c=='?' || ascii_dest[c]!='?') return 1;
return 0;
}


/**
 * Converts an ASCII string to lower case.
 *
 * WARNING: as the given string is modified, this function will
 *          raise an error if called on a constant string.
 */
void strtolower(char* s) {
if (s==NULL) return;
for (int i=0;s[i];i++) {
	if (s[i]>='A' && s[i]<='Z') s[i]=s[i]+32; /* 32 = 'a'-'A' */
}
}


/**
 * This function installs a new one byte encoding. 'name' is the main
 * name of the encoding and 'aliases', if not NULL, contains equivalent
 * names of it. A non NULL code page initialization function must be
 * given. The function will raise a fatal error if the name is NULL,
 * the initialization function is NULL or the name or an alias is
 * already used by another encoding.
 * If not NULL, the 'aliases' array is supposed to contains NULL as last
 * element.
 */
void install_one_byte_encoding(const char* name,void (*init_function)(unichar*),
                               void (*usage_function)(void),
                               const char** aliases) {
if (name==NULL) {
   fatal_error("NULL name error in install_one_byte_encoding\n");
}
/* First we build the encoding */
struct encoding* encoding=new_encoding();
encoding->type=E_ONE_BYTE_ENCODING;
if ((encoding->name=strdup(name))==NULL) {
	fatal_alloc_error("install_one_byte_encoding");
}
strtolower(encoding->name);
if (init_function==NULL) {
	fatal_error("NULL init_function error in install_one_byte_encoding\n");
}
encoding->init_function=init_function;
if (usage_function==NULL) {
	fatal_error("NULL usage_function error in install_one_byte_encoding\n");
}
encoding->usage_function=usage_function;
encoding->can_be_encoded_function=can_encode;
encoding->input_function=NULL;
encoding->output_function=NULL;
if (aliases==NULL) {
	/* If there is no aliases, we can return */
}
int i=0;
while (aliases[i]!=NULL) {
	encoding->aliases=(char**)realloc(encoding->aliases,(i+1)*sizeof(char*));
	if (encoding->aliases==NULL) {
	   fatal_alloc_error("install_one_byte_encoding");
	}
	encoding->aliases[i]=strdup(aliases[i]);
	strtolower(encoding->aliases[i]);
	if (encoding->aliases[i]==NULL) {
	   fatal_alloc_error("install_one_byte_encoding");
	}
	i++;
}
encoding->number_of_aliases=i;
/* Now, we install this encoding, enlarging the encoding array */
encodings=(struct encoding**)realloc(encodings,(number_of_encodings+1)*sizeof(struct encoding*));
if (encodings==NULL) {
   fatal_alloc_error("install_one_byte_encoding");
}
encodings[number_of_encodings]=encoding;
/* Then we insert the encoding name and its aliases in the encoding name tree,
 * associating them to the corresponding index in 'encodings'. The insertion
 * operation will raise a fatal error if the given encoding name is already
 * in the encoding name tree. */
if (!insert_string(&encoding_names,name,number_of_encodings)) {
	fatal_error("Internal error in install_multi_bytes_encoding: encoding name %s already used\n",name);
}
for (i=0;i<encoding->number_of_aliases;i++) {
	if (!insert_string(&encoding_names,encoding->aliases[i],number_of_encodings)) {
		fatal_error("Internal error in install_multi_bytes_encoding: encoding name %s already used\n",encoding->aliases[i]);
	}
}
/* And finally, we do not forget to increase the number of encodings */
number_of_encodings++;
}


/**
 * This function installs a new multi-bytes encoding. 'name' is the main
 * name of the encoding and 'aliases', if not NULL, contains equivalent
 * names of it. Non NULL input and output functions must be
 * given. The function will raise a fatal error if the name is NULL,
 * the input or output function is NULL or the name or an alias is
 * already used by another encoding.
 * If not NULL, the 'aliases' array is supposed to contains NULL as last
 * element.
 *
 * We consider that a multi-bytes encoding can encode any character.
 */
void install_multi_bytes_encoding(const char* name,int type,int (*input_function)(ABSTRACTFILE*),
								int (*output_function)(unichar,ABSTRACTFILE*),
								void (*usage_function)(void),
								const char** aliases) {
if (name==NULL) {
   fatal_error("NULL name error in install_multi_bytes_encoding\n");
}
/* First we build the encoding */
struct encoding* encoding=new_encoding();
encoding->type=type;
if ((encoding->name=strdup(name))==NULL) {
	fatal_alloc_error("install_multi_bytes_encoding");
}
strtolower(encoding->name);
if (input_function==NULL) {
	fatal_error("NULL input_function error in install_multi_bytes_encoding\n");
}
encoding->input_function=input_function;
if (output_function==NULL) {
	fatal_error("NULL output_function error in install_multi_bytes_encoding\n");
}
encoding->output_function=output_function;
if (usage_function==NULL) {
	fatal_error("NULL usage_function error in install_multi_bytes_encoding\n");
}
encoding->usage_function=usage_function;
/*
 * We consider that a multi-bytes encoding can encode any character.
 */
encoding->can_be_encoded_function=can_always_encode;
if (aliases==NULL) {
	/* If there is no aliases, we can return */
}
int i=0;
while (aliases[i]!=NULL) {
	encoding->aliases=(char**)realloc(encoding->aliases,(i+1)*sizeof(char*));
	if (encoding->aliases==NULL) {
	   fatal_alloc_error("install_multi_bytes_encoding");
	}
	encoding->aliases[i]=strdup(aliases[i]);
	strtolower(encoding->aliases[i]);
	if (encoding->aliases[i]==NULL) {
	   fatal_alloc_error("install_multi_bytes_encoding");
	}
	i++;
}
encoding->number_of_aliases=i;
/* Now, we install this encoding, enlarging the encoding array */
encodings=(struct encoding**)realloc(encodings,(number_of_encodings+1)*sizeof(struct encoding*));
if (encodings==NULL) {
   fatal_alloc_error("install_multi_bytes_encoding");
}
encodings[number_of_encodings]=encoding;
/* Then we insert the encoding name and its aliases in the encoding name tree,
 * associating them to the corresponding index in 'encodings'. The insertion
 * operation will raise a fatal error if the given encoding name is already
 * in the encoding name tree. */
if (!insert_string(&encoding_names,name,number_of_encodings)) {
	fatal_error("Internal error in install_multi_bytes_encoding: encoding name %s already used\n",name);
}
for (i=0;i<encoding->number_of_aliases;i++) {
	if (!insert_string(&encoding_names,encoding->aliases[i],number_of_encodings)) {
		fatal_error("Internal error in install_multi_bytes_encoding: encoding name %s already used\n",encoding->aliases[i]);
	}
}
/* And finally, we do not forget to increase the number of encodings */
number_of_encodings++;
}


/**
 * This function install all the available encodings. If you
 * want to add an encoding, you must install it via this function.
 *
 * NOTE: all encoding will be put in lower case in order to match them
 *       ignoring case.
 */
void install_all_encodings() {
/*
 * First we install UTF encodings.
 */
const char* aliases_utf8[2]={"utf-8",NULL};
install_multi_bytes_encoding("utf8",E_UTF8,u_fgetc_UTF8_raw,u_fputc_UTF8_raw,usage_utf8,aliases_utf8);
const char* aliases_utf16_le[4]={"utf-16-le","utf16le","little-endian",NULL};
install_multi_bytes_encoding("utf16-le",E_UTF16_LE,u_fgetc_UTF16LE_raw,u_fputc_UTF16LE_raw,usage_utf16_le,aliases_utf16_le);
const char* aliases_utf16_be[4]={"utf-16-be","utf16be","big-endian",NULL};
install_multi_bytes_encoding("utf16-be",E_UTF16_BE,u_fgetc_UTF16BE_raw,u_fputc_UTF16BE_raw,usage_utf16_be,aliases_utf16_be);
/*
 * ISO encodings
 */
const char* aliases_iso_8859_1[4]={"iso88591","latin1","latin-1",NULL};
install_one_byte_encoding("iso-8859-1",init_iso_8859_1,usage_iso_8859_1,aliases_iso_8859_1);
const char* aliases_iso_8859_2[4]={"iso88592","latin2","latin-2",NULL};
install_one_byte_encoding("iso-8859-2",init_iso_8859_2,usage_iso_8859_2,aliases_iso_8859_2);
const char* aliases_iso_8859_3[4]={"iso88593","latin3","latin-3",NULL};
install_one_byte_encoding("iso-8859-3",init_iso_8859_3,usage_iso_8859_3,aliases_iso_8859_3);
const char* aliases_iso_8859_4[4]={"iso88594","latin4","latin-4",NULL};
install_one_byte_encoding("iso-8859-4",init_iso_8859_4,usage_iso_8859_4,aliases_iso_8859_4);
const char* aliases_iso_8859_5[4]={"iso88595","latin5","latin-5",NULL};
install_one_byte_encoding("iso-8859-5",init_iso_8859_5,usage_iso_8859_5,aliases_iso_8859_5);
const char* aliases_iso_8859_7[4]={"iso88597","latin7","latin-7",NULL};
install_one_byte_encoding("iso-8859-7",init_iso_8859_7,usage_iso_8859_7,aliases_iso_8859_7);
const char* aliases_iso_8859_9[4]={"iso88599","latin9","latin-9",NULL};
install_one_byte_encoding("iso-8859-9",init_iso_8859_9,usage_iso_8859_9,aliases_iso_8859_9);
const char* aliases_iso_8859_10[4]={"iso885910","latin10","latin-10",NULL};
install_one_byte_encoding("iso-8859-10",init_iso_8859_10,usage_iso_8859_10,aliases_iso_8859_10);
const char* aliases_iso_8859_15[4]={"iso885915","latin15","latin-15",NULL};
install_one_byte_encoding("iso-8859-15",init_iso_8859_15,usage_iso_8859_15,aliases_iso_8859_15);
/*
 * Microsoft Windows code pages
 *
 * As the Microsoft Windows code page 1252 is the default one on many computers,
 * we associate to it aliases for some language names.
 */
const char* aliases_windows_874[4]={"windows-874","windows874","thai",NULL};
install_one_byte_encoding("ms-windows-874",init_windows_874,usage_windows_874,aliases_windows_874);
#ifndef HGH_INSERT
/* Note that ms-windows-949 is a multi-bytes encoding */
const char* aliases_windows_949[4]={"windows-949","windows949","korean",NULL};
install_multi_bytes_encoding("ms-windows-949",E_MBCS_KR,read_mbcs_char,write_mbcs_char,usage_windows_949,aliases_windows_949);
#endif
const char* aliases_windows_1250[4]={"windows-1250","windows1250","czech",NULL};
install_one_byte_encoding("ms-windows-1250",init_windows_1250,usage_windows_1250,aliases_windows_1250);
const char* aliases_windows_1251[4]={"windows-1251","windows1251","cyrillic",NULL};
install_one_byte_encoding("ms-windows-1251",init_windows_1251,usage_windows_1251,aliases_windows_1251);
const char* aliases_windows_1252[10]={"windows-1252","windows1252","french","english",
								"german","spanish","portuguese","italian",
								"norwegian",NULL};
install_one_byte_encoding("ms-windows-1252",init_windows_1252,usage_windows_1252,aliases_windows_1252);
const char* aliases_windows_1253[4]={"windows-1253","windows1253","greek",NULL};
install_one_byte_encoding("ms-windows-1253",init_windows_1253,usage_windows_1253,aliases_windows_1253);
const char* aliases_windows_1254[4]={"windows-1254","windows1254","turkish",NULL};
install_one_byte_encoding("ms-windows-1254",init_windows_1254,usage_windows_1254,aliases_windows_1254);
const char* aliases_windows_1257[4]={"windows-1257","windows1257","baltic",NULL};
install_one_byte_encoding("ms-windows-1257",init_windows_1257,usage_windows_1257,aliases_windows_1257);
const char* aliases_windows_1258[5]={"windows-1258","windows1258","viet","vietnamese",NULL};
install_one_byte_encoding("ms-windows-1258",init_windows_1258,usage_windows_1258,aliases_windows_1258);
/*
 * NeXTSTEP encoding
 */
const char* aliases_NeXTSTEP[2]={"next-step",NULL};
install_one_byte_encoding("nextstep",init_NeXTSTEP,usage_NeXTSTEP,aliases_NeXTSTEP);
}


/**
 * This function prints the main names of encodings to the standard output,
 * so that a program can get the list of all supported encodings.
 */
void print_encoding_main_names() {
for (int i=0;i<number_of_encodings;i++) {
	u_printf("%s\n",encodings[i]->name);
}
}


/**
 * This function prints the aliases of encodings to the standard output,
 * so that a program can get the list of all supported encoding aliases.
 */
void print_encoding_aliases() {
for (int i=0;i<number_of_encodings;i++) {
	for (int j=0;j<encodings[i]->number_of_aliases;j++) {
		u_printf("%s\n",encodings[i]->aliases[j]);
	}
}
}


/**
 * Prints all the information about the given encoding.
 */
void print_encoding_infos(struct encoding* encoding) {
u_printf("Main name = %s\n",encoding->name);
if (encoding->number_of_aliases>0) {
	u_printf("Alias%s =",(encoding->number_of_aliases==1)?"":"es");
	for (int i=0;i<encoding->number_of_aliases;i++) {
		u_printf(" %s",encoding->aliases[i]);
	}
	u_printf("\n");
}
encoding->usage_function();
}


/**
 * Prints all the information about the encoding named 'name'.
 * Prints an error message if 'name' is not a valid encoding main
 * name or alias.
 */
void print_encoding_infos(char* name) {
struct encoding* encoding=get_encoding(name);
if (encoding==NULL) {
	error("%s is not a valid encoding name\n",name);
	return;
}
print_encoding_infos(encoding);
}


/**
 * Prints information about all the available encodings.
 */
void print_information_for_all_encodings() {
for (int i=0;i<number_of_encodings;i++) {
	print_encoding_infos(encodings[i]);
	u_printf("\n");
}
}


/**
 * Returns the encoding named 'name' or NULL if 'name' is not a valid
 * encoding main name or alias.
 */
struct encoding* get_encoding(char* name) {
	char name_in_lower[1024];
strcpy(name_in_lower,name);
strtolower(name_in_lower);
int encoding_number;
if (!get_string_number(encoding_names,name_in_lower,&encoding_number)) {
	return NULL;
}
return encodings[encoding_number];
}

