#ifndef MYGL_H
#define MYGL_H

#include <string.h>

#include "core.h"
#include "frame_buffer.h"

// Declaração da função que chamará as funções implementadas pelo aluno
void MyGlDraw(void);

//
// >>> Declare aqui as funções que você implementar <<<
//

typedef struct ponto Ponto;
typedef struct cor Cor;


void PutPixel(Ponto ponto, Cor cor);
void DrawLine(Ponto inicial, Ponto final, Cor cor1, Cor cor2);
void drawTriangle(Ponto ponto1, Ponto ponto2, Ponto ponto3, Cor cor1, Cor cor2, Cor cor3);
#endif  // MYGL_H
