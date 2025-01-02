#PASOS

1. Arrancar nats

2. Ejecutar mainChat
    ```node mainChat.js```

3. Ejecutar mainClient (el numero de veces que se crea necesario | minimo 2 veces)
    ```node mainClient.js tcp://${host-de-nats} ${nombre-de-usuario}```
    con el nats corriendo en local:
        ```node mainClient.js tcp://localhost usuario-1```
        
4. Escribir mensajes en los clientes
