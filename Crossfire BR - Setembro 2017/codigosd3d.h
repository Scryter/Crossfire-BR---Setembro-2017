/*********************************************************/
/* Base D3D Menu Tab V1
/* Creditos:
/*	PaiN		-> Base D3D Menu Tab.
/*  Dreek1		-> Disponibilizou Hook.
/*  AeroMan		-> D3DTest.
/*********************************************************/
#include "timer.h"

POINT cPos;
INT Tab1 = 1, Tab2, Tab3, Tab4, Tab5, Tab6;
INT PosX = 50, PosY = 60;
CTimer ClickCheck[900];

#define PI 3.14159265//Defining what PI is. PI is a Circle
LPDIRECT3DDEVICE9 pDevice;
ID3DXLine *pLine;


#define Red			D3DCOLOR_ARGB(255, 255, 000, 000)
#define Green		D3DCOLOR_ARGB(255, 127, 255, 000)
#define Orange		D3DCOLOR_ARGB(255, 255, 140, 000)
#define Blue		D3DCOLOR_ARGB(255, 000, 000, 255)
#define Yellow		D3DCOLOR_ARGB(255, 255, 255,  51)
#define Black		D3DCOLOR_ARGB(255, 000, 000, 000)
#define Grey		D3DCOLOR_ARGB(255, 112, 112, 112)
#define Gold		D3DCOLOR_ARGB(255, 255, 215, 000)
#define Pink		D3DCOLOR_ARGB(255, 255, 192, 203)
#define Purple		D3DCOLOR_ARGB(255, 128, 000, 128)
#define White		D3DCOLOR_ARGB(255, 255, 255, 249)
#define Cyan		D3DCOLOR_ARGB(255, 000, 255, 255)
#define Magenta		D3DCOLOR_ARGB(255, 255, 000, 255)
#define TBlack		D3DCOLOR_ARGB(128, 000, 000, 000)
#define BlueViolet	D3DCOLOR_ARGB(255, 127, 255, 212)
#define DarkGreen	D3DCOLOR_ARGB(255, 0,	128, 0)
//LuizimLoko----------------------------------------------
#define FundoMenu	D3DCOLOR_ARGB(255, 12,	12,	 12)
#define FundoMenu2	D3DCOLOR_ARGB(255, 68,  68,  68)
#define TopoGradi1	D3DCOLOR_ARGB(255, 251, 108, 1)
#define TopoGradi2	D3DCOLOR_ARGB(255, 241, 87, 13)
//Menu novo
#define BlackFundo	D3DCOLOR_ARGB(255, 30, 33, 36)
#define BlackFundo2 D3DCOLOR_ARGB(255,47, 49, 54)
#define BlackFundo3 D3DCOLOR_ARGB(255,54, 57, 62)
#define buttontab	D3DCOLOR_ARGB(255, 43, 87, 154)
#define TMenu DT_LEFT | DT_NOCLIP


DWORD MenuColor = FundoMenu;

enum Gr_Orientation {
	horizontal, vertical
};

/*================================== Estrutura do Menu ====================================*/
struct CMenu
{
	INT MenuSelection,
		matrixPos[3],
		Current;

	BOOL ShowMenu;

	CMenu(VOID)
	{
		ShowMenu = 1;
		Current = 1;

		matrixPos[0] = 22; //x1
		matrixPos[1] = 48; //y1
		matrixPos[2] = 350; //y2
		matrixPos[3] = 400; //x2
	}
}
menu;
/*=====================================================================================*/

/*======================================= Texto =======================================*/
LPD3DXFONT pFont;

VOID BaseTexto(INT x, INT y, D3DCOLOR Color, CHAR *String)
{
	RECT Rect;
	SetRect(&Rect, x, y, x, y);
	pFont->DrawTextA(0, String, -1, &Rect, DT_LEFT | DT_NOCLIP, Color);
}
/*=====================================================================================*/
VOID WriteText(INT x, INT y, D3DCOLOR color, D3DCOLOR bordercolor, CHAR *String)
{
	BaseTexto(x + 1, y + 1, bordercolor, String);
	BaseTexto(x, y, color, String);
}
/*============================= Box Menu =============================================*/
VOID FillRGB(INT x, INT y, INT w, INT h, D3DCOLOR Color, LPDIRECT3DDEVICE9 pDevice)
{
	D3DRECT rec = { x, y, x + w, y + h };
	pDevice->Clear(1, &rec, D3DCLEAR_TARGET, Color, 0, 0);
}

VOID DrawBorder(INT x, INT y, INT w, INT h, INT px, D3DCOLOR BorderColor, LPDIRECT3DDEVICE9 pDevice)
{
	FillRGB(x, (y + h - px), w, px, BorderColor, pDevice);
	FillRGB(x, y, px, h, BorderColor, pDevice);
	FillRGB(x, y, w, px, BorderColor, pDevice);
	FillRGB(x + w - px, y, px, h, BorderColor, pDevice);
}


VOID DrawBox(INT x, INT y, INT w, INT h, D3DCOLOR Color, D3DCOLOR BorderColor, LPDIRECT3DDEVICE9 pDevice)
{
	DrawBorder(x, y, w, h, 2, BorderColor, pDevice);

	const DWORD D3D_FVF = D3DFVF_XYZRHW | D3DFVF_DIFFUSE;

	struct Vertex
	{
		FLOAT x, y, w, h;
		D3DCOLOR Color;
	}
	V[4] = { { (FLOAT)x, (FLOAT)(y + h), 0.0f, 0.0f, Color },
	{ (FLOAT)x, (FLOAT)y, 0.0f, 0.0f, Color },
	{ (FLOAT)(x + w), (FLOAT)(y + h), 0.0f, 0.0f, Color },
	{ (FLOAT)(x + w), (FLOAT)y, 0.0f, 0.0f, Color }
	};

	pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, D3DZB_TRUE);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	pDevice->SetRenderState(D3DRS_ZENABLE, D3DZB_FALSE);
	pDevice->SetRenderState(D3DRS_FOGENABLE, D3DZB_FALSE);

	pDevice->SetFVF(D3D_FVF);
	pDevice->SetTexture(0, NULL);
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, V, sizeof(Vertex));
}
/*==================================================================================*/
/*================================= Gradient =====================================*/
VOID Gradient(float x, float y, float w, float h, DWORD IniciaCor, DWORD FimCor, Gr_Orientation Orientation, LPDIRECT3DDEVICE9 pDevice) {//Modificado para funcionar(Aparecer) em todos Computadores by Kssiobr/oO>Kssio<Oo™
																																		 //	extern enum Gr_Orientation;
	const DWORD D3DGRADE_ALLCOMPUTER = 0x004 | 0x040;
	struct D3DVERTEX { float x, y, z, rhw; DWORD COR; }


	vertices[4] = {
		{ 0, 0, 0, 1.0f, 0 },
		{ 0, 0, 0, 1.0f, 0 },
		{ 0, 0, 0, 1.0f, 0 },
		{ 0, 0 ,0, 1.0f, 0 }
	};


	vertices[0].x = x;
	vertices[0].y = y;
	vertices[0].COR = IniciaCor;


	vertices[1].x = x + w;
	vertices[1].y = y;
	vertices[1].COR = Orientation == vertical ? FimCor : IniciaCor;


	vertices[2].x = x;
	vertices[2].y = y + h;
	vertices[2].COR = Orientation == vertical ? IniciaCor : FimCor;


	vertices[3].x = x + w;
	vertices[3].y = y + h;
	vertices[3].COR = FimCor;


	pDevice->SetTexture(false, false);
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, true);
	pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATEREQUAL);
	pDevice->SetRenderState(D3DRS_ALPHAREF, (DWORD)8);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	pDevice->SetRenderState(D3DRS_ZENABLE, D3DZB_FALSE);
	pDevice->SetRenderState(D3DRS_FOGENABLE, D3DZB_FALSE);
	pDevice->SetFVF(0x004 | 0x040 | 0X100);
	pDevice->SetFVF(D3DGRADE_ALLCOMPUTER);
	pDevice->SetTexture(0, NULL);
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, vertices, sizeof(D3DVERTEX));
}
//=============================================//
//================== Group Box =============================\\

VOID DesenharTexto(INT Type, LPD3DXFONT g_pFont, INT x, INT y, DWORD Color, DWORD Flags, CHAR *Text)
{
	RECT rect;
	SetRect(&rect, x, y, x, y);

	RECT rect2;
	SetRect(&rect2, x + 1, y + 1, x + 1, y + 1);

	switch (Type)
	{
	case 0:
		g_pFont->DrawTextA(NULL, Text, -1, &rect, Flags, Color);
		break;

	case 1:
		g_pFont->DrawTextA(NULL, Text, -1, &rect2, Flags, 0xFF000000);
		g_pFont->DrawTextA(NULL, Text, -1, &rect, Flags, Color);
		break;
	}
}

INT GetText(CONST CHAR* Text)
{
	RECT Rect = { NULL, NULL, NULL, NULL };
	pFont->DrawTextA(NULL, Text, -1, &Rect, DT_CALCRECT, NULL);
	return Rect.right;
}


VOID DrawGroupBox(INT X, INT Y, INT W, INT H, DWORD Color, CHAR* Text, LPDIRECT3DDEVICE9 pDevice)
{
	INT Soma = 13;

	FillRGB(X, Y, Soma, 1, Color, pDevice);
	FillRGB(X + Soma + GetText(Text) + 3, Y, W - GetText(Text) - Soma, 1, Color, pDevice);
	FillRGB(X, Y, 1, H, Color, pDevice);

	FillRGB(X, Y + H, W + 4, 1, Color, pDevice);
	FillRGB(X + Soma + GetText(Text) + 3 + W - GetText(Text) - Soma, Y, 1, H, Color, pDevice);

	DesenharTexto(FALSE, pFont, X + Soma + 2, Y - 7, Orange, TMenu, Text);
}


//================== Tab ===========================================\\

INT CheckTabs(FLOAT x, FLOAT y, FLOAT w, FLOAT h, INT Speed, CTimer* TimerList)
{
	GetCursorPos(&cPos);
	ScreenToClient(GetForegroundWindow(), &cPos);
	if (cPos.x > x && cPos.x < x + w && cPos.y > y && cPos.y < y + h)
	{
		if (GetAsyncKeyState(VK_LBUTTON) < 0)
		{
			if (!TimerList[100].Running())
			{
				TimerList[100].Start((FLOAT)Speed);
				return 1;
			}
		}
		return 2;
	}
	return 0;
}

/*INT GetText(CONST CHAR* Text)
{
RECT Rect = { NULL, NULL, NULL, NULL };
pFont->DrawTextA(NULL, Text, -1, &Rect, DT_CALCRECT, NULL);
return Rect.right;
}*/

/*VOID DesenharTab(CHAR* TabName, INT TextX, INT X, INT Y, INT W, INT H, INT &Variable, LPDIRECT3DDEVICE9 pDevice)
{
	INT Check = CheckTabs(X - 1, Y - 1, W, H - 1, 170, ClickCheck);

	DWORD ColorText;

	if (Check == 0)
	{
		ColorText = White;		//ColorText = D3DCOLOR_ARGB(255, 150, 150, 150);
								//	DrawBox(X, Y, W, 20, FundoMenu2, FundoMenu, pDevice);
								//DrawBorder(X, Y+ 4, W, 22, 1, Orange, pDevice);			//Borda do menu de dentro


	}
	else
	{
		ColorText = D3DCOLOR_ARGB(255, 180, 180, 180);

	}

	if (Check == 1)
	{
		Tab1 = 0;
		Tab2 = 0;
		Tab3 = 0;
		Tab4 = 0;
		Tab5 = 0;
		Tab6 = 0;
		Variable = !Variable;
	}

	if (Variable == 1)
	{
		DrawBox(X, Y, W, 25, FundoMenu2, FundoMenu2, pDevice);
		//DrawBorder(X, Y, W, 25, 1, Orange, pDevice);			//Borda do menu de dentro
		DrawBox(X, Y + 30, W, 7, FundoMenu2, FundoMenu2, pDevice);

	}
	WriteText(X + (W / 2) - TextX, Y + (Y / 2), White, Black, TabName);

}*/
VOID DesenharTab(CHAR* TabName, INT TextX, INT X, INT Y, INT W, INT H, INT &Variable, LPDIRECT3DDEVICE9 pDevice)
{
	INT Check = CheckTabs(X - 1, Y - 1, W, H, 170, ClickCheck); //INT Check = CheckTabs(X - 1, Y - 1, W, H - 1, 170, ClickCheck);
	DWORD ColorText;

	if (Check == 0)
	{
		ColorText = White;		//ColorText = D3DCOLOR_ARGB(255, 150, 150, 150);				//	DrawBox(X, Y, W, 20, FundoMenu2, FundoMenu, pDevice);
								//DrawBorder(X, Y+ 4, W, 22, 1, Orange, pDevice);			//Borda do menu de dentro


	}
	else
	{
		ColorText = D3DCOLOR_ARGB(255, 180, 180, 180);

	}

	if (Check == 1)
	{
		Tab1 = 0;
		Tab2 = 0;
		Tab3 = 0;
		Tab4 = 0;
		Tab5 = 0;
		Tab6 = 0;
		Variable = !Variable;
	}

	if (Variable == 1)
	{
		DrawBox(X, Y, W + 15, 25, FundoMenu, White, pDevice);
		//DrawBorder(X, Y, W, 25, 1, Orange, pDevice);			//Borda do menu de dentro
		

	}
	if (Variable == 0)
	{
		DrawBox(X, Y, W + 15, 25, FundoMenu2, FundoMenu2, pDevice); //DrawBox(X + 93, Y, 7, 25, FundoMenu2, FundoMenu2, pDevice);
	}
	WriteText(X + (W / 2) - TextX, Y + 3, White, Black, TabName);
	//DesenharTexto(FALSE, pFont, X + (W / 2) - TextX, Y + 3, ColorText, TMenu, TabName);

}


void DrawCircle(int X, int Y, int radius, int numSides, DWORD Color)
{

        D3DXVECTOR2 Line[128];
        float Step = PI * 2.0 / numSides;
        int Count = 0;
        for (float a=0; a < PI*2.0; a += Step)
        {
                float X1 = radius * cos(a) + X;
                float Y1 = radius * sin(a) + Y;
                float X2 = radius * cos(a+Step) + X;
                float Y2 = radius * sin(a+Step) + Y;
                Line[Count].x = X1;
                Line[Count].y = Y1;
                Line[Count+1].x = X2;
                Line[Count+1].y = Y2;
                Count += 2;
        }
        pLine->Begin();
        pLine->Draw(Line,Count,Color);
        pLine->End();
}
VOID DesenharCheckBox(INT X, INT Y, INT &Variable, CHAR* Text, LPDIRECT3DDEVICE9 pDevice)
{
	INT Check = CheckTabs(X, Y - 5, 050, 020, 170, ClickCheck);

	DWORD ColorText = White;
	DWORD BoxColor = FundoMenu2;



	if (Check == 0)
	{
		ColorText = White;
	}
	else {
		ColorText = White;
		BoxColor = FundoMenu2;
	}

	if (Variable)
	{
		DrawBox(X, Y, 12, 12, Orange, FundoMenu2, pDevice);
		DrawBox(X + 2, Y + 2, 8, 8, MenuColor, MenuColor, pDevice);
	}
	else {
		DrawBox(X, Y, 12, 12, Orange, FundoMenu2, pDevice);
	}

	DesenharTexto(FALSE, pFont, X + 17, Y, ColorText, TMenu, Text);
}



VOID DrawArrowList(INT X, INT Y, INT &Var, INT Max, CHAR **Opt, LPDIRECT3DDEVICE9 pDevice)
{
	INT Check1 = CheckTabs(X, Y, 12, 12, 170, ClickCheck);
	INT Check2 = CheckTabs(X + 100, Y, 12, 12, 170, ClickCheck);

	DWORD ColorText1 = D3DCOLOR_ARGB(255, 100, 100, 100);
	DWORD ColorText2 = D3DCOLOR_ARGB(255, 100, 100, 100);

	if (Check1 == 1)
	{
		if (Var > 0)
			Var--;
		else if (Var == 0)
			Var = Max - 1;
	}

	if (Check2 == 1)
	{
		if (Var < Max - 1)
			Var++;
		else if (Var == Max - 1)
			Var = 1;
	}

	if (Check1 == 2)
	{
		ColorText1 = Red;
	}

	if (Check2 == 2)
	{
		ColorText2 = Green;
	}

	DrawBox(X, Y, 15, 15, White, D3DCOLOR_ARGB(255, 150, 150, 150), pDevice);
	DrawBox(X + 100, Y, 15, 15, White, D3DCOLOR_ARGB(255, 150, 150, 150), pDevice);

	DesenharTexto(FALSE, pFont, X + (15 / 2) - 2, Y + (1 / 2), ColorText1, TMenu, "<");
	DesenharTexto(FALSE, pFont, X + 98 + (15 / 2), Y + (1 / 2), ColorText2, TMenu, ">");

	DesenharTexto(FALSE, pFont, X + 50 - GetText(Opt[Var]) / 2 + 7, Y + (1 / 2), D3DCOLOR_ARGB(255, 100, 100, 100), TMenu, Opt[Var]);
}

void Slider(int x, int y, int w, int max, void* State, char*text, LPDIRECT3DDEVICE9 pDevice)
{
	POINT CursorPos;
	GetCursorPos(&CursorPos);
	ScreenToClient(GetForegroundWindow(), &CursorPos);



	if (*(int*)State > max)
		*(int*)State = max;
	if (*(int*)State < 0)
		*(int*)State = 0;

	int Current = ((*(int*)State - 0) * w / (max - 0));


	if ((CursorPos.x >= x && CursorPos.x <= x + w && CursorPos.y >= y && CursorPos.y <= y + 10))
	{
		if (GetAsyncKeyState(VK_LBUTTON))
		{
			*(int*)State = (CursorPos.x - x) * (max - 0) / w;
		}
	}

	//DrawBox(x, y - 3, 8, 1, D3DCOLOR_ARGB(255, 33, 33, 33), D3DCOLOR_ARGB(255, 33, 33, 33), pDevice);

	char buffer[256];
	sprintf(buffer, "%i", *(int*)State);
	FillRGB(x + 2, y - 2, w, 4, Black, pDevice);
	//FillRGB(x + 2, y - 2, Current - 1, 6, D3DCOLOR_ARGB(255, 114, 137, 218), pDevice);
	FillRGB(x + Current, y - 2, 2, 4, D3DCOLOR_ARGB(255, 114, 137, 218), pDevice);
	DrawBox(x + Current, y - 5, 5, 10, White, D3DCOLOR_ARGB(255, 33, 33, 33), pDevice);

	WriteText(x, y - 24, D3DCOLOR_XRGB(200, 200, 200), Black, text);
	WriteText((x + w) - 30, y - 24, D3DCOLOR_XRGB(200, 200, 200), Black, buffer);
}
void DrawCheck( DWORD Color, float x, float y, LPDIRECT3DDEVICE9 pDevice )
{
	FillRGB( x, y, 1, 3, Color,         pDevice );
	FillRGB( x + 1, y + 1, 1, 3, Color, pDevice );
	FillRGB( x + 2, y + 2, 1, 3, Color, pDevice );
	FillRGB( x + 3, y + 1, 1, 3, Color, pDevice );
	FillRGB( x + 4, y, 1, 3,     Color, pDevice );
	FillRGB( x + 5, y - 1, 1, 3, Color, pDevice );
	FillRGB( x + 6, y - 2, 1, 3, Color, pDevice );
	FillRGB( x + 7, y - 3, 1, 3, Color, pDevice );
}
void CheckDrawBorder( int x, int y, int w, int h, int s,D3DCOLOR FillColor, D3DCOLOR Color,LPDIRECT3DDEVICE9 device)//Draws GUI Box and Border
{ 
    FillRGB( x, y, w, h, FillColor, device);
	FillRGB( x, y-1, w, s, Color, device);
    FillRGB( x-1, y, s, h, Color,device );
    FillRGB( (x+w), y, s, h, Color, device);
    FillRGB( x, (y+h), w, s, Color,device );
}

bool MouseIsOver(int x, int y, int w, int h)
{ 
    bool bover; 
	GetCursorPos(&cPos);
	if(cPos.x >= x && cPos.x <= x + w && cPos.y >= y && cPos.y <= y + h)
	{ 
		bover = true; 
	}else{ 
		bover = false; 
	} 
    return bover;
}

void DrawCheckBox(int x, int y, int &val, CHAR* String, LPDIRECT3DDEVICE9 pDevice)
{
	if(MouseIsOver(x,y,10,10) && GetAsyncKeyState(VK_LBUTTON)&1)
	{
		val =! val;
	}
	WriteText(x + 22, y -1, White, Black, String);
	//DrawTitulo( x + 22, y -1, White, Directx_Font, text);//Cor do Nome da Função
	if(val)
	{
		CheckDrawBorder( x, y, 10, 10,1, Grey, Grey, pDevice );//Box do Quadrado de Ativação [Ativado]
		DrawCheck( Green, x + 1, y + 4 , pDevice);//Cor do Ok do Box de Ativação [Ativado]
	}
	else
	{
		CheckDrawBorder( x, y, 10, 10, 1, Grey, Grey, pDevice );//Box do Quadrado de Ativação [Desativado]
	}
}
