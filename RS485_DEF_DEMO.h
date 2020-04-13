/* Définition des ID du RS485 de sonia
   adapté pour la démonstration par port série.

   Production: Détruire ce fichier et enlever le calcul de
   offset dans le main
 */
#ifndef __RS485_DEF_H__
#define __RS485_DEF_H__

#define SLAVE_powersupply0	'q'
#define SLAVE_powersupply1 	'w'
#define SLAVE_powersupply2 	'e'
#define SLAVE_powersupply3 	'r'
#define PS_DATA_OFFSET      'a'

#define SLAVE_killMission  	'z'
#define KS_DATA_OFFSET      '0'

#define SLAVE_ESC_1 		'a'
#define SLAVE_ESC_2 	   	's'
#define SLAVE_ESC_3 	   	'd'
#define SLAVE_ESC_4 	   	'f'
#define SLAVE_ESC_5 	   	'g'
#define SLAVE_ESC_6 	   	'h'
#define SLAVE_ESC_7 	   	'j'
#define SLAVE_ESC_8 	   	'k'
#define MOTOR_DATA_OFFSET   '0'

#endif