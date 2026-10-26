#ifndef _PRST_DATA_H_
#define _PRST_DATA_H_

#include "prstlib/adc.h"
#include "prstlib/shtc4.h"

typedef struct {
  prst_adc_soil_moisture_t soil;
  prst_adc_photo_sensor_t photo;
  prst_batt_t batt;
  prst_shtc4_read_t shtc4;
} prst_sensors_t;

int prst_sensors_read_all(prst_sensors_t *out);

#endif  // _PRST_DATA_H_
