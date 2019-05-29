
#include "wheels_config.h"

/**
 * Table of wheel configuration.
 * If the motor to encoder assignation is wrong, the problem is probably here.
 * Every tim need to be initialized in the main().
 */
Wheel_t g_wheels[] =
{// diameter 66 mm
#ifdef DELTA
#define RADIUS 0.033f // m
#define TICK_PER_TURN 3.57f * 4096.0f // tick/turn
#define DIST_FROM_CENTER 0.0785f // m
		// angle of speed vector 60, 141
		// Distance from center to wheel  78.5 mm
{"wheel 1", {0}, EncoderTim1, &htim5, TIM_CHANNEL_1, MOTOR1_DIR_GPIO_Port, MOTOR1_DIR_Pin, ClockWise, (float)(+60.f / 180.0f * M_PI),  1.0f, cosf((60.f + 90.f) / 180.0f * M_PI),   sinf((60.f + 90.f) / 180.0f * M_PI),   RADIUS, DIST_FROM_CENTER, TICK_PER_TURN, 0.0f},
{"wheel 2", {0}, EncoderTim2, &htim8, TIM_CHANNEL_3, MOTOR2_DIR_GPIO_Port, MOTOR2_DIR_Pin, ClockWise, (float)(+141.f/ 180.0f * M_PI), 1.0f, cosf((141.f + 90.f) / 180.0f * M_PI),  sinf((141.f + 90.f) / 180.0f * M_PI),  RADIUS, DIST_FROM_CENTER, TICK_PER_TURN, 0.0f},
{"wheel 3", {0}, EncoderTim3, &htim5, TIM_CHANNEL_3, MOTOR3_DIR_GPIO_Port, MOTOR3_DIR_Pin, ClockWise, (float)(-141.f/ 180.0f * M_PI),  1.0f, cosf((-141.f + 90.f) / 180.0f * M_PI), sinf((-141.f + 90.f) / 180.0f * M_PI),  RADIUS, DIST_FROM_CENTER, TICK_PER_TURN, 0.0f},
{"wheel 4", {0}, EncoderTim4, &htim5, TIM_CHANNEL_4, MOTOR4_DIR_GPIO_Port, MOTOR4_DIR_Pin, ClockWise, (float)(-60.f / 180.0f * M_PI),   1.0f, cosf((-60.f + 90.f) / 180.0f * M_PI),  sinf((-60.f + 90.f) / 180.0f * M_PI), RADIUS, DIST_FROM_CENTER, TICK_PER_TURN, 0.0f}
#else
#define RADIUS 0.025f // m
#define TICK_PER_TURN 3.2f * 4096.0f // tick/turn
{"wheel 1", {0}, EncoderTim1, &htim5, TIM_CHANNEL_1, MOTOR1_DIR_GPIO_Port, MOTOR1_DIR_Pin, ClockWise, (float)(M_PI_4),          1.0f, cosf(0.75f * (float)M_PI), sinf(0.75f * (float)M_PI), RADIUS, 0.085f, TICK_PER_TURN, 0.0f},
{"wheel 2", {0}, EncoderTim2, &htim8, TIM_CHANNEL_3, MOTOR2_DIR_GPIO_Port, MOTOR2_DIR_Pin, ClockWise, (float)(M_PI_2 + M_PI_4), 1.0f, cosf(1.25f * (float)M_PI), sinf(1.25f * (float)M_PI), RADIUS, 0.085f, TICK_PER_TURN, 0.0f},
{"wheel 3", {0}, EncoderTim3, &htim5, TIM_CHANNEL_3, MOTOR3_DIR_GPIO_Port, MOTOR3_DIR_Pin, ClockWise, (float)(-M_PI_2 -M_PI_4), 1.0f, cosf(1.75f * (float)M_PI), sinf(1.75f * (float)M_PI), RADIUS, 0.085f, TICK_PER_TURN, 0.0f},
{"wheel 4", {0}, EncoderTim4, &htim5, TIM_CHANNEL_4, MOTOR4_DIR_GPIO_Port, MOTOR4_DIR_Pin, ClockWise, (float)(-M_PI_4),         1.0f, cosf(0.25f * (float)M_PI), sinf(0.25f * (float)M_PI), RADIUS, 0.085f, TICK_PER_TURN, 0.0f}
#endif
};

#undef RADIUS
#undef TICK_PER_TURN
#undef DIST_FROM_CENTER

const size_t wheelsLen = sizeof(g_wheels) / sizeof(Wheel_t);
