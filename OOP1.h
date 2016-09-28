#pragma once
#include <vector>
#include <array>
#include <chrono>
#include <iostream>
#include <random>
#include "glm/vec3.hpp"
#include "glm/vec4.hpp"
#include "glm/gtx/normalize_dot.hpp"

using glm::vec3;
using glm::vec4;

struct OOP1Ball
{
	vec3 pos;
	vec4 color;
	float dmg;
	vec3 aimdirection;
	vec3 direction;
	float radius;
	float speed;
	float hp;
	vec3 cursorPos;
	size_t targetIndex;
	
	void Move()
	{
		aimdirection = glm::normalize(pos - cursorPos);
		pos += direction * speed;
	}

	void Attack(std::vector<OOP1Ball*>& balls)
	{
		balls.at(targetIndex)->hp -= dmg;
	}

	void Render(std::vector<std::array<float, 8>>& rendertarget)
	{
		rendertarget.push_back( {
				pos.x, pos.y, pos.z,
				color.x, color.y, color.z, color.w,
				radius } );
	}
};

void OOP1Test(int nr_of_balls, std::vector<std::array<float, 8>>& rendertarget)
{
	std::vector<OOP1Ball*> oopballs;
	std::vector<OOP1Ball*> oopballsNotUsed;
	std::mt19937 rnd;
	std::uniform_real_distribution<float> rf(0.0f, 1.0f);
	for (int i = 0; i < nr_of_balls; ++i)
	{
		{
			OOP1Ball* ball = new OOP1Ball();
			ball->pos = glm::normalize(vec3(rf(rnd), rf(rnd), rf(rnd)) * 1000.0f);
			ball->direction = glm::normalize(vec3(rf(rnd), rf(rnd), rf(rnd)));
			ball->color = vec4( rf(rnd), rf(rnd), rf(rnd), rf(rnd) );
			ball->radius = rf(rnd);
			ball->speed = rf(rnd) * 10.0f;
			ball->dmg = rf(rnd);
			ball->hp = rf(rnd) * 10.0f;
			oopballs.push_back(ball);
		}
		{
			OOP1Ball* ball = new OOP1Ball();

			ball->pos = { 0.0f, (float)i, 0.0f };
			ball->movement = { (float)i, 0.0f, 0.0f };
			ball->color = { 1.0f, 0.0f, 1.0f, 1.0f };
			ball->radius = 1.0f;
			oopballsNotUsed.push_back(ball);
		}
		{
			OOP1Ball* ball = new OOP1Ball();
			ball->pos = { 0.0f, (float)i, 0.0f };
			ball->movement = { (float)i, 0.0f, 0.0f };
			ball->color = { 1.0f, 0.0f, 1.0f, 1.0f };
			ball->radius = 1.0f;
			oopballsNotUsed.push_back(ball);
		}
		{
			OOP1Ball* ball = new OOP1Ball();
			ball->pos = { 0.0f, (float)i, 0.0f };
			ball->movement = { (float)i, 0.0f, 0.0f };
			ball->color = { 1.0f, 0.0f, 1.0f, 1.0f };
			ball->radius = 1.0f;
			oopballsNotUsed.push_back(ball);
		}
	}

	std::chrono::high_resolution_clock::time_point start = std::chrono::high_resolution_clock::now();
	for ( auto& ball : oopballs )
	{
		ball->Update();
	}
	for ( auto& ball : oopballs )
	{
		ball->Render(rendertarget);
	}
	std::chrono::high_resolution_clock::time_point end = std::chrono::high_resolution_clock::now();
	std::cout << "OOP1 took " << std::chrono::duration_cast<std::chrono::milliseconds>( end - start ).count() << "ms" << std::endl;
	for ( auto& ball : oopballs )
	{
		delete ball;
	}
	for ( auto& ball : oopballsNotUsed )
	{
		delete ball;
	}
}