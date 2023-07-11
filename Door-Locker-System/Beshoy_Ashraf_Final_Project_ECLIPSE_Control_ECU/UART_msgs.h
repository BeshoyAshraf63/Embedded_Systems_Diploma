 /******************************************************************************
 *
 *
 * File Name: UART_msgs.h
 *
 * Description: Header file for the UART messages betwwen MC1 and MC2.
 *
 * Author: Beshoy Ashraf
 *
 *******************************************************************************/

#ifndef UART_MSGS_H_
#define UART_MSGS_H_

#define MC2_READY                    0x10

#define MC1_READY                    0x20

#define RequestedCorrectPassword     '<'

#define RequestedINCorrectPassword   '>'

#define getNewPassword               'N'

#define HMI_PasswordReady            'P'

#define PasswordSize                  5

#define RequestPassword              '!'

#define HMI_RequestedPasswordReady   ')'

#define openDoor                     '@'

#define passwordsUnmatched           'U'

#define wrogPassword                 'W'

#define errorScreen                  'E'

#define DoorOpening                  'O'

#define DoorClosing                  'C'

#define MainOptions                  'M'

#define PasswordMatch                'R'

#define DoorIsOpened                 '&'

#define DoorIsClosed                 '|'

#define EEPROM_Address               0x0311

#endif /* UART_MSGS_H_ */
