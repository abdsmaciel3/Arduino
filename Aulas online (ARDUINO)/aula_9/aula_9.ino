#define ledR 2
#define ledG 3
#define ledB 4
#define botao 7

class Btn{
public:
  int btnclicado, btnliberado, pino;      //forma clássica
  Btn(int p){
    pino=p;
    btnclicado=btnliberado=0;
  }
  bool press(){
    if(digitalRead(pino)==HIGH){
      btnclicado=1;
      btnliberado=0;
    }else{
      btnliberado=1;
    }
    if ((btnclicado==1)and(btnliberado==1)){
      btnclicado=0;
      btnliberado=0;
      return true;
    }else{
      return false;
    }
  } 
};

class Cor{
public:
  int pinoR, pinoG, pinoB, ciclo, maximo;
  Cor(int pr, int pg, int pb):pinoR(pr),pinoG(pg),pinoB(pb){     //lista de inicialização
    ciclo=0;
    maximo=3;
  }
  void trocaLed(){
    if(ciclo==0){
      corLed(1,0,0);
    }
  }
private:              //definir a cor do led
  void corLed(int r, int g, int b){
    digitalWrite(pinoR,r);
    digitalWrite(pinoG,g);
    digitalWrite(pinoB,b);
    
  }
}
Btnn btn(botao);



void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:

}
