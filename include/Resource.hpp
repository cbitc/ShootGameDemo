#pragma once
#include"Common.hpp"

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



class GraphContainer final
{
public:

	void add(const GraphInfo::Type type,const Graph& graph) {
		int index = int(type);
		if (index >= graphs_.size()) {
			graphs_.resize(index + 1,nullptr);
		}
		graphs_[index] = new Graph(graph);
	}

	Graph* get(const GraphInfo::Type type) {
		assertm("Graph is null",graphs_[int(type)]);
		return graphs_[int(type)];
	}

	~GraphContainer() {
		for (Graph* graph : graphs_) {
			delete graph;
		}
	}

	static Graph createTriangleVertexs(float sideLen) {
		std::vector<std::vector<int>> neibs(3,std::vector<int>(3,0));
		neibs[0][1] = neibs[0][2] = 1;
		neibs[1][0] = neibs[1][2] = 1;
		neibs[2][0] = neibs[2][1] = 1;

		std::vector<Vec2<float>> vertexs{};
		const float dx = sideLen / 2,dy = sideLen * 1.7 / 2;

		vertexs.emplace_back(0,0);
		vertexs.emplace_back(-dx,dy);
		vertexs.emplace_back(dx,dy);

		return Graph{ neibs,vertexs };
	}


	static Graph createArrowVertexs(float waistLen) {
		std::vector<std::vector<int>> neibs(4,std::vector<int>(4,0));
		neibs[0][1] = neibs[0][3] = 1;
		neibs[1][0] = neibs[1][2] = 1;
		neibs[2][1] = neibs[2][3] = 1;
		neibs[3][0] = neibs[3][2] = 1;

		std::vector<Vec2<float>> vertexs{};
		const float dx = waistLen * 0.26,dy = waistLen * 0.65;

		vertexs.emplace_back(0,0);
		vertexs.emplace_back(-dx,dy);
		vertexs.emplace_back(0,dy - 0.15 * waistLen);
		vertexs.emplace_back(dx,dy);

		return Graph{ neibs,vertexs };
	}


	static Graph createBulletVertexs(float len) {
		std::vector<std::vector<int>> neibs(3,std::vector<int>(3,0));
		neibs[0][1] = neibs[0][2] = 1;
		neibs[1][0] = 1;
		neibs[2][0] = 1;

		std::vector<Vec2<float>> vertexs{};
		const float dx = len / 3,dy = len * 1.7 / 2;

		vertexs.emplace_back(0,0);
		vertexs.emplace_back(-dx,dy);
		vertexs.emplace_back(dx,dy);

		return Graph{ neibs,vertexs };
	}
private:
	std::vector<Graph*> graphs_;
};