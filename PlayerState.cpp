#include "framework.h"
#include "PlayerState.h"

Player_Idle::Player_Idle()
{
	m_eState = STATE_TYPE::IDLE;
}

Player_Idle::~Player_Idle()
{
}

void Player_Idle::Enter()
{
}

void Player_Idle::update()
{
}

void Player_Idle::Exit()
{
}

Player_Trace::Player_Trace()
{
	m_eState = STATE_TYPE::TRACE;
}

Player_Trace::~Player_Trace()
{
}

void Player_Trace::Enter()
{
}

void Player_Trace::update()
{
}

void Player_Trace::Exit()
{
}

Player_Atk::Player_Atk()
{
	m_eState = STATE_TYPE::ATTACK;
}

Player_Atk::~Player_Atk()
{
}

void Player_Atk::Enter()
{
}

void Player_Atk::update()
{
}

void Player_Atk::Exit()
{
}

Player_Die::Player_Die()
{
	m_eState = STATE_TYPE::DEAD;
}

Player_Die::~Player_Die()
{
}

void Player_Die::Enter()
{
}

void Player_Die::update()
{
}

void Player_Die::Exit()
{
}
