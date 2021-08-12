#include "framework.h"
#include"AniAddList.h"

AniAddList::AniAddList()
{
	//=================== map ====================================================================================
	//=================== map ====================================================================================
	IMAGE->addImage("basement_normal", "images/map/basement_normal.bmp", MAPSIZEX, MAPSIZEY, true, RGB(255, 0, 255));
	IMAGE->addImage("basement_boss", "images/map/basement_boss.bmp", MAPSIZEX, MAPSIZEY, true, RGB(255, 0, 255));
	IMAGE->addImage("shop", "images/map/shop.bmp", MAPSIZEX, MAPSIZEY, true, RGB(255, 0, 255));

	IMAGE->addFrameImage("objectTile", "images/map/objectTile.bmp", TILEWIDTH * 6, TILEHEIGHT * 3, 6, 3, true, RGB(255, 0, 255));
	IMAGE->addFrameImage("monsterTile", "images/map/monsterTile.bmp", TILEWIDTH * 7, TILEHEIGHT, 7, 1, true, RGB(255, 0, 255));
	IMAGE->addFrameImage("roomTile", "images/map/roomTile.bmp", TILEWIDTH * 3, TILEHEIGHT, 3, 1, true, RGB(255, 0, 255));

	//=================== player ====================================================================================
	//=================== player ====================================================================================
	IMAGE->addFrameImage("isaac", "images/player/player_head.bmp", 256 * 2, 32 * 2, 8, 1, true, RGB(255, 0, 255));
	IMAGE->addFrameImage("mulliganbody", "images/enemy/mulliganbody.bmp", 300 * 1.5, 90 * 1.5, 10, 3, true, RGB(255, 0, 255));
	
	ANIMATION->addAnimation("down_head", "isaac", 0, 1, 10, false, false);
	ANIMATION->addAnimation("right_head", "isaac", 2, 3, 10, false, false);
	ANIMATION->addAnimation("up_head", "isaac", 4, 5, 10, false, false);
	ANIMATION->addAnimation("left_head", "isaac", 6, 7, 10, false, false);
	int playeridle[] = { 0 };
	ANIMATION->addAnimation("playeridlehead", "isaac", playeridle, 1, 10, false);
	ANIMATION->addAnimation("playerrightbody", "mulliganbody", 10, 19, 10, false, true);
	ANIMATION->addAnimation("playerleftbody", "mulliganbody", 20, 29, 10, false, true);
	ANIMATION->addAnimation("playerupbody", "mulliganbody", 0, 9, 10, false, true);
	ANIMATION->addAnimation("playerdownbody", "mulliganbody", 0, 9, 10, false, true);
	int mulliganidle[] = { 0 };
	ANIMATION->addAnimation("playeridlebody", "mulliganbody", mulliganidle, 1, 10, false);

	IMAGE->addImage("shadow", "images/shadow.bmp", 10, 10, true, RGB(255, 0, 255));
	//==================================mulligan=================================================================
	//==================================mulligan=================================================================
	IMAGE->addFrameImage("mulliganhead", "images/enemy/mulliganhead.bmp", 240*1.5, 70*1.5, 6, 2, true, RGB(255, 0, 255));

	ANIMATION->addAnimation("righthead", "mulliganhead", 0, 5, 10, false, true);
	ANIMATION->addAnimation("rightbody", "mulliganbody", 10, 19, 10, false, true);

	ANIMATION->addAnimation("lefthead", "mulliganhead", 6, 11, 10, false, true);
	ANIMATION->addAnimation("leftbody", "mulliganbody", 20, 29, 10, false, true);

	ANIMATION->addAnimation("upbody", "mulliganbody", 0, 9, 10, false, true);
	ANIMATION->addAnimation("downbody", "mulliganbody", 0, 9, 10, false, true);


	ANIMATION->addAnimation("mulliganidle", "mulliganbody", mulliganidle, 1, 10, false);

	//================================================warm========================================
	//================================================warm========================================
	IMAGE->addFrameImage("worm", "images/enemy/worm.bmp", 260/1.3, 320/1.3, 4, 5, true, RGB(255, 0, 255));
	ANIMATION->addAnimation("rightworm", "worm", 0, 3, 10, false, true);
	ANIMATION->addAnimation("upworm", "worm", 4, 7, 10, false, true);
	ANIMATION->addAnimation("downworm", "worm", 8, 11, 10, false, true);
	ANIMATION->addAnimation("leftworm", "worm", 16, 19, 10, false, true);

	int down[] = { 12 };
	ANIMATION->addAnimation("downwormAtk", "worm", down, 1, 10, true);
	int right[] = { 13 };
	ANIMATION->addAnimation("rightwormAtk", "worm", right, 1, 10, true);
	int left[] = { 14 };
	ANIMATION->addAnimation("leftwormAtk", "worm", left, 1, 10, true);
	int up[] = { 15 };
	ANIMATION->addAnimation("upwormAtk", "worm", up, 1, 10, true);

	//==========================================================host============================================
	//==========================================================host============================================
	IMAGE->addFrameImage("host", "images/enemy/host.bmp", 105*2, 44*2, 3, 1, true, RGB(255, 0, 255));
	int idle[] = { 0 };
	ANIMATION->addAnimation("hostidle", "host", idle, 1, 10, false);
	int trace[] = { 1 };
	ANIMATION->addAnimation("hosttrace", "host", trace, 1, 10, false);
	int atk[] = { 2 };
	ANIMATION->addAnimation("hostatk", "host", atk, 1, 10, false);

	//==============================================hopper===========================================
	//==============================================hopper===========================================
	IMAGE->addFrameImage("hopper", "images/enemy/hopper.bmp", 180, 30 , 6, 1, true, RGB(255, 0, 255));
	int hopperidle[] = { 0 };
	ANIMATION->addAnimation("idlehopper", "hopper", hopperidle, 1, 10, true);
	ANIMATION->addAnimation("jumphopper", "hopper", 0, 3, 10, false, false);
	ANIMATION->addAnimation("downhopper", "hopper", 4, 5, 10, false, false);

	//==============================================fly===========================================
	//==============================================fly===========================================
	IMAGE->addFrameImage("fly", "images/enemy/fly.bmp", 120*1.3, 240 * 1.3, 4, 8, true, RGB(255, 0, 255));

	ANIMATION->addAnimation("rightfly", "fly", 0, 1, 10, false, true);
	ANIMATION->addAnimation("rightAtkfly", "fly", 2, 15, 10, false, false);
	int arrleft[] = { 18, 19 };
	ANIMATION->addAnimation("leftfly", "fly", arrleft, 2, 10, true);
	int arrleftAtk[] = { 17, 16, 23,22,21,20,27,26,25,24,31,30,29,28 };
	ANIMATION->addAnimation("leftAtkfly", "fly", arrleftAtk, 14, 10, false);

	//=========================gurdy==========================================================================
	//=========================gurdy==========================================================================
	IMAGE->addFrameImage("gurdybody", "images/boss/gurdy_body.bmp", 450*2, 150*2, 3, 1, true, RGB(255, 0, 255));
	ANIMATION->addAnimation("gurdybodybeat", "gurdybody", 0, 2, 4, false, true);
	int gurdyIdlebody[] = { 0 };
	ANIMATION->addAnimation("gurdybodyidle", "gurdybody", gurdyIdlebody, 1, 10, false);
	IMAGE->addFrameImage("gurdyface", "images/boss/gurdy_face.bmp", 360*2, 160*2, 6, 4, true, RGB(255, 0, 255));
	int gurdyIdleface[] = { 2 };
	ANIMATION->addAnimation("gurdyfaceidle", "gurdyface", 0, 2, 10, false, false);

	int gurdyatkready[] = { 5, 4, 3 };
	ANIMATION->addAnimation("gurdyatkready", "gurdyface", gurdyatkready, 3, 10, false);

	ANIMATION->addAnimation("gurdydownatkready", "gurdyface", 3, 5, 10, false, false);
	ANIMATION->addAnimation("gurdydownatk", "gurdyface", 16, 17,10, false, true);
	ANIMATION->addAnimation("gurdydownatkclose", "gurdyface", gurdyatkready, 3, 10, false);

	ANIMATION->addAnimation("gurdyleftatkready", "gurdyface", 5, 7,10, false, false);
	ANIMATION->addAnimation("gurdyleftatk", "gurdyface", 12, 13,10, false, true);
	int gurdyleftclose[] = { 7,6,5 };
	ANIMATION->addAnimation("gurdyleftatkclose", "gurdyface", gurdyleftclose, 3, 10, false);

	int gurdyrightready[] = { 11, 10 , 9 };
	ANIMATION->addAnimation("gurdyrightatkready", "gurdyface", gurdyrightready, 3, 10, false);
	ANIMATION->addAnimation("gurdyrightatk", "gurdyface", 14, 15,10, false, true);
	ANIMATION->addAnimation("gurdyrightatkclose", "gurdyface", 9, 11,10, false, false);

	ANIMATION->addAnimation("gurdysummonflyready", "gurdyface", 18, 20,10, false, false);
	ANIMATION->addAnimation("gurdysummonfly", "gurdyface", 20, 21,30, false, true);
	int gurdysummonfly[] = { 22 };
	ANIMATION->addAnimation("gurdysummonflyclose", "gurdyface", gurdysummonfly, 1, 10, false);
	int gurdysummonpooter[] = { 23 };
	ANIMATION->addAnimation("gurdysummonpooter", "gurdyface", gurdysummonpooter, 1, 10, false);

	//=========================smallfly==========================================================================
	//=========================smallfly==========================================================================
	IMAGE->addFrameImage("smallfly", "images/enemy/smallfly.bmp", 38 * 1.5, 14 * 1.5, 2, 1, true, RGB(255, 0, 255));
	ANIMATION->addAnimation("smallflyani", "smallfly", 0, 1, 10, false, true);
}

AniAddList::~AniAddList()
{
}
