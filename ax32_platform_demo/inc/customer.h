/****************************************************************************
**
 **                              CUSTOMER
  ** *   **             THE APPOTECH MULTIMEDIA PROCESSOR
   **** **                  CUSTOMER HEADER
  *** ***
 **  * **               (C) COPYRIGHT 2016 BUILDWIN 
**      **                         
         **         BuildWin SZ LTD.CO  ; VIDEO PROJECT TEAM
          **   
* File Name   : customer.h
* Author      : Mark.Douglas 
* Version     : V100
* Date        : 09/22/2016
* Description : This file is customer define 
*               
* History     : 
* 2016-09-22  : 
*      <1>.This is created by mark,set version as v100.
*      <2>.Add basic functions & information
******************************************************************************/
#ifndef  CUSTOMER_H
    #define  CUSTOMER_H

//--------------software version-------------
#define  SYSTEM_VERSION     "3295B_KIDS_CAM"  //----user configure
#define  BOARD_TYPE_BWV1          0
#define  BOARD_TYPE_FPGA          1

#define RECORD_MODE_DEFAULT       0  //  default mode,720P+VGA doule sensor.
#define RECORD_MODE_SIGNAL        1  //B  only 720P
#define RECORD_MODE_AUTO           2  //  720P first.if VGA in ,creating B folder

#define AUDIO_REC_EN       0

#define  RECORD_MODE       RECORD_MODE_SIGNAL 


#define  SYSTEM_BOARD      BOARD_TYPE_BWV1//BOARD_TYPE_FPGA// BOARD_TYPE_BWV1     //----user configure


#define  VIDEO_RATIO       VIDEO_RATIO_DEFAULT     //----user configure


#define  VIDEO_ROTATE      VIDEO_ROTATE_DEFAULT   //----user configure


#define  BAT_SAVE_POWER     5 // second.when battery powered and no key event.0,disable power save


#define  SDC_NULL_TIMEOUT   3 // second .sdc null dialog showing time. 0,disable sdc null showing


//#define  POWER_ON_RECORD     1 // power on record if power_key power on.0:disable


#define  TAKE_PHOTO_MODE     1  // take photo from A and B once if B channel is valided .0:only A OR B


#define  MOTION_DEC_TIME    20 // second.when motion dection no active recording this time will stop recording


#define  KEYSOUND_VOLUME    100 // key & take photo sound volume [0-100]


#define  AVI_TYPE_ODML       1  // AVI FILE TYPE .1-open dml,0-std


#define  FILE_SYNC_WRITE    1  // write sync for avi file


#define  FILE_SYNC_DELETE   0  // delete sync 

#define  FILE_SIZE_PRE_MALLOC	0 // 0: file is not pre malloc , 1 : file is pre malloc(FILE MAX SIZE before REC)

#define  VERSION_LOAD_AUTO     0   // auto load version from resource


#define  DATETIME_LOAD_AUTO    1  // auto load default time from resource


#define  KEYSOUND_LOAD_AUTO    1  // auto load key sound from resource

#define  USENSOR_PWRCTRL_EN    0  // if enable,control usensor power by PE1;if disable,usensor power always power-on
								 // AX3282S define 1, AX3291A define 0

#define	 IO1DO1_USE_SOFTSTART		0 //usensor power control use io1do1 softstart, 1: use softstart, 0: not use
						
#define  USENSOR_AUDIO_ON      0 // back record audio volume on, use front record audio

#define  LCD_CROP_SCALE      1 //lcd crop scale show image ,  0 : is disable , 1 : is enable 
#define  LCD_PLAY_SCALE      0//1 //LCD show updown black for 4:3 LCD ,  0 : is disable , 1 : is enable 
#define  LCD_PLAY_JPEG_SCALE   0 //suport play jpeg file ,scale up or down ,  0 : is disable , 1 : is enable 

#define  USENSOR_RESOLUTION      0 //usensor recording resolution. 1: 640*480; 2: 1280:720; 3:1280:960

#define  SMALL_PANEL_SUPPORT		0//support lcd panel smaller than 320X240,remove sub menu on the right side && remove current time show on top bar and so on
									  //enable it when in need
#define  IR_MENU_EN            0  // 0: not IR control , 1 IR control

#define  AVI_LOCK_FOLDER 		0 // 0:  not Lock Folder , 1: have Lock Folder 

#define  ICON_FRAME_NUM			9//20  //resource frame num

#define  USE_EXTERNAL_DAC_PA	0// 0 : use ic dclass , 1: use external pa

#if (1==USE_EXTERNAL_DAC_PA)
//==need to set ax32xx_dac.c  ax32xx_dacInit(void)
//==R_DAC_CTRL1 |= (1<<9);//Class AB
#define   DAC_PA_MUTE_CH  GPIO_PA
#define   DAC_PA_MUTE_PIN GPIO_PIN9
#define   DAC_PA_MUTE_INIT() {hal_gpioInit(DAC_PA_MUTE_CH,DAC_PA_MUTE_PIN,GPIO_OUTPUT,GPIO_PULL_FLOATING);}
#define   DAC_PA_MUTE_OFF()  {hal_gpioWrite(DAC_PA_MUTE_CH,DAC_PA_MUTE_PIN,GPIO_HIGH);}	// have sound
#define   DAC_PA_MUTE_ON()  {hal_gpioWrite(DAC_PA_MUTE_CH,DAC_PA_MUTE_PIN,GPIO_LOW);}	// no sound
#else
//==need to set ax32xx_dac.c  ax32xx_dacInit(void)
//==R_DAC_CTRL1 &=~(1<<9);  //Class D==
#define   DAC_PA_MUTE_INIT() 
#define   DAC_PA_MUTE_OFF() 
#define   DAC_PA_MUTE_ON() 
#endif



#define  FRONT_SENSOR_RESET_CH	 GPIO_PE
#define  FRONT_SENSOR_RESET_PIN  GPIO_PIN1

#define  REAR_SENSOR_RESET_CH	 GPIO_PE
#define  REAR_SENSOR_RESET_PIN	GPIO_PIN0




//---------file dir-----------------------
#define  FILEDIR_VIDEO  "VIDEO/"              //----user configure
#define  FILEDIR_PHOTO  "PHOTO/"              //----user configure
#define  FILEDIR_AUDIO  "AUDIO/"              //----user configure
#if RECORD_MODE == RECORD_MODE_SIGNAL
#define  FILEDIR_VIDEOA "VIDEO/"
#define  FILEDIR_VIDEOB "VIDEO/"
#else
#define  FILEDIR_VIDEOA "VIDEOA/"
#define  FILEDIR_VIDEOB "VIDEOB/"
#endif

#if (1 == AVI_LOCK_FOLDER)
#define  FILEDIR_LOCKA "SOSA/"
#define  FILEDIR_LOCKB "SOSB/"
#endif

#define  FILEDIR_MP3	 "MP3/"

#endif




