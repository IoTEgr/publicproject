#include "cmos_sensor.h"

#if DEV_SENSOR_SP0838 >0

//ECLK Drv
#define  SP0838_P0_0x30  0x00
//Filter en&dis
#define  SP0838_P0_0x56  0x70
#define  SP0838_P0_0x57  0x10  //filter outdoor
#define  SP0838_P0_0x58  0x10  //filter indoor
#define  SP0838_P0_0x59  0x10  //filter night
#define  SP0838_P0_0x5a  0x02  //smooth outdoor
#define  SP0838_P0_0x5b  0x02  //smooth indoor
#define  SP0838_P0_0x5c  0x20  //smooht night
//outdoor sharpness
#define  SP0838_P0_0x65  0x03
#define  SP0838_P0_0x66  0x01
#define  SP0838_P0_0x67  0x03
#define  SP0838_P0_0x68  0x46
//indoor sharpness
#define  SP0838_P0_0x6b  0x04
#define  SP0838_P0_0x6c  0x01
#define  SP0838_P0_0x6d  0x03
#define  SP0838_P0_0x6e  0x46
//night sharpness
#define  SP0838_P0_0x71  0x05
#define  SP0838_P0_0x72  0x01
#define  SP0838_P0_0x73  0x03
#define  SP0838_P0_0x74  0x46
//color
#define  SP0838_P0_0x7f  0xd7  //R 
#define  SP0838_P0_0x87  0xf8  //B
//satutation
#define  SP0838_P0_0xd8  0x48
#define  SP0838_P0_0xd9  0x48
#define  SP0838_P0_0xda  0x48
#define  SP0838_P0_0xdb  0x48
//AE target
#define  SP0838_P0_0xf7  0x78
#define  SP0838_P0_0xf8  0x63
#define  SP0838_P0_0xf9  0x68
#define  SP0838_P0_0xfa  0x53
//HEQ
#define  SP0838_P0_0xdd  0x70
#define  SP0838_P0_0xde  0x90
//AWB pre gain
#define  SP0838_P1_0x28  0x75
#define  SP0838_P1_0x29  0x4e

//VBLANK
#define  SP0838_P0_0x05  0x00
#define  SP0838_P0_0x06  0x00
//HBLANK
#define  SP0838_P0_0x09  0x01
#define  SP0838_P0_0x0a  0x76

SENSOR_INIT_SECTION const unsigned char SP0838InitTable[]=
{
#if 0
	//SP0838 ini
	0xfd,0x00,//P0
	0x1B,0x02,
	0x27,0xe8,
	0x28,0x0B,
	0x31,0x10,
	0x32,0x00,
	0x22,0xc0,
	0x26,0x10, 
	0x5f,0x11,//Bayer order
	0xfd,0x01,//P1
	0x25,0x1a,//Awb start
	0x26,0xfb,
	0x28,SP0838_P1_0x28,
	0x29,SP0838_P1_0x29,
	0xfd,0x00,
	0xe7,0x03,
	0xe7,0x00,
	0xfd,0x01,
	0x31,0x60,//64
	0x32,0x18,
	0x4d,0xdc,
	0x4e,0x53,
	0x41,0x8c,
	0x42,0x57,
	0x55,0xff,
	0x56,0x00,
	0x59,0x82,
	0x5a,0x00,
	0x5d,0xff,
	0x5e,0x6f,
	0x57,0xff,
	0x58,0x00,
	0x5b,0xff,
	0x5c,0xa8,
	0x5f,0x75,
	0x60,0x00,
	0x2d,0x00,
	0x2e,0x00,
	0x2f,0x00,
	0x30,0x00,
	0x33,0x00,
	0x34,0x00,
	0x37,0x00,
	0x38,0x00,//awb end
	0xfd,0x00,//P0
	0x33,0x6f,//LSC BPC EN
	0x51,0x3f,//BPC debug start
	0x52,0x09,
	0x53,0x00,
	0x54,0x00,
	0x55,0x10,//BPC debug end
	0x4f,0x08,//blueedge
	0x50,0x08,
	0x57,SP0838_P0_0x57,//Raw filter debut start
	0x58,SP0838_P0_0x58,
	0x59,SP0838_P0_0x59,
	0x56,SP0838_P0_0x56,
	0x5a,SP0838_P0_0x5a,
	0x5b,SP0838_P0_0x5b,
	0x5c,SP0838_P0_0x5c,//Raw filter debut end 
	0x65,SP0838_P0_0x65,//Sharpness debug start
	0x66,SP0838_P0_0x66,
	0x67,SP0838_P0_0x67,
	0x68,SP0838_P0_0x68,
	0x69,0x7f,
	0x6a,0x01,
	0x6b,SP0838_P0_0x6b,
	0x6c,SP0838_P0_0x6c,
	0x6d,SP0838_P0_0x6d,//Edge gain normal
	0x6e,SP0838_P0_0x6e,//Edge gain normal
	0x6f,0x7f,
	0x70,0x01,
	0x71,SP0838_P0_0x71, //锐化阈值          
	0x72,SP0838_P0_0x72, //弱轮廓阈值        
	0x73,SP0838_P0_0x73, //边缘正向增益值    
	0x74,SP0838_P0_0x74, //边缘反向增益值    
	0x75,0x7f,              //使能位            
	0x76,0x01,//Sharpness debug end
	0xcb,0x07,//HEQ&Saturation debug start 
	0xcc,0x04,
	0xce,0xff,
	0xcf,0x10,
	0xd0,0x20,
	0xd1,0x00,
	0xd2,0x1c,
	0xd3,0x16,
	0xd4,0x00,
	0xd6,0x1c,
	0xd7,0x16,
	0xdd,SP0838_P0_0xdd,//Contrast
	0xde,SP0838_P0_0xde,//HEQ&Saturation debug end
	0x7f,SP0838_P0_0x7f,//Color Correction start
	0x80,0xbc,                        
	0x81,0xed,                        
	0x82,0xd7,                        
	0x83,0xd4,                        
	0x84,0xd6,                        
	0x85,0xff,                        
	0x86,0x89,                        
	0x87,SP0838_P0_0x87,                        
	0x88,0x3c,                        
	0x89,0x33,                        
	0x8a,0x0f,//Color Correction end  
	0x8b,0x0 ,//gamma start
	0x8c,0x1a,             
	0x8d,0x29,             
	0x8e,0x41,             
	0x8f,0x62,             
	0x90,0x7c,             
	0x91,0x90,             
	0x92,0xa2,             
	0x93,0xaf,             
	0x94,0xbc,             
	0x95,0xc5,             
	0x96,0xcd,             
	0x97,0xd5,             
	0x98,0xdd,             
	0x99,0xe5,             
	0x9a,0xed,             
	0x9b,0xf5,             
	0xfd,0x01,//P1         
	0x8d,0xfd,             
	0x8e,0xff,//gamma end  
	0xfd,0x00,//P0
	0xca,0xcf,
	0xd8,SP0838_P0_0xd8,//UV outdoor
	0xd9,SP0838_P0_0xd9,//UV indoor 
	0xda,SP0838_P0_0xda,//UV dummy
	0xdb,SP0838_P0_0xdb,//UV lowlight
	0xb9,0x00,//Ygamma start
	0xba,0x04,
	0xbb,0x08,
	0xbc,0x10,
	0xbd,0x20,
	0xbe,0x30,
	0xbf,0x40,
	0xc0,0x50,
	0xc1,0x60,
	0xc2,0x70,
	0xc3,0x80,
	0xc4,0x90,
	0xc5,0xA0,
	0xc6,0xB0,
	0xc7,0xC0,
	0xc8,0xD0,
	0xc9,0xE0,
	0xfd,0x01,//P1
	0x89,0xf0,
	0x8a,0xff,//Ygamma end
	0xfd,0x00,//P0
	0xe8,0x30,//AEdebug start
	0xe9,0x30,
	0xea,0x40,//Alc Window sel
	0xf4,0x1b,//outdoor mode sel
	0xf5,0x80,
	0xf7,SP0838_P0_0xf7,//AE target
	0xf8,SP0838_P0_0xf8,
	0xf9,SP0838_P0_0xf9,//AE target 
	0xfa,SP0838_P0_0xfa,
	0xfd,0x01,//P1
	0x09,0x31,//AE Step 3.0
	0x0a,0x85,
	0x0b,0x0b,//AE Step 3.0
	0x14,0x20,
	0x15,0x0f,

	//caprure preview daylight 24M 50hz 20-8FPS maxgain:0x70	12fps
/*	0xfd,0x00,
	0x05,SP0838_P0_0x05 ,
	0x06,SP0838_P0_0x06 ,
	0x09,SP0838_P0_0x09 ,
	0x0a,SP0838_P0_0x0a ,
	0xf0,0x62,
	0xf1,0x0 ,
	0xf2,0x5f,
	0xf5,0x78,
	0xfd,0x01,
	0x00,0xb2,
	0x0f,0x60,
	0x16,0x60,
	0x17,0xa2,
	0x18,0xaa,
	0x1b,0x60,
	0x1c,0xaa,
	0xb4,0x20,
	0xb5,0x3a,
	0xb6,0x5e,
	0xb9,0x40,
	0xba,0x4f,
	0xbb,0x47,
	0xbc,0x45,
	0xbd,0x43,
	0xbe,0x42,
	0xbf,0x42,
	0xc0,0x42,
	0xc1,0x41,
	0xc2,0x41,
	0xc3,0x41,
	0xc4,0x41,
	0xc5,0x70,
	0xc6,0x41,
	0xca,0x70,
	0xcb,0x0c,*/

	//==24m input , vga 12~20FPS==  15fps
	0xfd,0x00,
	0x05,SP0838_P0_0x05 ,
	0x06,SP0838_P0_0x06 ,
	0x09,SP0838_P0_0x09 ,
	0x0a,SP0838_P0_0x0a ,
	0xf0,0x62,
	0xf1,0x0 ,
	0xf2,0x5f,
	0xf5,0x78,
	0xfd,0x01,
	0x00,0xb2,
	0x0f,0x60,
	0x16,0x60,
	0x17,0x9a,
	0x18,0xa2,
	0x1b,0x60,
	0x1c,0xa2,
	0xb4,0x20,
	0xb5,0x3a,
	0xb6,0x5e,
	0xb9,0x40,
	0xba,0x4f,
	0xbb,0x47,
	0xbc,0x45,
	0xbd,0x43,
	0xbe,0x42,
	0xbf,0x42,
	0xc0,0x42,
	0xc1,0x78,
	0xc2,0x41,
	0xc3,0x41,
	0xc4,0x41,
	0xc5,0x41,
	0xc6,0x41,
	0xca,0x78,
	0xcb,0x08,

	0xfd,0x00,

	0xfd,0x00,  //P0
	0x32,0x15,  //Auto_mode set
	0x34,0x66,  //Isp_mode set
	0x35,0x40,  //out format
#else
	//客户样机20230505
	0xfd,0x00,
	0x1b,0x02,
	0x1c,0x07,
	0x27,0xe8,
	0x28,0x0b,
	0x32,0x00,
	0x22,0xc0,
	0x26,0x10,
	0x31,0x70,
	0x5f,0x11,
	
	0xfd,0x01, 
	0x25,0x1a, 
	0x26,0xfb,
	0x28,0x75,
	0x29,0x4e,

	0xfd,0x00,
	0xe7,0x03,
	0xe7,0x00,
	
	0xfd,0x01,
	0x31,0x60,
	0x32,0x18,
	0x4d,0xdc,
	0x4e,0x53,
	0x41,0x8c,
	0x42,0x57,
	0x55,0xff,
	0x56,0x00,
	0x59,0x82,
	0x5a,0x00,
	0x5d,0xff,
	0x5e,0x6f,
	0x57,0xff,
	0x58,0x00,
	0x5b,0xff,
	0x5c,0xa8,
	0x5f,0x75,
	0x60,0x00,
	0x2d,0x00,
	0x2e,0x00,
	0x2f,0x00,
	0x30,0x00,
	0x33,0x00,
	0x34,0x00,
	0x37,0x00,
	0x38,0x00,

	0xfd,0x00,
	0x33,0x6f,
	0x51,0x3f,
	0x52,0x09,
	0x53,0x00,
	0x54,0x00,
	0x55,0x10,
	0x4f,0x05,
	0x50,0x05,
	0x57,0x10,
	0x58,0x10,
	0x59,0x10,
	0x56,0x70,
	0x5a,0x08,
	0x5b,0x10,
	0x5c,0x30,
	0x65,0x03,
	0x66,0x01,
	0x67,0x03,
	0x68,0x45, 
	0x69,0x7f,
	0x6a,0x01,
	0x6b,0x04, 
	0x6c,0x01,   
	0x6d,0x03,
	0x6e,0x43,
	0x6f,0x7f,
	0x70,0x01,
	0x71,0x05,
	0x72,0x01,
	0x73,0x03,
	0x74,0x43,
	0x75,0x7f,
	0x76,0x01,
	0xcb,0x07,
	0xcc,0x04,
	0xce,0xff,
	0xcf,0x10,
	0xd0,0x20,
	0xd1,0x00,
	0xd2,0x1c,
	0xd3,0x16,
	0xd4,0x00,
	0xd6,0x1c,
	0xd7,0x16,
	0xdd,0x70,
	0xde,0x94,
	0x7f,0xd2,
	0x80,0xbc,
	0x81,0xed,
	0x82,0xd7,
	0x83,0xd4,
	0x84,0xd6,
	0x85,0xff,
	0x86,0x89,
	0x87,0xf8,
	0x88,0x3c,	
	0x89,0x33,
	0x8a,0x0f,
	0x8b,0x00,  
	0x8c,0x1a,
	0x8d,0x29,
	0x8e,0x41,
	0x8f,0x62,
	0x90,0x7c,
	0x91,0x90,
	0x92,0xa2,
	0x93,0xaf,
	0x94,0xbc,
	0x95,0xc5,
	0x96,0xcd,
	0x97,0xd5,
	0x98,0xdd,
	0x99,0xe5,
	0x9a,0xed,
	0x9b,0xf5,

	0xfd,0x01,
	0x8d,0xfd,
	0x8e,0xff,

	0xfd,0x00,
	0xca,0xcf,
	0xd8,0x44,
	0xd9,0x44,
	0xda,0x40,
	0xdb,0x40,
	0xb9,0x00,
	0xba,0x04,
	0xbb,0x08,
	0xbc,0x10,
	0xbd,0x20,
	0xbe,0x30,
	0xbf,0x40,
	0xc0,0x50,
	0xc1,0x60,
	0xc2,0x70,
	0xc3,0x80,
	0xc4,0x90,
	0xc5,0xa0,
	0xc6,0xb0,
	0xc7,0xc0,
	0xc8,0xd0,
	0xc9,0xe0,

	0xfd,0x01,
	0x89,0xf0,
	0x8a,0xff,

	0xfd,0x00,
	0xe8,0x30,
	0xe9,0x30,
	0xea,0x40,
	0xf4,0x1b,
	0xf5,0x80,
	0xf7,0x80,
	0xf8,0x6b,
	0xf9,0x70,
	0xfa,0x5b,
	
	0xfd,0x01,
	0x09,0x31,
	0x0a,0x85,
	0x0b,0x0b,
	0x14,0x10,
	0x15,0x0f,

	0xfd,0x00,
	0x05,0x00, 
	0x06,0x00,
	0x09,0x00,
	0x0a,0x96,
	0xf0,0x78,
	0xf1,0x00,
	0xf2,0x65,
	0xf5,0x7e,

	0xfd,0x01,
	0x00,0xb2,	
	0x0f,0x66,
	0x16,0x66,
	0x17,0x9a,
	0x18,0xa2,
	0x1b,0x66,
	0x1c,0xa2,
	0xb4,0x20,
	0xb5,0x3c,
	0xb6,0x74,
	0xb9,0x40,
	0xba,0x4f,   
	0xbb,0x47,
	0xbc,0x45,
	0xbd,0x43,
	0xbe,0x42,
	0xbf,0x78,
	0xc0,0x42,
	0xc1,0x41,
	0xc2,0x41,
	0xc3,0x41,
	0xc4,0x41,
	0xc5,0x41,
	0xc6,0x41, 
	0xca,0x78,
	0xcb,0x06,

	0xfd,0x00,
	0xfd,0x00,
	0x32,0x15,
	0x34,0x66,
	0x35,0x40,
	0x62,0x00,
	0x63,0x80,
	0x64,0x80,
#endif
	-1,-1,
};


static void SP0838_rotate(u32 r)
{
	unsigned char buf[2];

	buf[0] = 0x31;		//0',180'
	buf[1] = 0x70&(r<<0);
	sensor_iic_write(buf);
	//sensor_iic_read(buf);
}

static void SP0838_hvblank(u32 h,u32 v)
{
	
}

SENSOR_OP_SECTION const Sensor_Op_t SP0838_cmd= 
{
	.typ =CSI_TYPE_YUV422,
	.pixelw = 640,
	.pixelh= 480,
//	.pixelw = 320,
//	.pixelh= 240,
	.hsyn = 1,
	.vsyn = 1,
	.AVDD = SYS_VOL_V2_8,
	.DVDD = SYS_VOL_V2_8,
	.VDDIO = SYS_VOL_V2_8,
	.colrarray = 2,//0:_RGRG_ 1:_GRGR_,2:_BGBG_,3:_GBGB_
	.rotate_adapt = {0},
	.hvb_adapt = {42000000,1120,0,0,0xff,25,0},
	.mclk = 24000000,
	//.pclk_fir_en = 0,
	//.pclk_inv_en = 0,
	//.pclk_fir_class = 0,//
	//.csi_tun = 0,
	.p_fun_adapt = {SP0838_rotate,NULL,NULL},
};

SENSOR_HEADER_ITEM_SECTION const Sensor_Init_t SP0838_init=
{
	.sensor_struct_addr =	(u32 *)&SP0838_cmd,    
	.sensor_struct_size = sizeof(Sensor_Op_t),
	.sensor_init_tab_adr =	(u32 *)SP0838InitTable,     
	.sensor_init_tab_size = sizeof(SP0838InitTable),
	.id               =	0x27,                
	.w_cmd            =	0x30,                 
	.r_cmd            =	0x31,                 
	.addr_num         =	0x01,                  
	.data_num         =	0x01,                  
	.id_reg           =	0x02                   
};


#endif

