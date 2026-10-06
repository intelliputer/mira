#ifndef MIRA_DEBUG_SOURCE_MAP_TAGS_H_
#define MIRA_DEBUG_SOURCE_MAP_TAGS_H_

/* Bits stored in an AS1600 source-map range.  Kept here because Mira reads
 * source maps but deliberately does not embed the SDK assembler. */
#define SOURCE_MAP_CODE   (0x10)
#define SOURCE_MAP_DATA   (0x20)
#define SOURCE_MAP_DBDATA (0x40)
#define SOURCE_MAP_STRING (0x80)

/* Compatibility names used by the established source-map reader. */
#define TYPE_CODE   SOURCE_MAP_CODE
#define TYPE_DATA   SOURCE_MAP_DATA
#define TYPE_DBDATA SOURCE_MAP_DBDATA
#define TYPE_STRING SOURCE_MAP_STRING

#endif
