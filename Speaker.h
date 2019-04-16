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


#ifdef	__cplusplus
}
#endif

#endif	/* SPEAKER_H */

