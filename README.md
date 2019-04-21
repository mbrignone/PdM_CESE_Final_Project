# PdM_CESE_Final_Project
Repository for the final project of the subject "Microcontroller Programming", a course part of the Specialization Career in Embedded Systems (CESE), offered by the University of Buenos Aires (UBA). 

Repositorio para el proyecto final de la materia "Programación de Microcontroladores", un curso parte de la Carrera de Especialización en Sistemas Embebidos (CESE), de la Universidad de Buenos Aires (UBA).

## Descripción
En el trabajo final de la CESE se va a comunicar el microcontrolador utilizado (ESP32) con la placa de control de un electrodoméstico mediante comunicación serie (I2C o SPI, a determinar). A su vez el microcontrolador recibiría comandos por WiFi o Bluetooth y en base a eso ejecutaría acciones y enviaría comandos a la placa de control del electrodoméstico.

Para emular esto usando el hardware que se tiene ahora (no se cuenta ni con el microcontrolador que se va a utilizar, que incluye la comunicación WiFi/Bluetooth, ni con la placa del electrodoméstico), la EDU-CIAA recibiría comandos por UART (en vez de WiFi/Bluetooth), ejecutaría acciones básicas a modo de ejemplo (prender LEDs o usar el ADC de forma simple) y enviaría comandos por SPI, I2C o UART (sólo uno de estos protocolos) a un Arduino (en vez de a la placa del electrodoméstico, se usa un Arduino ya que es el único otro microcontrolador con el que se cuenta en este momento). En el Arduino habría un programa simple que recibiría los comandos y devolvería una respuesta específica de acuerdo al comando recibido. En la EDU-CIAA nuevamente se tomarían medidas de acuerdo a la respuesta recibida por SPI, I2C o UART.

Debido a que las interafaces SPI e I2C de Arduino funcionan a 5V, y las de la EDU-CIAA a 3.3V, se decide utilizar solamente comunicación UART, ya que no se cuentan con los componentes necesarios para hacer la conversión de niveles. Para que ambas placas puedan comunicarse por UART, se desarrolla un programa en Python que se encarga de redirigir adecuadamente los mensajes que la EDU-CIAA envía a Arduino, y viceversa, pasando siempre a través de la PC, además de permitir que el usuario envíe sus propios comandos.

### Funcionalidades 
A continuación se enumeran a grandes rasgos, las funcionalidades más importantes implementadas en la EDU-CIAA:
* Recepción de comandos por UART, comprobando que tengan el formato correcto y analizando si provienen del usuario o de Arduino. 
* Procesamiento de comandos, verificando que el comando recibido sea válido y ejecutando diferentes acciones (manejo de LEDs, lectura de ADC, envío de comandos a Arduino, envío al usuario de la información solicitada), informando además al usuario el comando que se recibió y la acción que se ejecuturá.
* En caso de enviar un comando a Arduino, el programa espera una respuesta determinada por parte de Arduino indicando que recibió el comando satisfactoriamente. Si transcurren 2000 milisegundos desde el envío del comando y no se recibe una respuesta por parte de Arduino, se produce un timeout que indica que hubo una falla en el envío del comando. 
* Actualización de la Máquina de Estados del *electrodoméstico* (Arduino), de acuerdo a los comandos que envía el usuario y a las respuestas y comandos enviados por Arduino. En todo momento el usuario puede conocer este estado mediante el envío del comando correspondiente.
* Se contempla también que Arduino envíe comandos "en cualquier momento" para indicar que terminó un determinado proceso (es decir, no lo envía como respuesta inmediata a un comando enviado por la EDU-CIAA), en cuyo caso se lo recibe, se analiza que efectivamente haya habido un proceso ejecutándose en Arduino, se actualiza la máquina de estados de Arduino y se informa al usuario de lo ocurrido.
* Almacenamiento de estadísticas, llevando un conteo de cuántas veces se reciben los diferentes comandos que puede enviar el usuario. Mediante el comando correspondiente, esta información puede ser enviada al usuario.
