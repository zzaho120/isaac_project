#include "framework.h"
#include "CBossUI.h"
#include "CGurdy.h"
CBossUI::CBossUI()
{
}

CBossUI::~CBossUI()
{
}

HRESULT CBossUI::init()
{
	return E_NOTIMPL;
}

void CBossUI::release()
{
}

void CBossUI::update()
{
}

void CBossUI::render()
{
	
	int bossHp = boss->getMaxHp() - boss->gethp();
	if (bossHp > boss->getMaxHp()) { bossHp = boss->getMaxHp(); }
	if (bossHp < boss->getMaxHp())
	{
		minusHp = (IMAGE->findImage("bossFront")->getWidth() / boss->getMaxHp()) * bossHp;
		IMAGE->render("bossBack", getMemDC(), WINSIZEX / 2 - IMAGE->findImage("bossBack")->getWidth() / 2, 100);
		IMAGE->render("bossFront", getMemDC(), WINSIZEX / 2 - IMAGE->findImage("bossFront")->getWidth() / 2 + 14, 100 + 14,
			0, 0, IMAGE->findImage("bossFront")->getWidth() - minusHp, IMAGE->findImage("bossFront")->getHeight());
	}
}
