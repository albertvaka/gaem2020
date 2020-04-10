#include "tiledexport.h"

const sf::IntRect TiledTiles::tileToTextureRect[] = {
	{},	//NONE
	{ 9 * 16, 2 * 16, 16, 16 }, //=1, BG_1, gid=67
	{ 10 * 16, 2 * 16, 16, 16 }, //=2, BG_2, gid=68
	{ 11 * 16, 2 * 16, 16, 16 }, //=3, BG_3, gid=69
	{ 21 * 16, 2 * 16, 16, 16 }, //=4, BG_4, gid=79
	{ 22 * 16, 2 * 16, 16, 16 }, //=5, BG_5, gid=80
	{ 23 * 16, 2 * 16, 16, 16 }, //=6, BG_6, gid=81
	{ 24 * 16, 2 * 16, 16, 16 }, //=7, BG_7, gid=82
	{ 14 * 16, 3 * 16, 16, 16 }, //=8, BG_8, gid=101
	{ 15 * 16, 3 * 16, 16, 16 }, //=9, BG_9, gid=102
	{ 16 * 16, 3 * 16, 16, 16 }, //=10, BG_10, gid=103
	{ 18 * 16, 3 * 16, 16, 16 }, //=11, BG_11, gid=105
	{ 21 * 16, 3 * 16, 16, 16 }, //=12, BG_12, gid=108
	{ 22 * 16, 3 * 16, 16, 16 }, //=13, BG_13, gid=109
	{ 23 * 16, 3 * 16, 16, 16 }, //=14, BG_14, gid=110
	{ 24 * 16, 3 * 16, 16, 16 }, //=15, BG_15, gid=111
	{ 8 * 16, 4 * 16, 16, 16 }, //=16, BG_16, gid=124
	{ 9 * 16, 4 * 16, 16, 16 }, //=17, BG_17, gid=125
	{ 11 * 16, 4 * 16, 16, 16 }, //=18, BG_18, gid=127
	{ 12 * 16, 4 * 16, 16, 16 }, //=19, BG_19, gid=128
	{ 21 * 16, 4 * 16, 16, 16 }, //=20, BG_20, gid=137
	{ 22 * 16, 4 * 16, 16, 16 }, //=21, BG_21, gid=138
	{ 23 * 16, 4 * 16, 16, 16 }, //=22, BG_22, gid=139
	{ 26 * 16, 4 * 16, 16, 16 }, //=23, BG_23, gid=142
	{ 27 * 16, 4 * 16, 16, 16 }, //=24, BG_24, gid=143
	{ 8 * 16, 5 * 16, 16, 16 }, //=25, BG_25, gid=153
	{ 9 * 16, 5 * 16, 16, 16 }, //=26, BG_26, gid=154
	{ 10 * 16, 5 * 16, 16, 16 }, //=27, BG_27, gid=155
	{ 11 * 16, 5 * 16, 16, 16 }, //=28, BG_28, gid=156
	{ 12 * 16, 5 * 16, 16, 16 }, //=29, BG_29, gid=157
	{ 20 * 16, 5 * 16, 16, 16 }, //=30, BG_30, gid=165
	{ 21 * 16, 5 * 16, 16, 16 }, //=31, BG_31, gid=166
	{ 6 * 16, 6 * 16, 16, 16 }, //=32, BG_32, gid=180
	{ 8 * 16, 6 * 16, 16, 16 }, //=33, BG_33, gid=182
	{ 9 * 16, 6 * 16, 16, 16 }, //=34, BG_34, gid=183
	{ 10 * 16, 6 * 16, 16, 16 }, //=35, BG_35, gid=184
	{ 11 * 16, 6 * 16, 16, 16 }, //=36, BG_36, gid=185
	{ 17 * 16, 6 * 16, 16, 16 }, //=37, BG_37, gid=191
	{ 18 * 16, 6 * 16, 16, 16 }, //=38, BG_38, gid=192
	{ 20 * 16, 6 * 16, 16, 16 }, //=39, BG_39, gid=194
	{ 21 * 16, 6 * 16, 16, 16 }, //=40, BG_40, gid=195
	{ 22 * 16, 6 * 16, 16, 16 }, //=41, BG_41, gid=196
	{ 6 * 16, 7 * 16, 16, 16 }, //=42, BG_42, gid=209
	{ 16 * 16, 7 * 16, 16, 16 }, //=43, BG_43, gid=219
	{ 17 * 16, 7 * 16, 16, 16 }, //=44, BG_44, gid=220
	{ 20 * 16, 7 * 16, 16, 16 }, //=45, BG_45, gid=223
	{ 21 * 16, 7 * 16, 16, 16 }, //=46, BG_46, gid=224
	{ 22 * 16, 7 * 16, 16, 16 }, //=47, BG_47, gid=225
	{ 28 * 16, 7 * 16, 16, 16 }, //=48, BG_48, gid=231
	{ 17 * 16, 8 * 16, 16, 16 }, //=49, BG_49, gid=249
	{ 18 * 16, 8 * 16, 16, 16 }, //=50, BG_50, gid=250
	{ 11 * 16, 9 * 16, 16, 16 }, //=51, BG_51, gid=272
	{ 12 * 16, 9 * 16, 16, 16 }, //=52, BG_52, gid=273
	{ 13 * 16, 9 * 16, 16, 16 }, //=53, BG_53, gid=274
	{ 17 * 16, 9 * 16, 16, 16 }, //=54, BG_54, gid=278
	{ 18 * 16, 9 * 16, 16, 16 }, //=55, BG_55, gid=279
	{ 19 * 16, 9 * 16, 16, 16 }, //=56, BG_56, gid=280
	{ 20 * 16, 9 * 16, 16, 16 }, //=57, BG_57, gid=281
	{ 12 * 16, 10 * 16, 16, 16 }, //=58, BG_58, gid=302
	{ 14 * 16, 10 * 16, 16, 16 }, //=59, BG_59, gid=304
	{ 16 * 16, 10 * 16, 16, 16 }, //=60, BG_60, gid=306
	{ 16 * 16, 11 * 16, 16, 16 }, //=61, BG_61, gid=335
	{ 18 * 16, 11 * 16, 16, 16 }, //=62, BG_62, gid=337
	{ 19 * 16, 11 * 16, 16, 16 }, //=63, BG_63, gid=338
	{ 21 * 16, 11 * 16, 16, 16 }, //=64, BG_64, gid=340
	{ 22 * 16, 11 * 16, 16, 16 }, //=65, BG_65, gid=341
	{ 23 * 16, 11 * 16, 16, 16 }, //=66, BG_66, gid=342
	{ 24 * 16, 11 * 16, 16, 16 }, //=67, BG_67, gid=343
	{ 25 * 16, 11 * 16, 16, 16 }, //=68, BG_68, gid=344
	{ 10 * 16, 12 * 16, 16, 16 }, //=69, BG_69, gid=358
	{ 11 * 16, 12 * 16, 16, 16 }, //=70, BG_70, gid=359
	{ 12 * 16, 12 * 16, 16, 16 }, //=71, BG_71, gid=360
	{ 13 * 16, 12 * 16, 16, 16 }, //=72, BG_72, gid=361
	{ 15 * 16, 12 * 16, 16, 16 }, //=73, BG_73, gid=363
	{ 18 * 16, 12 * 16, 16, 16 }, //=74, BG_74, gid=366
	{ 19 * 16, 12 * 16, 16, 16 }, //=75, BG_75, gid=367
	{ 10 * 16, 13 * 16, 16, 16 }, //=76, BG_76, gid=387
	{ 11 * 16, 13 * 16, 16, 16 }, //=77, BG_77, gid=388
	{ 12 * 16, 13 * 16, 16, 16 }, //=78, BG_78, gid=389
	{ 13 * 16, 13 * 16, 16, 16 }, //=79, BG_79, gid=390
	{ 14 * 16, 13 * 16, 16, 16 }, //=80, BG_80, gid=391
	{ 15 * 16, 13 * 16, 16, 16 }, //=81, BG_81, gid=392
	{ 18 * 16, 13 * 16, 16, 16 }, //=82, BG_82, gid=395
	{ 19 * 16, 13 * 16, 16, 16 }, //=83, BG_83, gid=396
	{ 10 * 16, 14 * 16, 16, 16 }, //=84, BG_84, gid=416
	{ 11 * 16, 14 * 16, 16, 16 }, //=85, BG_85, gid=417
	{ 12 * 16, 14 * 16, 16, 16 }, //=86, BG_86, gid=418
	{ 13 * 16, 14 * 16, 16, 16 }, //=87, BG_87, gid=419
	{ 18 * 16, 14 * 16, 16, 16 }, //=88, BG_88, gid=424
	{ 19 * 16, 14 * 16, 16, 16 }, //=89, BG_89, gid=425
	{ 18 * 16, 15 * 16, 16, 16 }, //=90, BG_90, gid=453
	{ 19 * 16, 15 * 16, 16, 16 }, //=91, BG_91, gid=454
	{ 24 * 16, 15 * 16, 16, 16 }, //=92, BG_92, gid=459
	{ 25 * 16, 15 * 16, 16, 16 }, //=93, BG_93, gid=460
	{ 28 * 16, 2 * 16, 16, 16 }, //=94, ONE_WAY_1, gid=86
	{ 19 * 16, 3 * 16, 16, 16 }, //=95, ONE_WAY_2, gid=106
	{ 20 * 16, 3 * 16, 16, 16 }, //=96, ONE_WAY_3, gid=107
	{ 28 * 16, 3 * 16, 16, 16 }, //=97, ONE_WAY_4, gid=115
	{ 16 * 16, 4 * 16, 16, 16 }, //=98, ONE_WAY_5, gid=132
	{ 17 * 16, 4 * 16, 16, 16 }, //=99, ONE_WAY_6, gid=133
	{ 18 * 16, 4 * 16, 16, 16 }, //=100, ONE_WAY_7, gid=134
	{ 20 * 16, 4 * 16, 16, 16 }, //=101, ONE_WAY_8, gid=136
	{ 28 * 16, 4 * 16, 16, 16 }, //=102, ONE_WAY_9, gid=144
	{ 25 * 16, 6 * 16, 16, 16 }, //=103, ONE_WAY_10, gid=199
	{ 27 * 16, 11 * 16, 16, 16 }, //=104, ONE_WAY_11, gid=346
	{ 21 * 16, 12 * 16, 16, 16 }, //=105, ONE_WAY_12, gid=369
	{ 22 * 16, 12 * 16, 16, 16 }, //=106, ONE_WAY_13, gid=370
	{ 27 * 16, 12 * 16, 16, 16 }, //=107, ONE_WAY_14, gid=375
	{ 28 * 16, 12 * 16, 16, 16 }, //=108, ONE_WAY_15, gid=376
	{ 10 * 16, 1 * 16, 16, 16 }, //=109, RIGHT_SLOPE_1, gid=39
	{ 13 * 16, 1 * 16, 16, 16 }, //=110, RIGHT_SLOPE_2, gid=42
	{ 23 * 16, 7 * 16, 16, 16 }, //=111, RIGHT_SLOPE_3, gid=226
	{ 22 * 16, 8 * 16, 16, 16 }, //=112, RIGHT_SLOPE_4, gid=254
	{ 11 * 16, 1 * 16, 16, 16 }, //=113, LEFT_SLOPE_1, gid=40
	{ 12 * 16, 1 * 16, 16, 16 }, //=114, LEFT_SLOPE_2, gid=41
	{ 27 * 16, 7 * 16, 16, 16 }, //=115, LEFT_SLOPE_3, gid=230
	{ 28 * 16, 8 * 16, 16, 16 }, //=116, LEFT_SLOPE_4, gid=260
	{ 12 * 16, 2 * 16, 16, 16 }, //=117, SOLID_1, gid=70
	{ 13 * 16, 2 * 16, 16, 16 }, //=118, SOLID_2, gid=71
	{ 14 * 16, 2 * 16, 16, 16 }, //=119, SOLID_3, gid=72
	{ 15 * 16, 2 * 16, 16, 16 }, //=120, SOLID_4, gid=73
	{ 16 * 16, 2 * 16, 16, 16 }, //=121, SOLID_5, gid=74
	{ 17 * 16, 2 * 16, 16, 16 }, //=122, SOLID_6, gid=75
	{ 18 * 16, 2 * 16, 16, 16 }, //=123, SOLID_7, gid=76
	{ 19 * 16, 2 * 16, 16, 16 }, //=124, SOLID_8, gid=77
	{ 20 * 16, 2 * 16, 16, 16 }, //=125, SOLID_9, gid=78
	{ 8 * 16, 3 * 16, 16, 16 }, //=126, SOLID_10, gid=95
	{ 9 * 16, 3 * 16, 16, 16 }, //=127, SOLID_11, gid=96
	{ 10 * 16, 3 * 16, 16, 16 }, //=128, SOLID_12, gid=97
	{ 11 * 16, 3 * 16, 16, 16 }, //=129, SOLID_13, gid=98
	{ 12 * 16, 3 * 16, 16, 16 }, //=130, SOLID_14, gid=99
	{ 13 * 16, 3 * 16, 16, 16 }, //=131, SOLID_15, gid=100
	{ 8 * 16, 7 * 16, 16, 16 }, //=132, SOLID_16, gid=211
	{ 9 * 16, 7 * 16, 16, 16 }, //=133, SOLID_17, gid=212
	{ 10 * 16, 7 * 16, 16, 16 }, //=134, SOLID_18, gid=213
	{ 24 * 16, 7 * 16, 16, 16 }, //=135, SOLID_19, gid=227
	{ 25 * 16, 7 * 16, 16, 16 }, //=136, SOLID_20, gid=228
	{ 26 * 16, 7 * 16, 16, 16 }, //=137, SOLID_21, gid=229
	{ 23 * 16, 8 * 16, 16, 16 }, //=138, SOLID_22, gid=255
	{ 27 * 16, 8 * 16, 16, 16 }, //=139, SOLID_23, gid=259
	{ 8 * 16, 9 * 16, 16, 16 }, //=140, SOLID_24, gid=269
	{ 9 * 16, 9 * 16, 16, 16 }, //=141, SOLID_25, gid=270
	{ 22 * 16, 9 * 16, 16, 16 }, //=142, SOLID_26, gid=283
	{ 28 * 16, 9 * 16, 16, 16 }, //=143, SOLID_27, gid=289
	{ 28 * 16, 10 * 16, 16, 16 }, //=144, SOLID_28, gid=318
	{ 24 * 16, 13 * 16, 16, 16 }, //=145, SOLID_29, gid=401
	{ 25 * 16, 13 * 16, 16, 16 }, //=146, SOLID_30, gid=402
	{ 24 * 16, 14 * 16, 16, 16 }, //=147, SOLID_31, gid=430
	{ 25 * 16, 14 * 16, 16, 16 }, //=148, SOLID_32, gid=431
	{ 1 * 16, 0 * 16, 16, 16 }, //=149, BREAKABLE_1, gid=1
	{ 1 * 16, 1 * 16, 16, 16 }, //=150, BREAKABLE_2, gid=30
	{ 24 * 16, 1 * 16, 16, 16 }, //=151, BREAKABLE_3, gid=53
	{},	//SOLID_TRANSPARENT
};

const int TiledMap::width = 160;
const int TiledMap::height = 64;

const unsigned short TiledMap::map[] = {
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,125,125,125,125,125,125,125,125,125,125,125,125,125,125,125,125,125,125,125,125,125,125,125,125,125,125,125,125,125,125,125,125,125,125,125,125,125,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,125,0,0,0,0,0,0,
		0,0,0,0,0,0,149,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,125,0,0,0,0,0,0,
		0,0,0,0,0,0,150,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,125,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,16,17,17,17,0,16,17,17,18,0,16,17,17,18,0,16,17,17,0,25,0,16,17,17,17,0,16,34,34,34,0,0,0,125,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,25,0,0,0,0,25,0,0,25,0,25,0,0,25,0,25,0,0,0,25,0,25,0,0,0,0,25,0,0,0,0,0,0,125,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,25,0,0,0,0,25,0,0,25,0,25,0,0,25,0,25,0,0,0,25,0,26,17,17,0,0,33,34,34,18,0,0,0,125,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,25,0,17,18,0,26,17,27,35,0,26,17,17,28,0,25,0,0,0,25,0,25,0,0,0,0,0,0,0,25,0,0,0,125,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,25,0,0,25,0,25,0,33,18,0,25,0,0,25,0,25,0,0,0,25,0,25,0,0,0,0,0,0,0,25,0,0,0,125,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,125,125,125,125,125,125,125,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,33,17,17,35,0,25,0,0,25,0,25,0,0,25,0,33,17,17,0,25,0,33,17,17,17,0,16,17,17,35,0,0,0,125,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,125,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,25,0,0,0,0,0,0,125,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,125,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,25,0,0,0,0,0,0,125,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,125,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,98,99,99,99,100,0,0,0,0,0,0,0,0,0,0,25,0,0,0,0,0,0,125,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,125,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,47,111,135,135,136,135,136,137,135,136,137,115,48,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,98,99,100,0,0,0,0,0,0,0,0,0,0,0,0,0,0,98,99,100,0,0,0,25,0,0,0,0,0,0,125,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,125,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,112,138,0,0,0,0,0,0,0,0,0,139,116,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,25,0,0,0,0,0,0,125,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,125,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,142,0,0,0,0,0,0,0,0,0,0,0,143,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,25,0,0,0,0,0,0,125,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,125,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,142,0,0,0,0,0,0,0,0,0,0,0,144,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,98,99,100,0,0,0,0,98,99,100,0,0,0,0,0,0,0,0,25,0,0,0,0,0,0,125,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,125,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,142,0,0,98,99,100,0,0,0,0,19,0,144,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,25,0,0,0,0,0,0,125,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,125,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,142,0,0,0,0,0,0,0,0,16,29,18,144,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,25,0,0,0,0,0,0,125,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,125,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,142,0,54,55,0,0,0,0,16,35,36,36,144,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,36,0,0,0,0,0,0,125,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,125,119,119,119,119,120,0,0,0,0,117,118,118,118,118,118,118,118,118,118,118,118,118,118,120,107,107,108,107,107,104,107,118,118,118,118,118,118,118,118,118,118,118,118,118,118,118,119,119,119,119,119,119,119,119,119,119,119,119,119,119,119,119,119,119,119,119,119,119,119,119,119,119,119,119,119,119,119,119,119,119,119,119,119,125,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,125,0,0,0,0,122,123,123,123,123,123,123,123,123,123,123,123,123,123,124,0,0,0,0,0,25,0,122,123,123,123,123,123,123,123,123,123,123,123,123,123,123,124,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,125,0,0,0,0,122,123,123,151,123,123,123,123,123,123,123,123,123,125,124,18,0,0,0,0,25,0,122,123,122,123,123,123,123,123,123,123,123,123,122,123,123,124,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,125,0,0,0,0,122,123,123,123,123,123,151,151,123,123,123,123,123,123,124,33,27,17,17,27,35,0,122,123,123,123,151,123,125,123,123,123,151,123,123,123,123,124,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,125,0,0,0,0,122,123,123,123,123,123,123,123,123,123,123,151,123,123,124,0,33,18,0,25,0,0,122,123,123,151,123,123,123,123,123,123,123,123,123,123,123,124,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,125,0,0,0,0,122,123,123,123,123,123,123,123,123,123,123,123,123,123,124,0,0,25,0,33,17,17,122,123,123,123,123,123,123,123,123,123,123,123,151,123,123,124,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,125,0,0,0,0,122,123,123,123,123,123,123,123,123,123,123,123,125,123,124,0,16,28,0,0,0,0,151,123,123,123,123,123,123,151,123,123,123,123,123,123,123,124,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,125,0,0,0,0,122,123,123,151,123,123,122,123,123,123,123,123,123,123,124,17,35,26,18,0,0,0,151,123,123,123,123,123,123,123,123,123,123,124,123,122,123,124,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,125,0,0,0,0,122,123,123,123,123,123,123,123,123,151,123,123,123,123,124,0,0,25,25,0,0,0,151,123,123,123,123,123,123,123,123,151,123,123,122,123,123,124,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,125,0,0,0,0,122,123,123,123,123,123,125,123,123,123,123,123,123,151,124,0,0,25,33,18,0,0,122,123,123,151,123,123,123,123,123,123,123,123,123,123,123,124,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,125,0,0,0,0,122,123,151,123,123,122,123,123,123,123,123,123,123,123,124,0,0,25,0,33,17,17,122,123,123,123,123,123,124,123,123,123,123,123,123,123,123,124,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,125,0,0,0,0,122,123,123,123,123,123,123,123,123,123,123,123,123,123,124,0,0,25,0,0,0,0,122,123,122,123,123,123,123,123,123,123,123,151,151,123,123,124,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,125,0,0,0,0,122,123,123,123,123,123,123,123,151,123,123,123,151,123,124,0,0,26,34,18,0,0,122,123,123,123,123,123,123,123,123,123,123,123,123,123,123,124,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,125,0,0,0,0,122,123,125,123,123,123,123,123,123,123,123,123,151,123,124,17,18,25,0,33,18,0,122,123,123,123,151,123,123,123,123,123,123,123,123,123,123,124,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,125,0,0,0,0,122,123,123,123,123,151,123,123,123,123,123,123,123,123,124,0,33,35,0,0,25,0,122,123,123,151,123,123,123,123,123,123,151,123,123,123,123,124,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,125,0,0,0,0,122,123,123,123,151,123,123,123,122,125,123,123,123,123,124,0,0,0,0,0,26,17,122,123,123,123,123,122,123,123,123,123,123,123,123,123,123,124,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,125,0,0,0,0,122,123,123,123,123,123,123,123,123,123,123,123,123,125,124,0,0,0,0,0,25,0,122,123,123,123,123,123,123,123,123,122,123,123,123,123,151,124,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,125,0,0,0,0,122,151,122,123,122,123,123,123,123,123,151,123,123,123,124,16,17,17,17,17,35,0,122,123,124,123,123,123,151,123,123,123,123,123,123,123,123,124,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,125,0,0,0,0,122,123,123,123,151,123,123,123,123,123,123,123,123,122,124,28,0,0,0,0,0,0,122,123,123,123,123,123,123,123,123,123,123,151,123,123,123,124,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,125,0,0,0,0,122,123,123,123,123,123,123,123,123,123,123,123,123,123,124,25,0,0,0,0,0,0,122,123,123,123,123,123,123,123,123,123,123,123,123,123,123,124,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,125,0,0,0,0,0,0,
		0,0,0,0,0,125,132,132,133,134,134,132,133,140,140,141,134,132,132,132,132,133,134,134,132,132,140,141,134,132,133,134,132,133,140,141,133,134,134,134,134,146,145,141,132,132,133,134,132,132,133,134,132,133,134,140,141,132,132,133,132,133,140,141,132,132,132,132,133,134,122,123,123,123,125,102,102,102,102,123,123,123,123,123,123,123,123,123,123,123,123,123,123,123,118,118,151,151,151,118,118,123,123,123,123,123,123,123,123,123,123,123,123,123,123,123,123,123,123,123,123,123,123,123,123,123,123,123,123,123,123,123,123,123,123,123,123,123,123,123,123,123,123,123,123,123,123,123,123,123,123,123,123,124,0,0,0,0,0,0,
		0,0,0,0,0,125,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,148,147,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,32,0,0,0,125,0,0,0,0,125,9,10,8,9,10,8,9,10,10,10,10,10,8,8,9,10,0,0,0,8,9,10,11,8,9,10,11,20,20,8,9,10,10,10,10,10,151,0,0,0,0,0,0,0,0,0,37,0,0,0,0,0,0,0,0,0,37,0,0,37,0,0,0,0,0,0,0,0,0,0,0,0,24,125,0,0,0,0,0,0,
		0,0,0,0,0,125,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,148,147,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,32,0,0,0,125,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,21,20,0,0,0,0,0,0,0,151,0,0,0,0,0,0,0,0,0,37,0,0,0,0,0,0,0,0,0,37,0,0,37,0,0,0,0,0,0,0,0,0,0,0,0,0,125,0,0,0,0,0,0,
		0,0,0,0,0,125,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,148,147,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,32,0,0,0,125,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,39,40,0,0,0,97,96,94,0,0,0,0,0,0,0,0,0,20,0,0,0,0,0,0,0,151,0,0,0,0,0,0,0,0,0,37,0,0,0,0,0,0,0,0,0,37,0,0,37,0,0,0,0,0,0,0,0,0,0,0,0,0,125,0,0,0,0,0,0,
		0,0,0,0,0,125,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,148,147,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,105,108,108,106,0,0,0,0,32,0,0,0,125,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,45,46,0,0,0,0,80,0,0,0,0,0,0,0,0,0,0,31,0,0,0,0,0,0,0,151,0,0,0,0,0,0,0,38,0,44,64,65,65,66,65,66,65,67,0,44,0,0,44,0,64,65,67,0,51,43,0,0,0,0,0,0,125,0,0,0,0,0,0,
		0,0,0,0,0,125,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,62,63,0,148,147,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,42,0,0,0,125,0,0,0,0,0,0,0,0,0,0,0,0,39,40,0,0,0,0,0,0,0,0,30,0,0,0,0,0,0,0,0,0,0,0,0,0,97,102,102,102,103,122,118,151,151,151,118,118,118,118,118,118,119,119,119,119,119,118,118,118,118,118,119,119,118,118,119,118,118,118,118,120,0,0,0,0,0,0,125,0,0,0,0,0,0,
		0,0,0,0,0,125,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,74,75,0,148,147,0,0,0,0,0,105,108,108,107,126,108,106,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,117,118,118,118,123,118,118,118,118,118,118,118,118,120,0,0,0,45,46,0,39,40,0,0,0,0,0,30,0,97,96,94,0,0,0,0,0,0,0,0,0,0,0,0,0,41,125,31,0,0,0,0,0,0,125,0,0,5,4,0,0,0,0,5,0,4,0,0,0,0,4,5,0,0,5,0,125,0,0,0,0,0,0,125,0,0,0,0,0,0,
		0,0,0,0,0,125,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,117,120,0,0,0,0,0,0,0,0,0,0,0,62,63,82,83,0,148,147,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,24,125,23,22,81,0,0,0,0,0,0,0,45,46,0,0,0,0,0,80,0,0,30,0,0,0,0,0,0,0,0,0,0,0,0,0,0,41,125,0,0,0,0,0,0,0,125,0,0,5,4,0,0,0,0,5,0,4,0,0,0,0,4,5,0,0,5,0,125,0,0,0,0,0,0,125,0,0,0,0,0,0,
		0,0,0,0,0,125,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,125,125,0,0,0,0,0,0,0,0,0,0,0,74,75,88,89,0,148,147,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,125,0,0,73,0,0,0,0,0,0,0,0,0,0,0,0,0,0,30,0,0,80,0,0,0,0,0,0,0,0,0,0,0,97,102,102,103,125,0,0,0,0,0,0,0,125,0,0,5,4,0,0,0,0,5,0,4,0,0,0,0,4,5,0,0,5,0,125,0,0,0,0,0,0,125,0,0,0,0,0,0,
		0,0,0,0,0,125,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,125,125,118,120,0,0,0,0,0,0,0,0,0,82,83,90,91,0,148,147,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6,7,0,0,125,0,0,80,0,0,0,0,0,0,0,0,0,0,0,97,96,94,30,0,0,30,0,0,0,0,62,63,0,0,0,0,0,0,0,0,41,125,0,0,0,0,0,49,50,125,0,0,13,4,0,0,0,0,5,0,4,0,0,0,0,12,5,0,0,13,0,125,0,0,0,0,0,0,125,0,0,0,0,0,0,
		0,0,0,0,0,125,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,125,125,125,125,0,0,0,0,0,0,0,0,0,88,89,82,83,0,148,147,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,14,15,0,0,125,60,52,58,53,0,0,0,0,0,0,0,0,0,0,0,30,0,80,0,0,30,0,0,62,63,74,75,0,0,0,0,0,0,0,0,41,122,119,151,151,151,117,119,119,124,95,0,0,4,0,0,0,0,5,0,4,0,0,0,0,0,0,0,0,0,0,125,0,0,0,0,0,0,125,0,0,0,0,0,0,
		0,0,0,0,0,125,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,125,125,125,125,118,120,0,0,0,0,0,0,0,88,89,82,83,0,148,147,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,22,0,0,0,125,61,0,0,59,0,0,0,0,0,0,0,0,0,0,0,30,0,30,0,0,80,0,0,74,75,82,83,0,0,0,0,0,0,97,102,103,125,69,0,0,0,0,0,0,125,4,0,0,12,0,0,121,0,13,0,4,0,0,151,0,0,5,0,0,0,0,125,0,0,0,0,0,0,125,0,0,0,0,0,0,
		0,0,0,0,0,125,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,125,125,125,125,125,125,0,0,0,0,0,0,0,82,83,88,89,0,93,92,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,2,2,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,70,71,72,0,0,0,0,0,0,0,0,0,0,80,0,101,96,94,30,0,0,82,83,88,89,62,63,0,0,0,0,0,0,41,125,76,0,0,0,0,0,0,125,4,0,0,0,0,0,5,0,0,0,4,0,0,0,0,0,5,0,0,0,0,125,0,0,0,0,0,0,125,0,0,0,0,0,0,
		0,0,0,0,0,125,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,125,125,125,125,125,125,102,102,102,94,0,0,0,82,83,82,83,0,0,0,0,0,0,0,0,0,109,131,131,113,1,2,3,0,0,0,109,126,129,130,131,127,126,131,113,2,0,0,0,0,0,0,0,0,0,0,0,0,0,77,78,79,0,0,0,0,0,0,0,0,0,0,30,0,30,80,0,30,0,0,88,89,88,89,74,75,0,0,0,0,0,0,41,125,84,0,0,0,0,0,0,125,12,0,0,0,0,0,5,0,0,0,12,0,0,0,0,0,5,0,0,0,95,125,0,0,0,0,0,0,125,0,0,0,0,0,0,
		0,0,0,0,0,125,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,151,151,0,0,151,151,0,0,0,0,0,0,0,88,89,88,89,0,0,0,0,0,0,109,131,131,92,0,0,93,130,131,127,126,129,129,92,0,0,0,0,0,0,0,93,130,131,113,0,3,0,0,0,1,2,0,0,0,2,85,86,87,0,3,0,0,0,1,2,3,0,0,30,0,30,30,0,30,3,0,90,91,90,91,90,91,0,0,0,0,1,2,41,125,84,0,0,0,56,57,68,125,0,0,0,0,0,0,5,0,0,0,0,0,0,0,0,0,13,0,0,0,4,125,0,0,0,0,0,0,125,0,0,0,0,0,0,
		0,0,0,0,0,125,2,0,0,0,0,0,0,0,0,0,0,0,0,0,2,3,0,151,151,1,3,151,151,0,0,0,1,2,0,0,90,91,90,91,0,0,1,1,3,109,92,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,93,130,129,129,130,129,130,130,130,129,129,130,131,127,126,130,131,129,129,129,130,131,130,129,130,129,129,130,131,129,130,130,131,126,127,127,126,127,131,129,130,130,129,129,131,106,122,119,151,151,151,117,119,119,124,0,0,0,0,0,0,5,0,0,0,0,0,0,0,0,0,0,0,0,0,4,125,0,0,0,0,0,0,125,0,0,0,0,0,0,
		0,0,0,0,0,131,130,131,113,3,0,0,0,0,0,0,0,1,109,127,128,131,127,126,130,131,129,129,131,131,129,130,131,126,131,126,131,129,131,130,131,131,131,131,131,92,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,125,0,0,0,0,0,5,4,0,0,0,0,0,0,0,13,0,0,0,0,0,0,0,0,121,0,0,0,0,12,125,0,0,0,0,0,0,125,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,93,127,113,2,109,127,113,3,109,129,92,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,125,0,0,0,0,0,13,4,0,0,0,0,0,0,0,0,0,0,0,121,0,0,0,0,4,0,0,0,0,0,125,119,114,0,0,110,118,125,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,93,129,92,0,93,131,92,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,125,0,0,0,0,0,0,12,0,0,0,0,0,151,0,0,0,0,0,0,0,0,0,0,4,0,0,0,0,0,125,123,125,119,119,125,123,125,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,122,119,119,119,119,119,119,119,120,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,12,0,0,0,0,0,125,124,123,125,122,123,125,125,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,125,125,125,125,125,125,125,125,0,0,0,0,0,0,
		};