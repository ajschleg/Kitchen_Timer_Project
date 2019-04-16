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
//Notes
//				ms				  HZ	
#define A4		78				//440 		
#define B4b		74				//466			
#define C4		132				//261
#define C4_1	130	
#define C5		65				//523		
#define D4		117				//293	
#define D4b		124				//277				
#define E4		105				//329			
#define F4		98				//349			
#define G4		88				//392	
#define A4S     74              //466
#define F5      49              //698
#define D5S     55              //622
#define D5      58              //587
#define A5S     37              //932
#define C2      527		//65
#define C3      264		//131
#define A2      313		//110
#define A3S     148		//233
#define D3      235		//147
#define C3S     249		//130
#define G3      176
#define E3      209
#define F3      197




    void InitPWM(void);
    void setDutyCycle(U8);
    void toneOut(unsigned char tone , unsigned int delay); //produce duty cycle & keep tone playing for delay time
    void turnSpeakerOn(void);
    void turnSpeakerOff(void);
    void playSong(void);
    void playBonus(void);

    //Jeopardy notes and delay period
    unsigned int jeopardy[] = {C2,F3,C3,A2,C3,F3,C3,C3,F3,C3,F3,A3S,G3,F3,E3,D3,C3S,0};    
    unsigned int delay_period_jep[] = {4,4,4,4,4,4,2,4,4,4,4,3,8,8,8,8,0};


    
    //Star Wars Theme Song notes and delay period
    U8 star_wars[] = {F4,F4,F4,A4S,F5,D5S,D5,C5,A5S,F5,D5S,D5,C5,A5S,F5,D5S,D5,D5S,C5,0};
    U8 delay_period[] = {2,2,2,6,6,2,2,2,6,3,2,2,2,6,3,2,2,2,6,0};

    
        //stop song notes and delay period
    unsigned int stopsong[] = {1,0};
    unsigned int delay_period0[] = {1,0};


#ifdef	__cplusplus
}
#endif

#endif	/* SPEAKER_H */

