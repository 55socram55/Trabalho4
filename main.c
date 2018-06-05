#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

struct elem{
    char iden;
    char cod[7];
    int comb;
    struct elem *prox;
};

typedef struct elem Lista;

struct fila{
     
    Lista *ini;
    Lista *fim;
    
};

typedef struct fila Fila;

Lista *insere(Lista *L,char cod[7],int comb, char ident);
Lista *gerarFila(int n, int c);
Fila *preencherFila(Lista *L);
void remover(Fila *F);
int detectarEmergencia(Fila *F);
void diminuirComb(Fila *F);
void simular(Fila *aprox, Fila *deco);

int main()
{
    
   srand(time(NULL));
  int na = rand()%23;
  na+=10;
  int nd = rand()%23;
 nd+=10;


  
  
  Lista *taprox;
  Lista *tdeco;
  Lista *aux;
   
  
  
  taprox = gerarFila(na,0);
  tdeco = gerarFila(nd,1);
  
  Fila *aprox;
  Fila *deco;
  aprox = preencherFila(taprox);
  deco = preencherFila(tdeco);

printf("----------------------------------------------\n");
printf("\"Aeroporto Internacional de Brasilia\"\n");
printf("Hora inicial: 12:00\n");
printf("Fila de pedidos: %s - P - %d\n",aprox->ini->cod,aprox->ini->comb);
printf("NVoos: %d\nNaproximacoes: %d\nNdecolagens: %d\n",na+nd,na,nd);
printf("----------------------------------------------\n");
 
 printf("Listagem de eventos:\n");


 simular(aprox,deco);
  
  

    
	return 0;
}
Lista *insere(Lista *L,char cod[7],int comb, char ident){
    
    Lista *elem;
    Lista *aux;
    
    elem = (Lista*)malloc(sizeof(Lista));
    strncpy(elem->cod,cod,sizeof(elem->cod)-1);
    elem->cod[6] = '\0';
    elem->comb = comb;
    elem->iden = ident;
    
    
    if(L==NULL){
        
        elem->prox = NULL;
        return elem;
        
        }
    
    if(comb == -1){
        
      for(aux=L;aux!=NULL;aux=aux->prox){
             
             if(aux->prox==NULL){
                 
                    aux->prox = elem; 
                    elem->prox = NULL;
                    return L;
                 
                 }
          }  
        
    }
    
    if(elem->comb < L->comb){
        
       elem->prox = L;        
       return elem;    
    
    }

            
    for(aux=L;aux!=NULL;aux=aux->prox){
        
        if(aux->prox==NULL){
                
               aux->prox = elem;
               elem->prox = NULL;
               return L;
             
        }  
        
        if((aux->prox)->comb > elem->comb){
               
                elem->prox = aux->prox;
                aux->prox = elem;
                return L;
            
            }
            
    }
    
    return NULL;
}

Lista *gerarFila(int n, int c){

    int i,comb;
    Lista *L;
    L = NULL;
    
    char *codigos[] = {"VG3001",
    "JJ4404", "LN7001", "TG1501", "GL7602", "TT1010", "AZ1009", "AZ1008",
    "AZ1010", "TG1506", "VG3002", "JJ4402", "GL7603", "RL7880", "AL0012",
    "TT4544", "TG1505", "VG3003", "JJ4403", "JJ4401", "LN7002", "AZ1002",
    "AZ1007", "GL7604", "AZ1006", "TG1503", "AZ1003", "JJ4403", "AZ1001",
    "LN7003", "AZ1004", "TG1504", "AZ1005", "TG1502", "GL7601", "TT4500", 
    "RL7801", "JJ4410", "GL7607", "AL0029", "VV3390", "VV3392", "GF4681", 
    "GF4690", "AZ1020", "JJ4435", "VG3010", "LF0920", "AZ1065", "LF0978", 
    "RL7867", "TT4502", "GL7645", "LF0932", "JJ4434", "TG1510", "TT1020", 
    "AZ1098", "BA2312", "VG3030", "BA2304", "KL5609", "KL5610", "KL5611"};
    
    if(c==0){
       for(i=0;i<n;i++){
             comb = rand()%13;
             L = insere(L,codigos[i],comb,'A');
           }
       return L; 
        
    }
    else{
        
       for(i=0;i<n;i++){
             L = insere(L,codigos[i+32],-1,'D');
           }
           
       return L;         
        
    }
    
    
}
Fila *preencherFila(Lista *L){
    
    Fila *F;
    Lista *aux;
    F = (Fila*)malloc(sizeof(Fila));
    F->ini = L;
    
    for(aux=L;aux!=NULL;aux=aux->prox){
          if(aux->prox==NULL){
              
               F->fim = aux;
               return F;
              
              }    
    
    }
    
    printf("Houve um erro");
    return NULL;
    
}

void remover(Fila *F){
    
   if(F->ini != NULL){
   
   Lista *temp = (F->ini)->prox;
   free(F->ini);
   F->ini = temp;
   
   }

}

int detectarEmergencia(Fila *F){
    
     if(F->ini==NULL){return 0;}
    
 
     int resultado = 0;
     int count = 0;
     Lista *aux;
     for(aux=F->ini;aux!=NULL;aux=aux->prox){
             
            if(aux->comb==0){
                  
                  count++;
                
                }
         
         }
      
     
     if(count>=3){resultado=1;}
     return resultado;
    
}

void diminuirComb(Fila *F){

    Lista *aux;
    for(aux=F->ini;aux!=NULL;aux=aux->prox){
        
        aux->comb  = aux->comb - 1; 
    
    }
    
}
void simular(Fila *aprox, Fila *deco){

    int hora = 12, min = 0,j=0,flg1=0,flg2=0,flg3=0,k=0;
    int h1=hora,h2=hora,h3=hora,m1=min,m2=min,m3=min,hd=hora,md=50;
    
    int i = 0;
    
    while(1){
        
        if(hora>hd ||(hora==hd && min >= md )){
              
        
         
           diminuirComb(aprox);
            
           md+=50;
           if(md>=60){md=md-60;hd++;}

            
        }
        
        if(detectarEmergencia(aprox)){printf("\nALERTA GERAL DE DESVIO DE AERONAVE\n");flg3=1;}
        
        //Pista 1
        if(j==0 || (hora>h1 ||(hora==h1 && min >=m1))){
            
           //pouso
           h1 = hora;
           m1 = min;
           
                      
            if(aprox->ini!=NULL && (flg1==0 || deco->ini==NULL || flg3==1 || aprox->ini->comb==0)){
                             
 
                printf("Codigo de voo: %s\nStatus: Aeronave Pousou\nHorario de inicio:%d:%.2d\nNumero da pista: 1\n\n"
                  ,aprox->ini->cod,hora,min);
                
                i++;
                
                
                              
                  remover(aprox);
                  m1+=20;
                  if(m1>=60){m1=m1-60;h1++;}

                  flg1 =1;                
                }
              //decolagem  
             else if((deco->ini)!=NULL || (deco->ini!=NULL && aprox->ini==NULL)){
            
                printf("Codigo de voo: %s\nStatus: Aeronave Decolou\nHorario de inicio:%d:%.2d\nNumero da pista: 1\n\n"
                  ,deco->ini->cod,hora,min);
                

                i++;
                              
                remover(deco);                 
                 
                 m1+=10;
                 if(m1>=60){m1=m1-60;h1++;}        
        
                 flg1 = 0;
        
             }
        
        
        }

        //Pista 2
        if(j==0 || (hora>h2 ||(hora==h2 && min >=m2))){
            
           //pouso
           h2 = hora;
           m2 = min;
           
            if(aprox->ini!=NULL && (flg2==0 || deco->ini==NULL || flg3==1 || aprox->ini->comb==0)){
                
                               
                printf("Codigo de voo: %s\nStatus: Aeronave Pousou\nHorario de inicio:%d:%.2d\nNumero da pista: 2\n\n"
                  ,aprox->ini->cod,hora,min);
                
                i++;
                              
                  remover(aprox);
                  m2+=20;
                  if(m2>=60){m2=m2-60;h2++;}

                  flg2 =1;                
                }
              //decolagem  
             else if((deco->ini)!=NULL || (deco->ini!=NULL && aprox->ini==NULL)){   
            
                printf("Codigo de voo: %s\nStatus: Aeronave Decolou\nHorario de inicio:%d:%.2d\nNumero da pista: 2\n\n"
                  ,deco->ini->cod,hora,min);

                i++;
                              
                remover(deco);                 
                 
                 m2+=10;
                 if(m2>=60){m2=m2-60;h2++;}        
        
                 flg2 = 0;
        
             }
        
        
        }


        //Pista 3
        
        if(j==0 || (hora>h3 ||(hora==h3 && min >=m3))){
            
           //Pouso emergencial
           h3 = hora;
           m3 = min;
           
            
            if(flg3==1){
            
                printf("Codigo de voo: %s\nStatus: Aeronave Pousou\nHorario de inicio:%d:%.2d\nNumero da pista: 3\n\n"
                  ,aprox->ini->cod,hora,min);

                i++;
                              
                remover(aprox);                 
                 
                 m3+=20;
                 if(m3>=60){m3=m3-60;h3++;}            
                 flg3=0;
           
            }
            else if((deco->ini)!=NULL){   
            
                printf("Codigo de voo: %s\nStatus: Aeronave Decolou\nHorario de inicio:%d:%.2d\nNumero da pista: 3\n\n"
                  ,deco->ini->cod,hora,min);
    
                i++;                
                              
                remover(deco);                 
                 
                 m3+=10;
                 if(m3>=60){m3=m3-60;h3++;}        
                
             }
             
        
        
        }else{
            
            if(flg3==1){
            
            
            printf("\nALERTA CRÍTICO, AERONAVE IRÁ CAIR\n");
            remover(aprox);
            flg3 = 0;
            
            }
            
        }
        
        k++;
        
        if(deco->ini==NULL && aprox->ini==NULL){break;}
    
        
        min += 5;
        if(min>=60){min=min-60;hora++;}
        j++;
       
    }
    
}
