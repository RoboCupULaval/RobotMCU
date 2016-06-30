/*
 * DCMotor_driver.c
 *
 *  Created on: 2013-12-19
 *      Author: Philippe Babin
 */


#include "DCMotor_driver.h"


//DCMotor_Handle DCMotor_Init(PWM_Handle pwmHandle, GPIO_Number_e pwmGPIO, GPIO_Mode_e mode, PWM_Number_e pwmNbr){
DCMotor_Handle dcMotor_init(DCMotor_pwm_e pPwmId,GPIO_Number_e pDirectionPin){
	DCMotor_Handle lMotor;
	GPIO_Number_e lPwmGPIO;
	GPIO_Mode_e lMode;
	PWM_Number_e lPwmNbr;

	lMotor.DirectionPin = pDirectionPin;
	GPIO_setMode(HandleRobot.HandleGPIO, pDirectionPin, GPIO_0_Mode_GeneralPurpose);  //CSN used to activate SPI communication
	GPIO_setDirection(HandleRobot.HandleGPIO, pDirectionPin, GPIO_Direction_Output);
	dcMotor_setDirection(&lMotor,LEFT);

	if(pPwmId == PWM_1A){
		lMotor.PwmHandler = HandleRobot.HandlePwm1;
		lMotor.aPwm = true;
		lPwmGPIO = GPIO_Number_0;
		lMode = GPIO_0_Mode_EPWM1A;
		lPwmNbr = PWM_Number_1;
	}
	else if(pPwmId == PWM_1B){
		lMotor.PwmHandler = HandleRobot.HandlePwm1;
		lMotor.aPwm = false;
		lPwmGPIO = GPIO_Number_1;
		lMode = GPIO_1_Mode_EPWM1B;
		lPwmNbr = PWM_Number_1;
	}
	else if(pPwmId == PWM_2A){
		lMotor.PwmHandler = HandleRobot.HandlePwm2;
		lMotor.aPwm = true;
		lPwmGPIO = GPIO_Number_2;
		lMode = GPIO_2_Mode_EPWM2A;
		lPwmNbr = PWM_Number_2;
	}
	else if(pPwmId == PWM_2B){
		lMotor.PwmHandler = HandleRobot.HandlePwm2;
		lMotor.aPwm = false;
		lPwmGPIO = GPIO_Number_3;
		lMode = GPIO_3_Mode_EPWM2B;
		lPwmNbr = PWM_Number_2;
	}
	else if(pPwmId == PWM_3A){
		lMotor.PwmHandler = HandleRobot.HandlePwm3;
		lMotor.aPwm = true;
		lPwmGPIO = GPIO_Number_4;
		lMode = GPIO_4_Mode_EPWM3A;
		lPwmNbr = PWM_Number_3;
	}
	else if(pPwmId == PWM_3B){
		lMotor.PwmHandler = HandleRobot.HandlePwm3;
		lMotor.aPwm = false;
		lPwmGPIO = GPIO_Number_5;
		lMode = GPIO_5_Mode_EPWM3B;
		lPwmNbr = PWM_Number_3;
	}


//	GPIO_setPullUp(HandleRobot.HandleGPIO, lPwmGPIO, GPIO_PullUp_Disable);
//	GPIO_setMode(HandleRobot.HandleGPIO, lPwmGPIO, lMode);

	 //// PWM
//	    CLK_disableTbClockSync(HandleRobot.HandleCLK);
//	    CLK_enablePwmClock(HandleRobot.HandleCLK, lPwmNbr);
//
//	        // Setup TBCLK
//	        PWM_setPeriod(lMotor.PwmHandler, EPWM_TIMER_TBPRD);   // Set timer period 801 TBCLKs
//	        PWM_setPhase(lMotor.PwmHandler, 0x0000);               // Phase is 0
//	        PWM_setCount(lMotor.PwmHandler, 0x0000);               // Clear counter
//
//	        // Set Compare values
//	        PWM_setCmpA(lMotor.PwmHandler, EPWM_MAX_CMPA);    // Set compare A value
//
//	        // Setup counter mode
//	        PWM_setCounterMode(lMotor.PwmHandler, PWM_CounterMode_UpDown); // Count up
//	        PWM_disableCounterLoad(lMotor.PwmHandler);                     // Disable phase loading
//	        PWM_setHighSpeedClkDiv(lMotor.PwmHandler, PWM_HspClkDiv_by_1); // Clock ratio to SYSCLKOUT
//	        PWM_setClkDiv(lMotor.PwmHandler, PWM_ClkDiv_by_1);

//	        if(lMotor.aPwm){
//				// Setup shadowing
//				PWM_setShadowMode_CmpA(lMotor.PwmHandler, PWM_ShadowMode_Shadow);
//				PWM_setLoadMode_CmpA(lMotor.PwmHandler, PWM_LoadMode_Zero);
//
//
//				// Set actions
//				PWM_setActionQual_CntUp_CmpA_PwmA(lMotor.PwmHandler, PWM_ActionQual_Set);      // Set PWM1A on event A, up count
//				PWM_setActionQual_CntDown_CmpA_PwmA(lMotor.PwmHandler, PWM_ActionQual_Clear);  // Clear PWM1A on event A, down count
//	        }
//	        else{
//				// Setup shadowing
//				PWM_setShadowMode_CmpB(lMotor.PwmHandler, PWM_ShadowMode_Shadow);
//				PWM_setLoadMode_CmpB(lMotor.PwmHandler, PWM_LoadMode_Zero);
//
//
//				// Set actions
//				PWM_setActionQual_CntUp_CmpB_PwmB(lMotor.PwmHandler, PWM_ActionQual_Set);      // Set PWM1A on event A, up count
//				PWM_setActionQual_CntDown_CmpB_PwmB(lMotor.PwmHandler, PWM_ActionQual_Clear);  // Clear PWM1A on event A, down count
//			}

	        // Interrupt where we will change the Compare Values
//	        PWM_setIntMode(lMotor.PwmHandler, PWM_IntMode_CounterEqualZero);   // Select INT on Zero event
//	        PWM_enableInt(lMotor.PwmHandler);                                  // Enable INT
//	        PWM_setIntPeriod(lMotor.PwmHandler, PWM_IntPeriod_ThirdEvent);     // Generate INT on 3rd event


//	        CLK_enableTbClockSync(HandleRobot.HandleCLK);
	        dcMotor_setPWM(&lMotor,EPWM_BRAKE);  //brake state at initialisation
	  return lMotor;
}

//TODO

void dcMotor_updatePWM(DCMotor_Handle *pMotor, uint16_t pPidValue){
	uint16_t lNewPwm = dcMotor_getPWM(pMotor)-pPidValue;  // PWM adjust

	if(lNewPwm > EPWM_MAX_CMPA){  						//saturation
		lNewPwm = EPWM_MAX_CMPA;
	}
	else if(lNewPwm < EPWM_MIN_CMPA){
		lNewPwm = EPWM_MIN_CMPA;
	}

    if(pMotor->aPwm)
    	PWM_setCmpA(pMotor->PwmHandler, lNewPwm);
    else
    	PWM_setCmpB(pMotor->PwmHandler, lNewPwm);
}
//TODO
void dcMotor_setPWM(DCMotor_Handle *pMotor, uint16_t pPwm){

    if(pMotor->aPwm)
    	PWM_setCmpA(pMotor->PwmHandler, pPwm);
    else
    	PWM_setCmpB(pMotor->PwmHandler, pPwm);
}
// TODO
uint16_t dcMotor_getPWM(DCMotor_Handle* pMotor){
    if(pMotor->aPwm)
    	return PWM_getCmpA(pMotor->PwmHandler);
    else
    	return PWM_getCmpB(pMotor->PwmHandler);
}

void dcMotor_setDirection(DCMotor_Handle *pMotor,DCMotor_DIR pDirection){
	HAL_GPIO_WritePin(HandleRobot.HandleGPIO, PMotor-> DirectionPin, pDirection == LEFT);
	if(pDirection == LEFT)
		GPIO_setHigh(HandleRobot.HandleGPIO, pMotor->DirectionPin);
	else
		GPIO_setLow(HandleRobot.HandleGPIO, pMotor->DirectionPin);
}

void dcMotor_break(DCMotor_Handle *pMotor){
	dcMotor_setPWM(pMotor, 3000);
}

void dcMotor_update(DCMotor_Handle* pMotor, PID_Handle *pPid){
	if(pPid->term.Ref < MIN_SPEED && pPid->term.Ref > -MIN_SPEED)
		dcMotor_setPWM(pMotor, 3000);
	else
		dcMotor_updatePWM(pMotor,(long)pPid->term.Out);
}
