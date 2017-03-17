
#include "wheels_config.h"


/**
 * Table of wheel configuration.
 * If the motor to encoder assignation is wrong, the problem is probably here.
 * Every tim need to be initialized in the main().
 */
Wheel_t g_wheels[] =
{
#ifdef BETA
/* wheel == sticker -> pin == cubeMX name + soudure*/
{"wheel 1", {0}, QuadEncoderB1, &htim5, TIM_CHANNEL_1, MOTOR4_DIR_GPIO_Port, MOTOR4_DIR_Pin, ClockWise, M_PI_4,          3.0},     /*wheel 1 -> pin_motor4*/
{"wheel 2", {0}, QuadEncoderA2, &htim8, TIM_CHANNEL_3, MOTOR1_DIR_GPIO_Port, MOTOR1_DIR_Pin, ClockWise, M_PI_2 + M_PI_4, 1.0},     /*wheel 2 -> pin_motor1*/
{"wheel 3", {0}, QuadEncoderA1, &htim5, TIM_CHANNEL_3, MOTOR2_DIR_GPIO_Port, MOTOR2_DIR_Pin, ClockWise, -M_PI_2 -M_PI_4, 1.0},     /*wheel 3 -> pin_motor2*/
{"wheel 4", {0}, QuadEncoderB2, &htim5, TIM_CHANNEL_4, MOTOR3_DIR_GPIO_Port, MOTOR3_DIR_Pin, ClockWise, -M_PI_4,         1.0}      /*wheel 4 -> pin_motor3*/
#elif defined (GAMMA)
{"wheel 1", {0}, EncoderTim3, &htim5, TIM_CHANNEL_1, MOTOR4_DIR_GPIO_Port, MOTOR4_DIR_Pin, AntiClockWise, M_PI_4,          1.0},     /*wheel 1 -> pin_motor4*/
{"wheel 2", {0}, EncoderTim1, &htim8, TIM_CHANNEL_3, MOTOR1_DIR_GPIO_Port, MOTOR1_DIR_Pin, AntiClockWise, M_PI_2 + M_PI_4, 1.0},     /*wheel 2 -> pin_motor1*/
{"wheel 3", {0}, EncoderTim2, &htim5, TIM_CHANNEL_3, MOTOR2_DIR_GPIO_Port, MOTOR2_DIR_Pin, AntiClockWise, -M_PI_2 -M_PI_4, 1.0},     /*wheel 3 -> pin_motor2*/
{"wheel 4", {0}, EncoderTim4, &htim5, TIM_CHANNEL_4, MOTOR3_DIR_GPIO_Port, MOTOR3_DIR_Pin, AntiClockWise, -M_PI_4,         1.0}      /*wheel 4 -> pin_motor3*/
#elif defined (GAMMA2)
{"wheel 1", {0}, EncoderTim1, &htim5, TIM_CHANNEL_1, MOTOR1_DIR_GPIO_Port, MOTOR1_DIR_Pin, ClockWise, (float)(M_PI_4),          1.0f, cosf(0.75f * (float)M_PI), sinf(0.75f * (float)M_PI), 0.025f, 0.085f, 3.2f * 4096.0f, 0.0f},
{"wheel 2", {0}, EncoderTim2, &htim8, TIM_CHANNEL_3, MOTOR2_DIR_GPIO_Port, MOTOR2_DIR_Pin, ClockWise, (float)(M_PI_2 + M_PI_4), 1.0f, cosf(1.25f * (float)M_PI), sinf(1.25f * (float)M_PI), 0.025f, 0.085f, 3.2f * 4096.0f, 0.0f},
{"wheel 3", {0}, EncoderTim3, &htim5, TIM_CHANNEL_3, MOTOR3_DIR_GPIO_Port, MOTOR3_DIR_Pin, ClockWise, (float)(-M_PI_2 -M_PI_4), 1.0f, cosf(1.75f * (float)M_PI), sinf(1.75f * (float)M_PI), 0.025f, 0.085f, 3.2f * 4096.0f, 0.0f},
{"wheel 4", {0}, EncoderTim4, &htim5, TIM_CHANNEL_4, MOTOR4_DIR_GPIO_Port, MOTOR4_DIR_Pin, ClockWise, (float)(-M_PI_4),         1.0f, cosf(0.25f * (float)M_PI), sinf(0.25f * (float)M_PI), 0.025f, 0.085f, 3.2f * 4096.0f, 0.0f}

#endif
};

const size_t wheelsLen = sizeof(g_wheels) / sizeof(Wheel_t);
