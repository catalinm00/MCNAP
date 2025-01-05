import { Subscriber, Push } from "zeromq";

const i = process.argv[2] || 0;
let hora = Date.now();
const subSocket = new Subscriber();
const pushSocket = new Push();

let estado;

async function run() {
    pushSocket.connect('tcp://localhost:3001');
    subSocket.connect('tcp://localhost:3000');
    // para la implementacion por defecto que hay en el disenyo
    //subSocket.subscribe(i.toString());
    
    subSocket.subscribe();

    console.log("Nodo " + i + " levantado");

    setInterval(() => {
        if(estado != "ACTUALIZANDO") hora = ++hora;
    }, 1);

    //for await (const [topic, msg] of subSocket) {
    for await (const [msg] of subSocket) {
        if (msg.toString() == "dimeHora") dimeHora();
        else {
            let hora = JSON.parse(msg.toString())["hora"];
            nuevaHora(Number.parseInt(hora));
        }
    }
}

await run();

async function dimeHora() {
    console.log("Nodo: " + i + " - Mandando hora al coordinador")
    let msg = { "hora": hora, "de": i }
    pushSocket.send(JSON.stringify(msg));
}

function nuevaHora(h) {
    console.log("Nodo: " + i + " - Actualizando hora a " + h.toString());
    estado = "ACTUALIZANDO"
    hora = h;
    estado = "CALCULADO"
}