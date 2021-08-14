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

HRESULT CBullet::init(float _angle, float _speed, vector2 _pt, float _height, float _distance, CHARACTER _type, float size, string _bulletType)
{
    CObject::init(_pt,
        RectMakeCenter(_pt.x, _pt.y, size, size),
        _pt, { size,size },
       _height
        , shadowPt, { size,size/3});
    firePt = _pt;
    angle = _angle;
    speed = _speed;
    BULLETSIZE = size;
    type = _type;
    distance = _distance;
    shadowdistance = _height;
    bulletType = _bulletType;
    bulletShadow = "Shadow";
    shadowPt.x = _pt.x;
    shadowPt.y = _pt.y + shadowdistance;
    shadow = RectMakeCenter(shadowPt.x, shadowPt.y, BULLETSIZE, BULLETSIZE);
    
    bulletAnimation = new animation;
    bulletAnimation->init(BULLETSIZE*13, BULLETSIZE, BULLETSIZE, BULLETSIZE);
    bulletAnimation->setDefPlayFrame(false, false);
    bulletAnimation->setFPS(1);
    bulletAnimation->start();
    bulletImage = IMAGE->findImage(_bulletType);
    
    return S_OK;
}

void CBullet::release()
{
    SAFE_DELETE(bulletAnimation);
}

void CBullet::update()
{
    move();
    bulletAnimation->frameUpdate(30.0f);
}

void CBullet::render()
{
    
    /*Rectangle(getMemDC(), colliderShadow->getPos().x - colliderShadow->getSize().x / 2,
        colliderShadow->getPos().y - colliderShadow->getSize().y / 2,
        colliderShadow->getPos().x + colliderShadow->getSize().x / 2,
        colliderShadow->getPos().y + colliderShadow->getSize().y / 2);*/

    RECT rec = RectMakeCenter(colliderShadow->getPos().x, colliderShadow->getPos().y, colliderShadow->getSize().x, colliderShadow->getSize().y);
    IMAGE->render(bulletType + bulletShadow, getMemDC(), rec.left, rec.top);

    bulletImage->aniRender(getMemDC(), collider->getPos().x - collider->getSize().x / 2,
        collider->getPos().y - collider->getSize().y / 2, bulletAnimation);
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
    colliderShadow->setPos({ RectX(shadow), RectY(shadow) });
    collider->setPos({ RectX(rc), RectY(rc)});
}