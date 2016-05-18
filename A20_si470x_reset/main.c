/* (c) 2016 - Felipe Astroza A. (felipe@astroza.cl)
 * Under BSD license
 */

#include "gpio_lib.h"

int main()
{
	sunxi_gpio_init();

	/* borrows SDA pin from TWI2 to initialize SI470x according to datasheet */
	sunxi_gpio_set_cfgpin(SUNXI_GPB(21), 1);
	sunxi_gpio_set_cfgpin(SUNXI_GPC(18), 1);

	sunxi_gpio_output(SUNXI_GPB(21), 0);
	sunxi_gpio_output(SUNXI_GPC(18), 0);

	usleep(1000);

	sunxi_gpio_output(SUNXI_GPC(18), 1);
	/* give back pin to TWI2 controller */
	sunxi_gpio_set_cfgpin(SUNXI_GPB(21), 2);

	return 0;
}
