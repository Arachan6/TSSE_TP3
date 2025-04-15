# TSSE_TP3

Este repositorio contiene la implementación de una máquina de estados finitos (FSM) para el control de un sistema de llenado de tanques de agua, junto con un conjunto de pruebas unitarias para validar su funcionamiento.

## Descripción del sistema

El sistema gestiona dos tanques de agua:
- **RDWC (Recirculating Deep Water Culture)**
- **TD (Tanque de Dosificación)**

Cada tanque cuenta con:
- **Sensor de nivel bajo**: Detecta cuando el nivel de agua es mínimo.
- **Sensor de nivel alto**: Detecta cuando el nivel de agua es máximo.
- **Electroválvula de llenado**: Controla el flujo de agua hacia el tanque.
- **Medidor de flujo**: Detecta si hay circulación de agua cuando la válvula está abierta.

La FSM se encarga de:
1. Iniciar en estado **IDLE**, esperando cambios en los sensores.
2. Activar la **electroválvula de llenado** correspondiente cuando el nivel es bajo en alguno de los tanques.
3. Cerrar la válvula una vez alcanzado el nivel alto.
4. Detectar posibles fallos, como tiempos de llenado excesivos sin flujo de agua, y entrar en **estado de alarma**.
5. Esperar un **reset manual** en caso de alarma.

## Contenido del repositorio

El repositorio contiene los siguientes archivos clave:

- `fsm_water_tanks.c`: Implementación de la FSM.
- `fsm_water_tanks.h`: Definiciones y estructuras de la FSM.
- `test_fsm.c`: Archivo de prueba que valida el correcto funcionamiento de la FSM utilizando la librería Unity.

## Funcionamiento de la FSM

### Estados principales:
- **STATE_IDLE**: Espera eventos de sensores para activar las válvulas.
- **STATE_FILLING_RDWC**: Llena el tanque RDWC hasta que el nivel alto sea detectado.
- **STATE_FILLING_TD**: Llena el tanque TD si es necesario.
- **STATE_ALARM**: Se activa cuando un llenado excede el tiempo límite sin detectar flujo de agua.

### Reglas de transición:
- Si `sensor_rdwc_low` es activado → **STATE_FILLING_RDWC**.
- Si `sensor_td_low` es activado y `sensor_rdwc_high` está en alto → **STATE_FILLING_TD**.
- Si el tiempo de llenado supera 10,000 ciclos sin flujo → **STATE_ALARM**.
- Si se detecta `sensor_rdwc_high` o `sensor_td_high`, se retorna a **STATE_IDLE**.
- En **STATE_ALARM**, el sistema permanece en ese estado hasta un **reset manual**.
