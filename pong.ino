const int ppj=A1;//tentar fazer com que os pinossejam diferentes dos da tela
const int ppa=A0;
const int LT=128;
const int AT=64;
const int AB=16;//altura barra: ver se é grande demais
const int R=2;

struct vetor{
    int vx;
    int vy;
};
struct bola{
    int x;
    int y;
    int r;
    vetor v;
};

int rq(int x){
    int n=0;
    for(int i=0; i<x; i++){
        if(i*i==x){
            return i;
        }else if(abs(x-i*i)<abs(x-n*n)){
            n=i;
        }
    }
    return n;
}

int abs(int x){
    if x>=0{
        return x;
    }
    return x*-1;
}
int dst(int x1, int y1, int x2, int y2){
    dx=abs(x1-x2);
    dy=abs(y1-y2);
    return rq(dx*dx+dy*dy);
}


void setup(){
    //tela
    pinMode(ppj, INPUT);
    pinMode(ppa, INPUT);
    bola b;
    b.x=LT/2;
    b.y=AT/2;
    b.r=R;
    b.v.vx=10;//em px/s
    b.v.vy=2;//multiplicar ambos por 1 ou -1
    int hj=0;//altura jogador
    int ha=0;
    int ptj=0;
    int pta=0;
}

void loop(){
    comeco:
//fazer telinha
    hj=map(analogRead(ppj), 0, 0, 1023, AT-AB);//lado do jogador é o direito
    ha=map(analogRead(ppa), 0, 0, 1023, AT-AB);//lado do adversário éo esquerdo
    qc=1;
    b.x=LT/2;
    b.y=AT/2;
    b.r=R;
    b.v.vx=10*qc;//em px/s
    b.v.vy=2;//multiplicar ambos por 1 ou -1
    b.x+=b.v.vx;
    b.y+=b.v.vy;
    //teto ou chão
        if(b.y<b.r||b.y>AT-b.r){
            b.y*=-1;
        }
        //paredes
        if(b.x<b.r){
            ptj++;
            goto comeco;
        }
        if(b.x>LT-b.r){
            pta++;
            goto comeco;
        }
        for(int i=hj; i<hj+AB; i++){
            if(dst(b.x, b.y, 0, i)<b.r){//testar?
                b.v.vx*=-1;
                if(i==(hj+AB)/2){
                }else if(i>(hj+AB)/2){
                    b.v.vx*=3;
                    b.v.vx/=2;
                    b.v.vy=abs(b.v.vy);
                }else{
                    b.v.vx*=3;
                    b.v.vx/=2;
                    b.v.vy=abs(b.v.vy)+-1;
                }
            }
        }
        delay(500);
}