/*
Contagem do relogio
Milena Freitas e Vanessa Cunha
18 de maio de 2021
versao 1.0
*/
#include <REGX52.H> //LIBRARY 8051
//variaveis
int seg=0;        // caractere segundo
int min=0;       // caractere minuto
int hora=12;    // caractere hora
int dia=1;    // caractere dia
int mes=1;    // caractere mes
int ano=21;  // caractere ano
char diaDaSemana; // caractere dia da semana
int contador=0;
int zeller=0;
int seculo;
int finaal;
//codigos display
unsigned char COD0;
unsigned char COD1;
unsigned char COD2;
unsigned char COD3;
unsigned char COD4;
unsigned char COD5;
unsigned char COD6;
unsigned char COD7;

//pin's display

sbit dsp1=P2^0;
sbit dsp2=P2^1;
sbit dsp3=P2^2;
sbit dsp4=P2^3;
sbit dsp0=P2^4;
sbit dsp5=P2^5;
sbit dsp6=P2^6;
sbit dsp7=P2^7;

//chaves
sbit 	chaveData=P3^0;
sbit 	chaveWeek=P3^1;
sbit 	chaveSeg=P3^2;
sbit 	chaveMin=P3^3;
sbit 	chaveHora=P3^4;
sbit 	chaveDia=P3^5;
sbit 	chaveMes=P3^6;
sbit 	chaveAno=P3^7;

//TABELA DE CÓDIGOS PARA O DISPLAY 0-9
unsigned char tabela[10]={0xC0, 0xF9, 0xA4, 0xB0, 0x99, 0x92, 0x82, 0xF8, 0x80, 0x90};

//**************VARREDURA DISPLAY**************************
extern void delay();     //delay externo 
void display(){
	if(dsp0==0){
		dsp0=1;             // dsp0 desligado
		P0=COD1;
		dsp1=0;            // dsp1 ligado 
	} else if(dsp1==0){
		dsp1=1;          // dsp1 desligado 
		P0=COD2;
		dsp2=0;         // dsp2 ligado
	} else if(dsp2==0){
		dsp2=1;        // dsp2 desligado 
		P0=COD3;
		dsp3=0;        // dsp3 ligado 
	} else if(dsp3==0){	
		dsp3=1;       // dsp3 desligado
		P0=COD4;
		dsp4=0;      // dsp4 ligado
	} else if(dsp4==0){
		dsp4=1;       // dsp4 desligado
		P0=COD5;
		dsp5=0;       // dsp5 ligado 
	} else if(dsp5==0){
		dsp5=1;       // dsp5 desligado 
		P0=COD6;
		dsp6=0;       // dsp6 ligado
	} else if(dsp6==0){
		dsp6=1;       // dsp6 desligado
		P0=COD7;
		dsp7=0;      // dsp7 ligado
 } else if(dsp7==0){
		dsp7=1;      // dsp7 desligado
		P0=COD0;
		dsp0=0;     // dsp0 ligado
	}
}
//*********************CONVERSÃO****************************
void conversao(){
	if(chaveData==1){          //mostra hora
		COD0=tabela[seg%10];    // resto da divisão
		COD1=tabela[seg/10];   // divisão
		COD2=0x7F;            // ponto
		COD3=tabela[min%10];   
		COD4=tabela[min/10];
		COD5=0x7F;             // ponto
		COD6=tabela[hora%10];
		COD7=tabela[hora/10];
	} else if(chaveData==0){  //mostra dataa
		COD0=tabela[ano%10];    // resto da divisão
		COD1=tabela[ano/10];   // divisão
		COD2=0xBF;            // traço
		COD3=tabela[mes%10];
		COD4=tabela[mes/10];
		COD5=0xBF;           // traço
		COD6=tabela[dia%10];
		COD7=tabela[dia/10];
	}
}
//****************CONTAGEM DATA/HORA*************************
void contaHora(){
	seg++; 			  		   //incremente seg
	if(seg==60){ 			  //verifica se já tem 60s
		seg=0;				   // se seg=60, zera o segundo
		min++;          //  incrementa o minuto depois que o seg zerar
	} else if(min==60){  // se o min = 60	
		min=0;            // zera min
		hora++;          // incrementa hora
	} else if(hora>24){ // se hora>24
		hora=0;          // zera hora
		dia++;          // incrementa dia 
	}
}
void mes31(){      
	if(dia>31){     // se dia>31, quer dizer que é dia 1° do próximo mês
		dia=1;       
		mes++;      // incrementa mês
	}
}
void mes30(){
	if(dia>30){  // se dia>30, quer dizer que é dia 1° do próximo mês
		dia=1;
		mes++;    // incrementa mês
	}
}
void fev(){
	if((ano/4)==0){   //ano bissexto
		if(dia>29){    // se dia>29
			dia=1;      // dia 1° do próximo mês
			mes++;     // incrementa mês
		}
	} else if(dia>28){  // se nã for bissexto, dia>29
		dia=1;           // dia 1° do próximo mês
		mes++;          // incrementa mês
	}
}
void mesDez(){         
	if(dia==31){      //ano acabou
		mes=1;         // mes 1
		dia=1;        //  dia 1°
		ano++;       // incrementa ano
		if(ano>99){ // se ano>99
			ano=0;   // zera ano
		}
	}
}
void contaData(){
	switch (mes){       // verifica tudo que é mês
		case 1:          //se mês for 1, ou seja, janeiro 
			mes31();      // executa mes31
			break;
		case 2:       //se mês for 2, ou seja, fevereiro
			fev();     // executa fev
			break;
		case 3:     //se mês for 3, ou seja, março
			mes31(); // executa mes31
			break;
		case 4:     //se mês for 4, ou seja, abril
			mes30(); // executa mes30
			break;
		case 5:     //se mês for 5, ou seja, maio
			mes31(); // executa mes31
			break;
		case 6:     //se mês for 6, ou seja, junho
			mes30(); // executa mes30
			break;
		case 7:     //se mês for 7, ou seja, julho
			mes31(); // executa mes31
			break;
		case 8:     //se mês for 8, ou seja, agosto
			mes31(); // executa mes31
			break;
		case 9:     //se mês for 9, ou seja, setembro
			mes30(); // executa mes30
			break;
		case 10:    //se mês for 10, ou seja, outubro
			mes31(); // executa mes31
			break;
		case 11:     //se mês for 11, ou seja, novembro
			mes30();  // executa mes30
			break;
		default:
			mesDez();  //executa mesDez
			break;
	}
}	
//*********************ZELLER***************************
void algoritimoSemana(){
	ano = ano%100;  		//ANO=21
	seculo=20;
	if(mes==1){			 		//janeiro
		mes=mes+12;  			//mes 13 do zeller
		ano=ano-1;
	} else if(mes==2){ 	//fevereiro
		mes=mes+12;				//mes14 do zeller
		ano=ano-1;
	} 
	if(mes==9){
		zeller=26; //(9+1)*26/10
	} else if(mes==10){
		zeller=28; //(10+1)*26/10
	} else if(mes==11){
		zeller=31; //(9+1)*26/10
	} else if(mes==12){
		zeller=33; //(9+1)*26/10
	} else{
	zeller=(mes+1)*26/10;
	}
	zeller=zeller+dia+ano+(ano/4)+(seculo/4);
	zeller=zeller+(seculo*5);
	zeller=zeller%7; //dia da semana 0-6
	if(mes==14){ //retorna mes para valor normal
		mes=2;
		ano=ano+1;
	} if(mes==13){
		mes=1;
		ano=ano+1;
	}
}
//*********************SEMANA VISOR****************************
void mostraDiaSemana(){
	if(zeller==0){ //SABADO
		COD7=0x92;
		COD6=0x88;
		COD5=0x83;
		COD4=0xFF;
		COD3=0xFF;
		COD2=0xFF;
		COD1=0xFF;
		COD0=0xFF;
	} else if(zeller==1){ //DOMINGO
		COD7=0xA1;
		COD6=0xC0;
		COD5=0xC8;
		COD4=0xFF;
		COD3=0xFF;
		COD2=0xFF;
		COD1=0xFF;
		COD0=0xFF;
	}else if(zeller==2){ //SEGUNDA
		COD7=0x92;
		COD6=0x86;
		COD5=0xC2;
		COD4=0xFF;
		COD3=0xFF;
		COD2=0xFF;
		COD1=0xFF;
		COD0=0xFF;
	}else if(zeller==3){ //TERCA
		COD7=0x87;
		COD6=0x86;
		COD5=0xCC;
		COD4=0xFF;
		COD3=0xFF;
		COD2=0xFF;
		COD1=0xFF;
		COD0=0xFF;
	}else if(zeller==4){ //QUARTA
		COD7=0x98;
		COD6=0xC1;
		COD5=0x88;
		COD4=0xFF;
		COD3=0xFF;
		COD2=0xFF;
		COD1=0xFF;
		COD0=0xFF;
	}else if(zeller==5){ //QUINTA
		COD7=0x98;
		COD6=0xC1;
		COD5=0xCF;
		COD4=0xFF;
		COD3=0xFF;
		COD2=0xFF;
		COD1=0xFF;
		COD0=0xFF;
	}else if(zeller==6){ //SEXTA
		COD7=0x92;
		COD6=0x86;
		COD5=0x89;
		COD4=0xFF;
		COD3=0xFF;
		COD2=0xFF;
		COD1=0xFF;
		COD0=0xFF;
	}
}
//*********************AJUSTES RELOGIO****************************
void ajustes(){
	if(chaveSeg==0){  //zera segundos
		seg=0;
	}	else if(chaveMin==0){ //incrementa minutos
		min=min+1;
		if(min==60){ //conta ate 59
			min=1;
		}
	} else if(chaveHora==0){  //incrementa hora
		hora++;
		if(hora==24){
		hora=0;
		}
	} else if(chaveDia==0){   //incrementa dia
		dia++;
		if(dia==32){
			dia=1;
			conversao();
		}
	} else if(chaveMes==0){   //incrementa mes
		mes=mes+1;
		if(mes==13){
			mes=1;
		}
	} else if(chaveAno==0){  //incrementa ano
		ano++;
		if(ano==50){
			ano=0;
		}
	}
}
//*********************PRINCIPAL****************************
void main(void){
	dsp0=0;
	while(1){
		display();
		conversao();
		delay();
		contador++;
		if(chaveWeek==0){
			mostraDiaSemana();
		}
		if(contador>=480){
			ajustes();
			contaHora();			
			contaData();
			algoritimoSemana();
			contador=0;
		}
	}
}