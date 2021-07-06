#include "hack.h"

BOOL bFont = FALSE;  //Variável da fonte:

void CriarFonte(LPDIRECT3DDEVICE9 pDevice)
{
	if (pFont)
	{
		pFont->Release();
		pFont = NULL;
		bFont = FALSE;
	}

	if (!bFont)
	{
		D3DXCreateFont(pDevice, 14, 0, 400, 1, 0, 1, 0, 4, 0 | (0 << 4), "System", &pFont);
		bFont = TRUE;
	}
}

VOID RENDMENU(LPDIRECT3DDEVICE9 pDevice)
{

	if (GetAsyncKeyState(VK_INSERT) & 1)
		menu.ShowMenu = !menu.ShowMenu;

	if (menu.ShowMenu && pFont)
	{
		pDevice->SetRenderState(D3DRS_ZENABLE, D3DZB_FALSE);

		GetTimeFormat(0, 0, 0, 0, Timestruct, 15);										//Estrutura do relógio.
		DrawBox(menu.matrixPos[0], menu.matrixPos[1], menu.matrixPos[2], menu.matrixPos[3], FundoMenu, FundoMenu, pDevice);			//Fundo do Menu
		DrawBorder(menu.matrixPos[0], menu.matrixPos[1], menu.matrixPos[2], menu.matrixPos[3], 1, White, pDevice);			//Borda do menu
		WriteText(menu.matrixPos[0] + 130, menu.matrixPos[1] + 20, White, Black, "Light CFBR");
		DrawBox(menu.matrixPos[0] + 1, menu.matrixPos[1] + 50, menu.matrixPos[2] - 2, menu.matrixPos[3] - 395, Red, Red, pDevice);
		DrawBox(menu.matrixPos[0] + 1, menu.matrixPos[1] + 55, menu.matrixPos[2] - 250, menu.matrixPos[3] - 56, BlackFundo, BlackFundo, pDevice);
		//Gradient(menu.matrixPos[0], menu.matrixPos[1], 350, 25, TopoGradi1, TopoGradi2, Gr_Orientation::horizontal, pDevice);// Degradê laranja do menu no topo
		//DrawBox(menu.matrixPos[0] + 10, menu.matrixPos[1] + 68, 330, 330, FundoMenu2, FundoMenu2, pDevice);//Caixa de dentro do menu
		//DrawBorder(menu.matrixPos[0] + 10, menu.matrixPos[1] + 68, 330, 330, 1, Orange, pDevice);			//Borda do menu de dentro
		DesenharTab("D3D", 17, menu.matrixPos[0] + 1,	menu.matrixPos[1] + 56,		menu.matrixPos[2] - 265,		menu.matrixPos[3] - 350,	Tab1, pDevice);
		DesenharTab("Tab", 8,menu.matrixPos[0] + 1,	menu.matrixPos[1] + 83,		menu.matrixPos[2] - 265,		menu.matrixPos[3] - 370,	Tab2, pDevice);

		if (Tab1)
		{
			DrawCheckBox(menu.matrixPos[0] + 110, menu.matrixPos[1] + 100, Crosshair, "Crosshair", pDevice);
			Slider(menu.matrixPos[0] + 110, menu.matrixPos[1] + menu.matrixPos[1] + 150, 100, 255, &Alpha, "Alpha", pDevice);
			Slider(menu.matrixPos[0] + 110, menu.matrixPos[1] + menu.matrixPos[1] + 200, 100, 255, &Vermelho, "Vermelho", pDevice);
			Slider(menu.matrixPos[0] + 110, menu.matrixPos[1] + menu.matrixPos[1] + 250, 100, 255, &Verde, "Verde", pDevice);
			Slider(menu.matrixPos[0] + 110, menu.matrixPos[1] + menu.matrixPos[1] + 300, 100, 255, &Azul, "Azul", pDevice);
			//WriteText(60, 130, White, "wtf? '-'");
			//DesenharCheckBox(60, 150, FlyHack, "CheckBox 1", pDevice);
			//DesenharCheckBox(PosX - 15, PosY + 45, SpeedHack, String_Function32, pDevice);
			//DesenharCheckBox(PosX - 15, PosY + 60, SuperJump, String_Function33, pDevice);
			//DesenharCheckBox(PosX - 15, PosY + 75, EDistance, String_Function34, pDevice);
		}
		if (Tab2)
		{
			WriteText(150, 120, Orange, Black, "Teste");
		}
		//WriteText		(50,	80,	Green,	"Teste"							);			//Texto
		//DrawBox			(23/*distância*/,	49/*altura*/,	498,	20,		White, White,	pDevice );//topo
		//WriteText		(220,	50, Black,	"PaiN D3D");//titulo
		//DrawBox(22, 350, 500, 30, TBlack, White, pDevice);			//Draw box da barra inferior
		//DrawBorder(22, 350, 500, 30, 1, White, pDevice);			//Borda da box da barra inferior

		//sprintf_s(TimeString, "%s", Timestruct);			//Buffer do relógio.
		//WriteText(450, 357, Green, TimeString);			//Texto do relógio.
		//WriteText(35, 357, Green, "LegionHax                              LegionHax.ml");

	}

	D3DVIEWPORT9 Viewport;
	pDevice->GetViewport(&Viewport);
	DWORD CenterX = Viewport.Width / 2;
	DWORD CenterY = Viewport.Height / 2;
	//if (Crosshair == 1)
	//{
			//DrawCircle(CenterX-1,CenterY-1,8,8,Red);//Circle
		//FillRGB(CenterX-13, CenterY, 10, 1,D3DCOLOR_ARGB(Alpha, Vermelho, Verde, Azul),pDevice);//Left line
		//FillRGB(CenterX+4, CenterY, 10, 1,D3DCOLOR_ARGB(Alpha, Vermelho, Verde, Azul),pDevice);//Right line
		//FillRGB(CenterX, CenterY-13, 1, 10,D3DCOLOR_ARGB(Alpha, Vermelho, Verde, Azul),pDevice);//Top line
		//FillRGB(CenterX, CenterY+4, 1, 10,D3DCOLOR_ARGB(Alpha, Vermelho, Verde, Azul),pDevice);//Bottom line
//	}
}
