/*
 * two_wheel_ctrl.c
 *
 *  Created on: 2014-01-06
 *      Author: Philippe Babin
 */

#include "four_wheel_ctrl.h"

void fourWheelCtrl_Init(){

}
// v1 = Tsin(te - 45) + 0.18PI W
// v2 = Tsin(te - 135) + 0.18PI W
// v3 = Tsin(te - 225) + 0.18PI W
// v4 = Tsin(te - 315) + 0.18PI W

void fourWheelCtrl_Update( float pX, float pY, float pTheta){

	float magnitude = sqrt(pX * pX + pY * pY);
	float angle = atan2( pY, pX);

	// j = 0.18 * PI * w
	//_iq j = _IQmpy(w, _IQ(0.5654));
	// dephasage = 45 degrees = 0.785 radians
	float v0 = magnitude * sin(angle + 0.785398163);
	// dephasage = 135 degrees = 2.3561925 radians
	float v1 = magnitude * sin(angle + 2.3561925);
	// dephasage = 225 degrees = 3.9269875 radians
	float v2 = magnitude * sin(angle + 3.9269875);
	// dephasage = 315 degrees = 5.4977825 radians
	float v3 = magnitude * sin(angle + 5.4977825);

#ifdef BETA
	DCMotor_DIR dir_right_alpha = LEFT;
	DCMotor_DIR dir_left_alpha = RIGHT;
	HandleRobot.HandlePid[0].term.Ref = v2;// + pTheta;
	HandleRobot.HandlePid[1].term.Ref = v1;// + pTheta;
	HandleRobot.HandlePid[2].term.Ref = v0;// + pTheta;
	HandleRobot.HandlePid[3].term.Ref = v3;// + pTheta;
#else // Alpha
	DCMotor_DIR dir_right_alpha = RIGHT;
	DCMotor_DIR dir_left_alpha = LEFT;
	HandleRobot.HandlePid[0].term.Ref = v2;// + pTheta;
	HandleRobot.HandlePid[1].term.Ref = v3;// + pTheta;
	HandleRobot.HandlePid[2].term.Ref = v0;// + pTheta;
	HandleRobot.HandlePid[3].term.Ref = v1;// + pTheta;
#endif // BETA
for (i = 0; i<2; i++)
{
	if(_IQtoF(HandleRobot.HandlePid[i].term.Ref) < 0 ){dcMotor_setDirection(&HandleRobot.HandleMotor[i],dir_right_alpha);}
	else{dcMotor_setDirection(&HandleRobot.HandleMotor[i],dir_left_alpha);}
}

	HandleRobot.HandlePid[0].term.Ref= abs(HandleRobot.HandlePid[0].term.Ref);
	HandleRobot.HandlePid[1].term.Ref= abs(HandleRobot.HandlePid[1].term.Ref);
	HandleRobot.HandlePid[2].term.Ref= abs(HandleRobot.HandlePid[2].term.Ref);
	HandleRobot.HandlePid[3].term.Ref= abs(HandleRobot.HandlePid[3].term.Ref);

}
