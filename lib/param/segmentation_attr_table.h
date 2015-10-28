/* training: percentage of **training set** correctly classified */
ATTR( training, float64 )

/* threshold: threshold for **segmentation** correctly classified */
ATTR( threshold, float64 )

/* percentage_threshold_intensity: set to a higher value to only
 * include thick structures */
ATTR( percentage_threshold_intensity, float64 )

ATTR( apply_log, bool )
ATTR( release, bool )
ATTR( min_conn_comp_to_remove, uint32_t )
ATTR( bins, uint32_t )
