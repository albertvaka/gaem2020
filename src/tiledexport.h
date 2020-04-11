#pragma once

#include <array>

#include <SFML/Graphics.hpp>

struct TiledTiles
{
	static const sf::IntRect tileToTextureRect[];

	enum Value : unsigned short
	{
		NONE = 0,
		BG_1,
		BG_2,
		BG_3,
		BG_4,
		BG_5,
		BG_6,
		BG_7,
		BG_8,
		BG_9,
		BG_10,
		BG_11,
		BG_12,
		BG_13,
		BG_14,
		BG_15,
		BG_16,
		BG_17,
		BG_18,
		BG_19,
		BG_20,
		BG_21,
		BG_22,
		BG_23,
		BG_24,
		BG_25,
		BG_26,
		BG_27,
		BG_28,
		BG_29,
		BG_30,
		BG_31,
		BG_32,
		BG_33,
		BG_34,
		BG_35,
		BG_36,
		BG_37,
		BG_38,
		BG_39,
		BG_40,
		BG_41,
		BG_42,
		BG_43,
		BG_44,
		BG_45,
		BG_46,
		BG_47,
		BG_48,
		BG_49,
		BG_50,
		BG_51,
		BG_52,
		BG_53,
		BG_54,
		BG_55,
		BG_56,
		BG_57,
		BG_58,
		BG_59,
		BG_60,
		BG_61,
		BG_62,
		BG_63,
		BG_64,
		BG_65,
		BG_66,
		BG_67,
		BG_68,
		BG_69,
		BG_70,
		BG_71,
		BG_72,
		BG_73,
		BG_74,
		BG_75,
		BG_76,
		BG_77,
		BG_78,
		BG_79,
		BG_80,
		BG_81,
		BG_82,
		BG_83,
		BG_84,
		BG_85,
		BG_86,
		BG_87,
		BG_88,
		BG_89,
		BG_90,
		BG_91,
		BG_92,
		BG_93,
		BG_94,
		BG_95,
		BG_96,
		BG_97,
		BG_98,
		BG_99,
		BG_100,
		BG_101,
		BG_102,
		BG_103,
		BG_104,
		BG_105,
		BG_106,
		BG_107,
		BG_108,
		BG_109,
		ONE_WAY_1,
		ONE_WAY_2,
		ONE_WAY_3,
		ONE_WAY_4,
		ONE_WAY_5,
		ONE_WAY_6,
		ONE_WAY_7,
		ONE_WAY_8,
		ONE_WAY_9,
		ONE_WAY_10,
		ONE_WAY_11,
		ONE_WAY_12,
		ONE_WAY_13,
		ONE_WAY_14,
		ONE_WAY_15,
		ONE_WAY_16,
		RIGHT_SLOPE_1,
		RIGHT_SLOPE_2,
		RIGHT_SLOPE_3,
		RIGHT_SLOPE_4,
		LEFT_SLOPE_1,
		LEFT_SLOPE_2,
		LEFT_SLOPE_3,
		LEFT_SLOPE_4,
		SOLID_1,
		SOLID_2,
		SOLID_3,
		SOLID_4,
		SOLID_5,
		SOLID_6,
		SOLID_7,
		SOLID_8,
		SOLID_9,
		SOLID_10,
		SOLID_11,
		SOLID_12,
		SOLID_13,
		SOLID_14,
		SOLID_15,
		SOLID_16,
		SOLID_17,
		SOLID_18,
		SOLID_19,
		SOLID_20,
		SOLID_21,
		SOLID_22,
		SOLID_23,
		SOLID_24,
		SOLID_25,
		SOLID_26,
		SOLID_27,
		SOLID_28,
		SOLID_29,
		SOLID_30,
		SOLID_31,
		SOLID_32,
		SOLID_33,
		SOLID_34,
		SOLID_35,
		SOLID_36,
		BREAKABLE_1,
		BREAKABLE_2,
		BREAKABLE_3,
		BREAKABLE_4,
		SOLID_TRANSPARENT,
	};

	static const Value ONE_WAY_BEGIN = ONE_WAY_1;
	static const Value RIGHT_SLOPE_BEGIN = RIGHT_SLOPE_1;
	static const Value LEFT_SLOPE_BEGIN = LEFT_SLOPE_1;
	static const Value SOLID_BEGIN = SOLID_1;
	static const Value BREAKABLE_BEGING = BREAKABLE_1;

};

struct TiledMap
{
	static const unsigned short map[];
	static const sf::Vector2f map_size;
	static const std::array<sf::Rect<float>, 9> screens;
};

struct TiledEntities
{
	static const std::array<sf::Vector2f, 14> bat;
	static const sf::Vector2f gun;
	static const std::array<sf::Vector2f, 4> powerup;
	static const sf::Vector2f walljump;
	static const std::array<sf::Vector2f, 3> angrybat;
	static const std::array<sf::Vector2f, 2> batawake;
	static const sf::Vector2f spawn;
	
};

struct TiledAreas
{
	static const std::array<sf::Rect<float>, 1> lava;
	
};