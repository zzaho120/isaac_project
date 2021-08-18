#include "framework.h"
#include "CMainMenu.h"

CMainMenu::CMainMenu() :
    isBreakoutTitle(false),
    isPassNextScene(false),
    selectMenu(0)
{
}

CMainMenu::~CMainMenu()
{
}

HRESULT CMainMenu::init()
{
    isBreakoutTitle = false;
    isPassNextScene = false;
    selectMenu = 0;
    ANIMATION->findAnimation("title_isaacAni")->start();
    SOUND->play("titlebgm");
    return S_OK;
}

void CMainMenu::release()
{
    SOUND->stop("titlebgm");
}

void CMainMenu::update()
{
    if (!isBreakoutTitle && InputManager->isOnceKeyDown(VK_SPACE)) isBreakoutTitle = true;
    if (isBreakoutTitle)
    {
        if (InputManager->isOnceKeyDown(VK_UP))
        {

            selectMenu--;
            if (selectMenu < 0)
                selectMenu = 0;
        }
        else if (InputManager->isOnceKeyDown(VK_DOWN))
        {
            selectMenu++;
            if (selectMenu > 2)
                selectMenu = 2;
        }
        else if (InputManager->isOnceKeyDown(VK_SPACE))
        {
            SOUND->play("selectmenu");
            isPassNextScene = true;
        }

        if (isPassNextScene)
        {
            if(alphaValue < 254)
                alphaValue += 2;
            else
            {
                switch (selectMenu)
                {
                case 0:
                    SCENE->changeScene("game");
                    break;
                case 1:
                    SCENE->changeScene("mapTool");
                    break;
                case 2:
                    PostQuitMessage(0);
                    break;
                }
            }
        }
    }
}

void CMainMenu::render()
{
    if (!isBreakoutTitle)
    {
        IMAGE->render("title_screen", getMemDC());
        IMAGE->render("title", getMemDC(), 250, 80);
        IMAGE->findImage("title_isaac")->aniRender(getMemDC(), 370, 300, ANIMATION->findAnimation("title_isaacAni"));
    }
    else
    {
        IMAGE->alphaRender("mainMenu", getMemDC(), 255 - alphaValue);
        if(!isPassNextScene)
            IMAGE->render("menu_arrow", getMemDC(), 380, 180 + selectMenu * 150);
    }
}
