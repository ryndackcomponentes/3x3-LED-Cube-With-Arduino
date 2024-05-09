//Matriz 3x9 com os niveis lógicos de cada led do cubo.

int estados[3][9];
const int niveis[3]={A0, A1, A2};
const int colunas[9]={2,3,4,5,6,7,8,9,10};
void setup(){                 
  
for(int i=0; i<3; i++){
    pinMode (niveis[i], OUTPUT);
  }

  for(int i=0; i<9; i++){
    pinMode (colunas[i], OUTPUT);
  }
}                  

void loop(){
  acende_limpa_cubo(0);         
  envia_estados(estados, 2);

  for(int n=0; n<3; n++){                           //Loop para piscar todos os leds do cubo
    acende_limpa_cubo(1);
    envia_estados(estados, 2);
    delay(1000);
    acende_limpa_cubo(0);
    envia_estados(estados, 2);
    delay(1000);
  }

  seleciona_nivel(3);                               //Efeito de leds girando uma vez em cada nivel,
  gira_led(75, 15, 2);                              //alternando o sentido.
  seleciona_nivel(2);
  gira_led(75, 15, 1);
  seleciona_nivel(1);
  gira_led(75, 15, 2);

  acende_limpa_cubo(0);
  envia_estados(estados, 2);

  
  for(int n=0; n<300; n++){                          //Leds aleatórios piscando aleatóriamente.
    led_aleatorio(30,1);
    acende_limpa_cubo(0);
    envia_estados(estados, 2);
  }

  acende_limpa_cubo(0);
  envia_estados(estados, 2);
  delay(100);
  for(int n=0; n<100; n++){                          //Cubo acendendo 1 led por vez, de forma aleatória
    led_aleatorio(500,1);                            //até todos os leds serem acesos.
  }
  acende_limpa_cubo(1);
  for(int n=0; n<1000; n++){
    envia_estados(estados, 1);
  }

for(int n=0; n<100; n++){                            //Cubo apagando 1 led por vez.
    led_aleatorio(500,0);
    n++;
  }
  acende_limpa_cubo(0);
  envia_estados(estados, 2);
  delay(1000);

  acende_limpa_cubo(1);
  envia_estados(estados, 2);
  delay(1000);

  for(int nivel=0; nivel<4; nivel++){                //"planos" subindo e descendo.
    seleciona_nivel(nivel);
    delay(250);
  }
  seleciona_nivel(0);
  delay(250);
  for(int nivel=3; nivel>=0; nivel--){
    seleciona_nivel(nivel);
    delay(250);
    if(nivel==0){
      acende_limpa_cubo(0);
      envia_estados(estados, 2);
    }
  }
  for(int n=0; n<3; n++){                            //"planos" verticais se movendo para lateralmente.
    plano_vertical(n+4);
    envia_estados(estados,2);
    delay(250);
    acende_limpa_cubo(0);
    envia_estados(estados, 2);
  }
  delay(250);
  for(int n=0; n<3; n++){
    plano_vertical(6-n);
    envia_estados(estados,2);
    delay(250);
    acende_limpa_cubo(0);
    envia_estados(estados, 2);
  }
  for(int n=0; n<3; n++){                            //"planos" verticais se movendo para tras e para frente.
    plano_vertical(n+1);
    envia_estados(estados,2);
    delay(250);
    acende_limpa_cubo(0);
    envia_estados(estados, 2);
  }
  delay(250);
  for(int n=0; n<3; n++){
    plano_vertical(3-n);
    envia_estados(estados,2);
    delay(250);
    acende_limpa_cubo(0);
    envia_estados(estados, 2);
  }

  delay(750);
  for(int i=1; i<=3; i++){                             //Led aceso "caminhando" pelo cubo,
    for(int j=0; j<=8; j++){                           //ficando uma vez aceso a cada posição.
      seleciona_nivel(i);
      digitalWrite(colunas[j], HIGH);
      delay(1000);
      digitalWrite(colunas[j], LOW);
    }
  }
}

//Função seleciona o nível que sera controlado no cubo.
//Se o nivel selecionado for 0 nenhum nivel sera controlado.
//Se o nivel escolhido for 4 todos os niveis são controlados.
void seleciona_nivel(int nivel) {
    
    for (int i = 0; i < 3; ++i){
        digitalWrite(niveis[i], LOW);
    }    
    if (nivel >= 1 && nivel <= 4) {
        if (nivel != 4) {
            digitalWrite(niveis[nivel - 1], HIGH);
        }
        else {
          for (int i = 0; i < 3; ++i) {
              digitalWrite(niveis[i], HIGH);
          }
        }
    }
}

//Envia a matriz que representa os niveis dos led para o cubo.
//Pode realizar uma varredura nivel a nivel (varredura 1) ou 
//habilitar todos os niveis simultaneamente (varredura 2).
void envia_estados(int estados[3][9], int varredura){
  if(varredura==1){
    for(int i=0; i<=2; i++){
      for(int j=0; j<9; j++){
        digitalWrite(colunas[j], estados[i][j]);
        seleciona_nivel(i+1);
      }
    }
  }
  //Verifica o valor de "varredura".
  else if(varredura==2){
    //Envia para a saida os valores lógicos do nivel 0 da matriz "estados".
    for(int j=0; j<9; j++){
      digitalWrite(colunas[j], estados[0][j]);
    }
    seleciona_nivel(4);
  }
}

//Função torna alto ou baixo o nivel lógico de todos os leds do cubo.
void acende_limpa_cubo(int on_off){
  for(int i=0; i<4; i++){
    for(int j=0; j<9; j++){
      estados[i][j]=on_off;
    }
  }
}

//Acende ou apaga um led aleatório do cubo.
void led_aleatorio(int pausa, int on_off){
  estados[random(0,3)][random(0,9)]=on_off;  
  for(int tempo=0; tempo<pausa; tempo++){
    envia_estados(estados, 1);
  }
}

//Acende conjuntos de 3 colunas do cubo, formando planos.
void plano_vertical(int plano){
  if(plano>=1 && plano<=3){
    for(int i=0; i<3; i++){
      for(int j=(3*(plano-1)); j<(3*plano); j++){
        estados[i][j]=1;
      }
    }
  }
  else if(plano>=4 && plano <=6){
    for(int i=0; i<3; i++){
      for(int j=(plano-4); j<(plano+3); j+=3){
        estados[i][j]=1;
      }
    }
  }
}

//Função cria o efeito de leds girando em torno da coluna
//central. A quantidade de voltas pode ser inseria e o sentido
//de rotação pode ser horário ou anti-horário, sendo  para horário
//e 2 para anti-horário.
void gira_led(int pausa, int voltas, int sentido) {
    // Padrões de ligar/desligar dos LEDs para cada passo do movimento
    const int padrao_antihorario[4][9] = {
        {LOW, LOW, HIGH, LOW, HIGH, LOW, HIGH, LOW, LOW},
        {LOW, HIGH, LOW, LOW, HIGH, LOW, LOW, HIGH, LOW},
        {HIGH, LOW, LOW, LOW, HIGH, LOW, LOW, LOW, HIGH},
        {LOW, LOW, LOW, HIGH, HIGH, HIGH, LOW, LOW, LOW}
    };

    const int padrao_horario[4][9] = {
        {LOW, LOW, HIGH, LOW, HIGH, LOW, HIGH, LOW, LOW},
        {LOW, LOW, LOW, HIGH, HIGH, HIGH, LOW, LOW, LOW},
        {HIGH, LOW, LOW, LOW, HIGH, LOW, LOW, LOW, HIGH},
        {LOW, HIGH, LOW, LOW, HIGH, LOW, LOW, HIGH, LOW}
    };

    int (*padrao)[9]; // Ponteiro para o padrão de acordo com o sentido
    if (sentido == 1) {
        padrao = padrao_horario;
    } else {
        padrao = padrao_antihorario;
    }

    for (int i = 0; i < voltas; i++) {
        for (int j = 0; j < 4; j++) {
            // Define o estado dos LEDs de acordo com o padrão atual
            for (int k = 0; k < 9; k++) {
                digitalWrite(colunas[k], padrao[j][k]);
            }
            delay(pausa);
        }
    }
}
