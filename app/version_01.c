//Version_01
//Data: 09/06/2018
//Horario de inicio: 11:41am

/*
Membros: 	Lucas Marques Ribeiro;
			André Pereira
			Jhunu Fernandes
			Pedro Inácio
			Douglas Shuji
*/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>

/************************************************************/
/**************DECLARAÇÃO DE VARIÁVEIS***********************/
/************************************************************/
	unsigned char out=0;
	unsigned char state;
	unsigned char id[11], *id_p, n_paciente[4], *n_paciente_p;
	unsigned char buffer_c[1], buffer[200], *buffer_p;

	unsigned int n_paciente_int;
	unsigned int var_01;

	char str_date[100];

	fpos_t position, position_02;	

/************************************************************/
/**************MANUSEIO DE ARQUIVOS**************************/
/************************************************************/

	FILE *fp, *fp_2;

/************************************************************/
/**************DECLARAÇÃO DO STRUCT**************************/
/************************************************************/

typedef struct{
	unsigned char id_s[11];
	unsigned char prioridade[2];
	unsigned char nome[50];
	unsigned char rg[15];
	unsigned char cpf[12];
	unsigned char alergia[50];
	unsigned char doenca[50];
	unsigned char medicamento[50];
	unsigned char sangue[5];
	unsigned char historico[50];
	unsigned char convenio[30];
	unsigned char contato[15];
} Dados;
Dados paciente;

/************************************************************/
/*********OBTENÇÃO DO VALOR INT DE NUMERO DE CADASTRO********/
/************************************************************/

int char_int(unsigned char *n_paciente_p){
	int n_paciente_int;

	n_paciente_int = (*(n_paciente_p)-0x30)*100+(*(n_paciente_p+1)-0x30)*10+(*(n_paciente_p+2)-0x30);
	//printf("%d\n", n_paciente_int);
	return(n_paciente_int);
}

/*void int_char(int n_paciente_in){
	unsigned char n_paciente_c[4];

	n_paciente_in++;

	printf("%d\n", n_paciente_in);

	fp_2 = fopen("database.ods", "a+");
	fsetpos(fp_2, &position_02);
	fseek( fp, 0, SEEK_END );
	rewind(fp_2);
	fputc((n_paciente_in/100)+0x30,fp_2);
	fputc(((n_paciente_in%100)/10)+0x30,fp_2);
	fputc((n_paciente_in%10)+0x30,fp_2);
	fclose(fp_2);
}*/

/************************************************************/
/**************MONTAGEM DOS STRUCTS DO PACIENTE**************/
/************************************************************/

void mont_struct(unsigned char *buffer_p){
	unsigned int var_01 = 0, var_02 = 0;
	unsigned char buffer[50];

	Dados *paciente_p;
	paciente_p = &paciente;

	//ID
	var_01 = 0;
	while(*(buffer_p+var_01) != ','){
		buffer[var_02] = *(buffer_p+var_01);
		var_01++;
		var_02++;	
	}
	buffer[var_02] = '\0';
	strcpy(paciente_p->id_s, buffer);
	//printf("%s\n", paciente.id_s);
	var_01++;

	//PRIORIDADE
	var_02 = 0;
	while(*(buffer_p+var_01) != ','){
		buffer[var_02] = *(buffer_p+var_01);
		var_01++;
		var_02++;	
	}
	buffer[var_02] = '\0';
	strcpy(paciente_p->prioridade, buffer);
	//printf("%s\n", paciente.prioridade);
	var_01++;

	//NOME
	var_02 = 0;
	while(*(buffer_p+var_01) != ','){
		buffer[var_02] = *(buffer_p+var_01);
		var_01++;
		var_02++;	
	}
	buffer[var_02] = '\0';
	strcpy(paciente_p->nome, buffer);
	//printf("%s\n", paciente.nome);
	var_01++;

	
	//RG
	var_02 = 0;
	while(*(buffer_p+var_01) != ','){
		buffer[var_02] = *(buffer_p+var_01);
		var_01++;
		var_02++;	
	}
	buffer[var_02] = '\0';
	strcpy(paciente_p->rg, buffer);
	//printf("%s\n", paciente.rg);
	var_01++;

	//CPF
	var_02 = 0;
	while(*(buffer_p+var_01) != ','){
		buffer[var_02] = *(buffer_p+var_01);
		var_01++;
		var_02++;	
	}
	buffer[var_02] = '\0';
	strcpy(paciente_p->cpf, buffer);
	//printf("%s\n", paciente.cpf);
	var_01++;

	//ALERGIA
	var_02 = 0;
	while(*(buffer_p+var_01) != ','){
		buffer[var_02] = *(buffer_p+var_01);
		var_01++;
		var_02++;	
	}
	buffer[var_02] = '\0';
	strcpy(paciente_p->alergia, buffer);
	//printf("%s\n", paciente.alergia);
	var_01++;

	//DOENÇA CRONICA
	var_02 = 0;
	while(*(buffer_p+var_01) != ','){
		buffer[var_02] = *(buffer_p+var_01);
		var_01++;
		var_02++;	
	}
	buffer[var_02] = '\0';
	strcpy(paciente_p->doenca, buffer);
	//printf("%s\n", paciente.doenca);
	var_01++;

	//MEDICAMENTO
	var_02 = 0;
	while(*(buffer_p+var_01) != ','){
		buffer[var_02] = *(buffer_p+var_01);
		var_01++;
		var_02++;	
	}
	buffer[var_02] = '\0';
	strcpy(paciente_p->medicamento, buffer);
	//printf("%s\n", paciente.medicamento);
	var_01++;

	//TIPO SANGUINEO
	var_02 = 0;
	while(*(buffer_p+var_01) != ','){
		buffer[var_02] = *(buffer_p+var_01);
		var_01++;
		var_02++;	
	}
	buffer[var_02] = '\0';
	strcpy(paciente_p->sangue, buffer);
	//printf("%s\n", paciente.sangue);
	var_01++;

	//HISTORICO MÉDICO
	var_02 = 0;
	while(*(buffer_p+var_01) != ','){
		buffer[var_02] = *(buffer_p+var_01);
		var_01++;
		var_02++;	
	}
	buffer[var_02] = '\0';
	strcpy(paciente_p->historico, buffer);
	//printf("%s\n", paciente.historico);
	var_01++;

	//CONVENIO
	var_02 = 0;
	while(*(buffer_p+var_01) != ','){
		buffer[var_02] = *(buffer_p+var_01);
		var_01++;
		var_02++;	
	}
	buffer[var_02] = '\0';
	strcpy(paciente_p->convenio, buffer);
	//printf("%s\n", paciente.convenio);
	var_01++;

	//CONTATO
	var_02 = 0;
	while(*(buffer_p+var_01) != ','){
		buffer[var_02] = *(buffer_p+var_01);
		var_01++;
		var_02++;	
	}
	buffer[var_02] = '\0';
	strcpy(paciente_p->contato, buffer);
	//printf("%s\n", paciente.contato);
	var_01++;

}

void ad_usuario(char **input){
	unsigned int var_01 = 0;


	fp = fopen("database.ods","a+");
	
	fgetpos(fp, &position_02);
	n_paciente_p = n_paciente;
	var_01 = 0;
	while(buffer_c[0] != ','){
		fread(buffer_c, 1, 1, fp);
		buffer[var_01] = buffer_c[0];
		var_01++;
	}
	buffer[var_01-1] = '\0';
	strcpy(n_paciente, buffer);
	n_paciente_int = char_int(n_paciente_p);
	//int_char(n_paciente_int);
	fclose(fp);


	fp = fopen(input[2], "a+");
	var_01 = 0;
	while(buffer_c[0] != '$'){
		fread(buffer_c, 1, 1, fp);
		buffer[var_01] = buffer_c[0];
		var_01++;
	}
	buffer[var_01-1] = ',';
	buffer[var_01] = '$';
	buffer[var_01+1] = '\n';
	buffer[var_01+2] = '\0';

	fclose(fp);

	fp = fopen("database.ods", "a+");
	fputs(buffer,fp);
	n_paciente_int++;
	fclose(fp);
}

unsigned char aq_usuario(char **input){
	time_t rawtime = time(NULL);
	struct tm *ptm = localtime(&rawtime);

/************************************************************/
/******************MAQUINA DE ESTADOS************************/
/************************************************************/
	
		
				//gets(id);
				strcpy(id,input[2]);
				//scanf("%s", id);
				fflush(stdin);

				fp = fopen("database.ods", "a+");
				
				//AQUISIÇÃO DO NUMEROD E PACIENTES NO DATABASE
				n_paciente_p = n_paciente;
				var_01 = 0;
				while(buffer_c[0] != ','){
					fread(buffer_c, 1, 1, fp);
					buffer[var_01] = buffer_c[0];
					var_01++;
				}
				buffer[var_01-1] = '\0';
				strcpy(n_paciente, buffer);
				n_paciente_int = char_int(n_paciente_p);

				//DESCARTE DA PRIMEIRA LINHA
				var_01 = 0;
				while(buffer_c[0] != '$'){
					fread(buffer_c, 1, 1, fp);
					buffer[var_01] = buffer_c[0];
					var_01++;
				}
				buffer[var_01-1] = '\0';
				fgetpos(fp, &position);

				//LEITURA DA SEGUNDA LINHA
				while(!feof(fp)/*n_paciente_int != 0*/){	
					fsetpos(fp, &position);
					buffer_c[0] = '0';
					var_01 = 0;
					fread(buffer_c, 1, 1, fp);
					while(buffer_c[0] != '$'){
						fread(buffer_c, 1, 1, fp);
						buffer[var_01] = buffer_c[0];
						var_01++;
					}
					buffer[var_01] = '\0';
					fgetpos(fp, &position);

					//TRUNCAMENTO NO VALOR DE ID
					var_01 = 0;
					while(buffer[var_01] != ','){
						var_01++;	
					}
					buffer[var_01] = '\0';

					id_p = id;
					buffer_p = buffer;
					if(strcmp(buffer_p, id_p) == 0){
						buffer[var_01] = ',';
						mont_struct(buffer_p);
						printf("ID: %s\nClasse: %s\nNome: %s\nRG: %s\nCPF: %s\nAlergia: %s\nDoenças Crônicas: %s\nMedicamentos: %s\nTipo Sanguíneo: %s\nHistórico Médico: %s\nConvênios: %s\nContato de Emergência: %s\n\n******************************************\n\n", paciente.id_s, paciente.prioridade, paciente.nome, paciente.rg, paciente.cpf, paciente.alergia, paciente.doenca, paciente.medicamento, paciente.sangue, paciente.historico, paciente.convenio, paciente.contato);
						break;
					} 
					n_paciente_int--;
					
				}
				fclose(fp);


				//REALIZAÇÃO DO LOG DE CADASTRO
				fp = fopen(str_date, "a+");
				var_01 = 0;
				while(*(buffer_p+var_01) != '$'){
					var_01++;
				}
				*(buffer_p+var_01) = ',';
				*(buffer_p+var_01+1) = '\0';
				sprintf(buffer_p, "%s%d:%d:%d", buffer_p, ptm->tm_hour, ptm->tm_min, ptm->tm_sec);
				//sprintf(str_date, "%d_%d_%d", ptm->tm_hour, ptm->tm_min, ptm->tm_sec);				
				//*(buffer_p+strlen(str_date)) = '\0';
				fputs(buffer_p,fp);
				fputc(0x0D,fp);

				fclose(fp);

	out = *(paciente.prioridade)-0x30;
	return(out);
}

int main(int argc, char **argv){

	unsigned char state_main = 0, output;

	time_t rawtime = time(NULL);
	struct tm *ptm = localtime(&rawtime);

	sprintf(str_date, "%d_%d_%d.ods", ptm->tm_mday, ptm->tm_mon+1, ptm->tm_year+1900);

	if(strcmp(argv[1], "-r") == 0){			//READ
		aq_usuario(argv);
	}else if(strcmp(argv[1], "-u") == 0){	//UPDATE

	}else if(strcmp(argv[1],"-a") == 0){		//ADD
		ad_usuario(argv);
	}else if(strcmp(argv[1], "-h") == 0 || strcmp(argv[1], "--help") == 0){
		printf("step-health --help\n\n   -r 	Read an information\n   -u 	Update an information\n   -a 	Add an information\n\n");
	}

/************************************************************/
/******************MAQUINA DE ESTADOS************************/
/************************************************************/
	/*while(1){
		switch(state_main){
			case 0:
				printf("Insira o cartão o profissional responsável: ");
				state_main = 1;
			break;
			case 1:
				output = aq_usuario();
				if(output == 5){
					printf("Usuário incorreto.\n");
					state_main = 0;
				}else{
					state_main = 2;
				}
			break;
			case 2:
				printf("Insira o cartão do paciente: ");
				state_main = 3;
			break;
			case 3:
				output = aq_usuario();
				state_main = 4;
			break;
		}
	}*/
	fflush(stdin);
	fflush(stdout);
	return(0);
}