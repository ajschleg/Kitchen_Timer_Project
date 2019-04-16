/* 
 * File:   Speaker.h
 * Author: austin schlegel
 *
 * Created on April 14, 2019, 8:40 PM
 */

#ifndef SPEAKER_H
#define	SPEAKER_H

#ifdef	__cplusplus
extern "C" {
#endif

    void InitPWM(void);
    void setDutyCycle(U8);
    void tone_out(unsigned char tone , unsigned int delay); //produce duty cycle & keep tone playing for delay time
    void turnSpeakerOn(void);
    void turnSpeakerOff(void);
    
        //birthday song notes and delay period
	U8 birthday[] = {C4,C4,D4,C4,F4,E4,C4_1,C4,D4,C4,G4,F4,C4_1,C4,C5,A4,F4,E4,D4,B4b,B4b,A4,F4,G4,F4,0};
	U8 delay_period[] = {1,1,2,2,2,3,1,1,2,2,2,3,1,1,2,2,2,2,3,1,1,2,2,2,3,0};
    
        //stop song notes and delay period
    unsigned int stopsong[] = {1,0};
    unsigned int delay_period0[] = {1,0};


#ifdef	__cplusplus
}
#endif

#endif	/* SPEAKER_H */

