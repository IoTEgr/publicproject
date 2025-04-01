#include "application.h"
#include "taskgame.h"

#define U 1
#define D 2
#define L 3 
#define R 4



// 7�ַ����4��ת״̬��4λΪһ�У�
static INT16U gs_uTetrisTable[7][4] = { 
		{ 0x00F0U, 0x2222U, 0x00F0U, 0x2222U },  // I��
		{ 0x0072U, 0x0262U, 0x0270U, 0x0232U },  // T��
		{ 0x0223U, 0x0074U, 0x0622U, 0x0170U },  // L��
		{ 0x0226U, 0x0470U, 0x0322U, 0x0071U },  // J��
		{ 0x0063U, 0x0264U, 0x0063U, 0x0264U },  // Z��
		{ 0x006CU, 0x0462U, 0x006CU, 0x0462U },  // S��
		{ 0x0660U, 0x0660U, 0x0660U, 0x0660U }   // O��
};
static INT16U gs_uTetrisTable_default[4] = {0};
static INT16U save_flag = 0;
// =============================================================================
// ��ʼ״̬����Ϸ��
// ÿ��Ԫ�ر�ʾ��Ϸ�ص�һ�У��±�������Ϸ�صײ�
// ���˸���2��1���ײ�2ȫ��Ϊ1�����ڽ�����ײ���
// ����һ����Ϸ�صĿ��Ϊ12��
// �����Ҫ��ͳ��10�У�ֻ���������1���ɣ�0xE007������Ȼ��ʾ��ز���ҲҪ��֮�Ķ�
// ��ĳ��Ԫ��Ϊ0xFFFFUʱ��˵�������ѱ�����
// ����4�����ڸ����飬����ʾ����
// �ٳ�ȥ�ײ�2�У���ʾ��������Ϸ�ظ߶�Ϊ22��
static const INT16U gs_uInitialTetrisPool[22] = {0xC003,0xC003, 0xC003,
		0xC003, 0xC003, 0xC003, 0xC003, 0xC003, 0xC003, 0xC003, 0xC003,
		0xC003, 0xC003, 0xC003, 0xC003, 0xC003, 0xC003, 0xC003, 0xC003,
		0xC003, 0xFFFF, 0xFFFF };
		
#define COL_BEGIN 2
#define COL_END 14
#define ROW_BEGIN 4
#define ROW_END 20

#define RECT_W 14
#define RECT_H 14

// =============================================================================
typedef struct TetrisManager  // ����ṹ��洢��Ϸ�������
{
	uint16_t pool[22];  // ��Ϸ��
	int8_t x;  // ��ǰ����x���꣬�˴�����Ϊ�������Ͻ�����
	int8_t y;  // ��ǰ����y����
	int8_t type[3];  // ��ǰ����һ��������һ����������
	int8_t orientation[3];  // ��ǰ����һ��������һ��������ת״̬
	unsigned score;  // �÷�
	unsigned erasedCount[4];  // ������
	unsigned erasedTotal;  // ��������
	unsigned tetrisCount[7];  // ��������
	unsigned tetrisTotal;  // ��������
	bool dead;  // ��
} TetrisManager;

// =============================================================================
typedef struct TetrisControl  // ����ṹ��洢�����������
{
	bool pause;  // ��ͣ
	bool clockwise;  // ��ת����˳ʱ��Ϊtrue
	int8_t direction;  // �ƶ�����0�����ƶ� 1�����ƶ�
	// ��Ϸ����ÿ�����ɫ
	// ���ڴ˰汾�ǲ�ɫ�ģ�������Ϸ�������޷��洢��ɫ��Ϣ
	// ��Ȼ�����ֻʵ�ֵ�ɫ��ģ���û��Ҫ�����������
	uint16_t color[22][16];
} TetrisControl;


static TetrisManager tetrisManager;
static TetrisControl tetrisControl;

static u8 *tetris_icon = 0;


// =============================================================================
// ���뷽��
void insertTetris(TetrisManager *manager) {
	// ��ǰ����
	uint16_t tetris = gs_uTetrisTable[manager->type[0]][manager->orientation[0]];

	// ��ǰ����ÿ4λȡ����λ����Ϸ����Ӧλ�ã�����ɲ��뷽��
	manager->pool[manager->y + 0] |= (((tetris >> 0x0) & 0x000F) << manager->x);
	manager->pool[manager->y + 1] |= (((tetris >> 0x4) & 0x000F) << manager->x);
	manager->pool[manager->y + 2] |= (((tetris >> 0x8) & 0x000F) << manager->x);
	manager->pool[manager->y + 3] |= (((tetris >> 0xC) & 0x000F) << manager->x);
}
bool checkCollision_L(uint16_t tetris)
{
	uint16_t dest = 0;
	
	dest |= ((tetris >> 0x0) & 0x0008);
	dest |= ((tetris >> 0x4) & 0x0008);
	dest |= ((tetris >> 0x8) & 0x0008);
	dest |= ((tetris >> 0xC) & 0x0008);
	
	return dest;
}
bool checkCollision_R(uint16_t tetris)
{
	uint16_t dest = 0;
	
	dest |= ((tetris >> 0x0) & 0x0001);
	dest |= ((tetris >> 0x4) & 0x0001);
	dest |= ((tetris >> 0x8) & 0x0001);
	dest |= ((tetris >> 0xC) & 0x0001);
	
	return dest;
}

// =============================================================================
// ��ײ���
bool checkCollision(const TetrisManager *manager) {
	// ��ǰ����
	uint16_t tetris = gs_uTetrisTable[manager->type[0]][manager->orientation[0]];
	uint16_t dest = 0;
	
	
	// ��ȡ��ǰ��������Ϸ���е�����
	// ��Ϸ������x y��С������Ϣ�����͵��ߴ����16λ�޷�������
	dest |= (((manager->pool[manager->y + 0] >> manager->x) << 0x0) & 0x000F);
	dest |= (((manager->pool[manager->y + 1] >> manager->x) << 0x4) & 0x00F0);
	dest |= (((manager->pool[manager->y + 2] >> manager->x) << 0x8) & 0x0F00);
	dest |= (((manager->pool[manager->y + 3] >> manager->x) << 0xC) & 0xF000);

	// ����ǰ������Ŀ����������ص�����ײ������λ��Ľ����Ϊ0
	return ((dest & tetris) != 0);
}
void show_one_diamonds(int8_t x,int8_t y,const uint16_t color)
{
	u8 * p;
	DISPLAY_ICONSHOW icon;
	
	p = (u8 *)setting_frame_buff;
	
	icon.icon_w = RECT_W;
	icon.icon_h = RECT_H;
	icon.transparent = TRANSPARENT_COLOR;
	icon.pos_x = x*RECT_W + 8;
	icon.pos_y = y*RECT_H + 8;
	
	frame_icon_draw(p, tetris_icon, &icon, NULL);
}


extern INT16U score[3];
// =============================================================================
// ��ʾ�÷���Ϣ
void printScore(const TetrisManager *manager) 
{
	int8_t i;
	INT16U pos_x_shift = 236;
	INT32U buf_show = setting_frame_buff;
	
	pos_x_shift += (R_drawAsciiChar((unsigned short *)buf_show, 48 + manager->score/10000,pos_x_shift,65, 320, 0xffff, 0, R_FONT_NUM5) & 0xff);
	pos_x_shift += (R_drawAsciiChar((unsigned short *)buf_show, 48 + manager->score/1000%10,pos_x_shift,65, 320, 0xffff, 0, R_FONT_NUM5) & 0xff);
	pos_x_shift += (R_drawAsciiChar((unsigned short *)buf_show, 48 + manager->score/100%10,pos_x_shift,65, 320, 0xffff, 0, R_FONT_NUM5) & 0xff);
	pos_x_shift += (R_drawAsciiChar((unsigned short *)buf_show, 48 + manager->score/10%10,pos_x_shift,65, 320, 0xffff, 0, R_FONT_NUM5) & 0xff);
	pos_x_shift += (R_drawAsciiChar((unsigned short *)buf_show, 48 + manager->score%10,pos_x_shift,65, 320, 0xffff, 0, R_FONT_NUM5) & 0xff);
}

// =============================================================================
// ��ʾ��һ��
void printNextTetris(const TetrisManager *manager) {
	int8_t i,x,y;
	uint16_t tetris;

	// ��һ��������Ӧ��ɫ��ʾ
	tetris = gs_uTetrisTable[manager->type[1]][manager->orientation[1]];

	for (i = 0; i < 16; ++i) {
		y = (i >> 2) + 11;  // �����õ���
		if (y > ROW_END)  // �����ײ�����
		{
			break;
		}
		x = (i & 3) + 16;  // �����õ���
		if ((tetris >> i) & 1)  // ���ĵ�С�������ڵ�ǰ��������
		{
			show_one_diamonds(x,y,0xF7A1);
		}
	}
}

// =============================================================================
// ��һ������
void giveTetris(TetrisManager *manager) {
	uint16_t tetris;

	manager->type[0] = manager->type[1];  // ��һ��������Ϊ��ǰ
	manager->orientation[0] = manager->orientation[1];

	manager->type[1] = rand_int() % 7;  // ���������һ������
	manager->orientation[1] = rand_int() & 3;

	tetris = gs_uTetrisTable[manager->type[0]][manager->orientation[0]]; // ��ǰ����
	// ���õ�ǰ����y���꣬��֤�ո���ʱֻ��ʾ����������һ��
	// ����ʵ��ʹ����ҿ����Ժܿ���ٶȽ��������ڲ���ʾ�����Ķ���4����
	if (tetris & 0xF000) {
		manager->y = 0;
	} else {
		manager->y = (tetris & 0xFF00) ? 1 : 2;
	}
	manager->x = 6;  // ���õ�ǰ����x����
	
	if (checkCollision(manager))  // ��⵽��ײ
	{
		manager->dead = 1;  // �����Ϸ����
	}
	else  // δ��⵽��ײ
	{
		insertTetris(manager);  // ����ǰ���������Ϸ��
	}
}


// =============================================================================
// �Ƴ�����
void removeTetris(TetrisManager *manager) {
	// ��ǰ����
	uint16_t tetris = gs_uTetrisTable[manager->type[0]][manager->orientation[0]];

	// ��ǰ����ÿ4λȡ������λȡ����λ�뵽��Ϸ����Ӧλ�ã�������Ƴ�����
	manager->pool[manager->y + 0] &=
			~(((tetris >> 0x0) & 0x000F) << manager->x);
	manager->pool[manager->y + 1] &=
			~(((tetris >> 0x4) & 0x000F) << manager->x);
	manager->pool[manager->y + 2] &=
			~(((tetris >> 0x8) & 0x000F) << manager->x);
	manager->pool[manager->y + 3] &=
			~(((tetris >> 0xC) & 0x000F) << manager->x);
}

// =============================================================================
// ��ʾ��ǰ����
void printCurrentTetris(const TetrisManager *manager,const TetrisControl *control) {
	int8_t x, y;
	int8_t i = 0, j= 0;

	// ��ʾ��ǰ���������ƶ�����õģ�Ϊ��ȥ�ƶ�ǰ�ķ��飬��Ҫ��չ��ʾ����
	// ���ڲ����������ƶ����ʲ���Ҫ������չ
	y = (manager->y > ROW_BEGIN) ? (manager->y - 1) : ROW_BEGIN;  // ������չһ��
	for (; y < ROW_END && y < manager->y + 4; ++y) {
		x = (manager->x > COL_BEGIN) ? (manager->x - 1) : COL_BEGIN;  // ������չһ��
		for (; x < COL_END && x < manager->x + 5; ++x)  // ������չһ��
		{
			if ((manager->pool[y] >> x) & 1)  // ��Ϸ�ظ÷����з���
			{
				// ����Ӧ��ɫ����ʾһ��ʵ�ķ���
				show_one_diamonds( x-2, y-ROW_BEGIN, control->color[y][x]);
			} 
			else
			{
				//show_one_diamonds( x, y-ROW_BEGIN, 0x8c71);
			}
		}
	}
}
// =============================================================================
// ������ɫ
void setPoolColor(const TetrisManager *manager, TetrisControl *control) {
	// ������ʾ��Ϸ��ʱ����Ҫ����Ϸ�����ж�ĳһ�����з������ʾ��Ӧ�������ɫ
	// ����ֻ�����ü��ɣ�û��Ҫ���
	// ���ƶ�������һ������ʱ����

	int8_t i, x, y;

	// ��ǰ����
	uint16_t tetris = gs_uTetrisTable[manager->type[0]][manager->orientation[0]];

	for (i = 0; i < 16; ++i) {
		y = (i >> 2) + manager->y;  // �����õ���
		if (y > ROW_END)  // �����ײ�����
		{
			break;
		}
		x = (i & 3) + manager->x;  // �����õ���
		if ((tetris >> i) & 1)  // ���ĵ�С�������ڵ�ǰ��������
		{
			control->color[y][x] = 0xF7A1;  // ������ɫ
		}
	}
}

// =============================================================================
// ��ת����
void rotateTetris(TetrisManager *manager, TetrisControl *control) {
	int8_t ori = manager->orientation[0];  // ��¼ԭ��ת״̬

	removeTetris(manager);  // ���ߵ�ǰ����

	// ˳/��ʱ����ת
	manager->orientation[0] =
			(control->clockwise) ? ((ori + 1) & 3) : ((ori + 3) & 3);

	if (checkCollision(manager))  // ��⵽��ײ
	{
		manager->orientation[0] = ori;  // �ָ�Ϊԭ��ת״̬
		insertTetris(manager);  // ���뵱ǰ���顣����״̬û�ı䣬����Ҫ������ɫ
	} else {
		insertTetris(manager);  // ���뵱ǰ����
		setPoolColor(manager, control);  // ������ɫ
		printCurrentTetris(manager, control);  // ��ʾ��ǰ����
	}
}



// ���м��
bool checkErasing(TetrisManager *manager, TetrisControl *control) {
	static const unsigned scores[5] = { 0, 50, 150, 300, 400};  // ���е÷�
	int8_t count = 0;
	int8_t k = 0, y = manager->y + 3;  // �������ϼ��

	do {
		if (y < ROW_END && manager->pool[y] == 0xFFFFU)  // ��Ч��������һ��������
				{
			++count;
			// ����һ�з���
			memmove(manager->pool + 1, manager->pool, sizeof(uint16_t) * y);
			// ��ɫ�����Ԫ����֮�ƶ�
			memmove(control->color[1], control->color[0],
					sizeof(int8_t[16]) * y);
		} else {
			--y;
			++k;
		}
	} while (y >= manager->y && k < 4);

	manager->erasedTotal += count;  // ��������
	manager->score += scores[count];  // �÷�
	//game_gradr += scores[count]; 

	if (count > 0) {
		++manager->erasedCount[count - 1];  // ����
	}

	giveTetris(manager);  // ����һ������
	setPoolColor(manager, control);  // ������ɫ

	return (count > 0);
}


// =============================================================================
// ��ʾ��Ϸ��
void printTetrisPool(const TetrisManager *manager, const TetrisControl *control) {
	int8_t x, y;

	for (y = ROW_BEGIN; y < ROW_END; ++y)  // ����ʾ����4�к͵ײ�2��
	{
		// ���㵽��Ϸ���еķ���
		for (x = COL_BEGIN; x < COL_END; ++x)  // ����ʾ���ұ߽�
		{
			if ((manager->pool[y] >> x) & 1)  // ��Ϸ�ظ÷����з���
			{
				// ����Ӧ��ɫ����ʾһ��ʵ�ķ���
				show_one_diamonds( x-2, y-ROW_BEGIN, control->color[y][x]);
			} else  // û�з��飬��ʾ�հ�
			{
				//show_one_diamonds( x, y-ROW_BEGIN, 0x8c71);
			}
		}
	}
	printCurrentTetris(manager, control);  // ��ʾ��ǰ����
	printNextTetris(manager);  // ��ʾ��һ������
	printScore(manager);  // ��ʾ�÷���Ϣ
}


// =============================================================================
// �����ƶ�����
void moveDownTetris(TetrisManager *manager, TetrisControl *control) 
{
	int8_t y = manager->y;  // ��¼ԭ��λ��

	removeTetris(manager);  // ���ߵ�ǰ����
	++manager->y;  // �����ƶ�

	if (checkCollision(manager))  // ��⵽��ײ
	{
		manager->y = y;  // �ָ�Ϊԭ��λ��
		insertTetris(manager);  // ���뵱ǰ���顣����λ��û�ı䣬����Ҫ������ɫ
		if (checkErasing(manager, control))  // ��⵽����
		{
			printTetrisPool(manager, control);  // ��ʾ��Ϸ��
		}
		//ap_setting_memcpy(buf_show,buf_base,getDispDevBufSize());
	}
	else 
	{
		insertTetris(manager);  // ���뵱ǰ����
		setPoolColor(manager, control);  // ������ɫ
		//printTetrisPool(manager, control);  // ��ʾ��Ϸ��
		printCurrentTetris(manager, control);  // ��ʾ��ǰ����
	}
}
// =============================================================================
// ˮƽ�ƶ�����
void horzMoveTetris(TetrisManager *manager, TetrisControl *control) {
	int x = manager->x;  // ��¼ԭ��λ��
	
	removeTetris(manager);  // ���ߵ�ǰ����
	control->direction == 0 ? (--manager->x) : (++manager->x);  // ��/���ƶ�

	if (checkCollision(manager))  // ��⵽��ײ
	{
		manager->x = x;  // �ָ�Ϊԭ��λ��
		insertTetris(manager);  // ���뵱ǰ���顣����λ��û�ı䣬����Ҫ������ɫ
	} else {
		insertTetris(manager);  // ���뵱ǰ����
		setPoolColor(manager, control);  // ������ɫ
		printCurrentTetris(manager, control);  // ��ʾ��ǰ����
	}
}

// =============================================================================
// ������
void keydownControl(TetrisManager *manager, TetrisControl *control, int key) 
{
	INT16U tetris;
	tetris = gs_uTetrisTable[manager->type[0]][manager->orientation[0]]; // ��ǰ����
	setting_frame_buff = get_game_show_buf(TRUE);

	switch (key) {
		case U:  // ��
			control->clockwise = 1;  // ˳ʱ����ת
			rotateTetris(manager, control);  // ��ת����
			break;
		
		case L:  // ��
			control->direction = 0;  // �����ƶ�
			horzMoveTetris(manager, control);  // ˮƽ�ƶ�����
			break;
		
		case R:  // ��
			control->direction = 1;  // �����ƶ�
			horzMoveTetris(manager, control);  // ˮƽ�ƶ�����
			break;
		
		case D:  // ��
			moveDownTetris(manager, control);  // �����ƶ�����
			break;
		
		default:
			break;
	}
	
	printTetrisPool(manager, control);//��ʾ��Ϸ��
	frame_buff_display();
}

//������Ϸ�ж�
INT8U endgame(TetrisManager *manager)
{
	if(manager->dead == 1)
		return 0;
	return 1;
}
// ���¿�ʼ��Ϸ
void restartGame(TetrisManager *manager, TetrisControl *control) 
{
	//INT8U i;
	memset(manager, 0, sizeof(TetrisManager));  // ȫ����0
	//gp_memset((INT8S *) manager, 0, sizeof(TetrisManager));
	// ��ʼ����Ϸ��
	memcpy(manager->pool, gs_uInitialTetrisPool, sizeof(uint16_t[22]));
	
	manager->type[1] = rand_int() % 7;  // ��һ��
	manager->orientation[1] = rand_int() & 3;

	memset(control, 0, sizeof(TetrisControl));  // ȫ����0

	giveTetris(manager);  // ����һ������
	setPoolColor(manager, control);  // ������ɫ
}
// ��ʼ����Ϸ
void game_tetris_init(TetrisManager *manager, TetrisControl *control)
{ 
	tetris_icon = get_bin_data(RES_GAME_TETRIS_ICON);
	game_bk_draw((u8 *)get_game_base_buf(), RES_GAME_TETRIS_BK, NULL);
	get_game_show_buf(TRUE);
	frame_buff_display();
	restartGame(manager, control); 
	sleeptime = 34;
	endGamestatus = 0;
}



void game_tetris_exit()
{
	endGamestatus = 1;
	free_buf(tetris_icon);
}


void game_tetris_entry(void)
{
	u8 msg, err;
	game_tetris_init(&tetrisManager, &tetrisControl);
	while(1){
		msg = (u8)XMsgQPend(SysCtrl.sysQ,&err); 
		switch (msg){
			case KEY_EVENT_UP:
				keydownControl(&tetrisManager, &tetrisControl,U);
				break;
			case KEY_EVENT_DOWN:
				keydownControl(&tetrisManager, &tetrisControl,D);
				break;
			case KEY_EVENT_LEFT:  
				keydownControl(&tetrisManager, &tetrisControl,L);
				break;
			case KEY_EVENT_RIGHT:
				keydownControl(&tetrisManager, &tetrisControl,R);
				break;
			case KEY_EVENT_POWER:
				game_tetris_exit();
				return;
			case SYS_EVENT_GAME_TICK:
				if(endgame(&tetrisManager))
					keydownControl(&tetrisManager, &tetrisControl,D);
				else
					XMsgQPost(SysCtrl.sysQ,(void*)makeEvent(KEY_EVENT_POWER,0));
				break;
		}
	}
}

