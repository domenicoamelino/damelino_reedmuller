/*
 ============================================================================
 Name        : damelino_reedmuller.c
 Author      : damelino
 Version     :
 Copyright   : Your copyright notice
 Description : Reed Muller Encoder/Decoder
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include "utilities.h"
#include "reedmuller.h"
#include "Spongent.h"

//Questo valore di memory va sostituito con la PUF che andate ad estrarre voi via openocd.

uint8_t memory[352]={0x79,0x34,0x58,0x30,0xb9,0xdd,0x27,0x8d,0x0a,0x39,0xc3,0x26,0x73,0xf5,0x09,0x3c,0x54,0xb5,0x3e,0x22,0xbe,0x27,0x79,0xec,0x4d,0x41,0x2a,0x1b,0x23,0x32,0x68,0xe8,0x8f,0xe3,0x41,0xbf,0xc9,0x53,0x55,0xd7,0xe2,0xe9,0xa0,0xb1,0x96,0x54,0x90,0xfe,0x4a,0x2e,0xbe,0xef,0xe8,0x7d,0x38,0x0c,0xd1,0x3f,0x2a,0x50,0xb8,0x23,0x8a,0xa2,0x9a,0x01,0x3f,0xc8,0x16,0xdd,0xd9,0xd0,0x13,0xc9,0x93,0x8b,0x6d,0xda,0xb2,0x87,0x39,0xcf,0x20,0x72,0x6b,0xce,0x1d,0xe4,0x2d,0xf1,0x72,0x05,0x37,0x24,0x10,0x0b,0x05,0x68,0x31,0x63,0x64,0x73,0x51,0xf8,0x0c,0xa4,0x4c,0x51,0x8e,0x8e,0x76,0xad,0x72,0xbc,0x88,0xfe,0x7f,0x23,0xf6,0xae,0x38,0x9d,0xa2,0xf0,0x66,0x8e,0x42,0xb7,0xbc,0x32,0x12,0x4d,0x18,0x6d,0x50,0xa9,0x2e,0x4c,0x90,0x97,0xcf,0x6b,0xc6,0x12,0xa9,0xbc,0xf8,0x8b,0x65,0xd7,0xc2,0xea,0xf6,0x67,0xae,0x5b,0xb3,0xeb,0x11,0x1e,0x9f,0x43,0x6d,0xf1,0x3f,0xc7,0x23,0x3e,0x21,0xf1,0x00,0xc3,0x1f,0xfd,0xee,0xad,0x5c,0x30,0x4d,0x6b,0x7f,0x11,0x7f,0x0b,0x12,0x6c,0x0d,0x02,0x30,0xf3,0xe2,0x84,0xf6,0x14,0x22,0xd4,0xf7,0x57,0xda,0xc4,0x03,0xc4,0x0c,0x3f,0x5f,0x59,0x14,0x3f,0x40,0xbf,0x30,0xb8,0x56,0x19,0xc1,0x00,0x91,0xff,0x3b,0x86,0x96,0x56,0x3a,0xd6,0x1f,0x70,0x3b,0x52,0x75,0x57,0xc6,0x9c,0xb2,0x01,0xa2,0xa4,0x7f,0x7f,0x7e,0xf6,0x3f,0x20,0xf8,0x69,0xe6,0x59,0xf5,0x4a,0x33,0xb7,0x90,0xb8,0xf1,0x8f,0xd6,0x31,0xc0,0x92,0x83,0x9c,0xa5,0x1d,0x1b,0xf1,0x47,0xc1,0x5a,0x39,0xe5,0x1e,0x2f,0xf5,0x2a,0x44,0x05,0x50,0xc3,0xf4,0x71,0xcd,0x60,0x59,0x64,0x0c,0x96,0xb4,0x16,0xb0,0x5c,0x92,0x04,0x22,0x7d,0x4f,0xc7,0x84,0xc7,0x7b,0x6a,0xe2,0xea,0x9d,0xbd,0x51,0x27,0x76,0x70,0x5d,0x8e,0x28,0x2d,0xe1,0x4f,0x27,0x48,0x7a,0xdc,0x2b,0x85,0x33,0x55,0x92,0xc6,0xbf,0xf7,0x9f,0xce,0xfe,0x9c,0x36,0x1c,0x4a,0x23,0x25,0xc5,0xb7,0x81,0xfd,0x99,0x87,0xf8,0xf2,0x58,0xe4,0xe4,0x95,0x42,0x70,0x7b,0xc4,0xd4,0x6c};
//static uint8_t const helper_data [352] =  {0x45,0x08,0x9b,0xf3,0x7a,0x1e,0x1b,0xb1,0xc9,0xfa,0xff,0x1a,0x4f,0xc9,0xca,0xff,0x67,0x79,0x0d,0xee,0x8d,0xeb,0x4a,0x20,0x81,0x72,0xe6,0x28,0xef,0x01,0xa4,0xdb,0x4c,0xdf,0x7d,0x7c,0xf5,0x90,0x96,0xeb,0xde,0x2a,0x63,0x8d,0x55,0x68,0xac,0x3d,0xdc,0xb8,0x28,0x79,0x81,0x14,0x51,0x65,0x47,0xa9,0xbc,0xc6,0xd1,0x4a,0xe3,0xcb,0x59,0x3d,0xfc,0xf4,0x2a,0x1e,0xe5,0x13,0x2f,0x0a,0xaf,0x48,0xae,0xe6,0x71,0xbb,0x93,0x65,0x8a,0xd8,0x3e,0x9b,0x48,0xb1,0x87,0x5b,0xd8,0xaf,0x62,0x71,0x45,0x5e,0x63,0xf1,0x57,0xfa,0xfd,0x15,0xc8,0x9e,0x95,0xc2,0xd5,0x37,0xe8,0x17,0x10,0x34,0xd8,0x16,0xdd,0xab,0x2a,0x76,0x5c,0x04,0x6d,0xc8,0x08,0x5a,0xcc,0x24,0x17,0xe2,0x70,0x01,0xde,0x7e,0xd4,0x5e,0x9c,0x9a,0x1d,0x80,0xa3,0x5b,0xfc,0xa7,0xf5,0xde,0x56,0xbc,0xf8,0x74,0x65,0x28,0x3d,0xea,0xf6,0x98,0x51,0x5b,0x4c,0xeb,0x11,0xe1,0x90,0x4c,0x9d,0x01,0xcf,0x37,0x2c,0x31,0x2e,0xfe,0xf0,0x33,0xef,0x0d,0xe1,0xa2,0x06,0x6a,0x17,0x31,0xda,0xb4,0xda,0xae,0xb7,0xc9,0xa8,0xa7,0x6a,0xa9,0xb8,0xde,0xa3,0x41,0x88,0x7e,0xa2,0x02,0x70,0x6e,0x56,0x91,0xa6,0x95,0x0a,0x0c,0xbe,0x95,0x26,0x26,0x56,0x21,0xcf,0x7f,0x58,0x66,0x08,0x99,0xa2,0xe0,0xf0,0xcf,0x5c,0x4f,0xb5,0xda,0x91,0xf8,0x20,0x02,0x93,0xc9,0x18,0xab,0x08,0x0e,0x2a,0x2a,0x2b,0xa3,0xf3,0xec,0x34,0xa5,0x2a,0x95,0x39,0x86,0x00,0x84,0xa3,0x8b,0xc2,0xbc,0xe5,0x02,0x95,0xc7,0x29,0x36,0xf0,0x48,0xb1,0x5b,0x12,0x94,0xf0,0x93,0xb0,0x4b,0x85,0x5f,0x70,0xe1,0xa0,0x0a,0x66,0xae,0x2b,0x68,0x3a,0xfc,0xc1,0x56,0x33,0xee,0x4c,0x15,0x90,0xa1,0x37,0xee,0xb1,0x7c,0xf4,0x48,0x0b,0x48,0x59,0x2e,0x26,0xae,0x8e,0x9d,0x8d,0xdc,0x25,0x08,0xdb,0x7d,0x87,0x4b,0x1a,0x72,0xe2,0xd0,0x76,0x81,0xd0,0x66,0x00,0x38,0x6c,0xea,0x5d,0xca,0x9b,0x54,0x36,0x63,0x49,0xe0,0x76,0x8f,0x6f,0xe2,0x4d,0x31,0x55,0x4b,0xcb,0xc1,0x6b,0xd7,0xd7,0xa6,0x71,0x43,0xb7,0x08,0x18,0xa0};
//Potete modificarlo a piacere o lasciarlo così, è un valore randomico che può variare nel tempo o meno, per il vostro test potete tenerlo anche così.
static uint8_t const secret_code [22]= {0x76,0x4a,0xfe,0xa7,0xee,0xa1,0x6b,0xf1,0xca,0xf8,0x34,0x65,0x11,0x6b,0xa1,0xc2,0x11,0x3d,0x9a,0xf1,0x79,0xe2};
//uint8_t result [352];
int result[2816];
uint8_t result_bin[2816];
uint8_t result_hex[352];
uint8_t key[352];
uint8_t helper_data [352];
HashReturn res;

int main(void)
{

	// Generazione Helper Data -> Step 1 Codifica del Secret Code
	printf("------------GENERAZIONE HELPER DATA E KEY CON PUF E SECRET CODE IN INGRESSO------------ \n--- Domenico Amelino - Ph.D in Information Technology and Electronical Engineering ---- \n                      Versione con Reed Muller (1,7) e Spongent \n\n");
	encode(secret_code,result);

	//for(int i=0;i<2816;i++) printf("%d",result[i]);
	//printf("\n");
	int count = 0;
	for(int i=0;i<2816;i++) result_bin[i] = result[i];

	for(int i=0;i<2816;i+=8)
	{
		result_hex[count] = BinToHex(result_bin+i);
		count++;
	}

	//for(int i=0;i<352;i++) printf("%x ",result_hex[i]);
	//printf("\n");

	// Generazione Helper Data -> Step 2 Faccio la XOR tra la PUF ed il risultato dell'Encoding di Reed Muller
	for (int i = 0; i < 352; i++) {
		helper_data[i] = memory[i] ^ result_hex[i];
	}

	printf("Helper Data: (352 byte -- 2816 bit) \n");
	for(int i=0;i<352;i++) printf("%x ",helper_data[i]);
    printf("\n");

    //P
    res = SpongentHash(memory, 2816, key);

    printf("Chiave derivata dalla PUF (16 byte -- 128 bit) \n");
    for(int i=0;i<16;i++) printf("%x ",key[i]);
    printf("\n");



	// Inizializzazione FONDAMENTALE di KEY
	//int i=0;
	//  for(i=0;i<352;i++) key[i] =0;

	 //extractPUFfromMemory(memory, helper_data, 2816, key);

	// for(i=0;i<16;i++) printf("%x",key[i]);
	// printf("\n");

/*
	uint8_t msg[176];
	encode(input,result);
	printf("Risultato dell'encode \n");
	for(int i=0;i<RESULT_LENGTH;i++) printf("%d",result[i]);
	//led_on(LED_ORANGE);

	decode(result,msg);

	printf("\n");
	printf("Risultato finale in uscita dalla decode: \n");
	for(int i=0;i<176;i++) printf("%d",msg[i]);
	printf("\n");
	//led_on(LED_GREEN);

*/



	return EXIT_SUCCESS;
}
