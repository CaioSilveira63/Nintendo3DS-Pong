// Simple citro2d untextured shape example
#include <citro2d.h>
#include <vector>
#include <string>
#include <stdio.h>
#include <stdlib.h>

#define LarguraTela 400
#define AlturaTela 240

C2D_TextBuf g_staticBuf;
C2D_Text g_staticText[3];
C2D_Font font[3];

int PontosPlayer = 0;
int PontosPlayer2 = 0;

u32 White = C2D_Color32(0xFF, 0xFF, 0xFF, 0xFF);
u32 clrGreen = C2D_Color32(0x00, 0xFF, 0x00, 0xFF);
u32 clrRed = C2D_Color32(0xFF, 0x00, 0x00, 0xFF);
u32 clrBlue = C2D_Color32(0x00, 0x00, 0xFF, 0xFF);

u32 clrCircle1 = C2D_Color32(0xFF, 0x00, 0xFF, 0xFF);
u32 clrCircle2 = C2D_Color32(0xFF, 0xFF, 0x00, 0xFF);
u32 clrCircle3 = C2D_Color32(0x00, 0xFF, 0xFF, 0xFF);

u32 clrSolidCircle = C2D_Color32(0x68, 0xB0, 0xD8, 0xFF);

u32 clrTri1 = C2D_Color32(0xFF, 0x15, 0x00, 0xFF);
u32 clrTri2 = C2D_Color32(0x27, 0x69, 0xE5, 0xFF);

u32 clrRec1 = C2D_Color32(0x9A, 0x6C, 0xB9, 0xFF);
u32 clrRec2 = C2D_Color32(0xFF, 0xFF, 0x2C, 0xFF);
u32 clrRec3 = C2D_Color32(0xD8, 0xF6, 0x0F, 0xFF);
u32 clrRec4 = C2D_Color32(0x40, 0xEA, 0x87, 0xFF);

u32 clrClear = C2D_Color32(0xFF, 0xD8, 0xB0, 0x68);

u32 Black = C2D_Color32(0x00, 0x00, 0x00, 0x00);

class Player
{
public:
    float X = LarguraTela - 16;
    float Y = AlturaTela / 2 - 20;
    float Largura = 8;
    float Altura = 40;
    float Velocidade = 10;
    u32 Cor = White;
};

class Player2
{
public:
    float X = 0 + 8;
    float Y = AlturaTela / 2 - 20;
    float Largura = 8;
    float Altura = 40;
    float Velocidade = 10;
    u32 Cor = White;
};

class Bola
{
public:
    float X = LarguraTela / 2;
    float Y = AlturaTela / 2 - 4;
    float Largura = 8;
    float Altura = 8;
    float Velocidade = 1;
    int DirecaoX = 1;
    int DirecaoY = 1;
    u32 Cor = White;
};

Player player;
Player2 player2;
Bola bola;
Bola Novabola;

bool Pause = false;

void DesenharRetangulo(float x, float y, float width, float height, u32 Cor)
{
    C2D_DrawRectangle(x, y, 0, width, height, Cor, Cor, Cor, Cor);
}

void DesenharTexto(std::string texto, float X, float Y, float Size, u32 Cor)
{
    std::vector<char> writable(texto.begin(), texto.end());
    writable.push_back('\0');
    g_staticBuf = C2D_TextBufNew(4096);
    font[0] = C2D_FontLoad("romfs:/8bit.bcfnt");
    C2D_TextFontParse(&g_staticText[0], font[0], g_staticBuf, &writable[0]);
    C2D_TextOptimize(&g_staticText[0]);
    C2D_DrawText(&g_staticText[0], C2D_AtBaseline, X, Y, 0, Size, Size);
}

void IniciarTexto()
{
    g_staticBuf = C2D_TextBufNew(4096); // support up to 4096 glyphs in the buffer
    font[0] = C2D_FontLoadSystem(CFG_REGION_USA);
    font[2] = C2D_FontLoad("romfs:/8bit.bcfnt");

    // Parse the text strings
    // Loads system font
    C2D_TextFontParse(&g_staticText[0], font[0], g_staticBuf, "A boring system font.");
    // Uses loaded font
    // Uses other loaded font
    C2D_TextFontParse(&g_staticText[2], font[2], g_staticBuf, "Wow, this is interesting.");

    // Optimize the text strings
    C2D_TextOptimize(&g_staticText[0]);
    C2D_TextOptimize(&g_staticText[2]);
}

void TesteTexto()
{
    float text2PosX = 400.0f - 16.0f - g_staticText[2].width * 0.75f; // right-justify
    C2D_DrawText(&g_staticText[0], 0, 8.0f, 8.0f, 0.5f, 0.5f, 0.5f);
    C2D_DrawText(&g_staticText[2], C2D_AtBaseline, text2PosX, 210.0f, 0.5f, 0.5f, 0.5f);
}

void DesenharPlayer()
{
    DesenharRetangulo(player.X, player.Y, player.Largura, player.Altura, player.Cor);
}

void DesenharPlayer2()
{
    DesenharRetangulo(player2.X, player2.Y, player2.Largura, player2.Altura, player2.Cor);
}

void DesenharBola()
{

    DesenharRetangulo(bola.X, bola.Y, bola.Largura, bola.Altura, bola.Cor);
}

void InputPlayer1()
{
    u32 kDown = hidKeysDown();
    u32 kHeld = hidKeysHeld();

    if (kHeld & KEY_X)
    {

        player.Y = player.Y - player.Velocidade;
    }

    else if (kHeld & KEY_B)
    {
        player.Y = player.Y + player.Velocidade;
    }

    if (player.Y < 0)
    {
        player.Y = 0;
    }
    else if (player.Y > AlturaTela - player.Altura)
    {
        player.Y = AlturaTela - player.Altura;
    }
}

void InputPlayer2()
{
    u32 kDown = hidKeysDown();
    u32 kHeld = hidKeysHeld();

    if (kHeld & KEY_DUP)
    {

        player2.Y = player2.Y - player2.Velocidade;
    }
    else if (kHeld & KEY_DDOWN)
    {
        player2.Y = player2.Y + player2.Velocidade;
    }

    if (player2.Y < 0)
    {
        player2.Y = 0;
    }
    else if (player2.Y > AlturaTela - player2.Altura)
    {
        player2.Y = AlturaTela - player2.Altura;
    }
}

void Inputs()
{
    InputPlayer1();
    InputPlayer2();
}

bool ColisaoPlayerBola()
{
    return player.X < bola.X + bola.Largura &&
           player.X + player.Largura > bola.X &&
           player.Y < bola.Y + bola.Altura &&
           player.Y + player.Altura > bola.Y;
}

bool ColisaoPlayer2Bola()
{
    return player2.X < bola.X + bola.Largura &&
           player2.X + player2.Largura > bola.X &&
           player2.Y < bola.Y + bola.Altura &&
           player2.Y + player2.Altura > bola.Y;
}

void Logica()
{
    Inputs();

    bola.X += bola.Velocidade * bola.DirecaoX;
    bola.Y += bola.Velocidade * bola.DirecaoY;

    if (bola.Y < 0)
    {
        bola.Y = 0;
        bola.DirecaoY *= -1;
    }
    else if (bola.Y > AlturaTela - bola.Altura)
    {
        bola.Y = AlturaTela - bola.Altura;
        bola.DirecaoY *= -1;
    }

    if (ColisaoPlayerBola())
    {
        bola.X = LarguraTela - 24;
        bola.DirecaoX *= -1;
    }
    else if (ColisaoPlayer2Bola())
    {
        bola.X = 16;
        bola.DirecaoX *= -1;
    }

    if (bola.X < 0)
    {
        PontosPlayer2++;
        bola = Novabola;
        bola.DirecaoX = 1;
    }
    else if (bola.X > LarguraTela - bola.Largura)
    {
        PontosPlayer++;
        bola = Novabola;
        bola.DirecaoX = -1;
    }
}

void InputPause()
{
    u32 kDown = hidKeysDown();
    u32 kHeld = hidKeysHeld();
    if (kDown & KEY_START)
    {
        Pause = !Pause;
    }
}

void DesenharPlacar()
{
    DesenharTexto(std::to_string(PontosPlayer), 57, 63, 1.0f, White);
    DesenharTexto(std::to_string(PontosPlayer2), 257, 63, 1.0f, White);
}

void Logs()
{
    printf("\x1b[1;1HPLAYER Y: %d", 0);
    printf("\x1b[2;1HBola Y: %d", 0);
    printf("\x1b[3;1HBola X: %d", 0);
}

//---------------------------------------------------------------------------------
int main(int argc, char *argv[])
{
    //---------------------------------------------------------------------------------
    // Init libs
    romfsInit();
    cfguInit();

    gfxInitDefault();
    C3D_Init(C3D_DEFAULT_CMDBUF_SIZE);
    C2D_Init(C2D_DEFAULT_MAX_OBJECTS);
    C2D_Prepare();
    consoleInit(GFX_BOTTOM, NULL);

    // Create screens
    C3D_RenderTarget *top = C2D_CreateScreenTarget(GFX_TOP, GFX_LEFT);

    IniciarTexto();
    // Main loop
    while (aptMainLoop())
    {
        hidScanInput();

        // Respond to user input
        u32 kDown = hidKeysDown();
        u32 kHeld = hidKeysHeld();
        if (kDown & KEY_SELECT)
        {
            break; // break in order to return to hbmenu
        }

        // Render the scene
        C3D_FrameBegin(C3D_FRAME_SYNCDRAW);
        C2D_TargetClear(top, Black);
        C2D_SceneBegin(top);

        InputPause();
        if (!Pause)
        {
            Logica();
        }
        //DesenharTexto("Teste", 0, 0, 200, White);
        DesenharPlayer();
        DesenharPlayer2();
        DesenharBola();
        TesteTexto();
        DesenharPlacar();

        C3D_FrameEnd(0);
    }

    // Deinit libs
    C2D_Fini();
    C3D_Fini();
    gfxExit();
    return 0;
}
