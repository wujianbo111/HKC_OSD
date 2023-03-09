
#ifndef _IC2DEF_H_
#define _IC2DEF_H_
typedef enum i2c_direction
{
	I2C_WRITE, I2C_READ
}
I2C_Direction;

#define HW_I2C_ENABLE               		0       // The MIIC SDC&SCL are reverse on demo braor Jonson

#define I2C_ACCESS_DUMMY_TIME   	3

#define I2C_ACKNOWLEDGE           		_LOW
#define I2C_NON_ACKNOWLEDGE       	_HIGH

#endif
