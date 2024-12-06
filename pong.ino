//https://www.makerhero.com/blog/controlando-um-display-oled-com-a-biblioteca-ssd1306/

#include <SPI.h>
#include <Wire.h>

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

const int ppj=A1;
const int ppa=A0;
const int LT=128;
const int AT=64;
const int AB=16;//altura barra: ver se é grande demais
const int R=2;
const int ptm=3;//alterar, por enquanto 3 é bom para testes
const float fa=1.1;//fator de aumento

Adafruit_SSD1306 display(LT, AT, &Wire, -1);

float abso(float n){
  if(n>=0){
    return n;
  }
  return n*(-1);
}

float dst(int x1, int y1, int x2, int y2){
    float dx=abso(float(x1-x2));
    float dy=abso(float(y1-y2));
    return sqrt(dx*dx+dy*dy);
}
int prev(int bx, int by, int bvx, int bvy){
    
}


void setup(){
    display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
    display.clearDisplay();
    //tela
    pinMode(ppj, INPUT);
    pinMode(ppa, INPUT);
}

void loop(){
    int hj=0;//altura jogador
    int ha=0;//altura adversario
    int ptj=0;
    int pta=0;
    int qc=1;//fazer aleatório
    //bola
    int bvx=2*qc;//em px/s
    int bvy=2;//multiplicar ambos por 1 ou -1
      comeco:
    int bx=LT/2;
    int by=AT/2;
    int br=R;
    
//fazer telinha/já fiz:apagar comen´tarios desnecessários
    while(ptj<ptm&&pta<ptm){
        
        hj=map(analogRead(ppj), 0, 1023, 0, AT-AB);//lado do jogador é o direito
        ha=map(analogRead(ppa), 0, 1023, 0, AT-AB);//lado do adversário éo esquerdo
        
        display.clearDisplay();
        display.setTextSize(1);
        display.setTextColor(WHITE);
        display.setCursor(16, 0);
        display.print(ptj);
        display.setCursor(111, 0);
        display.print(pta);
        //display.print("versfstfgs\nriotejo\ngrouchomarx");
        display.drawLine(3, hj, 3, hj+AB, WHITE);
        display.drawLine(124, ha, 124, ha+AB, WHITE);
        display.fillCircle(bx, by, br, WHITE);
        display.display();
        bx+=bvx;
        by+=bvy;
    //teto ou chão
        if(by<=br||by>=AT-br){//pus >=
            by*=-1;
        }
        //raquete
        for(int i=hj; i<hj+AB; i++){
            if(dst(bx, by, 3, i)<=float(br)){//testar?
                bvx*=-1;
                if(i==(hj+AB)/2){
                  //y nao muda
                }else if(i>(hj+AB)/2){
                    bvx=int(float(bvx)*fa);
                    bvy=abs(bvy);
                }else{
                    bvx=int(float(bvx)*fa);
                    bvy=abs(bvy*(-1));
                }
            }
        }
        for(int i=ha; i<ha+AB; i++){
            if(dst(bx, by, 124, i)<=float(br)){//testar?
                bvx*=-1;
                if(i==(ha+AB)/2){
                  //y nao muda
                }else if(i>(ha+AB)/2){
                    bvx=int(float(bvx)*fa);
                    bvy=abs(bvy);
                }else{
                    bvx=int(float(bvx)*fa);
                    bvy=abs(bvy*(-1));
                }
            }
        }
        //paredes
        if(bx<=br){
            ptj+=1;
            int bx=LT/2;
            int by=AT/2;
            int bvx=abs(bvx);
            goto comeco;
        }
        if(bx>=LT-br){
            pta+=1;
            int bx=LT/2;
            int by=AT/2;
            int bvx=abs(bvx)*(-1);
            goto comeco;
        }
        delay(100);
    }
    display.clearDisplay();
    display.setTextSize(1);//testar e voltar para 2
    display.setCursor(32, 63);
    if(ptj>=ptm){
    display.print("Jogador 1 ganhou");
    }else if(pta>=ptm){
    display.print("Jogador 2 ganhou");
    }
    delay(10000);
}