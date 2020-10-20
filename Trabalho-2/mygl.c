#include "mygl.h"

//
// >>> Defina aqui as funções que você implementar <<<
//
struct ponto
{
    int x;
    int y;
};

struct cor
{
    float red;
    float blue;
    float green;
    float alpha;
};


void PutPixel(Ponto ponto, Cor cor){
    fb_ptr[4*((int)ponto.x) + 4*((int)ponto.y)*IMAGE_WIDTH + 0] = cor.red;
    fb_ptr[4*((int)ponto.x) + 4*((int)ponto.y)*IMAGE_WIDTH + 1] = cor.green;
    fb_ptr[4*((int)ponto.x) + 4*((int)ponto.y)*IMAGE_WIDTH + 2] = cor.blue;
    fb_ptr[4*((int)ponto.x) + 4*((int)ponto.y)*IMAGE_WIDTH + 3] = cor.alpha;
}

void DrawLine(Ponto inicial, Ponto final, Cor cor1, Cor cor2)
{
    int dx = final.x - inicial.x;
    int dy = final.y - inicial.y;
    int incremento_x = 1; //Variável para incremento no eixo do x 
    int incremento_y;     //Variável para incremento no eixo do y. Varia se y cresce ou decresce


    int absdx = dx; //Valor absoluto de dx
    int absdy = dy; //Valor absoluto de dy

    /*Caso os valores anteriores sejam negativos*/
    if (absdy < 0) 
        absdy = - dy;
    if (absdx < 0)
        absdx = -dx;

    int c; //tamanho do maior eixo
    if (absdx >= absdy)
        c = absdx;
    else 
        c = absdy;
      
    float acrescimosRed = (cor2.red - cor1.red)/c;
    float acrescimosGreen = (cor2.green - cor1.green)/c;
    float acrescimosBlue = (cor2.blue - cor1.blue)/c;
    float acrescimosAlpha = (cor2.alpha - cor1.alpha)/c; 

    if (dx == 0 || dy == 0) //Caso as linhas sejam horizontais ou verticais
    {
        int plus; 
        Ponto pontoAuxiliar = inicial;

        if(dy == 0){ //Reta horizontal
            if (dx < 0)
                plus = -1; //Da esquerda pra direita
            else
            {
                plus = 1; //Da direita pra esquerda
            }

            while(pontoAuxiliar.x != final.x)
            {
                PutPixel(pontoAuxiliar, cor1);
                (pontoAuxiliar.x)+= plus;
                cor1.red+=acrescimosRed;
                cor1.green+=acrescimosGreen;
                cor1.blue+=acrescimosBlue;
                cor1.alpha+=acrescimosAlpha;
            }
        }
        else //Reta vertical
        {
            if (dy < 0) //De cima pra baixo
                plus = -1;
            else //De baixo pra cima
                plus = 1;
            
            while(pontoAuxiliar.y != final.y)
            {
                PutPixel(pontoAuxiliar, cor1);
                (pontoAuxiliar.y) += plus;
                cor1.red+=acrescimosRed;
                cor1.green+=acrescimosGreen;
                cor1.blue+=acrescimosBlue;
                cor1.alpha+=acrescimosAlpha;
            }
        }
    
        return;
    }


    /*Para as linhas do quadrantes 3 a 6, desenhamos ao contrário para virar uma linha do quadrante oposto*/
    if (dx < 0)
    {
        DrawLine(final, inicial, cor2, cor1);
        return;
    }

    //se y está decrescendo, ao criar a linhas vamos diminuindo o valor de y do próximo pixel 
    if (dy < 0)
    {
        incremento_y = -1;
        dy = -dy;
    }
    else//caso contrário, aumentaremos
    {
        incremento_y = 1;
    }

    int D = 2*dy - dx;
    int incremento_NE = 2*(dy - dx);
    int incremento_L = 2*dy;
    

    Ponto aux = inicial;

    while(aux.x != final.x && aux.y != final.y) 
    {
        PutPixel(aux, cor1);
        cor1.red += acrescimosRed;
        cor1.green += acrescimosGreen;
        cor1.blue += acrescimosBlue;
        cor1.alpha += acrescimosAlpha;
        if(D > 0)
        {
            D += incremento_NE;
            (aux.y) += incremento_y;
            (aux.x) += incremento_x;
        } 
        else
        {
            
            D += incremento_L;
            if (absdx >= absdy) //se x for o maior eixo, andaremos(incrementaremos) só no x
                (aux.x) += incremento_x;
            else//caso contrário, andaremos(incrementaremos) só no y
            {
                (aux.y) += incremento_y;
            }
        }
    }
    PutPixel(aux, cor2);
}


/*Para desenhar um triangulo, ligamos os vértices */
void drawTriangle(Ponto ponto1, Ponto ponto2, Ponto ponto3, Cor cor1, Cor cor2, Cor cor3)
{
    DrawLine(ponto1, ponto2, cor1, cor2);
    DrawLine(ponto2, ponto3, cor2, cor3);
    DrawLine(ponto3, ponto1, cor3, cor1);
}

// Definição da função que chamará as funções implementadas pelo aluno
void MyGlDraw(void) {
    //
    // >>> Exemplos de testes <<<
    //
    Cor vermelho;
    vermelho.red = 255;
    vermelho.green = 0;
    vermelho.blue = 0;
    vermelho.alpha = 255;

    Cor verde;
    verde.red = 0;
    verde.green = 255;
    verde.blue = 0;
    verde.alpha = 255;

    Cor azul;
    azul.red = 0;
    azul.green = 0;
    azul.blue = 255;
    azul.alpha = 255;

    
    Ponto d;
    d.x = 0;
    d.y = 256;
    Ponto e;
    e.x = 511;
    e.y = 256;
    Ponto f;
    f.x = 256;
    f.y = 0;
    Ponto g;
    g.x = 256;
    g.y = 511;
    drawTriangle(d, e, f, verde, vermelho, azul);
    drawTriangle(d, e, g, verde, vermelho, azul);

    Ponto a, b, c;

    a.x = 256;
    a.y = 256;
    b.x = 0;
    b.y = 511;
    DrawLine(a, b, azul, verde);

    
    a.x = 256;
    a.y = 256;
    b.x = 0;
    b.y = 0;
    DrawLine(a, b, vermelho, verde);

    
    a.x = 256;
    a.y = 256;
    b.x = 511;
    b.y = 511;
    DrawLine(a, b, verde, vermelho);

    a.x = 256;
    a.y = 256;
    b.x = 511;
    b.y = 0;
    DrawLine(a, b, verde, vermelho);

    a.x = 256;
    a.y = 0;
    b.x = 256;
    b.y = 511;
    DrawLine(a, b, azul, verde);

    a.x = 350;
    a.y = 300; 
    PutPixel(a, vermelho);      

}
