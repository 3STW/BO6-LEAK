#include <cstdint>
#include "Client.h"
#pragma onc
class player_velocity_manager
{
public:
	struct velocity_data
	{
		math::vec3_t last_pos;
		math::vec3_t delta;
		math::vec3_t velocity;
		uint32_t time;
		uint32_t duration;
		float frame_time;
		float last_velocity;
	};
	bool b_update_tick = false;
	std::map<uint32_t, velocity_data> velocity_map;
	uint32_t server_time = 0;

	inline void update(entity_t* ent)
	{
		auto index = ent->nextstate().number;
		auto v_pos = ent->get_pos();
		auto at_time = server_time;

		math::vec3_t delta;
		if (!velocity_map[index].last_pos.is_Zero())
			delta = v_pos - velocity_map[index].last_pos;
		else
			velocity_map[index].last_pos = v_pos;

		auto length = fabsf(delta.length());

		// Check if player teleported.
		if (length < 0.5f || v_pos.is_Zero() || at_time - velocity_map[index].time < 16)
		{
			velocity_map[index].velocity = math::vec3_t();
			return;
		}

		velocity_map[index].last_pos = v_pos;

		velocity_map[index].duration = at_time - velocity_map[index].time;
		if (velocity_map[index].time < 1)
			velocity_map[index].duration = 0;

		velocity_map[index].time = at_time;

		if (velocity_map[index].duration > 200)
			velocity_map[index].frame_time = 200 * 0.001f;
		else if (velocity_map[index].duration < 1)
			velocity_map[index].frame_time = 1 * 0.001f;
		else
			velocity_map[index].frame_time = velocity_map[index].duration * 0.001f;

		velocity_map[index].delta = delta;

		if (velocity_map[index].velocity.dot(delta) >= 0.f)
			velocity_map[index].velocity = delta * (1.f / velocity_map[index].frame_time);
		else
			velocity_map[index].velocity = math::vec3_t();
	}

	inline void remove(entity_t* ent)
	{
		auto index = ent->nextstate().number;
		velocity_map.erase(index);
	}

	inline math::vec3_t get_speed(uint32_t index)
	{
		return velocity_map[index].velocity;
	}

	inline void tick()
	{
		server_time = *(uint32_t*)(Settings::client.cg + Settings::mem.CgGlobalsMP.Time);//timeGetTime();
	}

	inline void reset()
	{
		velocity_map.clear();
		b_update_tick = false;
	}

	~player_velocity_manager() { };
};