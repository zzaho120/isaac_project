#include "framework.h"
#include "CBullet.h"

CBullet::CBullet() :
    CObject(), firePt({ 0, 0 }), angle(0), speed(0),
    fallingHeight(0)
{ }

CBullet::CBullet(Vec2 _pos, RECT _rc, float _angle, float _speed, int _height) :
    CObject(_pos, _rc), firePt(_pos), angle(_angle), speed(_speed),
    fallingHeight(_height)
{ }

CBullet::~CBullet()
{ }

HRESULT CBullet::init(float _angle, float _speed, vector2 _pt, float _height)
{
    CObject::init(_pt,
        RectMakeCenter(_pt.x, _pt.y, BULLETSIZE, BULLETSIZE),
       _height);
    firePt = _pt;
    angle = _angle;
    speed = _speed;

    shadowdistance = 30;
    shadowPt.x = _pt.x;
    shadowPt.y = _pt.y + shadowdistance;
    shadow = RectMakeCenter(shadowPt.x, shadowPt.y, BULLETSIZE, BULLETSIZE);
    
    return S_OK;
}

void CBullet::release()
{
}

void CBullet::update()
{
    move();
}

void CBullet::render()
{
    Rectangle(getMemDC(), shadow.left, shadow.top, shadow.right, shadow.bottom);
    Rectangle(getMemDC(), getRC().left, getRC().top, getRC().right, getRC().bottom);
}

void CBullet::move()
{
    fallingHeight += 0.1; // 시간이 지나면 중력에 의해 눈물이 떨어지는 연출

    pt.x += cosf(angle) * speed;
    pt.y -= sinf(angle) * speed - fallingHeight;
    shadowPt.x += cosf(angle) * speed;
    shadowPt.y -= sinf(angle) * speed;
    rc = RectMakeCenter(pt, BULLETSIZE, BULLETSIZE);
    shadow = RectMakeCenter(shadowPt, BULLETSIZE, BULLETSIZE);
}