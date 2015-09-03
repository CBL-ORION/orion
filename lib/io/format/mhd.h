#ifndef IO_FORMAT_MHD_H
#define IO_FORMAT_MHD_H 1

#include <stdbool.h>

#include "ndarray/ndarray3.h"
#include "container/array.h"

#define ORION_IO_MHD_BUFFER_SZ ORION_BUFFER_SZ

typedef enum {
	MET_UCHAR = 1, /*  uint8_t   */
	MET_SHORT,     /*   int16_t  */
	MET_USHORT,    /*  uint16_t  */
	MET_ULONG,     /*  uint32_t  */
	MET_UINT,      /*  uint32_t  */
	MET_FLOAT,     /* float32 */
	MET_DOUBLE,    /* float64 */

	MET_DATATYPE_ENUM_FIRST = MET_UCHAR,
	MET_DATATYPE_ENUM_LAST = MET_DOUBLE
} orion_mhd_datatype;

typedef struct {
	/* used to hold the filename from which this
	 * MetaInfo metadata was read
	 */
	char* _filename;

	/* start of MetaInfo keys */
	/* NOTE: The ObjectType could be turned into an enum in the future
	 * since there are only a limited number of supported ObjectTypes.
	 */
	char* ObjectType;
	size_t NDims;
	orion_mhd_datatype ElementType;
	array_int* DimSize;
	char* ElementDataFile;
	bool BinaryData;
	bool BinaryDataByteOrderMSB;
	array_float* ElementSpacing;
	/* end of MetaInfo keys */
} orion_mhd_metadata;

extern ndarray3* orion_read_mhd(char* mhd_filename);
extern orion_mhd_metadata* orion_read_mhd_metdata( char* mhd_filename );

extern size_t orion_mhd_raw_byte_length( orion_mhd_metadata* meta );
extern size_t orion_mhd_element_sizeof( orion_mhd_datatype dtype );

#endif /* IO_FORMAT_MHD_H */
