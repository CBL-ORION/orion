#ifndef IO_FORMAT_MHD_H
#define IO_FORMAT_MHD_H 1

#include <stdbool.h>

#include "ndarray/ndarray3.h"
#include "container/array.h"

#define ORION_IO_MHD_BUFFER_SZ 256

typedef enum {
	MET_UCHAR = 1, /*  uint8   */
        MET_SHORT,     /*   int16  */
        MET_USHORT,    /*  uint16  */
        MET_ULONG,     /*  uint32  */
        MET_UINT,      /*  uint32  */
        MET_FLOAT,     /* float32 */
        MET_DOUBLE,    /* float64 */

	MET_DATATYPE_ENUM_FIRST = MET_UCHAR,
	MET_DATATYPE_ENUM_LAST = MET_DOUBLE
} orion_mhd_datatype;

typedef struct {
	size_t NDims;
	orion_mhd_datatype ElementType;
	array_int* DimSize;
	char* ElementDataFile;
	bool ElementByteOrderMSB;
	array_float* ElementSpacing;
} orion_mhd_metadata;

orion_mhd_metadata* orion_read_mhd_metdata( char* mhd_filename );
ndarray3* orion_read_mhd(char* mhd_filename);

#endif /* IO_FORMAT_MHD_H */
