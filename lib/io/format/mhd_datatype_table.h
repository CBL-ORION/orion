/*   enum      , val,  type     */
ENUM(MET_UCHAR , = 1,   uint8_t  )
ENUM(MET_SHORT ,    ,    int16_t )
ENUM(MET_USHORT,    ,   uint16_t )
ENUM(MET_ULONG ,    ,   uint32_t )
ENUM(MET_UINT  ,    ,   uint32_t )
ENUM(MET_FLOAT ,    ,  float32   ) /* float32, float64 defined in util/float.h */
ENUM(MET_DOUBLE,    ,  float64   )

/* enum: name of the value for the ElementType key.
 *  val: enum value to assign (optional: empty indicates increasing value).
 * type: corresponding storage type for the enum.
 */
