#if COMPRESS_MONO_FONT
  extern code BYTE tOSDFont1[616];
  extern code WORD tMonoFontDataAddr[43];
#else // No compress
  extern code WORD tOSDFont1[774]; // Format 2: 1 word ==> 1 line

#endif
#ifndef __COLOR_FONT_H
#define __COLOR_FONT_H

  #ifdef COMPRESS_COLOR_FONT
    extern code BYTE tCompressColorFontData[0];
  #else
    extern code BYTE tColorFontData[0];
  #endif

#endif
#ifndef __COLOR_FONT_H
#define __COLOR_FONT_H

  #ifdef COMPRESS_COLOR_FONT
    extern code BYTE tCompressColorFontData[0];
  #else
    extern code BYTE tColorFontData[0];
  #endif

#endif
