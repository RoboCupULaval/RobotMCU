/* =================================================================================
File name: pid.c
Originator: C2000 System Applications, Texas Instruments
Description: Data and macro definitions for PID controller
=====================================================================================
History:
-------------------------------------------------------------------------------------
06-07-2010 Version 1.0
-------------------------------------------------------------------------------------
19-12-2013 Version 1.1
-------------------------------------------------------------------------------------
*/
#include "pid.h"

PID_Handle pid_init(float pKp, float pKi, float pKd, float pUmax, float pUmin){
	PID_Handle lPid;

	lPid.param.Kr = 1.0;   //pid Constant
	lPid.param.Kp = pKp;
	lPid.param.Ki = pKi;
	lPid.param.Kd = pKd;
	lPid.param.Km = 1.0;

	lPid.param.Umax = pUmax;  //saturation filter
	lPid.param.Umin = pUmin;

	lPid.term.c1 = 1.0;  //D filter
	lPid.term.c2 = 0.0;
	lPid.data.d1 = 0.0;
	lPid.data.d2 = 0.0;
	lPid.data.i1 = 0.0;
	lPid.data.ud = 0.0;
	lPid.data.ui = 0.0;
	lPid.data.up = 0.0;
	lPid.data.v1 = 0.0;
	lPid.data.w1 = 0.0;

	return lPid;
}

float pid_update(PID_Handle *pPid, float pFbk){
	pPid->term.Fbk = pFbk;
	//v->term.Ref = Ref;


	/* proportional term */
	// Kr * Ref - Fbk
	pPid->data.up = pPid->param.Kr* pPid->term.Ref - pPid->term.Fbk;
	/* integral term */
	// Ki * (w1 * (Ref - Fbk)) + i1
	pPid->data.ui = pPid->param.Ki* pPid->data.w1* (pPid->term.Ref - pPid->term.Fbk) + pPid->data.i1;
	pPid->data.i1 = pPid->data.ui;

	/* derivative term */
	// Kd * (c1 * (Ref * Km,  - Fbk-) ) - d2
	pPid->data.d2 = pPid->param.Kd *
						pPid->term.c1 * pPid->term.Ref * (pPid->param.Km, -pPid->term.Fbk) ;
	pPid->data.ud = pPid->data.d2 + pPid->data.d1;
	pPid->data.d1 = pPid->data.ud * pPid->term.c1;

	/* control output */
	// v1 = Kp * (up + ui + ud)
	pPid->data.v1 =  pPid->param.Kp * (pPid->data.up + pPid->data.ui + pPid->data.ud);
	// out = Kp * (up + ui + ud)
	// This is the saturation of the wheel speed
	pPid->term.Out = pPid->data.v1 > pPid>param.Umax?
									 pPid->param.Umax
					: (pPid->data.v1 < pPid->param.Umin?
									 pPid->param.Umin
					: pPid->data.v1);

	pPid->data.w1 = (pPid->term.Out == pPid->data.v1) ? 1.0 : 0.0;

	return pPid->term.Out;
}

void pid_set(PID_Handle *pPid,float pKp, float pKi, float pKd){
	pPid->param.Kp = pKp;
	pPid->param.Ki = pKi;
	pPid->param.Kd = pKd;
}

void pid_display(PID_Handle *pPid){
	System_printf("pid =%f \n\r", pPid->term.Out);
}
