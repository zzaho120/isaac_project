#pragma once
#include "CMonster.h"
class CMulligan : public CMonster
{
private:
	bool isleft;
	animation* anihead;

	CCollider* thisCollider;
	CCollider* thisShadowCollider;
public:
	CMulligan();
	~CMulligan();

	HRESULT init(float x, float y);
	void release();
	void update();
	void render();
};

