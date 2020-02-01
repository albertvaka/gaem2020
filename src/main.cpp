#include "imgui.h"
#include "imgui-SFML.h"

#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>

#include <iostream>
#include <queue>
#include <random>
#include <set>

#include "animation.h"
#include "input.h"
#include "mates.h"
#include "rand.h"

#include <fstream>

InputState input;
sf::Font font;

namespace Editor
{
	sf::Texture texture;

	sf::Sprite spr_selected;

	std::vector<Animation> all_animations(16);
	Animation* anim = &all_animations[0];
	std::vector<AnimationData> all_animation_datas(16);
	AnimationData* data = &all_animation_datas[0];
	std::vector<std::string> all_animation_names(16);

	int anims_total = 1;
	int anim_selected = 0;

	int frame_current; 
	sf::IntRect* rect = &data->rect[0];
	int* time = &data->timer[0];

	char buff_animation_name[128];

	void RefreshFrameSelected()
	{
		//spr_selected.setTexture(texture);

		rect = &data->rect[frame_current];
		time = &data->timer[frame_current];
		spr_selected.setTextureRect(*rect);
	}

	void RefreshAnimationNameInputText()
	{
		strcpy_s(Editor::buff_animation_name, Editor::all_animation_names[Editor::anim_selected].c_str());
	}

	void InitNewAnim()
	{
		data->frames = 1;
		frame_current = 0;
		data->timer[frame_current] = 1;
		data->rect[frame_current] = sf::IntRect(1, 1, 1, 1);
		RefreshFrameSelected();

		Editor::anim->data = Editor::data;
	}

	void AddNewAnim()
	{
		int last_anim = Editor::anims_total;
		Editor::anims_total++;
		AnimationData* last_data = &all_animation_datas[last_anim];
		last_data->frames = 1;
		last_data->timer[0] = 1;
		last_data->rect[0] = sf::IntRect(1, 1, 1, 1);

		all_animations[last_anim].data = last_data;
	}

	void UpdatePreview(sf::Time t)
	{
		anim->Update(t.asMilliseconds());
	}

	void AddNewFrame()
	{
		anim->data->frames++;
		//current = anim->data->frames-1;
		//RefreshFrameSelected();
	}

	void SelectFrame(int f)
	{
		frame_current = f;
		RefreshFrameSelected();
	}


	
	
};

sf::RenderTexture rtex_preview;

const int SCR_WIDTH = 1200;
const int SCR_HEIGHT = 800;

void LoadGame(sf::RenderWindow& window)
{
	Editor::texture.loadFromFile("data/spritesheet.png");

	Editor::spr_selected.setTexture(Editor::texture);
	Editor::spr_selected.setTextureRect(sf::IntRect(16, 16, 16, 16));
	
	window.setFramerateLimit(60);
	ImGui::SFML::Init(window);

	input.RemapInput();
}

void Image( const sf::FloatRect& textureRect, const sf::Color& tintColor = sf::Color::White, const sf::Color& borderColor = sf::Color::Transparent )
{
	sf::Vector2f textureSize = static_cast<sf::Vector2f>(Editor::texture.getSize());
	ImVec2 uv0(textureRect.left / textureSize.x, (textureRect.top + textureRect.height) / textureSize.y);
	ImVec2 uv1((textureRect.left + textureRect.width) / textureSize.x, textureRect.top / textureSize.y);
	ImGui::Image(rtex_preview.getTexture().getNativeHandle(), rtex_preview.getTexture().getSize(), uv0, uv1, tintColor, borderColor);
}

void EditorSection_Editor()
{
	sf::Sprite& spr = Editor::spr_selected;

	std::string editor_title = "editor.";
	if (input.IsMousePressed(1))
	{
		editor_title += " (" + std::to_string(sf::Mouse::getPosition().x) + ", " +
							   std::to_string(sf::Mouse::getPosition().y) + ")";
	}

	ImGui::Text(editor_title.c_str());
	ImGui::NewLine();

	ImGui::Columns(2, "columns", false);
	
	spr.setScale(4, 4);
	ImGui::Image(spr, sf::Color::White, sf::Color::Red);
	ImGui::NextColumn();
	ImGui::PushItemWidth(100);
	ImGui::InputInt("X", &Editor::rect->left, 1, 1, 0);

	ImGui::SameLine();
	ImGui::PushItemWidth(100);
	ImGui::InputInt("W", &Editor::rect->width, 1, 1, 0);

	ImGui::PushItemWidth(100);
	ImGui::InputInt("Y", &Editor::rect->top, 1, 1, 0);
	ImGui::SameLine();
	ImGui::PushItemWidth(100);
	ImGui::InputInt("H", &Editor::rect->height, 1, 1, 0);

	ImGui::InputInt("duration (ms)", Editor::time, 1, 1, 0);
	ImGui::NextColumn();


	
}

void EditorSection_Selector()
{
	sf::Sprite& spr = Editor::spr_selected;

	ImGui::Text("selector.");

	{
		static int frame_sel = 0;
		int frames = Editor::data->frames;
		if (frames > 1)
		{
			for (int i = 0; i < frames; ++i)
			{
				if (ImGui::RadioButton(std::to_string(i + 1).c_str(), &frame_sel, i))
				{
					Editor::frame_current = frame_sel;
					Editor::RefreshFrameSelected();
				}
				ImGui::SameLine();
			}
		}

		if (ImGui::Button("ADD FRAME"))
		{
			Editor::AddNewFrame();
		}
	}

	//Show all frames
	for (int i = 0; i < Editor::data->frames; ++i)
	{
		if (i > 0) ImGui::SameLine();
		spr.setTextureRect(Editor::data->rect[i]);
		spr.setScale(2, 2);
		ImGui::Image(spr);
		
	}
}

void EditorSection_AnimationSelector()
{

	ImGui::Columns(1, "columns", false);
	static int anim_sel = 0;
	
	if (ImGui::InputText("name", &Editor::buff_animation_name[0], 128))
	{
		Editor::all_animation_names[Editor::anim_selected] = std::string(Editor::buff_animation_name);
	}

	int anims = Editor::anims_total;
	if (anims > 1)
	{
		for (int i = 0; i < anims; ++i)
		{
			if (ImGui::RadioButton(("a"+std::to_string(i + 1)).c_str(), &anim_sel, i))
			{
				Editor::anim = &Editor::all_animations[i];
				Editor::data = &Editor::all_animation_datas[i];
				Editor::frame_current = 0;
				Editor::RefreshFrameSelected();
				Editor::anim_selected = i;

				Editor::RefreshAnimationNameInputText();
			}
			ImGui::SameLine();
		}
	}

	if (ImGui::Button("ADD ANIM"))
	{
		Editor::AddNewAnim();
	}

	ImGui::Columns(2, "columns", false);
}

void EditorStuff()
{
	static bool show_demo = false;
	if (input.IsJustPressed(GameKeys::F1))
	{
		show_demo = !show_demo;
	}

	if (show_demo)
	{
		ImGui::ShowDemoWindow();
	}

	ImGui::Begin("animus", NULL, /*ImGuiWindowFlags_::ImGuiWindowFlags_NoMove  |*/ ImGuiWindowFlags_::ImGuiWindowFlags_NoDecoration);
	
	EditorSection_Editor();
	ImGui::Separator();
	EditorSection_Selector();
	ImGui::Separator();
	ImGui::Text("preview.");
	ImGui::NewLine();

	//Show preview image
	sf::Sprite spr_preview;
	spr_preview.setTexture(Editor::texture);
	spr_preview.setTextureRect(Editor::anim->CurrentFrame());
	spr_preview.setScale(8, 8);
	ImGui::Image(spr_preview, sf::Vector2f(64, 64));

	ImGui::Separator();
	ImGui::Text("animations.");
	ImGui::NewLine();

	EditorSection_AnimationSelector();

	//static char buff[128];
	//ImGui::InputText("le text", &buff[0], 128);

	ImGui::Separator();
	ImGui::Text("cosas.");
	ImGui::NewLine();

	if (ImGui::Button("LOAD"))
	{
		std::ifstream file;
		file.open("project.anm", ios::in);

		file >> Editor::anims_total;

		for (int i = 0; i < Editor::anims_total; ++i)
		{
			std::string anim_name;
			file >> anim_name;

			Editor::all_animation_names[i] = anim_name;

			int frames;
			file >> frames;
			Editor::all_animation_datas[i].frames = frames;

			AnimationData* data = &Editor::all_animation_datas[i];

			for (int j = 0; j < frames; ++j)
			{
				file >> data->rect[j].left;
				file >> data->rect[j].top;
				file >> data->rect[j].width;
				file >> data->rect[j].height;
				file >> data->timer[j];
			}

			Editor::all_animations[i].data = data;
		}

		file.close();

		Editor::RefreshFrameSelected();
		Editor::RefreshAnimationNameInputText();
	}

	ImGui::SameLine();

	if (ImGui::Button("SAVE"))
	{
		std::ofstream file;
		file.open("project.anm", ios::out | ios::trunc);

		file << Editor::anims_total << " ";

		for (int i = 0; i < Editor::anims_total; ++i)
		{
			file << Editor::all_animation_names[i] << " ";

			int frames = Editor::all_animation_datas[i].frames;
			file << frames << " ";
			
			AnimationData* data = &Editor::all_animation_datas[i];

			for (int j = 0; j < frames; ++j)
			{
				file << data->rect[j].left << " ";
				file << data->rect[j].top << " ";
				file << data->rect[j].width << " ";
				file << data->rect[j].height << " ";	
				file << data->timer[j] << " ";
			}
		}

		file.close();
	}

	if (ImGui::Button("EXPORT"))
	{
		std::ofstream file;
		file.open("anim_data.h", ios::out | ios::trunc);

		file << "#pragma once\n";

		file << "\n";

		file << "enum AnimationType\n";
		file << "{\n";

		for (int i = 0; i < Editor::anims_total; ++i)
		{
			file << "\t" << Editor::all_animation_names[i] << ",\n";
		}

		file << "};\n";


		file << "\n";

		file << "AnimationData anim_lib[] = \n";
		file << "{\n";

		for (int i = 0; i < Editor::anims_total; ++i)
		{
			file << "\t//LA ANIM NUMERO " << i << "\n";

			AnimationData* data = &Editor::all_animation_datas[i];

			file << "\t{\n";
			{
				file << "\t\t" << data->frames << ",\n";

				{
					file << "\t\t{\n";
					for (int j = 0; j < data->frames; ++j)
					{
						file << "\t\t\t{" << data->rect->left << ",";
						file << data->rect->top << ",";
						file << data->rect->width << ",";
						file << data->rect->height << "},\n";
					}
					file << "\t\t},\n";
				}
				{
					file << "\t\t{\n";
					file << "\t\t\t";
					for (int j = 0; j < data->frames; ++j)
					{
						file << data->timer[j] << ",";
					}
					file << "\n\t\t},\n";
				}
				
			}
			file << "\t},\n";
		}
		file << "};\n";

		file.close();
	}


	ImGui::End();
}

void UpdateInput(sf::RenderWindow& window, int dt)
{
	static bool moving_rect = false;
	static sf::Vector2i moving_rect_st;
	static sf::Vector2i moving_rect_mp;
	sf::Vector2i mp = sf::Mouse::getPosition(window);

	if (input.IsJustMousePressed(0))
	{
		if (Editor::rect->contains(mp/2))//The 2 is bg_texture_scale 
		{
			moving_rect = true;
			moving_rect_st.x = Editor::rect->left;
			moving_rect_st.y = Editor::rect->top;
			moving_rect_mp = mp;
		}
	}

	if (moving_rect)
	{
		Editor::rect->left = (moving_rect_st.x + (-moving_rect_mp.x + mp.x)/2); 
		Editor::rect->top = (moving_rect_st.y + (-moving_rect_mp.y + mp.y)/2);
	}

	if (input.IsJustMouseReleased(0))
	{
		moving_rect = false;
	}

	if (input.IsJustMousePressed(1))
	{
		Editor::rect->left = sf::Mouse::getPosition(window).x / 2;
		Editor::rect->top = sf::Mouse::getPosition(window).y / 2;
	}

	if (input.IsMousePressed(1))
	{
		Editor::rect->width = (sf::Mouse::getPosition(window).x / 2 - Editor::rect->left);
		Editor::rect->height = (sf::Mouse::getPosition(window).y / 2 - Editor::rect->top);
	}

	if (input.IsPressed(GameKeys::SHIFT))
	{
		if (input.IsJustPressed(GameKeys::RIGHT))
		{
			Editor::rect->width++;
		}
		if (input.IsJustPressed(GameKeys::LEFT))
		{
			Editor::rect->width--;
		}
		if (input.IsJustPressed(GameKeys::UP))
		{
			Editor::rect->height--;
		}
		if (input.IsJustPressed(GameKeys::DOWN))
		{
			Editor::rect->height++;
		}
	}
	else
	{
		static int timer_r = 0;
		static int timer_l = 0;
		static int timer_d = 0;
		static int timer_u = 0;

		const int LAUNCH_TIME = 200;
		if (input.IsJustPressed(GameKeys::RIGHT))
		{
			Editor::rect->left++;
			timer_r = -LAUNCH_TIME;
		}
		if (input.IsJustPressed(GameKeys::LEFT))
		{
			Editor::rect->left--;
			timer_l = -LAUNCH_TIME;
		}
		if (input.IsJustPressed(GameKeys::UP))
		{
			Editor::rect->top--;
			timer_u = -LAUNCH_TIME;
		}
		if (input.IsJustPressed(GameKeys::DOWN))
		{
			Editor::rect->top++;
			timer_d = -LAUNCH_TIME;
		}

		const int SNAP_TIME = 50;

		if (input.IsPressed(GameKeys::RIGHT))
		{
			timer_r += dt;
			if (timer_r > SNAP_TIME)
			{
				timer_r -= SNAP_TIME;
				Editor::rect->left++;
			}
		}
		if (input.IsPressed(GameKeys::LEFT))
		{
			timer_l += dt;
			if (timer_l > SNAP_TIME)
			{
				timer_l -= SNAP_TIME;
				Editor::rect->left--;
			}
		}
		if (input.IsPressed(GameKeys::UP))
		{
			timer_u += dt;
			if (timer_u > SNAP_TIME)
			{
				timer_u -= SNAP_TIME;
				Editor::rect->top--;
			}
		}
		if (input.IsPressed(GameKeys::DOWN))
		{
			timer_d += dt;
			if (timer_d > SNAP_TIME)
			{
				timer_d -= SNAP_TIME;
				Editor::rect->top++;
			}
		}
	}
}

int main()
{
	sf::RenderWindow window(sf::VideoMode(SCR_WIDTH, SCR_HEIGHT), "animus");
	LoadGame(window);

	sf::Clock clk_frame;
	sf::Clock clk_general;

	sf::Clock clk_fps;
	int fps_counter = 0;

	rtex_preview.create(200, 200);

	Editor::InitNewAnim();

	

	while (window.isOpen())
	{
		Editor::texture.loadFromFile("data/spritesheet.png");

		int time_general = clk_general.getElapsedTime().asMilliseconds();
		sf::Time t_frame = clk_frame.getElapsedTime();
		int dt = t_frame.asMilliseconds();
		clk_frame.restart();

		sf::Event event;
		while (window.pollEvent(event))
		{
			ImGui::SFML::ProcessEvent(event);

			if (event.type == sf::Event::Closed) 
			{
				window.close();
			}
		}

		input.UpdateInput();

		UpdateInput(window, dt);

		ImGui::SFML::Update(window, t_frame);

		Editor::UpdatePreview(t_frame);

		window.clear();

		static sf::Sprite main_texture; 
		main_texture.setTexture(Editor::texture);
		main_texture.setScale(2, 2);
		window.draw(main_texture);

		sf::RectangleShape shape_frame_selected;
		shape_frame_selected.setFillColor(sf::Color::Transparent);
		shape_frame_selected.setOutlineColor(sf::Color::Red);
		shape_frame_selected.setOutlineThickness(1);
		
		shape_frame_selected.setPosition(2*Editor::rect->left, 2*Editor::rect->top);
		shape_frame_selected.setSize(sf::Vector2f(2*Editor::rect->width, 2*Editor::rect->height));
		window.draw(shape_frame_selected);

		Editor::RefreshFrameSelected();
		rtex_preview.clear();
		rtex_preview.draw(Editor::spr_selected);
		rtex_preview.display();

		EditorStuff();

		//Editor::anim->name = std::string(Editor::buff_animation_name);


		/*
		sf::Text txt_fps;
		txt_fps.setString(std::to_string(static_cast<int>(fps_counter*1000 / std::max(1, clk_fps.getElapsedTime().asMilliseconds()))));
		txt_fps.setPosition(10, 10);
		txt_fps.setFont(font);
		window.draw(txt_fps);
		fps_counter++;
		*/

		ImGui::SFML::Render(window);
		window.display();
	}

	ImGui::SFML::Shutdown();
}
