#include "framework.h"
#include "CBullet.h"

CBullet::CBullet() :
    CObject(), firePt({ 0, 0 }), angle(0), speed(0),
    fallingHeight(0)
{ }

CBullet::CBullet(Vec2 _pos, RECT _rc, float _angle, float _speed, float _distance, int _height, CHARACTER _type, int size) :
    CObject(_pos, _rc), firePt(_pos), angle(_angle), speed(_speed),
    fallingHeight(_height), distance(_distance), type(_type), BULLETSIZE(size)
{ }

CBullet::~CBullet()
{ }

HRESULT CBullet::init(float _angle, float _speed, vector2 _pt, float _height, float _distance, CHARACTER _type, int size)
{
    CObject::init(_pt,
        RectMakeCenter(_pt.x, _pt.y, size, size),
       _height);
    firePt = _pt;
    angle = _angle;
    speed = _speed;
    BULLETSIZE = size;
    type = _type;
    distance = _distance;
    shadowdistance = _height;

    shadowPt.x = _pt.x;
    shadowPt.y = _pt.y + shadowdistance;
    shadow = RectMakeCenter(shadowPt.x, shadowPt.y, BULLETSIZE, BULLETSIZE);
    
    vector2 colliderpt = { _pt.x, _pt.y + shadowdistance };
    vector2 collidersize ;
    collidersize.x = BULLETSIZE;
    collidersize.y = BULLETSIZE;

    collider = new CCollider(colliderpt, collidersize);

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
    /*RECT rec = RectMakeCenter(collider->getPos(), 50, 50);
    Rectangle(getMemDC(), rec.left, rec.top, rec.right, rec.bottom);*/
}

void CBullet::move()
{
    if (UTIL::getDistance(firePt.x, firePt.y, pt.x, pt.y) > distance)
    {
        fallingHeight += 0.1; // 시간이 지나면 중력에 의해 눈물이 떨어지는 연출
    }
    pt.x += cosf(angle) * speed;
    pt.y -= sinf(angle) * speed - fallingHeight;
    shadowPt.x += cosf(angle) * speed;
    shadowPt.y -= sinf(angle) * speed;
    rc = RectMakeCenter(pt, BULLETSIZE, BULLETSIZE);
    shadow = RectMakeCenter(shadowPt, BULLETSIZE, BULLETSIZE);
    collider->setPos({ RectX(rc), RectY(rc) + shadowdistance });
}