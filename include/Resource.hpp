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



