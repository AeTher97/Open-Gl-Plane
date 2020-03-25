/*

 OpenGL - Szablon 3D do cwiczen laboratoryjnych
 (C) Micha³ Turek.

*/

#include <windows.h>
#include "GL/glut.h"
#include "include/model3DS.h"
#include <time.h>
#include <direct.h>
#include <GL/glu.h>
#include <cmath>



//#include <GL/glaux.h>
//#define GLUTCHECKLOOP

// Wymiary okna
int oknoSzerkosc = 800;
int oknoWysokosc = 600;
bool oknoFullScreen = false;
GLint oknoLewe = 1, oknoPrawe = 2;      // id okien stereo

// Opcje projekcji stereo
int stereoTryb = 0;
int stereoRozstawOczu = 5;                // dystans miêdzy oczami
int stereoPunktPatrzenia = 150;            // odleg³oœæ do punktu, na który patrz¹ oczy
bool stereoIDRamki = false;
bool timing100FPS = true;                // flaga polecenia odmierzania czasu

// Kamera
int pozycjaMyszyX;                        // na ekranie
int pozycjaMyszyY;
double kameraX;
double kameraY;

#include <math.h>       /* acos */

double kameraZ;
double kameraPunktY;
double kameraPredkoscPunktY;
double kameraPredkosc;
bool kameraPrzemieszczanie;        // przemieszczanie lub rozgl¹danie
double kameraKat;                // kat patrzenia
double kameraPredkoscObrotu;
bool sunAnimation = true;


double slonceX = 0;
double slonceY = 0;
double slonceZ = 0;
GLdouble slonceProjection[16];


double ksiezycX = 0;
double ksiezycY = 0;
double ksiezycZ = 0;


#define MIN_DYSTANS 0.5            // minimalny dystans od brzegu obszaru ograniczenia kamery
double obszarKamery = 0;
GLUquadricObj *obiekt;

#define _DEFINICJE

// DEFINICJE ZMIENNYCH

// w tablicy s¹ pozycje drzew i krzewów: {x,y,z,rotacjaY}
float drzewa1[12][4] = {{-110, -8,  130,  16},
                        {-90,  -8,  145,  96},
                        {-150, -8,  -60,  158},
                        {-140, -8,  -90,  138},
                        {30,   -6,  -80,  70},
                        {-43,  -16, -120, -70},
                        {20,   -8,  80,   180},
                        {30,   -8,  30,   80},
                        {35,   -8,  160,  50},
                        {40,   -8,  130,  0},
                        {133,  -8,  29,   210},
                        {128,  -16, -70,  110}};
float drzewa2[12][4] = {{-120, -17, 100,  16},
                        {-95,  -8,  70,   76},
                        {-135, -8,  -10,  158},
                        {-148, -15, 10,   128},
                        {-10,  -10, -40,  70},
                        {-20,  -8,  40,   20},
                        {30,   -8,  130,  80},
                        {80,   -8,  160,  180},
                        {110,  -8,  140,  0},
                        {140,  -8,  150,  100},
                        {81,   -8,  -90,  140},
                        {119,  -8,  -140, 210}};
float drzewa3[12][4] = {{-99,  -8, 110,  16},
                        {-151, -8, 72,   76},
                        {-145, -8, -30,  178},
                        {-128, -8, 40,   128},
                        {-140, 1,  -140, 170},
                        {-23,  -8, 75,   20},
                        {15,   -8, 120,  80},
                        {100,  -8, 138,  180},
                        {115,  -8, 120,  0},
                        {98,   -8, 50,   100},
                        {83,   -8, -110, 110},
                        {111,  -8, -134, 210}};
float krzaki[12][4] = {{-181, 43, -64, 100},
                       {-104, -6, 40,  90},
                       {-138, -7, -60, 40},
                       {-113, -5, -70, 76},
                       {-8,   -8, -80, 320},
                       {20,   -5, 53,  170},
                       {-39,  11, -53, 120},
                       {30,   -8, 140, 10},
                       {80,   7,  100, 40},
                       {120,  -8, 45,  206},
                       {140,  1,  -23, 6},
                       {101,  -8, 110, 146}};

int animacjaLisci = 0;
int animacjaSlonca = 0;

float mnoznik = 3;

float posx = 0;
float posy = 0;

float mgla = 0;

int zmienna = 0;


float lawkaPozycja = 0;
float lawkaPredkosc = 0;

int iterator = 0;
/******************************************************/
bool rysujLawke = true;


/** REJESTRATOR PRZESZKOD **/

struct przeszkoda {
    przeszkoda *next;
    double posX1;
    double posZ1;
    double posX2;
    double posZ2;
};
przeszkoda *obszarPrzeszkody = NULL;

void resetKamery() {
    kameraX = 0;
    kameraY = 4;
    kameraZ = 40;
    kameraKat = -0.4;
    kameraPunktY = -15;
    kameraPredkoscPunktY = 0;
    kameraPredkosc = 0;
    kameraPredkoscObrotu = 0;
    kameraPrzemieszczanie = true;
}

void ustalObszar(double X) {
    obszarKamery = X;
}

bool wObszarze(double posX, double posZ) {
    if (posX * posX + posZ * posZ > (obszarKamery - MIN_DYSTANS * 2) * (obszarKamery - MIN_DYSTANS * 2)) return false;
    przeszkoda *pom = obszarPrzeszkody;
    while (pom) {
        if (pom->posX1 < posX &&
            pom->posX2 > posX &&
            pom->posZ1 < posZ &&
            pom->posZ2 > posZ)
            return false;
        pom = pom->next;
    }
    return true;
}

void rejestrujPrzeszkode(double X1, double Z1, double X2, double Z2) {
    przeszkoda *pom = new przeszkoda;
    if (X1 > X2) {
        double tmp = X1;
        X1 = X2;
        X2 = tmp;
    }
    if (Z1 > Z2) {
        double tmp = Z1;
        Z1 = Z2;
        Z2 = tmp;
    }
    pom->posX1 = X1;
    pom->posZ1 = Z1;
    pom->posX2 = X2;
    pom->posZ2 = Z2;
    pom->next = obszarPrzeszkody;
    obszarPrzeszkody = pom;
}

/** OBSLUGA INTERAKCJI Z UZYTKOWNIKIEM **/

void SzablonPrzyciskMyszyWcisniety(int button, int state, int x, int y) {
    switch (state) {
        case GLUT_UP:
            kameraPredkosc = 0;
            kameraPredkoscObrotu = 0;
            kameraPredkoscPunktY = 0;
            break;
        case GLUT_DOWN:
            pozycjaMyszyX = x;
            pozycjaMyszyY = y;
            if (button == GLUT_LEFT_BUTTON)
                kameraPrzemieszczanie = true;
            else
                kameraPrzemieszczanie = false;
            break;
    }
}

void SzablonRuchKursoraMyszy(int x, int y) {
    kameraPredkoscObrotu = -(pozycjaMyszyX - x) * 0.001;
    if (kameraPrzemieszczanie) {
        kameraPredkosc = (pozycjaMyszyY - y) * 0.02;
        kameraPredkoscPunktY = 0;
    } else {
        kameraPredkoscPunktY = (pozycjaMyszyY - y) * 0.06;
        kameraPredkosc = 0;
    }
}

void SzablonKlawiszKlawiaturyWcisniety(GLubyte key, int x, int y) {
    switch (key) {
        case 27:
            exit(1);
            break;
        case ' ':
            if (stereoTryb != 2) glutFullScreen();
            break;

    }

}

/*

 C++ przez OpenGL - szablon do æwiczeñ laboratoryjnych
 (C) Micha³ Turek.

*/



/******************* SZABLON **************************/

// DEFINICJE FUNKCJI OBS£UGUJ¥CYCH ZDARZENIA MYSZY I KLAWIATURY

void PrzyciskMyszyWcisniety(int button, int state, int x, int y) {
    SzablonPrzyciskMyszyWcisniety(button, state, x, y); // wywolanie standardowej obslugi zdarzen szablonu


    //*************************************************************
    // tu mo¿na umieciæ kod obs³uguj¹cy wciniêcie przycisku myszy









}

void RuchKursoraMyszy(int x, int y) {
    SzablonRuchKursoraMyszy(x, y); // wywolanie standardowej obslugi zdarzen szablonu

    //****************************************************
    //tu mo¿na umieciæ kod obs³uguj¹cy ruch kursora myszy







}

void KlawiszKlawiaturyWcisniety(GLubyte key, int x, int y) {
    SzablonKlawiszKlawiaturyWcisniety(key, x, y);    // wywolanie standardowej obslugi zdarzen szablonu

    //*******************************************************************************
    // tu mo¿na umieciæ kod obs³uguj¹cy wciniêcie klawisza klawiatury, przyk³adowo:

    switch (key) {
        case 'e':
            glEnable(GL_FOG);
            break;
        case 'd':
            glDisable(GL_FOG);
            break;

        case 'n':
            rysujLawke = false;
            break;
        case 'r':
            rysujLawke = true;
            break;

        case 'p':
            lawkaPredkosc += 0.04;
            break;
        case 'o':
            lawkaPredkosc -= 0.04;
            break;


    }


}


void KlawiszSpecjalnyWcisniety(GLint key, int x, int y) {

    //*******************************************************************************
    // tu mo¿na umieciæ kod obs³uguj¹cy wciniêcie specjalnego klawisza klawiatury, przyk³adowo:

    switch (key) {
        case GLUT_KEY_LEFT:

            break;
        case GLUT_KEY_RIGHT:

            break;
        case GLUT_KEY_UP:
            kameraY++;
            break;
        case GLUT_KEY_DOWN:
            kameraY--;
            break;

    }


}


/******************************************************/
void rozmiar(int width, int height) {
    if (width == 0) width++;
    if (width == 0) width++;
    if (stereoTryb != 2) {
        oknoSzerkosc = width;   // przy stereo nie mo¿na zmieniaæ rozmiaru
        oknoWysokosc = height;
    }
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glViewport(0, 0, oknoSzerkosc, oknoWysokosc + 24);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0f, (GLfloat) oknoSzerkosc / (GLfloat) oknoWysokosc, 1.0f, 10000.0f);
    glMatrixMode(GL_MODELVIEW);

}

struct model_w_skladzie {
    char *filename;
    model3DS *model;
    struct model_w_skladzie *wsk;
};

struct model_w_skladzie *sklad_modeli = NULL;

void dodajModel(model3DS *_model, char *file_name) {
    struct model_w_skladzie *tmp;
    tmp = (struct model_w_skladzie *) malloc(sizeof(struct model_w_skladzie));
    tmp->filename = (char *) malloc(strlen(file_name) + 1);
    strcpy(tmp->filename, file_name);
    tmp->model = _model;
    tmp->wsk = sklad_modeli;
    sklad_modeli = tmp;
}

model3DS *pobierzModel(char *file_name) {
    struct model_w_skladzie *sklad_tmp = sklad_modeli;
    while (sklad_tmp) {
        if (!_stricmp(sklad_tmp->filename, file_name)) return sklad_tmp->model;
        char file_name_full[_MAX_PATH];
        strcpy(file_name_full, file_name);
        strcat(file_name_full, ".3ds");
        if (!_stricmp(sklad_tmp->filename, file_name_full)) return sklad_tmp->model;

        sklad_tmp = sklad_tmp->wsk;
    }
    return NULL;
}

void rysujModel(char *file_name, int tex_num = -1) {
    model3DS *model_tmp;
    if (model_tmp = pobierzModel(file_name))
        if (tex_num == -1)
            model_tmp->draw();
        else
            model_tmp->draw(tex_num, false);

}

void aktywujSpecjalneRenderowanieModelu(char *file_name, int spec_id = 0) {
    model3DS *model_tmp;
    if (model_tmp = pobierzModel(file_name))
        model_tmp->setSpecialTransform(spec_id);
}

void ladujModele() {
    WIN32_FIND_DATA *fd;
    HANDLE fh;
    model3DS *model_tmp;
    char directory[_MAX_PATH];
    if (_getcwd(directory, _MAX_PATH) == NULL) return;
    strcat(directory, "\\data\\*.3ds");

    fd = (WIN32_FIND_DATA *) malloc(sizeof(WIN32_FIND_DATA));
    fh = FindFirstFile((LPCSTR) directory, fd);
    if (fh != INVALID_HANDLE_VALUE)
        do {
            if (fd->dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {    // katalogi ignorujemy
                if (FindNextFile(fh, fd)) continue; else break;
            }
            // ladowanie obiektu i dodanie do kontenera
            char filename[_MAX_PATH];
            strcpy(filename, "data\\");
            strcat(filename, fd->cFileName);
            model_tmp = new model3DS(filename, 1, stereoTryb == 2);
            dodajModel(model_tmp, fd->cFileName);
            printf("[3DS] Model '%s' stored\n", fd->cFileName);
        } while (FindNextFile(fh, fd));
}

void windowInit() {

    animacjaSlonca = 150;
    glViewport(0, 0, oknoSzerkosc, oknoWysokosc); // O

    glClearColor(0.2, 0.2, 1.0, 0.0);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_DEPTH_TEST);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);


    obiekt = gluNewQuadric();
    gluQuadricOrientation(obiekt, GLU_OUTSIDE);
    //gluobiektDrawStyle (obiekt, GLU_FILL);

    glLightModelf(GL_LIGHT_MODEL_TWO_SIDE, 1);



    /*******************!SZABLON!**************************/


}

/** ZARZADANIE SKLADEM MODELI 3DS **/


void slonce() {
    GLfloat ambientLight0[4];
    GLfloat diffuseLight0[4];
    GLfloat specular0[4];
    GLfloat lightPos0[4];


    double intensity = cos((float) animacjaSlonca / 100 / mnoznik);
    double sunIntensity = std::max(intensity, 0.00);


    ambientLight0[0] = 0.3f * sunIntensity;
    ambientLight0[1] = 0.3f * sunIntensity;
    ambientLight0[2] = 0.3f * sunIntensity;
    ambientLight0[3] = 1.0f;

    double redIntensity = sunIntensity;

    if (sunIntensity < 0.8) {
        redIntensity = 1 - 2 * abs(std::min(intensity, 0.00));
    }
//    std::cout << "red";
//    std::cout << redIntensity;
//    std::cout << "\n";
    diffuseLight0[0] = 1.0f * redIntensity;
    diffuseLight0[1] = 1.0f * sunIntensity;
    diffuseLight0[2] = 1.0f * sunIntensity;
    diffuseLight0[3] = 1.0f;

    specular0[0] = 0.4f;
    specular0[1] = 1.0f;
    specular0[2] = 0.4f;
    specular0[3] = 1.0f;

    lightPos0[0] = slonceX;
    lightPos0[1] = slonceY;
    lightPos0[2] = slonceZ;
    lightPos0[3] = 1.0f;


//    glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight0);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight0);
//    glLightfv(GL_LIGHT0, GL_SPECULAR, specular0);
    glLightfv(GL_LIGHT0, GL_POSITION, lightPos0);
    glEnable(GL_LIGHT0);

}


void latarnia() {

    GLfloat ambientLight1[4];
    GLfloat diffuseLight1[4];
    GLfloat spotDirectionLight1[4];

    GLfloat specular1[4];
    GLfloat lightPos1[4];

    ambientLight1[0] = 0.0f;
    ambientLight1[1] = 0.0f;
    ambientLight1[2] = 0.0f;
    ambientLight1[3] = 1.0f;

    double intensity = cos((float) animacjaSlonca / 100 / mnoznik);
    double lampIntensity = 0;
    if (intensity < 0.2) {
        lampIntensity = 1;
    }
    diffuseLight1[0] = 2.0f * lampIntensity;
    diffuseLight1[1] = 2.0f * lampIntensity;
    diffuseLight1[2] = 1.6f * lampIntensity;
    diffuseLight1[3] = 1.0f;

    specular1[0] = 0.4f * lampIntensity;
    specular1[1] = 1.0f * lampIntensity;
    specular1[2] = 0.4f * lampIntensity;
    specular1[3] = 1.0f;

    lightPos1[0] = -20.0f;
    lightPos1[1] = 30.0f;
    lightPos1[2] = 120.0f;
    lightPos1[3] = 1.0f;

    spotDirectionLight1[0] = 0.0f;
    spotDirectionLight1[1] = -90.0f;
    spotDirectionLight1[2] = 0.0f;
    spotDirectionLight1[3] = 1.0f;

    glLightfv(GL_LIGHT1, GL_AMBIENT, ambientLight1);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, diffuseLight1);
    glLightfv(GL_LIGHT1, GL_SPECULAR, specular1);
    glLightfv(GL_LIGHT1, GL_POSITION, lightPos1);
    glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, 60.0);
    glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, 50.0);
    glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, spotDirectionLight1);

    glEnable(GL_LIGHT1);
}


void latarnia2() {

    GLfloat ambientLight1[4];
    GLfloat diffuseLight1[4];
    GLfloat spotDirectionLight1[4];

    GLfloat specular1[4];
    GLfloat lightPos1[4];

    ambientLight1[0] = 0.0f;
    ambientLight1[1] = 0.0f;
    ambientLight1[2] = 0.0f;
    ambientLight1[3] = 1.0f;

    double intensity = cos((float) animacjaSlonca / 100 / mnoznik);
    double lampIntensity = 0;
    if (intensity < 0.2) {
        lampIntensity = 1;
    }
    diffuseLight1[0] = 2.0f * lampIntensity;
    diffuseLight1[1] = 2.0f * lampIntensity;
    diffuseLight1[2] = 1.6f * lampIntensity;
    diffuseLight1[3] = 1.0f;

    specular1[0] = 0.4f * lampIntensity;
    specular1[1] = 1.0f * lampIntensity;
    specular1[2] = 0.4f * lampIntensity;
    specular1[3] = 1.0f;

    lightPos1[0] = -20.0f;
    lightPos1[1] = 30.0f;
    lightPos1[2] = -120.0f;
    lightPos1[3] = 1.0f;

    spotDirectionLight1[0] = 0.0f;
    spotDirectionLight1[1] = -90.0f;
    spotDirectionLight1[2] = 0.0f;
    spotDirectionLight1[3] = 1.0f;

    glLightfv(GL_LIGHT2, GL_AMBIENT, ambientLight1);
    glLightfv(GL_LIGHT2, GL_DIFFUSE, diffuseLight1);
    glLightfv(GL_LIGHT2, GL_SPECULAR, specular1);
    glLightfv(GL_LIGHT2, GL_POSITION, lightPos1);
    glLightf(GL_LIGHT2, GL_SPOT_CUTOFF, 60.0);
    glLightf(GL_LIGHT2, GL_SPOT_EXPONENT, 50.0);
    glLightfv(GL_LIGHT2, GL_SPOT_DIRECTION, spotDirectionLight1);

    glEnable(GL_LIGHT2);
}


void mglafunc() {
    double intensity = cos((float) animacjaSlonca / 100 / mnoznik);

    float fogColor[4] = {0.8f, 0.8f, 0.8f, 0.1f};
    glFogi(GL_FOG_MODE, GL_EXP2); // [GL_EXP, GL_EXP2, GL_LINEAR ]
    glFogfv(GL_FOG_COLOR, fogColor);
    glFogf(GL_FOG_DENSITY, 0.005f * intensity);
    glFogf(GL_FOG_START, 250.0f);
    glFogf(GL_FOG_END, 300.0f);
    glEnable(GL_FOG);

}

void sunLensFlare() {


    //Sprawdzanie czy słonce jest na ekranie
    GLdouble projection[16];
    GLdouble modelView[16];
    GLint viewport[4];

    glGetDoublev(GL_MODELVIEW_MATRIX, modelView);
    glGetDoublev(GL_PROJECTION_MATRIX, projection);
    glGetIntegerv(GL_VIEWPORT, viewport);

    GLdouble screenX, screenY, screenZ;
    gluProject(slonceX, slonceY, slonceZ,
               modelView, projection, viewport,
               &screenX, &screenY, &screenZ);

    boolean drawFlares = false;

    if (screenX > 0 && screenX < oknoSzerkosc && screenY > 0 && screenY < oknoWysokosc && slonceY > 160) {
        drawFlares = true;
    }

    //Rysowanie flar

    if (drawFlares) {

        float no_mat[] = {0.0f, 0.0f, 0.0f, 1.0f};
        float mat_ambient_color[] = {0.8f, 0.8f, 0.2f, 1.0f};
        float no_shininess = 0.0f;
        float mat_emission[7][4] = {{0.3f, 0.2f,  0.2f, 0.0f},
                                    {0.3f, 0.05f, 0.0f, 0.0f},
                                    {0.4f, 0.1f,  0.5f, 0.0f},
                                    {0.3f, 0.2f,  0.2f, 0.0f},
                                    {0.5f, 0.6f,  0.2f, 0.0f},
                                    {0.3f, 0.2f,  0.2f, 0.0f},
                                    {0.8f, 0.2f,  0.2f, 0.0f}};

        float sizes[7] = {0.8f, 1.0f, 1.0f, 1.0f, 1.0f, 2.0f, 2.2f};


        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_COLOR, GL_ONE); //to calkiem dobre
//    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
//    glBlendFunc(GL_ONE, GL_ONE);
//    glBlendFunc(GL_SRC_ALPHA, GL_DST_ALPHA);
//    glBlendFunc(GL_SRC_COLOR, GL_DST_COLOR);
        //glBlendFunc(GL_ONE, GL_ONE);
        // pierwszy parametr:GL_ZERO, GL_ONE, GL_DST_COLOR, GL_ONE_MINUS_DST_COLOR, GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_DST_ALPHA, GL_ONE_MINUS_DST_ALPHA, GL_SRC_ALPHA_SATURATE.
        // drugi parametr:GL_ZERO, GL_ONE, GL_SRC_COLOR, GL_ONE_MINUS_SRC_COLOR, GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_DST_ALPHA, GL_ONE_MINUS_DST_ALPHA

        GLfloat odleglosc = 3;
        GLfloat centerX = kameraX + sin(kameraKat) * odleglosc;
        GLfloat centerY = kameraY;
        GLfloat centerZ = kameraZ - cos(kameraKat) * odleglosc;

        GLfloat vectorX = slonceX - centerX;
        GLfloat vectorY = slonceY - centerY;
        GLfloat vectorZ = slonceZ - centerZ;
        GLfloat flareX = 0;
        GLfloat flareZ = 0;
        GLfloat flareY = 0;


        for (int i = 0; i < 7; i++) {

            flareX = centerX + 0.002 * i * i * vectorX - 0.0015 * vectorX;
            flareY = centerY + 0.002 * i * i * vectorY - 0.0015 * vectorY;
            flareZ = centerZ + 0.002 * i * i * vectorZ - 0.0015 * vectorZ;

            glPushMatrix();
            glTranslatef(flareX, flareY, flareZ);
            glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient_color);
            glMaterialfv(GL_FRONT, GL_DIFFUSE, no_mat);
            glMaterialfv(GL_FRONT, GL_SPECULAR, no_mat);
            glMaterialf(GL_FRONT, GL_SHININESS, no_shininess);
            glMaterialfv(GL_FRONT, GL_EMISSION, mat_emission[i]);
            gluSphere(obiekt, sizes[i], 16, 16);


            glPopMatrix();
        }


        glDisable(GL_BLEND);
    }

}


void config() {
    oknoFullScreen = false;


    ustalObszar(500);
    rejestrujPrzeszkode(-200, -200, -147, 200);    // lewy brzeg
    rejestrujPrzeszkode(132, -200, 200, 200);        // prawy  brzeg
    rejestrujPrzeszkode(-200, -130, 200, -200);    // przedni brzeg
    rejestrujPrzeszkode(-200, 157, 200, 200);        // tylny brzeg
    rejestrujPrzeszkode(-101, -90, -26, 200);        // lewa wyspa
    rejestrujPrzeszkode(13, -200, 90, 132);        // prawa wyspa


}

/**********************************************************
 		RYSOWANIE TRESCI RAMKI
 *********************************************************/


void draw() {

    float no_mat[] = {0.0f, 0.0f, 0.0f, 1.0f};
    float mat_ambient_color[] = {0.8f, 0.8f, 0.2f, 1.0f};
    float no_shininess = 0.0f;
    float mat_emission[] = {1.0f, 1.0f, 0.2f, 0.0f};

    glPushMatrix();
    glTranslatef(0, 1, 0);
    rysujModel("teren");
    rysujModel("niebo");


    glPushMatrix();
    glTranslatef(10, -8, -43);
    glRotatef(-42, 0, 1, 0);
    rysujModel("lawka");

    glPopMatrix();


    glPushMatrix();
    glTranslatef(-25, -7, 120);
    glRotatef(90, 0, 1, 0);
    rysujModel("latarnia");
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-25, -7, -120);
    glRotatef(90, 0, 1, 0);
    rysujModel("latarnia");
    glPopMatrix();


    glPushMatrix();
    glTranslatef(120, -5.5, -103);
    glRotatef(-86, 0, 1, 0);
    rysujModel("lawka");
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-149, 50, -133);
    glRotatef(-33, 0, 1, 0);
    rysujModel("most");
    glPopMatrix();


    //okrag obiegu slonca i ksiezyca
    float radius = 300;

    //obliczanie pozycji slonca i ksiezyca
    ksiezycX = -std::sin((float) animacjaSlonca / 100 / mnoznik) * radius;
    ksiezycY = -std::cos((float) animacjaSlonca / 100 / mnoznik) * radius;
    ksiezycZ = std::sin((float) animacjaSlonca / 100 / mnoznik) * radius;
    slonceX = std::sin((float) animacjaSlonca / 100 / mnoznik) * radius;
    slonceY = std::cos((float) animacjaSlonca / 100 / mnoznik) * radius;
    slonceZ = std::sin((float) animacjaSlonca / 100 / mnoznik) * radius;

    glPushMatrix();
    if (sunAnimation)
        animacjaSlonca = ((++animacjaSlonca) % (int) (628 * mnoznik));



    GLfloat blue[4];

    blue[0] = 0.3f;
    blue[1] = 0.3f;
    blue[2] = 1.0f;
    blue[3] = 1.0f;


    GLfloat current[4];
    glGetFloatv(GL_AMBIENT, current);

    glTranslatef(slonceX, slonceY, slonceZ);
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient_color);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, no_mat);
    glMaterialfv(GL_FRONT, GL_SPECULAR, no_mat);
    glMaterialf(GL_FRONT, GL_SHININESS, no_shininess);
    glMaterialfv(GL_FRONT, GL_EMISSION, mat_emission);
    gluSphere(obiekt, 10, 50, 50);

    glGetDoublev(GL_MODELVIEW_MATRIX, slonceProjection);

    glPopMatrix();

    glPushMatrix();

    glTranslatef(ksiezycX, ksiezycY, ksiezycZ);
    glColor3f(0, 0, 1);
    float mat_emission2[4] = {0.7f, 0.6f, 0.8f, 0.0f};

    glMaterialfv(GL_FRONT, GL_EMISSION, mat_emission2);

    gluSphere(obiekt, 6, 50, 50);
    glPopMatrix();
    glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);


    glEnable(GL_LIGHTING);

    //rysowanie slonnca ksiezyca i swiatla latarni

    slonce();


    latarnia();
    latarnia2();
//    mglafunc();

    for (int a = 0; a < 12; a++) {
        glPushMatrix();
        glTranslatef(drzewa1[a][0], drzewa1[a][1], drzewa1[a][2]);
        glRotatef(drzewa1[a][3], 0, 1, 0);
        rysujModel("drzewo1");
        glPopMatrix();

    }

    sunLensFlare();


    glPushMatrix();
    glEnable(GL_BLEND);
    glDepthMask(GL_FALSE);
    glBlendFunc(GL_SRC_COLOR, GL_ONE_MINUS_SRC_COLOR);
    GLfloat mat1[4] = {0.5, 0.4, 0.7, 1};
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat1);
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat1);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat1);
    glTranslatef(105, -6.7, -103);
    rysujModel("woda");
    glDepthMask(GL_TRUE);
    glDisable(GL_BLEND);
    glPopMatrix();
    glPopMatrix();


}

void rysujRamke() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Kasowanie ekranu
    glLoadIdentity();

    gluLookAt(kameraX, kameraY, kameraZ, kameraX + 100 * sin(kameraKat), 3 + kameraPunktY,
              kameraZ - 100 * cos(kameraKat), 0, 1, 0); // kamera


    draw();
    glFlush();

}


void rysuj() {
    rysujRamke();
    glutSwapBuffers();
}


void timer() {
    double kameraXTmp = kameraX + kameraPredkosc * sin(kameraKat);
    double kameraZTmp = kameraZ - kameraPredkosc * cos(kameraKat);
    kameraKat = kameraKat + kameraPredkoscObrotu;
    kameraPunktY = kameraPunktY + kameraPredkoscPunktY;
    if (wObszarze(kameraXTmp, kameraZTmp)) {
        kameraX = kameraXTmp;
        kameraZ = kameraZTmp;
    } else
        kameraPredkosc = 0;
    rysuj();
}

void syncTimer(int ID) {
    timer();
    glutTimerFunc(1, syncTimer, 10);
}

int main(int argc, char **argv) {
    config();
    if (argc > 1 && argv[1][0] == '-' &&
        argv[1][1] == 's')    // poprawki w konfiguracji na podstawie parametró (te maj¹ pierwszeñstwo)
    {
        stereoTryb = 2;
        oknoSzerkosc = 800;
        oknoWysokosc = 600;
    }
    glutInit(&argc, argv);        // INIT - wszystkie funkcje obs³ugi okna i przetwzrzania zdarzeñ realizuje GLUT
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    // jedno okno
    glutInitWindowSize(oknoSzerkosc, oknoWysokosc);
    glutInitWindowPosition(0, 0);
    oknoLewe = glutCreateWindow("Szablon");


    glutReshapeFunc(rozmiar);                        // def. obs³ugi zdarzenia resize (GLUT)
    glutKeyboardFunc(KlawiszKlawiaturyWcisniety);        // def. obs³ugi klawiatury
    glutSpecialFunc(KlawiszSpecjalnyWcisniety);        // def. obs³ugi klawiatury (klawisze specjalne)
    glutMouseFunc(PrzyciskMyszyWcisniety);            // def. obs³ugi zdarzenia przycisku myszy (GLUT)
    glutMotionFunc(RuchKursoraMyszy);                    // def. obs³ugi zdarzenia ruchu myszy (GLUT)
    glutDisplayFunc(rysuj);                                // def. funkcji rysuj¹cej

    windowInit();

    glutTimerFunc(10, syncTimer, 10);
    resetKamery();
    //srand( (unsigned)time( NULL ) ); // generator liczb losowych
    ladujModele();
    aktywujSpecjalneRenderowanieModelu("woda", 1);
    aktywujSpecjalneRenderowanieModelu("most", 2);
    if (oknoFullScreen && stereoTryb != 2) glutFullScreen();
    glutMainLoop();
    return (0);
}