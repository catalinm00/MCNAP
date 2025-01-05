import { Publisher, Pull } from "zeromq";

let hora;
let N = 0;
const ESTABLECIDA = 'ESTABLECIDA';
const CALCULANDO = 'CALCULANDO';
const DESCONOCIDA = 'DESCONOCIDA';
let estado = ESTABLECIDA;
let horas = [];
let nodos = [];

// socket para pedir hora a los nodos y mandar la hora actualizada
const pubSocket = new Publisher();
// socket para recibir la hora de los nodos
const pullSocket = new Pull();

let conexionesPendientes = [];

function procesarConexionesPendientes() {
    while (conexionesPendientes.shift() != undefined) agregarNodo();
}

function agregarNodo() {
    nodos.push(N);
    horas.push(DESCONOCIDA);
    ++N;
    console.log("New node connected, total: " + N);
}

async function run() {
    await pubSocket.bind('tcp://localhost:3000');
    await pullSocket.bind('tcp://localhost:3001');

    pubSocket.events.on("accept", async () => {
        // Hacemos esto para proteger las variables globales y evitar posibles condiciones de carrera con la funcion que realiza el calculo.
        if (estado == CALCULANDO) conexionesPendientes.push(conexionesPendientes.length)
        else agregarNodo();
    });
    console.log("Coordinador preparado");

    setInterval(() => {
        if (N > 0 && estado == ESTABLECIDA) actualizarHora();
    }, 3000);

    for await (const [msg] of pullSocket) {
        let obj = JSON.parse(msg.toString());
        let de = Number.parseInt(obj.de);
        let horaRecibida = Number.parseInt(obj.hora);
        await laHoraEs(de, horaRecibida);
    }
}

run();

async function actualizarHora() {
    if (estado == CALCULANDO) return;
    console.log("Iniciando actualizacion de hora...");
    estado = CALCULANDO;
    for (let i = 0; i < N; i++) {
        horas[i] = DESCONOCIDA;
    }
    // diferencia entre diseño y realidad, una comunicación de tipo fan-out cumple el mismo proposito
    // que un bucle que le pide la hora a cada nodo de manera individual  
    // for(let i=0; i < nodos.length; i++) {
    //     dimeHora(i);
    // }
    dimeHora();
}

// async function dimeHora(i) {
//     let id = (i).toString()
//     await pubSocket.send([id, "dimeHora"])
// }

async function dimeHora() {
    await pubSocket.send("dimeHora")
}

function decidirHora() {
    for (let i = 0; i < N; i++) {
        if (horas[i] == DESCONOCIDA) {
            return;
        }
    }
    // muestra las horas recibidas, es muy posible que haya una pequeña variacion entre ellas
    // porque el diseño del algoritmo es un caso sencillo que no tiene en cuenta las latencias de la red
    console.log(horas)
    hora = promedio(horas);
    // for (const nodo of nodos) {
    //     nuevaHora(nodo, hora)
    // }
    nuevaHora(hora)
    estado = ESTABLECIDA;
    console.log("Actualizacion terminada");
    procesarConexionesPendientes();
}

function promedio(horas) {
    let promedio = 0;
    for (let i = 0; i < N; i++) {
        promedio += horas[i];
    }
    promedio = promedio / N;
    return promedio;
}

// para la implementacion por defecto que hay en el disenyo
// function nuevaHora(i, hora) {
//     let msg = {"hora":hora};
//     pubSocket.send([i, JSON.stringify(msg)]);
// }

// Lo mismo que en el caso anterior, una comunicacion de tipo fan-out 
// es más eficiente que un bucle que envia una peticion a cada nodo
// esto lo podemos hacer asi porque en el disenyo se envía el mismo mensaje a todos
// los nodos. En caso de seguir el algoritmo original donde el mensaje enviado es la diferencia 
// del tiempo de cada nodo con el promedio, habría que usar comunicación punto a punto obligatoriamente.
// La ventaja del socket tipo Publisher, es que se puede hacer eso mandando a el mensaje a cada nodo
// usando su id como topico, tal y como se aprecia en la funcion comentada anteriormente
function nuevaHora(hora) {
    let msg = { "hora": hora };
    pubSocket.send(JSON.stringify(msg));
}

async function laHoraEs(de, hora) {
    horas[de] = hora;
    decidirHora();
}