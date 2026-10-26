#ifndef _PRST_SHT4C_H_
#define _PRST_SHT4C_H_

// Values from the SHTC4 datasheet.
#define PRST_SHTC4_ADDR 0x44
#define PRST_SHTC4_CMD_MEASURE_HIGH_PRECISION 0xFD
#define PRST_SHTC4_CMD_MEASURE_MEDIUM_PRECISION 0xF6
#define PRST_SHTC4_CMD_MEASURE_LOW_PRECISION 0xE0

typedef struct {
  // Temperature in Celsius.
  float temp_c;
  // Relative humidity in [0, 1.0].
  float rel_humi;
} prst_shtc4_read_t;

int prst_shtc4_read(prst_shtc4_read_t *out);

#endif  // _PRST_SHT4C_H_
