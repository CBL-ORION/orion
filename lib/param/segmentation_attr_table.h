/* training: percentage of **training set** correctly classified */
ATTR( training, float64 )

/* threshold: threshold for **segmentation** correctly classified */
ATTR( threshold, float64 )

/* percentage_threshold_intensity: set to a higher value to only
 * include thick structures */
ATTR( percentage_threshold_intensity, float64 )

/* apply log to the data? */
ATTR( apply_log, bool )

/* release mode? */
ATTR( release, bool )

/* minimum number of connected components to remove: this is used to remove the
 * N smallest connected components */
ATTR( min_conn_comp_to_remove, uint32_t )

/* number of bins used to calculate the histogram */
ATTR( bins, uint32_t )
