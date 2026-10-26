#include "prstlib/shtc4.h"

#include <zephyr/drivers/i2c.h>
#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>

#include "prstlib/macros.h"

LOG_MODULE_REGISTER(shtc4, CONFIG_PRSTLIB_LOG_LEVEL);

static const struct i2c_dt_spec shtc4 = I2C_DT_SPEC_GET(DT_NODELABEL(shtc4));

static uint8_t buff[6];

static int write_cmd(uint8_t command) {
  RET_IF_ERR(i2c_write_dt(&shtc4, &command, sizeof(command)));
  return 0;
}

int prst_shtc4_read(prst_shtc4_read_t *out) {
  RET_IF_ERR_MSG(!device_is_ready(shtc4.bus), "SHTC4 is not ready");

  // Wake the sensor up.
  RET_IF_ERR(write_cmd(PRST_SHTC4_CMD_MEASURE_HIGH_PRECISION));
  k_msleep(10);

  // Read response.
  RET_IF_ERR(i2c_read_dt(&shtc4, buff, 6));

  // TODO: verify the CRC of the measurements. The function is described in the
  // datasheet.

  uint16_t t_ticks = buff[0] * 256 + buff[1];
  // uint8_t checksum_t = buff[2];
  uint16_t rh_ticks = buff[3] * 256 + buff[4];
  // uint8_t checksum_rh = buff[5];
  float t_degC = -45 + 175 * (float)t_ticks/65535;
  float rh_pRH = (-6 + 125 * (float)rh_ticks/65535)/100;
  if (rh_pRH > 1.0f){
    rh_pRH = 1.0f;
  };
  if (rh_pRH < 0.0f){
    rh_pRH = 0.0f;
  };

  out->temp_c = t_degC;
  out->rel_humi = rh_pRH;

  LOG_DBG("Read temp: %f oC (%d)", DOUBLE_PROMO_OK(out->temp_c), (int)out->temp_c);
  LOG_DBG("Read humi: %.0f %%", DOUBLE_PROMO_OK(100.0f * out->rel_humi));
  return 0;
}