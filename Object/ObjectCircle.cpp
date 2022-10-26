#include "ObjectCircle.h"
#include "game.h"
#include "DxLib.h"
#include "SceneTest.h"
#include "Mouse.h"

namespace
{
	// サイズ
	constexpr int kRadius = 64;
}

ObjectCircle::ObjectCircle() :
	m_pSceneTest(nullptr),
	m_color(GetColor(255, 255, 255)),
	m_isCatch(false),
	m_catchOffset()
{
}
ObjectCircle::~ObjectCircle()
{

}

void ObjectCircle::init()
{
	m_color = GetColor(255, 255, 255);
	m_isExist = true;
	m_isCatch = false;
}

void ObjectCircle::end()
{

}

void ObjectCircle::update()
{
	// 移動	マウスでつかんで移動させる
	Vec2 mousePos = Mouse::getPos();
	if (Mouse::isTriggerLeft() && isCatchEnable(mousePos))
	{
		m_isCatch = true;
		m_catchOffset = m_pos - mousePos;
	}
	if (!Mouse::isPressLeft())
	{
		m_isCatch = false;
	}
	if (m_isCatch)
	{
		m_pos = mousePos + m_catchOffset;
	}
}

void ObjectCircle::draw()
{
	DrawCircle(static_cast<int>(m_pos.x), static_cast<int>(m_pos.y), kRadius, m_color);

	if (m_isCatch)
	{
		DrawCircle(static_cast<int>(m_pos.x), static_cast<int>(m_pos.y), kRadius, GetColor(255, 0, 0), true);
	}

	// 当たり判定表示
//	DrawBoxAA(m_pos.x, m_pos.y, m_pos.x + m_colSize.x, m_pos.y + m_colSize.y, kColor, false);
}

bool ObjectCircle::isCatchEnable(Vec2 pos)
{
	//m_pos		円の中心
	//pos		マウスカーソルの位置

	//中心からマウスカーソル位置までの距離を調べる
	Vec2 toMouse = pos - m_pos;
	if (toMouse.length() < kRadius)
	{
		return true;
	}
	return false;
}