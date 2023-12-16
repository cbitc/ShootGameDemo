#pragma once
#include"Common.hpp"
#include<vector>
#include<chrono>
#include"PublicHeader.hpp"

class MouseInput final
{

public:
	void clear() {
		isPress_ = isUp_ = isMove = false;
	}

	bool hasPress() const {
		return isPress_;
	}

	bool hasUp() const {
		return isUp_;
	}

	bool hasMove() const {
		return isMove;
	}

	void press() {
		isPress_ = true;
	}

	void up() {
		isUp_ = true;
	}

	void move() {
		isMove = true;
	}

	const Vec2<uint16_t> getPosition() const {
		return position_;
	}

	void setPosition(Vec2<uint16_t> pos) {
		position_ = pos;
	}

	MouseInput() :isPress_(false),isUp_(false),isMove(false) {}
private:
	Vec2<uint16_t> position_;
	bool isPress_,isUp_,isMove;
};


class CollisionGroup final
{
public:
	using group_t = std::vector<ECS::Entity>;
	CollisionGroup() {
		collisionGroup_.resize(8,group_t{});
	}

	void setGroup(ECS::Entity entity,uint8_t groupIndex) {
		collisionGroup_[groupIndex].push_back(entity);
	}

	void remove(ECS::Entity entity,uint8_t groupIndex) {
		group_t& group = collisionGroup_[groupIndex];
		int index = 0,len = group.size();
		for (;index < len;index++) {
			if (group[index] == entity)break;
		}
		std::swap(group[index],group.back());
		group.pop_back();
	}

	
	const group_t& getGroup(uint8_t groupIndex) {
		return collisionGroup_[groupIndex];
	}

private:
	std::vector<group_t> collisionGroup_;

};

