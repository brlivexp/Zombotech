 

 
 
 
/*
 * Fun��o Each:%0[%1]
 *
 * Est� fun��o � servida para declarar novas arrays que usaram foreach
 *
*/
 
#define Each:%0[%1] \
                                g_IPSinicio%0 = -1, g_IPSfim%0 = -1, g_IPScount%0 , %0[%1] = {-1, ...}
 
 
 
 
 
 
 
/*
*
* new Meach:array[x][y]
*
* Essa sintaxe serve para criar uma array multi-dimensional
*
*/
 
 
#define Meach:%0[%1][%2] \
                                g_IPSinicio%0[%1] = {-1, ...}, g_IPSfim%0[%1] = {-1, ...}, g_IPScount%0[%1] = {-1, ...}, %0[%1][%2]
 
 
 
 
 
 
 
 
/*
 * Fun��o each(%0->new %1)
 *
 * Est� fun��o � servida para listar todos elementos ativo do loop
 *
*/
 
 
#define each(%1->new%0) \
                                for( new %0  = g_IPSinicio%1; %0 ^ -1; %0 = %1[%0] )
 
 
 
 
 
 
 
/*
 * Fun��o eachex(%0->%1)
 *
 * Est� fun��o � servida para listar todos elementos ativo do loop
 * A diferen�a, � que n�o declara vari�vel!
*/
 
 
 
#define eachex(%1->%0) \
                                for( %0  = g_IPSinicio%1; %0 ^ -1; %0 = %1[%0] )
 
 
 
 
 
 
/*
 * Fun��o EachAdd(%0,%1)
 *
 * Est� fun��o � servida para ativar itens da array
 *
*/
 
 
#define EachAdd(%0,%1) \
            AdicionarElemento(%0, %1, g_IPSfim%0, g_IPSinicio%0, EachCount(%0))
 
 
 
 
 
 
/*
 * Fun��o EachRemove(%0,%1)
 *
 * Est� fun��o � para remover/desativar itens da array
 *
*/
 
 
#define EachRemove(%0,%1) \
            RemoverElemento(%0, %1, g_IPSfim%0, g_IPSinicio%0, EachCount(%0))
 
 
 
 
 
 
 
/*
 * Fun��o EachFree(%0)
 *
 * Est� fun��o limpa TODOS elementos da array, para o Each
 *
*/
 
 
 
#define EachFree(%0) \
                        LimparElementos(%0, g_IPSfim%0, g_IPSinicio%0, EachCount(%0))
 
 
 
 
 
 
/*
 * Fun��o EachRemove(%0,%1)
 *
 * Est� fun��o � para contar o n�mero de itens ativos na rray
 *
*/
 
 
#define EachCount(%0) \
            g_IPScount%0
 
 
 
 
 
 
/*
*
* IsActive (%1, %0)
*
* Checa se um elemento da array est� ativo
*
*/
 
 
#define IsActive(%1,%0) (!!(~%1[%0]) | (g_IPSfim%1 == %0))
 
 
 
 
 
/*
*
* RandomFromArray(array)
* Pega um elemento rand�nomico da array
*
*/
 
 
#define RandomFromArray(%0) \
            ElementoAleatorio(%0,  g_IPSinicio%0, EachCount(%0))
 
 
 
 
 
 
/*
 * Fun��es internas do script, respons�vel por desativar elementos na array
 *
 */
 
 
stock
        ElementoAleatorio(arr[], inicio, totalelementos) {
 
        static r, i ;
 
        r = random(totalelementos);
 
        for( i  = inicio; i ^ -1; i = arr[i] ) {
 
            if(!r) break;
 
            --r;
        }
 
        return i;
}
 
 
 
 
 
 
stock
        LimparElementos(arr[], &ultimoelemento, &primeiroelemento, &totalelementos, size = sizeof arr)
{
 
        for( new x = 0; x != size; x++) {
            arr[x] = -1;
        }
       
        ultimoelemento = -1;
        primeiroelemento = -1;
        totalelementos = 0;
       
        return true;
}
 
 
 
 
 
 
stock
 
        RemoverElemento(arr[], id, &ultimoelemento, &primeiroelemento, &totalelementos, size = sizeof arr)
{
 
        new origem = -1;
 
        if(~primeiroelemento) {
 
                if(id == primeiroelemento) {
 
                        if(ultimoelemento == id) ultimoelemento = -1;
 
                        primeiroelemento = arr[id];
                        arr[id] = -1;
                        --totalelementos;
                        return true;
                }
        }
        else {
                #if defined DEBUG
                printf("[Erro] Array vazia, imposs�vel deletar o elemento: %d", id);
                #endif
                return false;
        }
 
        for( new i; i ^ size; i++) {
                if(arr[i] == id) {
                        origem = i;
                        break;
                }
        }
 
 
 
        if(~origem) {
 
                if(~ultimoelemento) {
                        if(ultimoelemento == id) {
                                ultimoelemento = origem;
 
                        }
                }
 
                arr[origem] = arr[id];
                arr[id] = -1;
                --totalelementos;
                return true;
        }
        #if defined DEBUG
        printf("[Erro] Elemento %d n�o est� dispon�vel na array.", id);
        #endif
        return false;
 
}
 
 
 
 
 
 
stock
 
        AdicionarElemento(arr[], id, &ultimoelemento, &primeiroelemento, &totalelementos, size = sizeof arr)
{
 
        if(!arr[id]) {
                for(new x; x != size; x++) arr[x] = -1;
        }
 
        if(id >= size){
                #if defined DEBUG
                printf("[Erro] ID acessado inv�lido: %d com tamanho arr[%d]", id, size);
                #endif
                return false;
        }
 
        if(ultimoelemento == -1) {
 
                primeiroelemento = id;
                ultimoelemento = id;
        }
        else {
                if( primeiroelemento == id) {
                        #if defined DEBUG
                        printf("[Erro] O valor acesso j� existe na array: %d", id);
                        #endif
                        return false;
                }
                for( new i; i != size; i++) {
                        if(arr[i] == id) {
                                #if defined DEBUG
                                printf("[Erro] O valor acesso j� existe na array: %d", id);
                                #endif
                                return false;
                        }
                }
 
                arr[ultimoelemento] = id;
                ultimoelemento = id;
 
        }
 
        ++totalelementos;
 
        return true;
}


