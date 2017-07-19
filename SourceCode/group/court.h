#ifndef __COURT__H__
#define __COURT__H__

#include "CTargaImage.h"


#include "md2.h"
#include "function.h"
#include "c3ds.h"

//草地尺寸
#define COURT_HALF_WIDTH 90.0f    //60+30
#define COURT_HALF_HEIGHT 50.0f  //45+5

//比赛场地尺寸
#define MATCH_HALF_WIDTH 75.0f
#define MATCH_HALF_HEIGHT 45.0f

//广告牌
#define COURT_AD_OFFSET1 95.0f
#define COURT_AD_OFFSET2 55.0f
#define COURT_AD1_HALF_WIDTH 90.0f
#define COURT_AD1_HEIGHT 5.0f
#define COURT_AD2_HALF_WIDTH 50.0f
#define COURT_AD2_HEIGHT 5.0f

//观众席
#define LEVEL_VERTICAL_DIS 17.0f
#define LEVEL_HORIZONTAL_DIS 25.0f
#define LEVEL_STEPS 15.0f    //每一层有多少个阶级

//中间层的墙
#define WALL_HEIGHT 13.0f

//球门
#define GOAL_WIDTH 7.32f
#define GOAL_HEIGHT 4.0f
#define GOAL_LENGTH 3.0f 
#define GOAL_BAR_RADIUS 0.07f
#define BACK_X_SCALE 2.3f
#define BACK_Y_SCALE 1.3f
#define BACK_Z_SCALE 1.2f

//替补席
#define BENCH_SEAT_WIDTH 11.0f
#define BENCH_SEAT_LENGTH 2.8f
#define BENCH_SEAT_HEIGHT 3.0f 

//栏杆
#define RAILING_RADIUS 0.1f
#define RAILING_HEIGHT 2.0f
#define RAILING_PART_WIDTH 2.0f

//观众
#define AUDIENCE_WIDTH 1.5f
#define AUDIENCE_HEIGHT 4.5f
#define AUDIENCE_GAP 0.1f

//大屏幕
#define TV_LENGTH 6.0f
#define TV_HEIGHT 30.0f
#define TV_HALF_WIDTH 40.0f

//模型文件
#define BENCH_FILENAME "resource/3ds/bench.3ds"
#define RAILING_FILENAME "resource/3ds/railing.3ds"

class Court {
public:
	Court();
	void init();
	void load_texture();
	void load_3ds_model(char*, CLoad3DS&, t3DModel&, unsigned int*);
	void draw_3ds_model(t3DModel, unsigned int*);
	void render();
	void draw_lines();
	void draw_models();
	void draw_advertisement();
	void draw_audience();
	void draw_railing(float length);
	void draw_first_level();
	void draw_second_level();
	void draw_middle_level();
	void draw_third_level();
	void draw_steps(float length, float height, float width, float l_edge_step, float r_edge_step, float step_count, bool mid_air = false);
	void draw_goal();
	void draw_bench_seat();
	void draw_wall();
	void draw_football();
	void draw_tv();
	void draw_match_floor();

	CMD2Model flag0;
	CMD2Model player_a0;
	CMD2Model player_a1;
	CMD2Model player_a2;
	CMD2Model player_a3;
	CMD2Model player_a4;

	CMD2Model player_b0;
	CMD2Model player_b1;
	CMD2Model player_b2;
	CMD2Model player_b3;
	CMD2Model player_b4;

	unsigned int grass_texture_id;
	unsigned int floor_texture_id;
	unsigned int floor2_texture_id;
	unsigned int wall_texture_id;
	unsigned int ad1_texture_id;
	unsigned int third_ad1_texture_id;
	unsigned int third_ad2_texture_id;
	unsigned int third_ad3_texture_id;
	unsigned int third_ad4_texture_id;
	unsigned int middle_wall1_texture_id;
	unsigned int middle_wall2_texture_id;
	unsigned int middle_wall3_texture_id;
	unsigned int middle_wall4_texture_id;
	unsigned int ad2_texture_id;
	unsigned int audience_texture_id;
	unsigned int football_texture_id;
	unsigned int audience_seat_vertical_texture_id;
	unsigned int audience_seat_horizontal_texture_id;
	unsigned int env_texture_id;
	unsigned int wall_outside_texture_id;
	unsigned int wall_inside_texture_id;
	unsigned int tv_texture_id[6];

	unsigned int seat_models_texture[10];
	unsigned int railing_models_texture[10];

	CLoad3DS seat_Load3ds;	
	CLoad3DS railing_Load3ds;

	t3DModel seat_model;	
	t3DModel railing_model;

	GLuint seat_model_index;
	GLuint railing_model_index;
	GLuint goal_index;
	GLuint audience_index;

	bool show_audience;
};

#endif //__COURT__H__